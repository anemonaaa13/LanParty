# Simularea unui campionat LANParty <br><br>

## **Obiective**: <br>

• Înțelegerea conceptului de funcționare și implementare a unor structuri de date(precum liste, stive, cozi, arbori binari de căutare)<br>
• Operarea cu aceste structuri de date<br>
• Implementarea unei funcționalități practice folosind aceste concepte<br><br>

## Cerință: [CLICK](https://ocw.cs.pub.ro/courses/sda-ab/tema1)

## Structura Proiectului:
```
PA-Project-LanParty
 ├── date/
 │ ├── t1/
 │ │ ├── c.in
 │ │ ├── d.in
 │ ├── ...
 │ ├── t15/
 │ │ ├── c.in
 │ │ ├── d.in
 ├── out/
 │ ├── out1.out
 │ ├── ...
 │ ├── out15.out
 ├── rezultate/
 │ ├── r1.out
 │ ├── ...
 │ ├── r15.out
 ├── README.md
 ├── checker.sh
 ├── lanparty
 ├── lanPartylib.c
 ├── main.c
 ├── lanPartylib.h
 ├── makefile
```
## Rularea & Verificarea Programului:
Pentru a putea rula întreg programul este necesară descărcarea codului sursă atașat și executarea comenzii:
```shell
./checker.sh
```

## **Descriere detaliată**

## **1. Citirea Sarcinilor și Datelor despre Echipe**

   Codul începe prin a citi sarcinile și datele echipelor din fișiere de intrare. Funcția `ReadTasks` se ocupă de citirea sarcinilor și stocarea lor într-un vector. Echipele sunt citite dintr-un fișier de intrare și adăugate la începutul unei liste înlănțuite folosind funcția `addAtBeginning`. Fiecare echipă este reprezentată de o structură care include numele echipei, jucătorii și punctajele acestora.<br>

## **2. Organizarea și Tipărirea Listelor**

   Echipele sunt gestionate într-o listă înlănțuită. Funcția `printList` tipărește numele tuturor echipelor din listă într-un fișier de ieșire, iar funcția `totalScoreTeam` calculează scorul total al fiecărei echipe prin media punctajelor jucătorilor.<br>

## **3. Eliminarea Echipei și Gestionarea Numărului de Echipe**

   Pentru a asigura că numărul de echipe este o putere a lui 2, funcția `powerOf2` determină cea mai mare putere a lui 2 mai mică sau egală cu numărul de echipe. Funcția `DeleteTeam` elimină echipa cu cel mai mic scor, iar `FinalDelete` continuă să elimine echipe până când rămâne un număr adecvat.<br>

## **4. Simularea Rundelor de Turneu**

   Funcția `Task3` simulează desfășurarea turneului. Echipele sunt adăugate într-o coadă și se desfășoară meciuri între ele până când rămâne o singură echipă câștigătoare. În timpul fiecărei runde, echipele câștigătoare sunt mutate într-o stivă pentru a fi reutilizate în rundele următoare.<br>

## **5. Gestionarea Echipei cu Arbori BST și AVL**

   Pentru a organiza echipele după scoruri, sunt folosiți arbori binari de căutare (BST) și arbori AVL. Funcția `Task4` creează un BST cu cele mai bune 8 echipe și le tipărește într-un fișier de ieșire în ordine crescătoare a scorurilor. Funcția `Task5` folosește un arbore AVL pentru a organiza și afișa echipele la un anumit nivel.<br>

## **6. Eliberarea Memoriei**

   Pentru a preveni scurgerile de memorie, funcția `deleteList` șterge complet lista de echipe și eliberează memoria alocată pentru numele echipelor și jucătorilor.<br>

## **Taskuri**

## **Task 1: Citirea echipelor si adaugarea lor in lista:**

ReadTasks(FILE *check, int no_tasks, int Tasks[]) - Funcția citește task-urile din fișierul de intrare și le stochează în vectorul Tasks.<br>
addAtBeginning(Team **head, FILE *input_file, int no_teams) - Funcția citește echipele din fișier și le adaugă la începutul listei.<br>

## **Task 2: Calcularea scorurilor echipelor și eliminarea echipelor:**

totalScoreTeam(Team **head) - Calculează scorul total pentru fiecare echipă și îl stochează în structura echipei.<br>
FinalDelete(Team **head, int *no_teams) - Elimină echipele până când numărul echipelor rămase este o putere a lui 2.<br>

## **Task 3: Desfășurarea meciurilor și determinarea echipelor câștigătoare:**

Task3(Team *head, Team **topTeam, int nr_teams, FILE *output_file) - Desfășoară meciurile între echipe și determină echipele câștigătoare, astfel: <br>
Se va crea o coadă în care se vor pune meciurile dintre echipe.<br>
Echipele vor forma meciuri în ordinea în care se află în lista de la punctul anterior, primele două echipe vor forma primul meci (și așa mai departe).<br>
Se vor crea două stive - una pentru învinși și una pentru câștigători - ce vor conține echipele ce au pierdut, respectiv, au câștigat meciul anterior.<br>
Se vor introduce în stivă echipele în funcție de rezultatul obținut și se va adauga un punct la punctajul de echipă al echipelor ce au câștigat.<br>
In cazul unui meci in care ambele echipe au acelasi punctaj, se va alege prima echipa adaugata in meciul disputat.<br>
Se vor șterge echipele ce se găsesc în stiva de învinși. (la finalul fiecărei etape; ex: dintr-o runda cu 8 echipe, stergerea se face dupa ce au fost eliminate toate echipele.<br>
Din stiva de câștigători se vor extrage echipele și se va umple din nou coada de meciuri formându-se meciuri cu echipele consecutive (prima echipă scoasă din stivă va juca cu a doua echipa scoasă din stivă primul meci).<br>
Se vor repeta pașii enumerați pana la aflarea echipelor de pe primele 8 locuri, care vor fi salvate intr-o alta lista, dupa aflarea acestora se vor continua meciurile pana la aflarea echipei castigatoare.Rezultatele sunt scrise în fișierul de ieșire.<br>

## **Task 4: Inserarea echipelor câștigătoare în BST și afișarea acestora:**

Task4(FILE *output_file, Team* topTeam, Team** orderTeam) - Inserează ultimele 8 echipe câștigătoare într-un arbore BST și le afișează în ordinea crescătoare a scorurilor (in cazul in care doua echipe au acelasi punctaj se vor ordona in functie de nume, descrescator).<br>

## **Task 5: Inserarea echipelor în AVL și afișarea echipelor de la nivelul 2:**
Task5(FILE* output_file, Team* topTeam) - Inserează echipele câștigătoare într-un arbore AVL și afișează echipele aflate la nivelul 2 al arborelui.<br>

## **Concluzie**

Acest cod oferă o soluție completă pentru gestionarea și simularea unui turneu LAN party, de la citirea inițială a datelor până la determinarea câștigătorului final și eliberarea memoriei. Structurile de date precum liste înlănțuite, cozi, stive, BST-uri și arbori AVL sunt utilizate pentru a asigura o organizare eficientă și clară a datelor despre echipe.<br>
