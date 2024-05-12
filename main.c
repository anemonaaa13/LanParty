#include "lanPartylib.h"

#define no_tasks 5

int main(int argc, char *argv[])
{
    printf("orice\n");
    if(argc < 2)
    {
        printf("Nu este in regula.\n");
        return 1;
    }

    FILE *check = fopen(argv[1], "r");
    if(check == NULL )
    {
        printf("Nu este in regula.\n");
        return 1;
    }

    FILE *input_file = fopen(argv[2], "r");
    if( input_file == NULL )
    {
        printf("Nu este in regula.n");
        return 1;
    }

    FILE *output_file = fopen( argv[3], "w+");
    if( output_file == NULL)
    {
        printf("Nu este in regula.\n");
        return 1;
    }

    // citire task uri de catre checker

    int Tasks[no_tasks];
    ReadTasks(check, no_tasks, Tasks);

    // citire nr de echipe - primul nr din fisier

    int no_teams;
    fscanf(input_file, "%d", &no_teams);
    
    // Task 1

    Team *head = NULL; 
    addAtBeginning(&head, input_file, no_teams);


    // Task 2

    if(Tasks[1] == 1 )
    {
        totalScoreTeam(&head);
        FinalDelete(&head, &no_teams);
    }
    printList(head, output_file);

    fclose(check);
    fclose(input_file);
    fclose(output_file);

    return 0;
}