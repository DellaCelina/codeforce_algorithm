#pragma once
#include <math.h>
#include <stdlib.h>
#include <stack>
#include <queue>
#include <time.h>
#include <functional>
#include <vector>
#include <memory>
#include <fstream>

#define WEIGHT_OF_H 3
#define FILL_CONST 10
#define MEMORY_OP 1
#define POP_FLUSH 1

using namespace std;

typedef int* puzzle_t;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef enum { UP, DOWN, RIGHT, LEFT, NONE } dir_t;

class Node_Compare;
class Puzzle;
class Node;
typedef shared_ptr<Node> NodePtr;

class Node {
	friend Puzzle;
protected:
	NodePtr parent;
	puzzle_t puzzle;
	uint blank;
	uint n;
	uint g, h;	//'A' star; f(x) = g(x) + h(x).
	dir_t dir;	//Direction from parent.

				//Array for check seted line, using bit.
	uint fillHorizen;
	uint fillVertical;

	//Compare before check F.
	uint filled;

	int getXofLoc(uint loc) { return loc % n; }
	int getYofLoc(uint loc) { return loc / n; }
	int differOfLoc(uint x, uint y);
	uint locPuzzle(int x);

	//Check location of blank.
	bool isLeftEnd();
	bool isRightEnd();
	bool isLowEnd();
	bool isHighEnd();

	//Bit functions for fill variables.
	bool setHorizen(uint x);
	bool getHorizen(uint x);
	bool setVertical(uint x);
	bool getVertical(uint x);
	void setFill();

	//Move Puzzle.
	void puzzleUp();
	void puzzleDown();
	void puzzleRight();
	void puzzleLeft();

public:
	Node(Puzzle &pz);	//Make First Node from Puzzle.
	Node(NodePtr parent, dir_t dir);	//Make Next Node from parent with direction.
	~Node() { if (puzzle != NULL) free(puzzle); }
	void SetG(uint g);
	uint GetF();
	uint GetH();
	uint GetFilled();
	NodePtr GetParent();

	//Check can push direction
	bool canLeft();
	bool canRight();
	bool canDown();
	bool canUp();

	void PrintNode();
	void PrintNodeToFile(ofstream &file);
};

class CheckNode : public Node{
private:
	uint inversion(uint x);
public:
	CheckNode(Puzzle &pz);
	uint SumInversion();
};

class Node_Compare {
public:
	bool operator()(NodePtr a, NodePtr b) {
		if (a->GetFilled() == b->GetFilled()) {
			if (a->GetF() == b->GetF()) return a->GetH() > b->GetH();
			return a->GetF() > b->GetF();
		}
		else return a->GetFilled() > b->GetFilled();
	}
};

class Puzzle {
protected:
	puzzle_t puzzle;
	uint blank;
	uint n;
	stack< NodePtr > bstack;
	priority_queue <  NodePtr, vector< NodePtr>, Node_Compare > pqueue;

	void flushQueue();
	void Enqueue_this();

public:
	Puzzle(uint n);
	puzzle_t GetPuzzle();
	uint GetBlank();
	uint GetN();
	void Solve();
	void Backtrace(NodePtr rslt);
	void PrintStack(ofstream & file);

	//Check Solve.
	bool canSolve();

	//Regenerate Puzzle
	void RegenPuzzle();
};

