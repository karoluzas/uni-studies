struct node {
    int data;
    int priority;
    struct node* next;
};
struct queue{
    int size;
    struct node *front, *rear;
};

//Type used to store data and the priority
typedef struct node Node;

//Type used to store the front and the rear of the list
//To create a queue one must initialise it with "createQueue()"
//Example: Queue *list = createQueue();
typedef struct queue Queue;

//Function creates a new and empty queue
Queue *createQueue();

//Function creates a new node to be added to the queue
Node *createNewNode(int value, int priority);

//Function inserts a node into the queue according to the given priority
//If the function returns a value of -1, then the queue is full
//If the function returns a value of 0, then the proccess compiled successfully
int insert(Queue *queue, int value, int priority);

//Function checks if a queue is empty
//If it's empty then it returns a 0
//Otherwise it returns 1
int IsEmpty(Queue *queue);

//Function checks the value in front of the list and returns it
//without making any changes to the queue itself
int Peek(Queue *queue);

//Function takes out the member at the front, and removes it
//from the queue
int popOut(Queue *queue);

//Function clears a queue of all it's members
void clearQueue(Queue *queue);

//Function prints an entire list
void printListPriority(Queue *queue);

//Checks if there's any memory left for a node
int isFull();

//Returns an integer of a queue size
int SizeOfQueue(Queue *queue);
