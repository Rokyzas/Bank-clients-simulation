#include <stdio.h>
#include <stdlib.h>
#include "queue_function_desc.h"
#include "priorityListFunc.h"

struct Worker
{
	int isFree;
	int timeOut;
	int overtime;
	int idletime;
};

int clientProbability = 35, clientVipProbability = 20;
enum { WorkersCount = 5 };
enum { WorkersVipCount = 3 };
int clientTime = 7, clientVipTime = 10;
int workingDayTime = 60 * 12;

void process1();
void process2();
void PrintListIntData(PriorityQueue* queue);
void printWorkers(struct Worker workers[]);



int main() 
{
	process1();

	process2();



	return 0;
}

void process1() 
{
	int clientWaitingSum = 0, clientVipWaitingSum = 0;
	int clientCount = 0, clientVipCount = 0;
	int idleTimeSum = 0;
	float overtimeSum = 0;
	float clientWaitingAvg = 0, clientVipWaitingAvg = 0;

	PriorityQueue *clientQueue;
	CreateEmptyQueue(&clientQueue);

	struct Worker clientWorkers[WorkersCount];
	for (int i = 0; i < WorkersCount; ++i) {
		clientWorkers[i].isFree = 1;
		clientWorkers[i].timeOut = 0;
		clientWorkers[i].overtime = 0;
		clientWorkers[i].idletime = 0;
	}


	int endOfWork = 1, overTime = 0;
	for (int i = 0; (i < workingDayTime) || !endOfWork; i++)
	{
		if (i <= workingDayTime)
		{
			if ((rand() % 100) < clientVipProbability)
			{
				Insert(&clientQueue, 0, 1);
				clientVipCount++;
			}

			if ((rand() % 100) < clientProbability)
			{
				Insert(&clientQueue, 0, 2);
				clientCount++;
			}
		}

		//PrintListIntData(clientQueue);

		endOfWork = 1;
		for (int j = 0; j < WorkersCount; j++)
		{
			if (clientWorkers[j].isFree == 1)
			{
				if (!IsEmpty(clientQueue))
				{
					clientWorkers[j].isFree = 0;
					if (clientQueue->head->priority == 1)
					{
						clientWorkers[j].timeOut = clientVipTime;
						clientVipWaitingSum += (int)clientQueue->head->data;
					}
					else
					{
						clientWaitingSum += (int)clientQueue->head->data;
						clientWorkers[j].timeOut = clientTime;
					}
					
					Remove(&clientQueue);
				}
				else
				{
					if (i < workingDayTime)
					{
						clientWorkers[j].idletime++;
					}
				}
			}
			else
			{

				clientWorkers[j].timeOut--;
				if (i > workingDayTime)
				{
					clientWorkers[j].overtime++;
				}

				if (clientWorkers[j].timeOut == 0)
				{
					clientWorkers[j].isFree = 1;
				}
				else
				{
					endOfWork = 0;
				}
			}
		}

		Node* temp = clientQueue->head;
		for (int i = 0; i < clientQueue->count; i++)
		{
			temp->data = (int)temp->data + 1;
			temp = temp->next;
		}
	

		//PrintListIntData(clientQueue);
		//printWorkers(clientWorkers, WorkersCount);

		//printf("%d\n", i);

	}

	for (int i = 0; i < WorkersCount; i++) {
		overtimeSum += clientWorkers[i].overtime;
		idleTimeSum += clientWorkers[i].idletime;
	}

	clientWaitingAvg = clientWaitingSum / clientCount;
	clientVipWaitingAvg = clientVipWaitingSum / clientVipCount;

	printf("Process1: Workers idle sum: %d Workers overtime sum: %.1f Client waiting time average: %.1f Vip client waiting time average: %.1f", idleTimeSum ,overtimeSum, clientWaitingAvg, clientVipWaitingAvg);
	printf("\n");
	return 0;
}

