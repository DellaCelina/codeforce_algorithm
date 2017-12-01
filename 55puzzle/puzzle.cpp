#include "puzzle.h"

uint Node::GetH()
{
	uint result = 0;
	uint hidx = log(fillHorizen + 1)/log(2);
	uint vidx = log(fillVertical + 1)/log(2);

	//hidx's number H.
	for (uint i = 1; i <= n; i++) {
		uint num = hidx * n + i;
		uint loc = locPuzzle(num);
		result += differOfLoc(num - 1, loc);
	}

	//vidx's number H.
	for (uint i = 0; i < n; i++) {
		uint num = vidx + 1 + (n*i);
		uint loc = locPuzzle(num);
		result += differOfLoc(num - 1, loc);
	}
	return result;
}

uint Node::GetFilled()
{
	return uint(filled);
}

int Node::differOfLoc(uint x, uint y)
{
	return WEIGHT_OF_H*(abs(getXofLoc(x) - getXofLoc(y)) + abs(getYofLoc(x) - getYofLoc(y)));
}

uint Node::locPuzzle(int x)
{
	for (uint i = 0; i < n*n; i++) {
		if (puzzle[i] == x) return i;
	}
	return 0;
}

bool Node::isLeftEnd()
{
	if (blank % n == 0) return true;
	else return false;
}

bool Node::isRightEnd()
{
	if (blank%n == n - 1) return true;
	else return false;
}

bool Node::isLowEnd()
{
	if (blank / n == n - 1) return true;
	else return false;
}

bool Node::isHighEnd()
{
	if (blank / n == 0) return true;
	else return false;
}

bool Node::setHorizen(uint x)
{
	int num = x * n + 1;
	for (int i = x * n; i < (x + 1) * n; i++) {
		if (puzzle[i] != num++) return false;
		if (num == n*n) num = 0;
	}
	if (!(fillHorizen & (1 << x))) filled--;
	fillHorizen |= (1 << x);
	return true;
}

bool Node::getHorizen(uint x)
{
	return (fillHorizen & (1 << x)) ? true : false;
}

bool Node::setVertical(uint x)
{
	int num = x + 1;
	for (int i = x; i < x + n * n; i += n) {
		if (puzzle[i] != num) return false;
		num += n;
		if (num == n*n) num = 0;
	}
	if (!(fillVertical & (1 << x))) filled--;
	fillVertical |= (1 << x);
	return true;
}

bool Node::getVertical(uint x)
{
	return (fillVertical & (1 << x)) ? true : false;
}

void Node::setFill()
{
	//Set Horizen line from side.
	for (uint i = 0; i < n; i++) {
		if (getHorizen(i)) continue;
		if (i != 0 && getHorizen(i - 1)) {
			if (!setHorizen(i - 1)) break;
		}
		if (!setHorizen(i)) break;
	}

	//Set Vertical line from side.
	for (uint i = 0; i < n; i++) {
		if (getVertical(i)) continue;
		if (i != 0 && getVertical(i - 1)) {
			if (!setVertical(i - 1)) break;
		}
		if (!setVertical(i)) break;
	}
}

void Node::puzzleUp(){
		puzzle[blank] = puzzle[blank - n];
		blank = blank - n;
		puzzle[blank] = 0;
}

void Node::puzzleDown(){
	puzzle[blank] = puzzle[blank + n];
	blank = blank + n;
	puzzle[blank] = 0;
}

void Node::puzzleRight(){
	puzzle[blank] = puzzle[blank + 1];
	blank = blank + 1;
	puzzle[blank] = 0;
}

void Node::puzzleLeft(){
	puzzle[blank] = puzzle[blank - 1];
	blank = blank - 1;
	puzzle[blank] = 0;
}

Node::Node(Puzzle &pz)
{
	parent = NULL;
	n = pz.GetN();
	this->puzzle = (puzzle_t)calloc(n*n, sizeof(int));
	for (uint i = 0; i < n*n; i++) {
		this->puzzle[i] = pz.GetPuzzle()[i];
	}
	blank = pz.GetBlank();
	g = 0;
	h = GetH();
	dir = NONE;
	fillHorizen = 0;
	fillVertical = 0;

	//Set bit of filled line.
	setFill();
	filled = n + n + FILL_CONST;
}

Node::Node(NodePtr parent, dir_t dir)
	: parent(parent), dir(dir), n(parent->n), blank(parent->blank), h(0),
	fillHorizen(parent->fillHorizen), fillVertical(parent->fillVertical), filled(parent->filled)
{
	puzzle = (puzzle_t)calloc(n * n, sizeof(int));
	for (uint i = 0; i < n*n; i++) {
		puzzle[i] = parent->puzzle[i];
	}

	switch (dir) {
	case UP:
		puzzleUp();
		break;
	case DOWN:
		puzzleDown();
		break;
	case LEFT:
		puzzleLeft();
		break;
	case RIGHT:
		puzzleRight();
		break;
	case NONE:
	default:
		break;
	}

	h = GetH();
	g = parent->g + 1;

	//Set bit of filled line.
	setFill();
}

void Node::SetG(uint g)
{
	this->g = g;
}

uint Node::GetF()
{
	return g + h;
}

NodePtr Node::GetParent()
{
	return parent;
}

bool Node::canLeft()
{
	return !isLeftEnd() && !(dir == RIGHT) && (!getVertical(getXofLoc(blank - 1)) || getXofLoc(blank - 1) == n - 2);
}

