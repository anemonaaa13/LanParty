#include "lanPartylib.h"

void ReadTasks(FILE *check, int no_tasks, int Tasks[])
{
    for(int i=0; i < no_tasks; i++)
        fscanf(check, "%d", &Tasks[i]);
}

void addAtBeginning(Team **head,  FILE *input_file, int no_teams)
{
    for(int i=0; i< no_teams; i++){
        Team* newTeam = (Team*)malloc(sizeof(Team));

        int no_players; char teamName[100]; Player *jucator;

        fscanf(input_file, "%d", &no_players);
        newTeam->no_players = no_players;

        fgetc(input_file);
        fgets(teamName, 100, input_file);
        teamName[strlen(teamName)-1] = '\0';
        newTeam->teamName = (char*)malloc(strlen(teamName) +1 );
        strcpy(newTeam->teamName, teamName);

        newTeam->value = (Player *)malloc(no_players * sizeof(Player));

        for(int j=0; j < no_players; j++){
           

            char buffer[50];

            fscanf(input_file, "%s", buffer);
            newTeam->value[j].firstName = malloc(strlen(buffer) + 1);
            strcpy(newTeam->value[j].firstName, buffer);

            fscanf(input_file, "%s", buffer);
            newTeam->value[j].secondName = malloc(strlen(buffer) + 1);
            strcpy(newTeam->value[j].secondName, buffer);

            fscanf(input_file, "%d", &jucator->points);
            newTeam->value[j].points = jucator->points;

        }
        newTeam->next = *head;
        *head = newTeam;
    }
}

void printList(Team *head, FILE *output_file)
{
    Team *copy = head;
    while( copy != NULL)
    {
        fprintf(output_file, "%s\n", copy->teamName);
        copy = copy->next;
    }
}

void totalScoreTeam(Team **head)
{
    Team *copy = *head;

    while( copy != NULL)
    {
        float total = 0;
        for( int i=0; i < (copy->no_players); i++ )
        {
        total = total + copy->value[i].points;
        }

    total = total / copy->no_players ; 
    copy->pointsTotal = total;
    copy = copy->next; 
    }
}

int powerOf2(int no_teams)
{
    int n=1;

    while(2*n <= no_teams)
        n = 2 * n;
    
    int deleted_teams;
    deleted_teams = no_teams - n;
    return deleted_teams;
}

float MinScore(Team *head)
{
    Team *copy = head;

    float MinScore = head->pointsTotal;

    while( copy != NULL)
    {
        if(copy->pointsTotal < MinScore)
        { 
            MinScore = copy->pointsTotal;
        }
        copy = copy->next;
    }
    return MinScore;
}

void DeleteTeam(Team **head)
{
    float minim = MinScore(*head);

    if(*head == NULL ) return; // daca lista e goala

    Team *copy = *head; // daca elem de sters e capul listei
    if( copy->pointsTotal == minim )
    {
        *head = (*head)->next;
        free(copy);
        return;
    }

    Team *prev = *head;
    while(copy != NULL)
    {
        if(copy->pointsTotal != minim)
        {
            prev = copy;
            copy = copy->next;
        }
        else
        {
            prev->next = copy->next;
            free(copy);
            return;
        }
    }
}


void FinalDelete(Team **head, int *no_teams)
{
    Team *copy = *head;

    int n = powerOf2(*no_teams);
    *no_teams = *no_teams - n;

    for(int i=0; i < n ; i++)
    {
        DeleteTeam(head);
    }
}