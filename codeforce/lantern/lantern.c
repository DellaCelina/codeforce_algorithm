#include <stdio.h>

typedef unsigned int uint;

struct list{
	uint p;
	struct list * next;
}

struct lh{
	struct list * next;
}

void list_add(struct lh *lh, struct list * list){
	struct **nl;
	nl = &((*lh)->next);
	while(!(*nl)){
		if((*nl)->p >= list->p)
			break;
		nl = &((*nl)->next);
	}
	list -> next = *nl;
	*nl = list;
}

struct list* init_list(uint p){struct list* list = malloc(sizeof(struct list)); list->p = p; list->next = NULL; return list;}

struct lh lh;

int main(void){
	int n, l;
	scanf("%d %d", &n, &l);
	lh.next = NULL;
	for(int i = 0; i < n; i++){
		uint p;
		scanf("%u", &p);
		list_add(init_list(p));
	}

	return 0;
}
