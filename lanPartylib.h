#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// citirea de catre checker a cerintei pe care trebuie sa o verifice

void ReadTasks(FILE *check, int no_tasks, int Tasks[]);

// creare structuri ajutatoare

typedef struct Player{

    char* firstName;
    char* secondName;
    int points;

}Player;

typedef struct Team{

    int no_players;
    char* teamName;
    float pointsTotal;
    Player *value;
    struct Team *next;

}Team;

typedef struct Queue{
    Team* front;
    Team* rear;

}Queue;

typedef struct BST_team {
    Team* echipa;
    struct BST_team *left, *right;

}BST_team;

typedef struct AVL_Team { 
    int key;
    Team * data;
    struct AVL_Team *left; 
    struct AVL_Team *right; 
    int height; 

}AVL_Team; 

// functii pentru LISTE

void addAtBeginning(Team **head,  FILE *input_file, int no_teams);
void printList(Team *head, FILE *output_file);

void totalScoreTeam(Team **head);
int powerOf2(int no_teams);
float MinScore(Team *head);
void DeleteTeam(Team **head);
void FinalDelete(Team **head, int *no_teams);
void printFromList(Team * list, int position, FILE * file);

// functii pentru COADA

Queue* createQueue();
void enQueue(Queue* q, Team * val);
void deQueue(Queue* q);

// functii pentru STIVA

void pushStack(Team **top, Team * val);
void popStack(Team** top);

// functii pentru ARBORI

BST_team* newNodeCreate( Team* value);
BST_team* insertNode( BST_team* node, Team* value);
void inOrder(BST_team* root, FILE* output_file, Team** lista);

// functii pentru AVL

int height(AVL_Team *N);
int max(int a, int b); 
AVL_Team* newNode(int key);
AVL_Team* rightRotate(AVL_Team* y);
AVL_Team* leftRotate(AVL_Team* x);
int getBalance(AVL_Team* N);
AVL_Team* insert(AVL_Team* node, int key);
void printAVL(AVL_Team* root, int level, Team * list, FILE * file);


// functii pentru TASK-URI

void Task3(Team *head, Team**, int, FILE*);
void Task4(FILE* output_file, Team* topTeam, Team **);
void Task5(FILE* output_file, Team* topTeam);