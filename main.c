#include "lanPartylib.h"

#define no_tasks 5

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("Nu este in regula.\n"); return 1;
    }
    FILE *check = fopen(argv[1], "r");
    if(check == NULL ){
        printf("Nu este in regula.\n"); return 1;
    }
    FILE *input_file = fopen(argv[2], "r");
    if( input_file == NULL ){
        printf("Nu este in regula.n"); return 1;
    }
    FILE *output_file = fopen( argv[3], "w+");
    if( output_file == NULL){
        printf("Nu este in regula.\n"); return 1;
    }

    int Tasks[no_tasks], no_teams;
    ReadTasks(check, no_tasks, Tasks);   // citire task uri de catre checker
    fscanf(input_file, "%d", &no_teams); // citire nr de echipe - primul nr din fisier

    // Task 1
    Team *head = NULL; 
    addAtBeginning(&head, input_file, no_teams);

    // Task 2
    if(Tasks[1] == 1 ){
        totalScoreTeam(&head);
        FinalDelete(&head, &no_teams);
    }
    printList(head, output_file);

    // Task 3
    Team * topTeam = NULL; 
    Team* orderTeam = NULL;

    if(Tasks[2] == 1) 
        Task3(head, &topTeam, no_teams, output_file);

    // Task 4
    if(Tasks[3] == 1)
        Task4(output_file, topTeam, &orderTeam);

    // Task 5
    if(Tasks[4] == 1)
        Task5(output_file, orderTeam);
    //dealocare de memorie
    deleteList(&head);
    deleteList(&topTeam);
    deleteList(&orderTeam);
    fclose(check);
    fclose(input_file);
    fclose(output_file);
    return 0;
}
