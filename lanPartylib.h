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


typedef struct Team{

    int no_players;
    char* teamName;
    float pointsTotal;
    Player *value;
    struct Team *next;

}Team;



// functii pentru LISTE

void addAtBeginning(Team **head,  FILE *input_file, int no_teams);
void printList(Team *head, FILE *output_file);


