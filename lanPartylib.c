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

/*void printStack(Stack* stiva, FILE* output_file)
{
    while(!isEmptyStack(stiva))
    {
        printf("%s \n", )
    }
}*/

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

int isEmptyQueue(Queue *q)
{
    return(q->front == NULL );
}

void enQueue( Queue *q, Team *t)
{
    Match *newMatch = (Match*)malloc(sizeof(Match));

    newMatch->team1 = t;
    newMatch->team2 = t->next;
    newMatch->next = NULL;

    if(q->rear == NULL)
        q->rear = newMatch;
    else
    {
        (q->rear)->next = newMatch;
        q->rear = newMatch;
    }

    if(q->front == NULL)
        q->front = q->rear;
}

void golire_coada(Queue *q)
{
    if(!q)
        return ;

    Match* aux = q->front;

    while(!isEmptyQueue(q))
    {
        /*free_team(aux->team1);
        free_team(aux->team2);*/

        q->front = aux->next;
        if( !q->front) // daca front ul ajunge pe ultimul element
        {
            q->rear = NULL;
        }

        golire_coada(q);
        free(aux);
    }
}

void pop_coada(Queue **q)
{
    if((*q)->front == NULL)
    {
        return ;
    }
    Match * m = (*q)->front;
    (*q)->front=(*q)->front->next;
    free(m);
}

Stack* createStack()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if( s == NULL )
        return NULL;

    s->echipa = NULL;
    return s;
}

void pushStack(Stack **top, Team *val)
{
    Stack* newTeam = (Stack*)malloc(sizeof(Stack));
    newTeam->echipa = (Team*)malloc(sizeof(Team));
    newTeam->echipa->no_players = val->no_players;

    newTeam->echipa->teamName = NULL;
    newTeam->echipa->teamName = (char*)malloc(( strlen(val->teamName) + 1) * sizeof(char));
    strcpy(newTeam->echipa->teamName, val->teamName);
    //printf("%s\n", newTeam->echipa->teamName);

    newTeam->echipa->pointsTotal = val->pointsTotal;
    newTeam->echipa->value = (Player *)malloc(val->no_players*sizeof(Player));
    for(int i=0; i< val->no_players; i++)
    {
        
        newTeam->echipa->value[i].firstName = (char*) malloc(( strlen(val->value[i].firstName) + 1) * sizeof(char));
        strcpy(newTeam->echipa->value[i].firstName, val->value[i].firstName);

        
        newTeam->echipa->value[i].secondName = (char*) malloc(( strlen(val->value[i].secondName) + 1) * sizeof(char));
        strcpy(newTeam->echipa->value[i].secondName, val->value[i].secondName);

        newTeam->echipa->value[i].points = val->value[i].points;
    }

    newTeam->next = *top;
    *top = newTeam;
}

int isEmptyStack(Stack *top)
{
    return(top == NULL );
}

Team* popStack(Stack** top, Queue *q)
{
    if(isEmptyStack(*top)) 
        return NULL;
    
    Stack* temp = (*top);
    printf( "%-33s-%.2f\n", (*top)->echipa->teamName, (*top)->echipa->pointsTotal);

    //printf("%s    %f\n", (*top)->echipa->teamName, (*top)->echipa->pointsTotal);
    Team* aux=temp->echipa;
    (*top)=(*top)->next;
    free(temp);
    enQueue(q,aux);
    return aux;
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

void stiva_castigatori_in_lista(Stack *win, Team *head)
{
    Stack *win_copy = win;
    Team* aux = head;
    while( !win_copy)
    {
        aux = win_copy->echipa; // salvam adresa echipei
        win_copy->echipa = NULL; // eliminam din stack echipa respectiva
        Stack *copie = win_copy; // salvam adresa stivei curente
        win_copy = win_copy->next; // parcurgem stiva de castigatori
        copie->next = NULL; // taiem legatura din stiva
        free(copie); // eliberam mem alocata stivei curente
        aux = aux->next; // trecem la urm nod din lista de echipe
    }
} 

void distribuire_pe_stive(Stack *castigatori, Stack *pierzatori, Queue *que)
{
    while(!isEmptyQueue(que))
    {
        
        if(que->front->team1->pointsTotal > que->front->team2->pointsTotal)
        {
            que->front->team1->pointsTotal += 1;
            pushStack(&castigatori, que->front->team1);
           // printf("%s \n", castigatori->echipa->teamName);
            pushStack(&pierzatori, que->front->team2);
        }
        else
        {    
            que->front->team2->pointsTotal += 1;
            pushStack(&pierzatori, que->front->team1);
            pushStack(&castigatori, que->front->team2);
            printf("%c", castigatori->echipa->teamName[0]);
            printf("%s \n", castigatori->echipa->teamName);
        } 
        pop_coada(&que);
    }
    //inainte de while golire coada
    while(!isEmptyStack(castigatori))
        popStack(&castigatori, que);
}

void Task3(Team *head, int no_teams, FILE* output_file)
{
    int nr_runda = 1; // initializam numarul de runde

    Team *copy = head; // luam o copie pentru lista de echipe ramase 
    Queue *q = createQueue();  // creare coada in care vom adauga cate 2 echipe pe rand
    Stack *win = NULL; // creare stiva pt castigatori
    Stack *lose = NULL; // creare stiva pt invinsi

    fprintf(output_file, "\n--- ROUND NO:%d\n", nr_runda);
    for(int i=0; i < no_teams/2; i++)
        {
            copy->teamName[strlen(copy->teamName)-1]='\0'; // anulam '\n' de la finalul fiecarui rand
            fprintf(output_file, "%-33s-%33s\n", copy->teamName, copy->next->teamName);
            enQueue(q, copy);
            copy = copy->next->next; 
        }

    fprintf(output_file, "\nWINNERS OF ROUND NO:%d", nr_runda);
    distribuire_pe_stive(win,lose,q);
    while( no_teams > 1)
    {
        nr_runda++;
        // stergere coada 
        popStack(&win, q);
        fprintf(output_file, "\n--- ROUND NO:%d\n", nr_runda);
        // stergere stack invinsi
        distribuire_pe_stive(win, lose,q);
        fprintf(output_file, "\nWINNERS OF ROUND NO:%d", nr_runda);
        no_teams /= 2;
    }
}
  




