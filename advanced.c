#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Exercice 1

void param(int arg)
{
    printf("Nombre d'arguments : %d\n", arg);
}

void printParam(int nbArg, char **arg)
{
    if (nbArg == 1)
    {
        printf("Pas d'arguments");
    }
    else
    {
        for (int i=1; i<nbArg; i++)
        {
            printf("Argument %d : %s\n", i, arg[i]);
        }
    }
}

void age(int nbArg, char **arg)
{
    typedef struct Person{
        char nom[50];
        char prenom[25];
        int age;
    } Person;
    
    Person *person = (Person *)malloc(sizeof(Person));
    if (!person) {
        fprintf(stderr, "Erreur d'allocation mémoire sur Personne\n");
        return;
    }
    
    strncpy(person->nom, arg[1], 50);
    strncpy(person->prenom, arg[2], 25);
    person->age = 0; // default value
    for (int i=3; i<nbArg; i++)
    {
        int ageTemp = atoi(arg[i]);
        if (ageTemp > 0 && ageTemp < 127)
        {
            person->age = ageTemp; break;
        }
    }
    printf("Nom : %s", person->nom);
    printf("Prenom : %s", person->prenom);
    printf("Age : %d", person->age);
    free(person);
}


//Exercice 2

void printFile() //fscanf n'affiche pas les retours à la ligne
{
    FILE *fp = fopen("advanced.txt", "r+");
    if (fp == NULL)
    {
        printf("Failed to open file\n");
    }
    /* char buffer[100];
    while (fscanf(fp, "%s", buffer) != EOF)
    {
        printf("%s ", buffer);
    } */
    int c;
    while ((c = fgetc(fp)) != EOF)
    {
        printf("%c", c);
    }
    fclose(fp);
}

void cpFile(char **arg)
{
    char *src_filename = arg[1];
    char *dest_filename = arg[2];
    FILE *src_fp = fopen(src_filename, "rb");
    if (src_fp == NULL) {
        printf("Failed to open source file\n");
    }
    FILE *dest_fp = fopen(dest_filename, "wb");
    if (dest_fp == NULL) {
        printf("Failed to open destination file\n");
        fclose(src_fp);
    }
    int c;
    while ((c = fgetc(src_fp)) != EOF) {
        fputc(c, dest_fp);
    }
    fclose(src_fp);
    fclose(dest_fp);
}


//Exercice 3

void pt()
{
    int *p = NULL;
    printf("%p\n", p);
    p = malloc(sizeof(int));
    printf("%p\n", p);
    int i = 10;
    p = &i;
    printf("%p", p);
}


//Exercice 4

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;

Queue* createQueue()
{
    Queue *q = (Queue*) malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

int isEmpty(Queue *q) {
    return (q->front == NULL);
}

void enqueue(Queue *q, int data)
{
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (q->rear == NULL){
        q->front = q->rear = newNode;
    }
    else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(Queue *q)
{
    if (q->front == NULL){
        printf("Queue is empty\n");
        return -1;
    }
    Node *temp = q->front;
    int data = temp->data;
    q->front = q->front->next;
    if (q->front == NULL){
        q->rear = NULL;
    }
    free(temp);
    return data;
}

int requeue(Queue *q)
{
    if (isEmpty(q)){
        printf("Queue is empty\n");
        return -1;
    }
    int n = q->front->data;
    return n;
}

int lenQ(Queue *q)
{
    int l = 0;
    Node *temp = q->front;
    while (temp != NULL){
        l++;
        temp = temp->next;
    }
    return l;
}

void printQueue(Queue *q)
{
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    Node *temp = q->front;
    while (temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void soloQ(int nbArg, char **arg, Queue *q)
{
    int input = 0;
    if (nbArg > 1)
    {
        for (int i=1; i<nbArg; i++)
        {
            int input = atoi(arg[i]);
            if (input < 0){
                printf("Invalid input: must be a positive integer\n");
            }
            else{
                enqueue(q, input);
            }
        }
    }
    else
    {
        while (1)
        {
            printf("Enter a positive integer (or -1 to stop): ");
            scanf("%d", &input);
            if (input == -1){
                break;
            }
            else if (input < 0){
                printf("Invalid input: must be a positive integer\n");
            }
            else{
                enqueue(q, input);
            }
        }
    }
    Node *temp = q->front;
    while (temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
        dequeue(q);
    }
    /* while (!isEmpty(q)) {
        int value = dequeue(q);
        printf("%d ", value);
    } */
    printf("\n");
}


int main(int argc, char **argv)
{
    //Queue *q = createQueue();
    age(argc, argv);
    return 0;
}
