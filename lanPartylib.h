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


typedef struct Queue{
    Team* front;
    Team* rear;

}Queue;

typedef struct BST_team {
    Team* echipa;
    struct BST_team *left, *right;

}BST_team;



// functii pentru LISTE

void addAtBeginning(Team **head,  FILE *input_file, int no_teams);
void printList(Team *head, FILE *output_file);

void totalScoreTeam(Team **head);
int powerOf2(int no_teams);
float MinScore(Team *head);
void DeleteTeam(Team **head);
void FinalDelete(Team **head, int *no_teams);

void free_team(Team* t);
void Task3(Team *head, Team**, int, FILE*);

void Task4(FILE* output_file, Team* topTeam, Team **);