void process2() {

	int clientWaitingSum = 0, clientVipWaitingSum = 0;
	int clientCount = 0, clientVipCount = 0;
	int idleTimeSum = 0;
	float overtimeSum = 0;
	float clientWaitingAvg = 0, clientVipWaitingAvg = 0;

	struct Queue* clientQueue = createQueue(), * clientVipQueue = createQueue();

	struct Worker clientWorkers[WorkersCount];
	for (int i = 0; i < WorkersCount; ++i) {
		clientWorkers[i].isFree = 1;
		clientWorkers[i].timeOut = 0;
		clientWorkers[i].overtime = 0;
		clientWorkers[i].idletime = 0;
	}

	struct Worker clientVipWorkers[WorkersVipCount];
	for (int i = 0; i < WorkersVipCount; ++i) {
		clientVipWorkers[i].isFree = 1;
		clientVipWorkers[i].timeOut = 0;
		clientVipWorkers[i].overtime = 0;
		clientVipWorkers[i].idletime = 0;
	}


	int endOfWork = 1, error = 0;
	for (int i = 0; (i < workingDayTime) || !endOfWork; i++)
	{
		if (i <= workingDayTime)
		{
			if ((rand() % 100) < clientVipProbability)
			{
				enQueue(clientVipQueue, 0, error);
				clientVipCount++;
			}

			if ((rand() % 100) < clientProbability)
			{
				enQueue(clientQueue, 0, error);
				clientCount++;
			}
		}

		//printList(clientQueue);
		//printList(clientVipQueue);

		endOfWork = 1;
		for (int j = 0; j < WorkersCount; j++)
		{
			if (clientWorkers[j].isFree == 1)
			{
				if (isEmpty(clientQueue))
				{
					clientWorkers[j].isFree = 0;
					clientWaitingSum += (int)clientQueue->front->data;
					clientWorkers[j].timeOut = clientTime;

					deQueue(clientQueue);
				}
				else
				{
					if (i < workingDayTime)
					{
						clientWorkers[j].idletime++;
					}
				}
			}
			else
			{

				clientWorkers[j].timeOut--;
				if (i > workingDayTime)
				{
					clientWorkers[j].overtime++;
				}

				if (clientWorkers[j].timeOut == 0)
				{
					clientWorkers[j].isFree = 1;
				}
				else
				{
					endOfWork = 0;
				}
			}
		}

		for (int j = 0; j < WorkersVipCount; j++)
		{
			if (clientVipWorkers[j].isFree == 1)
			{
				if (isEmpty(clientVipQueue))
				{
					clientVipWorkers[j].isFree = 0;
					clientVipWaitingSum += (int)clientVipQueue->front->data;
					clientVipWorkers[j].timeOut = clientTime;

					deQueue(clientVipQueue);
				}
				else
				{
					if (i < workingDayTime)
					{
						clientVipWorkers[j].idletime++;
					}
				}
			}
			else
			{

				clientVipWorkers[j].timeOut--;
				if (i > workingDayTime)
				{
					clientVipWorkers[j].overtime++;
				}

				if (clientVipWorkers[j].timeOut == 0)
				{
					clientVipWorkers[j].isFree = 1;
				}
				else
				{
					endOfWork = 0;
				}
			}
		}


		Node* temp = clientQueue->front;
		while(temp != NULL)
		{
			temp->data = (int)temp->data + 1;
			temp = temp->next;
		}

		temp = clientVipQueue->front;
		while (temp != NULL)
		{
			temp->data = (int)temp->data + 1;
			temp = temp->next;
		}

		//printList(clientQueue);
		//printList(clientVipQueue);
		//printWorkers(clientWorkers, WorkersCount);
		//printWorkers(clientVipWorkers, WorkersVipCount);

		//printf("%d\n", i);

	}

	for (int i = 0; i < WorkersCount; i++) {
		overtimeSum += clientWorkers[i].overtime;
		idleTimeSum += clientWorkers[i].idletime;
	}

	for (int i = 0; i < WorkersVipCount; i++) {
		overtimeSum += clientWorkers[i].overtime;
		idleTimeSum += clientWorkers[i].idletime;
	}

	clientWaitingAvg = clientWaitingSum / clientCount;
	clientVipWaitingAvg = clientVipWaitingSum / clientVipCount;

	printf("Process2: Workers idle sum: %d Workers overtime sum: %.1f Client waiting time average: %.1f Vip client waiting time average: %.1f", idleTimeSum, overtimeSum, clientWaitingAvg, clientVipWaitingAvg);
	printf("\n");
	return 0;
}

void PrintListIntData(PriorityQueue* queue)
{
	if (queue == NULL)
	{
		printf("Queue doesn't exist\n");
		return -1;
	}
	else if (IsEmpty(queue))
	{
		printf("Queue is empty\n");
		return -2;
	}
	else
	{
		Node* temp = queue->head;

		for (int i = 0; i < queue->count; ++i)
		{
			printf("%d ", (int)temp->data);
			temp = temp->next;
		}
	}

	printf("\n");
}

void printWorkers(struct Worker workers[], int count) {

	for (int i = 0; i < count; ++i)
	{
		printf("Nr. %d Status %d, Timeleft %d\n", i, workers[i].isFree, workers[i].timeOut);
	}
	
	printf("\n");

}