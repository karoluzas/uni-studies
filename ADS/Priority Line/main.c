#include <stdio.h>
#include <stdlib.h>
#include "priorityqueue.h"

int main()
{
    Queue *eile = createQueue();

    // insert(queue, value, priority)
    insert(eile, 2, 1);
    insert(eile, 3, 1);
    insert(eile, 51, 1);
    insert(eile, 1, 100);
    insert(eile, 34, -1);
    insert(eile, 8, 65);
    insert(eile, 324, -10);
    printListPriority(eile);
    
    int a = popOut(eile);
    printListPriority(eile);
    
    int b = peek(eile);
    printListPriority(eile);
    
    clearQueue(eile);
    printf("%d\n", isEmpty(eile));
    printf("%d", isFull());
    return 0;
}