//
// Created by liududu on 18-4-14.
//

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define QUEUE_MAX_SIZE 100
#define MAX_STEP 512
typedef enum {
	zero,
	one,
	two,
	three,
	four,
	five,
	six,
	seven,
	eight
} till;
typedef enum {
	UP,
	DOWN,
	LEFT,
	RIGHT
} move_step;

typedef struct table{
	struct table* last;
	till table_items[9];
	int zero_location;
	char* msg;
} table;



table* new_table(void) {
	table* ptable = (table*)malloc(sizeof(table));
	if (ptable != NULL){
		memset(ptable,0,sizeof(table));
		return ptable;
	}
	perror("malloc error");
}

table* set_table(table* t,table * last, till table_items[],char* msg) {
	for(int i = 0; i < 9; i++) {
		if(table_items[i] == zero) t->zero_location = i;
		t->table_items[i] = table_items[i];
	}
	t->last = last;
	t->msg = msg;
	return t;
}


table* move(table* t,move_step step) {
	table* new_tab = new_table();
	memcpy(new_tab,t,sizeof(table));
	int zero_location = new_tab->zero_location;
	int new_zero;
	int x = zero_location / 3;
	int y = zero_location % 3;
	till temp;
	switch(step) {
		case UP:
			if (x == 0){
				free(new_tab);
				return NULL;
			}
			new_zero = (x-1) * 3 + y;
			new_tab->msg = "向上移动";
			break;
		case DOWN:
			if (x == 2){
				free(new_tab);
				return NULL;
			}
			new_zero = (x+1) * 3 + y;
			new_tab->msg = "向下移动";
			break;
		case LEFT:
			if (y == 0){
				free(new_tab);
				return NULL;
			}
			new_zero = x * 3 + y - 1;
			new_tab->msg = "向左移动";
			break;
		case RIGHT:
			if (y == 2){
				free(new_tab);
				return NULL;
			}
			new_zero = x * 3 + y + 1;
			new_tab->msg = "向右移动";
			break;
	}
	temp = new_tab->table_items[new_zero];
	new_tab->table_items[new_zero] = new_tab->table_items[zero_location];
	new_tab->table_items[zero_location] = temp;
	new_tab->last = t;
	new_tab->zero_location = new_zero;
	return new_tab;
}

int issame(table* a, table* b) {
	till * t1 = a->table_items;
	till * t2 = b->table_items;
	for(int i = 0; i < 9; i++) {
		if (t1[i] != t2[i])
			return 0;
	}
	return 1;
}

void print_table(table* t) {
	for(int i = 0; i < 9; i++) {
		printf("%d ",t->table_items[i]);
		if (i % 3 == 2)
			printf("\n");
	}
	printf("\n");
}

typedef struct{
	int i,j;
	table *q[QUEUE_MAX_SIZE];
} queue;

queue* new_queue(void) {
	queue* q = (queue*)malloc(sizeof(queue));
	if (q == NULL) {
		perror("queue malloc error");
	}
	q->i = 0;
	q->j = 0;
	return q;
}

void enqueue(queue* q, table* t) {
	if (q->i % QUEUE_MAX_SIZE + 1 == q->j)
		perror("out of memory of queue");
	q->q[q->i] = t;
	(q->i)++;
}

table* dequeue(queue* q) {
	if (q->j % QUEUE_MAX_SIZE == q->i % QUEUE_MAX_SIZE)
		perror("dequeue error");
	return q->q[(q->j)++];
}

int is_empty(queue* q) {
	return q->i % QUEUE_MAX_SIZE == q->j % QUEUE_MAX_SIZE;
}

int is_in(queue* q, table* t) {
	int m = q->j, n = q->i;
	for(int it = m; it < n; it ++) {
		if (issame(q->q[it % QUEUE_MAX_SIZE],t))
			return 1;
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	table* start = new_table();
	table* goal = new_table();
	int step_count = 0;
	table* current_table = NULL;
	table* next_table = NULL;
	till start_tills[9] = {
		one ,three,four,
		eight,zero,two,
		seven,six,five
	};
	till goal_tills[9] = {
		one,two,three,
		eight,zero,four,
		seven,six,five
	};
	set_table(start,NULL,start_tills,"起始");
	set_table(goal,NULL,goal_tills,"结束");
	queue * openlist = new_queue();
	queue * closelist = new_queue();
	enqueue(openlist,start);
	while(!is_empty(openlist)) {
		if (step_count > MAX_STEP)
			perror("Max step reached");
		current_table = dequeue(openlist);
		enqueue(closelist,current_table);
		if (!issame(current_table,goal)) {
			next_table = move(current_table,UP);
			if (next_table != NULL && !is_in(closelist,next_table)) {
				enqueue(openlist,next_table);
			}
			next_table = move(current_table,DOWN);
			if (next_table != NULL && !is_in(closelist,next_table)) {
				enqueue(openlist,next_table);
			}
			next_table = move(current_table,LEFT);
			if (next_table != NULL && !is_in(closelist,next_table)) {
				enqueue(openlist,next_table);
			}
			next_table = move(current_table,RIGHT);
			if (next_table != NULL && !is_in(closelist,next_table)) {
				enqueue(openlist,next_table);
			}
		}else{
			break;
		}
		step_count++;
	}
	queue * result = new_queue();
	enqueue(result,current_table);
	table* temp = current_table->last;
	while(temp != NULL) {
		enqueue(result,temp);
		temp = temp->last;
	}
	while(!is_empty(result)) {
		print_table(dequeue(result));
	}
	return 0;
}
