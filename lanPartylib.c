#include "lanPartylib.h"

void ReadTasks(FILE *check, int no_tasks, int Tasks[])
{
    for(int i=0; i < no_tasks; i++)
        // Citeste fiecare task si il stocheaza in vectorul Tasks
        fscanf(check, "%d", &Tasks[i]);
}

// Functie pentru adaugarea echipelor la inceputul listei
void addAtBeginning(Team **head,  FILE *input_file, int no_teams)
{
    for(int i=0; i< no_teams; i++) {
        Team* newTeam = (Team*)malloc(sizeof(Team));

        int no_players; char teamName[100]; Player *jucator;

        fscanf(input_file, "%d", &no_players); // citire numar jucatori
        newTeam->no_players = no_players;

        fgetc(input_file);
        fgets(teamName, 100, input_file); // citire nume echipa
        if (teamName[strlen(teamName)-3] == ' ') { // eliminare caractere speciale si spatii suplimentare
            teamName[strlen(teamName)-3] = '\0';
        } else if (teamName[strlen(teamName)-2] = '\r') {
            teamName[strlen(teamName)-2] = '\0';
        }

        newTeam->teamName = (char*)malloc(strlen(teamName) +1 );
        strcpy(newTeam->teamName, teamName);

        newTeam->value = (Player *)malloc(no_players * sizeof(Player));
        for(int j=0; j < no_players; j++){
            char buffer[50];

            fscanf(input_file, "%s", buffer); // citire nume jucator
            newTeam->value[j].firstName = malloc(strlen(buffer) + 1); 
            strcpy(newTeam->value[j].firstName, buffer);

            fscanf(input_file, "%s", buffer); // citire prenume jucator
            newTeam->value[j].secondName = malloc(strlen(buffer) + 1);
            strcpy(newTeam->value[j].secondName, buffer);

            fscanf(input_file, "%d", &jucator->points); // citire punctaj jucator
            newTeam->value[j].points = jucator->points;
        }
        newTeam->next = *head; //  adauga noua echipa la inceputul listei
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

// Functie pentru calcularea scorului total al fiecarei echipe
void totalScoreTeam(Team **head)
{
    Team *copy = *head;

    while( copy != NULL)
    {
        float total = 0;
        for( int i=0; i < (copy->no_players); i++ )
        {
            // Calculeaza totalul punctelor pentru fiecare echipa
            total = total + copy->value[i].points;
        }

    // Calculeaza media aritmetica a punctelor si o atribuie echipei
    total = total / copy->no_players ; 
    copy->pointsTotal = total;
    copy = copy->next; // parcurgem lista de echipe
    }
}

// Functie pentru calcularea celei mai mari puteri a lui 2 mai mica sau egala cu numarul echipelor
int powerOf2(int no_teams)
{
    int n=1;

    while(2*n <= no_teams)
        n = 2 * n;
    
    int deleted_teams;
    deleted_teams = no_teams - n;
    return deleted_teams;
}

// Functie pentru gasirea scorului minim din lista de echipe
float MinScore(Team *head)
{
    Team *copy = head;

    float MinScore = head->pointsTotal;

    while( copy != NULL)
    {
        // Gaseste scorul minim din lista de echipe
        if(copy->pointsTotal < MinScore)
            MinScore = copy->pointsTotal;

        copy = copy->next; // parcurgem lista
    }
    return MinScore;
}

// Functie pentru stergerea unei echipe din lista
void DeleteTeam(Team **head)
{
    float minim = MinScore(*head);

    if(*head == NULL ) return; // daca lista e goala

    Team *copy = *head; // daca elementul de sters e capul listei
    if( copy->pointsTotal == minim ) {
        *head = (*head)->next;
        free(copy);
        return;
    }

    Team *prev = *head;
    while(copy != NULL) {
        if(copy->pointsTotal != minim) {
            prev = copy;
            copy = copy->next;
        } else {
            prev->next = copy->next;
            free(copy);
            return;
        }
    }
}

// Functie pentru stergerea echipelor pana cand numarul echipelor ramase este o putere a lui 2
void FinalDelete(Team **head, int *no_teams)
{
    Team *copy = *head;

    int n = powerOf2(*no_teams);
    (*no_teams) = (*no_teams) - n;

    for(int i=0; i < n ; i++)
        DeleteTeam(head);
}

// Functie pentru stergerea completa a listei de echipe
void deleteList(Team **head)
{
    Team *headcopy;
    while(*head!=NULL)
    {
        headcopy = (*head)->next;
        free((*head)->teamName);
        for(int i=0;i<(*head)->no_players;i++)
        {
            free((*head)->value[i].firstName);
            free((*head)->value[i].secondName);
        }
        free((*head)->value);
        free(*head);
        *head = headcopy;
    }
    *head = NULL;
}

//Functii pentru operatii cu cozi
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
    Team * temp = val;
    
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
 
    q->rear->next = temp;
    q->rear = temp;
}

void deQueue(Queue* q)
{
    if (q->front == NULL)
        return ;
 
    Team * temp = q->front;
 
    q->front = q->front->next;
 
    if (q->front == NULL)
        q->rear = NULL;
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
}

void Task3(Team *head, Team ** topTeam, int nr_teams, FILE * output_file) {
    Team * win = NULL; Team * lose = NULL; Queue * q = createQueue();
    int nr_runda = 1;
    while (head != NULL) { // Adauga toate echipele in coada
        enQueue(q, head);
        head = head->next;
    }
    while (nr_teams > 1) {  // Desfasurarea meciurilor pana cand ramane o singura echipa
        fprintf(output_file, "\r\n--- ROUND NO:%d\r\n", nr_runda);
        while (q->front != NULL) {
            Team * t1 = q->front; deQueue(q);  
            Team * t2 = q->front; deQueue(q);
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
        if (nr_teams == 16) { // Daca numarul echipelor este 16, adauga echipele castigatoare in stiva topTeam
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
        while(lose != NULL) 
            popStack(&lose);
        nr_runda++;  nr_teams /= 2;
    }
}

// Functie pentru crearea unui nod in arborele BST
BST_team* newNodeCreate( Team* value)
{
    BST_team* temp = ( BST_team* )malloc(sizeof( BST_team ));
    temp->echipa = value;
    temp->left = temp->right = NULL;
    return temp;
}

// Functie pentru inserarea unui nod in arborele BST
BST_team* insertNode( BST_team* node, Team* value)
{ 
    if (node == NULL) {
        return newNodeCreate(value);
    }
    if (value->pointsTotal > node->echipa->pointsTotal) {
        node->left = insertNode(node->left, value);
    }
    else if (value->pointsTotal < node->echipa->pointsTotal) {
        node->right = insertNode(node->right, value);
    }
    else{
        if(strcmp(value->teamName, node->echipa->teamName) < 0)
            node->right = insertNode(node->right, value);
        else
            node->left = insertNode(node->left, value);
    }
    return node;
}

// Functie pentru traversarea in-order a arborelui BST
void inOrder(BST_team* root, FILE* output_file, Team** lista)
{
    if (root != NULL) {
        inOrder(root->left, output_file, lista);;       
        pushStack(lista, root->echipa);
        fprintf(output_file, "%-34s-  %.2f\r\n", root->echipa->teamName, root->echipa->pointsTotal);
        inOrder(root->right, output_file, lista);
    }
}

void Task4(FILE* output_file, Team* topTeam, Team** orderTeam)
{
    fprintf(output_file, "\r\nTOP 8 TEAMS:\r\n");

    BST_team* root = NULL;
    while( topTeam != NULL)
    {
        root = insertNode(root, topTeam);
        topTeam = topTeam->next;
    }
    inOrder(root, output_file, orderTeam);
}

// Functie pentru calcularea inaltimii unui nod din arborele AVL
int height(AVL_Team *N) 
{ 
    if (N == NULL) 
        return 0;

    return N->height; 
} 
  
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 

// Functie pentru crearea unui nod nou in arborele AVL
AVL_Team* newNode(int key) 
{ 
    AVL_Team* node = ( AVL_Team* ) malloc(sizeof(AVL_Team)); 
    node->key = key;
    node->left = NULL; 
    node->right = NULL; 
    node->height = 1;  // nodul nou este initial adaugat ca frunza
    return(node); 
} 

// Functie pentru rotatia dreapta in arborele AVL
AVL_Team* rightRotate(AVL_Team* y) 
{ 
    AVL_Team* x = y->left; 
    AVL_Team* T2 = x->right; 
  
    // Realizarea rotatiei 
    x->right = y; 
    y->left = T2; 
  
    // Actualizarea inaltimilor 
    y->height = max(height(y->left), height(y->right)) + 1; 
    x->height = max(height(x->left), height(x->right)) + 1; 
  
    // Returnarea noii radacini 
    return x; 
} 

// Functie pentru rotatia stanga in arborele AVL
AVL_Team* leftRotate(AVL_Team* x) 
{ 
    AVL_Team* y = x->right; 
    AVL_Team* T2 = y->left; 
  
    // Realizarea rotatiei 
    y->left = x; 
    x->right = T2; 
  
    // Actualizarea inaltimilor 
    x->height = max(height(x->left), height(x->right)) + 1; 
    y->height = max(height(y->left), height(y->right)) + 1; 
  
    // Returnarea noii radacini 
    return y; 
} 

// Functie pentru obtinerea factorului de echilibrare al unui nod
int getBalance(AVL_Team* N) 
{ 
    if (N == NULL) 
        return 0; 

    return height(N->left) - height(N->right); 
} 

// Functie pentru inserarea unui nod în arborele AVL
AVL_Team* insert(AVL_Team* node, int key) 
{ 
    if (node == NULL) 
        return(newNode(key)); // inserare BST normala
  
    if (key < node->key) 
        node->left  = insert(node->left, key); 
    else if (key > node->key) 
        node->right = insert(node->right, key); 
      
    // Actualizarea inaltimii acestui nod stramos 
    node->height = 1 + max(height(node->left), height(node->right)); 
  
    // Obținerea factorului de echilibrare al acestui nod stramos
    // pentru a verifica daca acest nod a devenit dezechilibrat 
    int balance = getBalance(node); 
  
    // Daca acest nod devine dezechilibrat, atunci 
    // exista 4 cazuri 
  
    // Cazul Stanga - Stanga ( LL ) 
    if (balance > 1 && key < node->left->key) 
        return rightRotate(node); 
    // Cazul Dreapta - Dreapta ( RR )
    if (balance < -1 && key > node->right->key) 
        return leftRotate(node); 
    // Cazul Stanga - Dreapta ( LR )
    if (balance > 1 && key > node->left->key) 
    { 
        node->left =  leftRotate(node->left); 
        return rightRotate(node); 
    } 
    // Cazul Dreapta - Stanga ( RL )
    if (balance < -1 && key < node->right->key) 
    { 
        node->right = rightRotate(node->right); 
        return leftRotate(node); 
    } 
    // returnarea pointer-ului nodului (nemodificat)
    return node; 
} 

// Functie pentru afisarea echipelor din lista la o anumita pozitie
void printFromList(Team * list, int position, FILE * file) {

    for (int i = 0; i < position; i++) {
        list = list->next;
    }
    fprintf(file, "%s\r\n", list->teamName);
}

// Functie pentru afisarea AVL-ului la un anumit nivel
void printAVL(AVL_Team* root, int level, Team * list, FILE * file)
{
    if (root == NULL)
        return;
    if (level == 1)
        printFromList(list, root->key, file);
    else if (level > 1) {
        printAVL(root->left, level - 1, list, file);
        printAVL(root->right, level - 1, list, file);
    }
}

void Task5(FILE* output_file, Team* topTeam)
{
    fprintf(output_file, "\r\nTHE LEVEL 2 TEAMS ARE:\r\n");

    AVL_Team* root = NULL;
    Team * list = NULL;
    int nr_teams = 8;

    while(topTeam != NULL) {
        pushStack(&list, topTeam);
        topTeam = topTeam->next;
    }

    for (int i = 0; i < nr_teams; i++) {
        root = insert(root, i);
    }

    int level = 2;
    printAVL(root, level + 1, list, output_file);
    
}