#include "lanPartylib.h"

void addAtBeginning(Team **head,  FILE *input_file, int no_teams)
{

    for(int i=0; i< no_teams; i++)
    {
        Team* newTeam = (Team*)malloc(sizeof(Team));

        int no_players; char teamName[100]; Player *jucator;

        fscanf(input_file, "%d", &no_players);
        newTeam->no_players = no_players;

        fgetc(input_file);
        fgets(teamName, 100, input_file);
        teamName[strlen(teamName)-1] = '\0';
        newTeam->teamName = (char*)malloc(strlen(teamName) +1 );
        strcpy(newTeam->teamName, teamName);

        for(int j=0; j < no_players; j++)
        {
            newTeam->value = (Player *)malloc(no_players * sizeof(Player));

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

void ReadTasks(FILE *check, int no_tasks, int Tasks[])
{
    for(int i=0; i < no_tasks; i++)
        fscanf(check, "%d", &Tasks[i]);
}