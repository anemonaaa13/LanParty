#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// creare functii pentru lucrul cu fisierele

// citirea de catre checker a cerintei pe care trebuie sa o verifice

void ReadTasks(FILE *check, int no_tasks, int Tasks[]);


// creare structuri ajutatoare

typedef struct Player{

    char* firstName;
    char* secondName;
    int points;

}Player;


// creare lista de echipe

typedef struct Team{

    int no_players;
    char* teamName;
    float pointsTotal;
    Player *value;
    struct Team *next;

}Team;

typedef struct Match{
    Team *team1;
    Team *team2;
    struct Match* next;

}Match;

typedef struct Queue{
    Match* front;
    Match* rear;

}Queue;

typedef struct Stack{
    Team *echipa;
    struct Stack* next;

}Stack;

// functii pentru LISTE

void addAtBeginning(Team **head,  FILE *input_file, int no_teams);
void printList(Team *head, FILE *output_file);

void totalScoreTeam(Team **head);
int powerOf2(int no_teams);
float MinScore(Team *head);
void DeleteTeam(Team **head);
void FinalDelete(Team **head, int *no_teams);

// functii pentru COADA

Queue* createQueue();
int isEmptyQueue(Queue *q);
void enQueue( Queue *q, Team *t);
void golire_coada(Queue *q);
void pop_coada(Queue **q);

// functii pentru STIVA

Stack* createStack();
void pushStack(Stack **top, Team *val);
int isEmptyStack(Stack *top);
//Stack* popStack(Stack *top);

void free_team(Team* t);
void stiva_castigatori_in_lista(Stack *win, Team *head);
void Task3(Team *head, int no_teams, FILE* output_file);

void distribuire_pe_stive(Stack *castigatori, Stack *pierzatori, Queue *que);
Team* popStack(Stack** top, Queue *q);