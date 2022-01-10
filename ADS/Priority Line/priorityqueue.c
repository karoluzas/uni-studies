#include <stdio.h>
#include <stdlib.h>
#include "priorityqueue.h"

Queue *createQueue()
{
    Queue *temp = (Queue*)malloc(sizeof(Queue));
    temp->front = NULL;
    temp->rear = NULL;
    temp->size = 0;
    return temp;
}

Node *createNewNode(int value, int p)
{
    if(isFull() == 1){
        return NULL;
    }
    else {
        Node *temp = (Node*)malloc(sizeof(Node));
        temp->data = value;
        temp->priority = p;
        temp->next = NULL;
        return temp;
    }

}

int insert(Queue *que, int value, int p)
{
    Node *temp = createNewNode(value,p);
    if(isFull() == 1){
        return -1;
    }else{
        Queue *head = createQueue();
        head->front = que->front;
        head->rear = que->rear;

        if(que->front == NULL){
            que->front = que->rear = temp;
            que->size++;
            return 0;
        }

        if(temp->priority <= que->rear->priority){
            que->rear->next = temp;
            que->rear = temp;
            que->rear->next = NULL;
            que->size++;

        }else if(temp->priority > que->front->priority){
            temp->next = que->front;
            que->front = temp;
            que->size++;

        }else if(temp->priority <= head->front->priority){
            while(head->front->priority >= temp->priority && head->front->next != NULL){
                if(head->front->next->priority < temp->priority) {
                    temp->next = head->front->next;
                    head->front->next = temp;

                    que->size++;
                    break;
                }else {
                    head->front = head->front->next;
                }
            }
        }
        return 0;
    }
}

int isEmpty(Queue *que)
{
    if(que->size <= 0){
        return 1;
    }
    return 0;
}

int peek(Queue *que)
{
    if(!isEmpty(que)){
        return que->front->data;
    }else{
        return 0;
    }
}

int popOut(Queue *que)
{
    if(isEmpty(que)) {
        return 0;
    }
    Node *temp = que->front;
    int rez = que->front->data;
    que->front = que->front->next;
    que->size--;
    if(que->front == NULL){
        que->rear = NULL;
    }
    free(temp);
    return rez;
}

void clearQueue(Queue *que)
{
    if(que->front == NULL){
        return;
    }

    while(que->front != NULL){
        Node *temp = que->front->next;
        free(que->front);
        que->front = temp;
        que->size--;
    }

}

void printListPriority(Queue *head)
{
    Queue *temporary = createQueue();
    temporary->front = head->front;
    temporary->rear = head->rear;
    temporary->size = head->size;
    int counter = 0;

    while(temporary->front != NULL){
        counter++;
        if(temporary->size == counter){
            printf("%d", temporary->front->data);
            break;
        }
        printf("%d -> ", temporary->front->data);
        temporary->front = temporary->front->next;
    }
    printf("\n-----------------------------------------------------\n");
}

int isFull()
{
    Node *temp = (Node*)malloc(sizeof(Node));
    if(temp == NULL){
        free(temp);
        return 1;
    }
    else{
        free(temp);
        return 0;
    }
    return -1;
}

int SizeOfQueue(Queue *queue)
{
    return queue->size; 
}