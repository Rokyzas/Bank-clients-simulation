// Rokas Čebatorius, Programų sistemos 1 kursas, 2 pogrupis
// rokas.cebatorius@mif.stud.vu.lt

#include <stdio.h>
#include <stdlib.h>
#include "priorityListFunc.h"

void CreateEmptyQueue(PriorityQueue** queue)
{
	(*queue) = malloc(sizeof(PriorityQueue));
	(*queue)->head = NULL;
	(*queue)->count = 0;
}

int IsEmpty(PriorityQueue* queue)
{
	return queue->head == NULL;
}

void Insert(PriorityQueue** queue, void* data, int priority)
{
	++(*queue)->count;
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		return -1; // Insufficiant memory
	}

	newNode->data = data;
	newNode->priority = priority;
	newNode->next = NULL;

	if ((*queue)->head == NULL)
	{
		(*queue)->head = newNode;
	}
	else if (newNode->priority < (*queue)->head->priority) // Cheking if first element is top priority
	{
		newNode->next = (*queue)->head;
		(*queue)->head = newNode;
	}
	else
	{
		Node* temp = (*queue)->head;
		while (temp->next != NULL)
		{
			if (newNode->priority < temp->next->priority)
			{
				newNode->next = temp->next;
				temp->next = newNode;
				break;
			}
			else
			{
				temp = temp->next;
			}
		}
		if (temp->next == NULL) // newNode was not added to the list if we reached last element, so we add newNode at the end
		{
			temp->next = newNode;
		}
	}
}

void Remove(PriorityQueue** queue)
{
	Node* temp = (*queue)->head->next;
	free((*queue)->head);
	--(*queue)->count;
	(*queue)->head = temp;
}

void DeleteQueue(PriorityQueue** queue)
{
	Node *temp = (*queue)->head;
	while((*queue)->head != NULL)
	{
		temp = (*queue)->head->next;
		free((*queue)->head);
		(*queue)->head = temp;
	}

	free(*queue);
	*queue = NULL;
}

PriorityQueue* Join(PriorityQueue* queue1, PriorityQueue* queue2)
{
	PriorityQueue* newQueue;

	CreateEmptyQueue(&newQueue);

	Node* temp = queue1->head;
	while (temp != NULL)
	{
		Insert(&newQueue, temp->data, temp->priority);
		temp = temp->next;
	}

	temp = queue2->head;
	while (temp != NULL)
	{
		Insert(&newQueue, temp->data, temp->priority);
		temp = temp->next;
	}

	return newQueue;
}