bool Node::canRight()
{
	return !isRightEnd() && !(dir == LEFT);// && !getVertical(getXofLoc(blank + 1));
}

bool Node::canDown()
{
	return !isLowEnd() && !(dir == UP);// && !getHorizen(getYofLoc(blank + n));
}

bool Node::canUp()
{
	return !isHighEnd() && !(dir == DOWN) && (!getHorizen(getYofLoc(blank - n)) || getYofLoc(blank - n) == n - 2);
}

void Node::PrintNode()
{
	for (uint i = 0; i < n; i++) {
		for (uint j = 0; j < n; j++)
			printf("%d ", puzzle[i * n + j]);
		printf("\n");
	}
	printf("\n");
}

void Node::PrintNodeToFile(ofstream & file)
{
	for (uint i = 0; i < n; i++) {
		for (uint j = 0; j < n; j++)
			file << puzzle[i * n + j] << ' ';
		file << endl;
	}
	file << endl;
}

void Puzzle::flushQueue()
{
	//flush priority queue.
#if POP_FLUSH == 1
	while (pqueue.size() != 0) {
		pqueue.pop();
	}
#else
	priority_queue<NodePtr, vector<NodePtr>, Node_Compare> pq;
	pqueue.swap(pq);
#endif
}

void Puzzle::Enqueue_this()
{
	pqueue.push(NodePtr(new Node(*this)));
}

Puzzle::Puzzle(uint n)
{
	srand(uint(time(NULL)));
	puzzle = (puzzle_t)calloc(n*n, sizeof(int));
	this->n = n;

	//Initialize puzzle.
	for (uint i = 1; i < n*n; i++) {
		uint x;
		while (puzzle[x = rand() % (n*n)]);
		puzzle[x] = i;
	}

	//Find blank.
	for (uint i = 0; i < n*n; i++) {
		if (!puzzle[i]) {
			blank = i;
			break;
		}
	}

	Enqueue_this();
}

void Puzzle::RegenPuzzle(){
	srand(uint(time(NULL)));
	free(puzzle);
	puzzle = (puzzle_t)calloc(n*n, sizeof(int));

	//Initialize puzzle.
	for (uint i = 1; i < n*n; i++) {
		uint x;
		while (puzzle[x = rand() % (n*n)]);
		puzzle[x] = i;
	}

	//Find blank.
	for (uint i = 0; i < n*n; i++) {
		if (!puzzle[i]) {
			blank = i;
			break;
		}
	}
	flushQueue();
	Enqueue_this();
}

puzzle_t Puzzle::GetPuzzle()
{
	return puzzle_t(puzzle);
}

uint Puzzle::GetBlank()
{
	return uint(blank);
}

uint Puzzle::GetN()
{
	return uint(n);
}

void Puzzle::Solve()
{
	uint bfFilled = n + n + FILL_CONST;
	bool cksolve;
	do{
		printf("current Node:\n");
		pqueue.top()->PrintNode();
		system("pause");
		if(!(cksolve = canSolve())) {
			printf("Can't Solve this puzzle.\n");
			system("pause");
			printf("Regenerate Puzzle");
			RegenPuzzle();
		}
	}while(!cksolve);
	while (1) {
		NodePtr current = pqueue.top();
		pqueue.pop();

#ifdef _DEBUG
		current->PrintNode();
		printf("\n");
#endif

		//Check this Node.
		if (current->fillHorizen == (1 << current->n) - 1) {
			Backtrace(current);
			break;
		}

		//If current have more filled line, flush queue.
		if (current->filled < bfFilled) 
			flushQueue();
		bfFilled = current->filled;

		//Push Next Nodes to priority queue.
		if (current->canLeft()) pqueue.push(NodePtr(new Node(current, LEFT)));
		if (current->canRight()) pqueue.push(NodePtr(new Node(current, RIGHT)));
		if (current->canUp()) pqueue.push(NodePtr(new Node(current, UP)));
		if (current->canDown()) pqueue.push(NodePtr(new Node(current, DOWN)));
	}
}

void Puzzle::Backtrace(NodePtr rslt)
{
	NodePtr current = rslt;
	while (current != NULL) {
		bstack.push(current);
		current = current->GetParent();
	}
}

void Puzzle::PrintStack(ofstream & file)
{
	file.open("Solution.txt");
	while (bstack.size() != 0) {
		NodePtr current = bstack.top();
		current->PrintNode();
		current->PrintNodeToFile(file);
		bstack.pop();
	}
}

bool Puzzle::canSolve()
{
	CheckNode ck(*this);
	printf("Check Node:\n");
	ck.PrintNode();
	uint result = ck.SumInversion();
	printf("inversions : %u\n", result);
	if (result & 1) return false;
	else return true;
}

CheckNode::CheckNode(Puzzle &pz) : Node(pz){
	for(int i = getXofLoc(blank); i < n - 1; i++){
		puzzleRight();
	}
	for(int i = getYofLoc(blank); i < n - 1; i++){
		puzzleDown();
	}
}

uint CheckNode::inversion(uint x){
	int result = 0;
	int value = puzzle[x];
	if (value == 0) return 0;
	for (uint i = 0; i < x; i++) {
		if (puzzle[i] > value) result++;
	}
	return result;
}

uint CheckNode::SumInversion(){
	uint result = 0;
	for (uint i = 1; i < n*n; i++) {
		result += inversion(i);
	}
	return result;
}