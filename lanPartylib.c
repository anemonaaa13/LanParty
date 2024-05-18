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
        //teamName[strlen(teamName)-1] = '\0';
        if (teamName[strlen(teamName)-3] == ' ') {
            teamName[strlen(teamName)-3] = '\0';
        } else if (teamName[strlen(teamName)-2] = '\r') {
            teamName[strlen(teamName)-2] = '\0';
        }


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
        fprintf(output_file, "%s\r\n", copy->teamName);
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

Queue* createQueue()
{
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if( q == NULL )
        return NULL;

    q->front = q->rear = NULL;
    return q;
}

void enQueue(Queue* q, Team * val)
{
    // Create a new LL node
    Team * temp = val;
    
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
 
    // Add the new node at the end of queue and change rear
    q->rear->next = temp;
    q->rear = temp;
}

void deQueue(Queue* q)
{
    // If queue is empty, return NULL.
    if (q->front == NULL)
        return;
 
    // Store previous front and move front one node ahead
    Team * temp = q->front;
 
    q->front = q->front->next;
 
    // If front becomes NULL, then change rear also as NULL
    if (q->front == NULL)
        q->rear = NULL;
 
    //free(temp);
}

void pushStack(Team **top, Team * val)
{

    Team* newTeam = (Team*)malloc(sizeof(Team));
    newTeam->teamName = val->teamName;
    newTeam->pointsTotal = val->pointsTotal;
    newTeam->next = *top;
    *top = newTeam;
}

void popStack(Team** top)
{
    if((*top) == NULL) 
        return;
    
    Team * temp = (*top);
    (*top) = (*top)->next;
    //free(temp);
}

void free_team(Team* t)
{
    if(!t)
    {
        free(t->teamName);
        for(int i=0; i < t->no_players; i++)
            {
                free(t->value[i].firstName);
                free(t->value[i].secondName);
            }
        free(t->value);
        free_team(t->next);
        free(t);
    }
}

void Task3(Team *head, Team ** topTeam, int nr_teams, FILE * output_file) {
    Team * win = NULL;
    Team * lose = NULL;
    Queue * q = createQueue();

    int nr_runda = 1;

    while (head != NULL) {
        enQueue(q, head);
        head = head->next;
    }

    while (nr_teams > 1) {
        fprintf(output_file, "\r\n--- ROUND NO:%d\r\n", nr_runda);

        while (q->front != NULL) {
            Team * t1 = q->front;
            deQueue(q);
            
            Team * t2 = q->front;
            deQueue(q);
            
            fprintf(output_file, "%-33s-%33s\r\n", t1->teamName, t2->teamName);
            
            if (t1->pointsTotal > t2->pointsTotal) {
                t1->pointsTotal++;
                pushStack(&win, t1);
                pushStack(&lose, t2);
            } else {
                t2->pointsTotal++;
                pushStack(&win, t2);
                pushStack(&lose, t1);
            }
        }

        if (nr_teams == 16) {
            Team * temp = win;
            while(temp != NULL) {
                pushStack(topTeam, temp);
                temp = temp->next;
            }
        }
        
        fprintf(output_file, "\r\nWINNERS OF ROUND NO:%d\r\n", nr_runda);

        while(win != NULL) {
            fprintf(output_file, "%-34s-  %.2f\r\n", win->teamName, win->pointsTotal);
            enQueue(q, win);
            popStack(&win);
        }

        while(lose != NULL) {
            popStack(&lose);
        }

        nr_runda++;
        nr_teams /= 2;

    }
}


