
// Rokas Čebatorius, Programų sistemos 1 kursas, 2 pogrupis
// rokas.cebatorius@mif.stud.vu.lt

#ifndef priorityListFunc_h
#define priorityListFunc_h

typedef struct Node
{
	void* data;
	struct Node* next;
	int priority;
} Node;

typedef struct PriorityQueue
{
	struct Node* head;
	int count;
} PriorityQueue;

void CreateEmptyQueue(PriorityQueue** queue); // Create empty queue
int IsEmpty(PriorityQueue* queue); // Check if queue is empty
void Insert(PriorityQueue** queue, void* data, int priority); // Insert an element with priority into queue and returns -1 if insufficiant memory
void Remove(PriorityQueue** queue); // Remove highest priority element
void DeleteQueue(PriorityQueue** queue); // Delete the queue
PriorityQueue* Join(PriorityQueue* queue1, PriorityQueue* queue2); // Joins two queues into one and returns it's address (if priorities are same, queue1 will have higher priority)

#endif
