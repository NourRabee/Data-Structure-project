#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// Constants for status in hash table record
#define EMPTY 0
#define INSERT 1
#define DELETE 2

typedef struct info
{
    char name[20];
    char gender[5];
    int dateOfBirth;
    int dateOfAdmission;
    char disease[30];
    char address[20];
    char bloodType[10];
    int status;

} info;

typedef struct AVLnode *AVLNode;

struct AVLnode
{
    info data;
    AVLNode Left;
    AVLNode Right;
    int Height; //Balance information
};

typedef struct hashTable HT;

struct hashTable
{
    int size;
    int numOfRecords;
    info *records;
};

HT table = {0, 0, NULL};        // initializing the table with nulls
int hashTableLoaded = 0;        // this will remain zero until data loaded to the hash table
AVLNode tree=NULL;              // initializing the AVL tree with nulls

// AVL FUNCTIONS
int isEmpty(AVLNode );
AVLNode MakeEmpty( AVLNode  );
AVLNode createNewNode(info );
AVLNode search( char*, AVLNode  );
AVLNode FindMin( AVLNode);
AVLNode FindMax( AVLNode);
int Height( AVLNode);
int Max( int, int );
AVLNode SingleRotateWithLeft( AVLNode);
AVLNode SingleRotateWithRight( AVLNode);
AVLNode DoubleRotateWithLeft( AVLNode );
AVLNode DoubleRotateWithRight( AVLNode);
AVLNode Insert( info, AVLNode);
AVLNode elimination(AVLNode, info);
void readFile();
char * make_dashes(int);
void printHelper();
void printTreeInorder(AVLNode);
void printTree(AVLNode);
void SaveOnFile(AVLNode,FILE * );
void printDisease(char*,AVLNode );
void ListPatientsSameIllness(char *,AVLNode );
void updateNode(AVLNode );

//HASH TABLE FUNCTIONS

int isPrime(int num);
int requiredTableSize(int );
int hashFunction(HT, char *);
int quadraticHashing(HT, char *);
void reHash(HT *);
void insertToTable(HT *,info );
int findRecord(HT, char *);
void deleteFromTable(HT, char *);
void readTableFromFile(HT *);
void SaveTableToFile (HT );
void printTable(HT );
void printTableSize(HT );
void printHashFunction(HT );

int main()
{
    int option;

    do
    {
        printf("    \t\t\t\t\t\t     Main Menu\n\n");                   // displaying the menu
        printf("\t\t\t\t\t   1)Read Patients data from file\n");
        printf("\t\t\t\t\t   2)Print patients data\n");
        printf("\t\t\t\t\t   3)Search for patient and update it's data\n");
        printf("\t\t\t\t\t   4)Insert a new patient\n");
        printf("\t\t\t\t\t   5)Delete a patient\n");
        printf("\t\t\t\t\t   6)List all patients that have the same illness\n");
        printf("\t\t\t\t\t   7)Transfer patient's data to file\n");
        printf("\t\t\t\t\t   8)Load patients data from file to the hash table\n");
        printf("\t\t\t\t\t   9)Print table size\n");
        printf("\t\t\t\t\t   10)Print used hash function\n");
        printf("\t\t\t\t\t   11)Display hash table on the screen\n");
        printf("\t\t\t\t\t   12)Insert a new record to the hash table\n");
        printf("\t\t\t\t\t   13)Delete a record from the hash table\n");
        printf("\t\t\t\t\t   14)Search for a specific record in the hash table\n");
        printf("\t\t\t\t\t   15)Transfer patient's data in hash table  to file\n");
        printf("\t\t\t\t\t   16)Exit\n");

        printf("\n\n\t\t\t\t\t  Enter you choice please: ");

        scanf("%d",&option);            // getting the user's choice

        switch (option)
        {
            char patient[30];
            int Dates;
        //char countyFile[100];

        case 1:
            system("cls");          // clear the output screen
            readFile();        // reading data from file and saving it in tree T
            printf("Reading from file has done successfully\n");
            printf("\n\nPress any key to return to main menu\n");
            getch();
            system("cls");          // clear screen
            break;

        case 2:
            system("cls");          // clear the output screen
            printTree(tree);     // displaying tree printing choices menu
            printf("\n\nPress any key to return to main menu\n");
            getch();
            system("cls");          // clear screen
            break;

        case 3:
            system("cls");          // clear screen
            printf("Enter the patient's name that you are looking for please:\n");

            fflush(stdin);      // flushing/clear the stdin from any previous '\n'
            fgets(patient,sizeof(patient),stdin);      // getting the patient's name from user
            strtok(patient,"\n");
            AVLNode key = search(patient,tree);      // finding this patient's node in the tree

            printf("\n");       // new line

            if (key == NULL)        // if the key == NULL, then county does not exist, so show an error message
                printf("Patient \"%s\" does not found!\n", patient);
            else                    // if exist, print its data
                updateNode(key);

            printf("\n\nPress any key to return to main menu\n");       // returning to main menu
            getch();

            system("cls");          // clear screen
            break;

        case 4:
            system("cls");          // clear screen

            info data;
            Dates=0;

            printf("Enter the patient name that you want to insert please:\n");
            fflush(stdin);          // flushing the stdin from any previous '\n'
            fgets(patient,sizeof(patient),stdin);      // getting the patient's name from user
            strtok(patient,"\n");
            strcpy(data.name,patient);

            printf("\nEnter the patient's gender please:\n");
            fflush(stdin);
            fgets(patient,sizeof(patient),stdin);      // getting the patient's name from user
            strtok(patient,"\n");
            strcpy(data.gender,patient);

            printf("\nEnter the patient's disease please:\n");
            fflush(stdin);
            fgets(patient,sizeof(patient),stdin);      // getting the patient's name from user
            strtok(patient,"\n");
            strcpy(data.disease,patient);

            printf("\nEnter the patient's address please:\n");
            fflush(stdin);
            fgets(patient,sizeof(patient),stdin);      // getting the patient's name from user
            strtok(patient,"\n");
            strcpy(data.address,patient);

            printf("\nEnter the patient's blood type please:\n");
            fflush(stdin);
            fgets(patient,sizeof(patient),stdin);      // getting the patient's name from user
            strtok(patient,"\n");
            strcpy(data.bloodType,patient);

            printf("\nEnter the patient's date of birth please:\n");
            fflush(stdin);
            fgets(patient,sizeof(patient),stdin);      // getting the patient's name from user
            data.dateOfBirth=(int)strtol(patient,NULL,10);

            printf("\nEnter the patient's date of admission please:\n");
            fflush(stdin);
            scanf("%d",&Dates);
            data.dateOfBirth=(int)strtol(patient,NULL,10);

            AVLNode newNode=createNewNode(data);
            tree=Insert(newNode->data,tree);  // inserting Patient's data to the tree

            printf("\nPatient has inserted successfully\n");

            printf("\n\nPress any key to return to main menu\n");   // returning to main menu
            getch();

            system("cls");          // clear screen
            break;

        case 5:
            system("cls");          // clear screen

            if(tree != NULL)    // if the tree is not empty
            {
                printf("Enter the patient's name that you want to delete please:\n");

                fflush(stdin);   // flushing the stdin from any previous '\n'
                fgets(patient,sizeof(patient),stdin);      // getting the patient's name from user
                strtok(patient,"\n");
                AVLNode deleteNode;

                deleteNode=search(patient,tree);      // deleting the node
                elimination(tree,deleteNode->data);

                printf("\nPatient has deleted successfully\n");
                printTree(tree);
            }

            else               // if patient does not exist, show an error message
                printf("No patient to delete!");

            printf("\n\nPress any key to return to main menu\n");       // returning to main menu
            getch();

            system("cls");          // clear screen
            break;

        case 6:
            system("cls");          // clear screen

            if(tree != NULL)
            {
                printf("Please enter name of the illness:\n");
                fflush(stdin); //clear stdin from any previous"\n"
                fgets(patient,sizeof(patient),stdin);      // getting the patient's name from user
                strtok(patient,"\n");
                ListPatientsSameIllness(patient,tree);

            }
            else
                printf("Oops!This type of illness is not common in our hospital.");

            printf("\n\nPress any key to return to main menu\n");   // returning to main menu
            getch();
            system("cls");          // clear screen
            break;

        case 7:
            system("cls");          // clear screen

            if (tree != NULL)
            {
                FILE *out = fopen("patients_hash.txt","w");
                while (out == NULL)
                {
                    system("cls");// clear screen
                    printf("Error! File not Found!\n\n");
                }

                SaveOnFile(tree,out);
                printf("\nSaving on file has done successfully!\n");
                fclose(out);
            }
            else
                printf("No patients to list them on File!");


            printf("\n\nPress any key to return to main menu\n");
            getch();
            system("cls");      // clear screen
            break;

        case 8:
            system("cls");      // clear screen

            if (tree != NULL)          // if the tree is not empty
            {

                table.size = 0;             // reset hash table to load new data
                table.numOfRecords = 0;
                free(table.records);        // deleting the old records table
                table.records = NULL;

                readTableFromFile(&table);       // reading the data from file and saving it to the hash table

                hashTableLoaded = 1;            // this means that the data has been loaded to the hash table
            }
            else                    // if tree is empty, show an error message
                printf("No patients to load, tree is empty!");

            printf("\n\nPress any key to return to main menu\n");       // returning to main menu
            getch();
            system("cls");

            break;

        case 9:
            system("cls");          // clear screen

            if (hashTableLoaded)    // if data has read from file and  has loaded to the hash table
                printTableSize(table);      // print table size
            else                    // if data has not read from file or the hash table has not loaded yet, then show an error message
                printf("No data has been loaded to the hash table!");

            printf("\n\nPress any key to return to main menu\n");   // returning to main menu
            getch();
            system("cls");          // clear screen
            break;


        case 10:
            system("cls");          // clear screen

            if (hashTableLoaded)            // if data has read from file and the hash table has loaded
                printHashFunction(table);       // printing the hash function
            else                             // if data has not read from file or the hash table has not loaded yet, then show an error message
                printf("No data has been loaded to the hash table!");

            printf("\n\nPress any key to return to main menu\n");       // returning to main menu
            getch();
            system("cls");          // clear screen
            break;


        case 11:
            system("cls");          // clear screen

            if (hashTableLoaded)        // if data has read from file and the hash table has loaded
                printTable(table);      // printing the hash table on the screen
            else                        // if data has not read from file or the hash table has not loaded yet, then show an error message
                printf("No data has been loaded to the hash table!");

            printf("\n\nPress any key to return to main menu\n");       // returning to main menu
            getch();
            system("cls");          // clear screen
            break;


        case 12:
            system("cls");          // clear screen

            if (hashTableLoaded)    // if data has read from file and the hash table has loaded
            {

                info record;      // creating a record to save the data in, and to insert it to the hash table

                printf("Enter the patient name that you want to insert please:\n");
                fflush(stdin);          // flushing the stdin from any previous '\n'
                fgets(patient,sizeof(patient),stdin);      // getting the patient's name from user
                strtok(patient,"\n");
                strcpy(record.name,patient);

                printf("\nEnter patient's gender please:\n");
                fflush(stdin);
                fgets(patient,sizeof(patient),stdin);      // getting the patient's name from user
                strtok(patient,"\n");
                strcpy(record.gender,patient);

                printf("\nEnter patient's disease please:\n");
                fflush(stdin);
                fgets(patient,sizeof(patient),stdin);      // getting the patient's name from user
                strtok(patient,"\n");
                strcpy(record.disease,patient);

                printf("\nEnter  patient's address please:\n");
                fflush(stdin);
                fgets(patient,sizeof(patient),stdin);      // getting the patient's name from user
                strtok(patient,"\n");
                strcpy(record.address,patient);

                printf("\nEnter patient's blood type please:\n");
                fflush(stdin);
                fgets(patient,sizeof(patient),stdin);      // getting the patient's name from user
                strtok(patient,"\n");
                strcpy(record.bloodType,patient);

                printf("\nEnter patient's date of birth please:\n");
                fflush(stdin);
                fgets(patient,sizeof(patient),stdin);      // getting the patient's name from user
                record.dateOfBirth=(int)strtol(patient,NULL,10);

                printf("\nEnter the patient's date of admission please:\n");
                fflush(stdin);
                fgets(patient,sizeof(patient),stdin);      // getting the patient's name from user
                record.dateOfAdmission=(int)strtol(patient,NULL,10);

                insertToTable(&table, record);      // inserting the record to the hash table

                printf("\n\nRecord inserted successfully\n");

            }

            else // if data has not read from file or has not loaded to the hash table yet, then show an error message
                printf("No data loaded to the hash table!");

            printf("\n\nPress any key to return to main menu\n");       // returning to main menu
            getch();
            system("cls");          // clear screen
            break;

        case 13:
            system("cls");      // clear screen

            if (hashTableLoaded)    // if data has read from file and the hash table has loaded
            {

                printf("Enter the patient's name that you want to delete please:\n");
                fflush(stdin);                // getting the name from user
                fgets(patient,30,stdin);
                patient[strcspn(patient, "\n")] = '\0'; // removing \n from the array
                deleteFromTable(table, patient);     // deleting the record that has that ID

                printf("\n\nRecord deleted successfully\n");
            }
            else                    // if data has not read from file or the hash table has not loaded yet, then show an error message
                printf("No data loaded to the hash table!");

            printf("\n\nPress any key to return to main menu\n");       // returning to main menu
            getch();
            system("cls");      // clear screen
            break;


        case 14:
            system("cls");      // clear screen

            if (hashTableLoaded)        // if data has read from file and the hash table has loaded
            {

                printf("Enter the patient's name that you are looking for please:\n");
                fflush(stdin);        // getting name from user
                gets(patient);

                int key = findRecord(table, patient);        // searching for the record in the hash table

                if (key != -1)          // if exist, print its data
                {
                    // printing record's data
                    printHelper();
                    printf("%-20s%-15s%-20d%-20d%-15s%-15s%-10s\n",table.records[key].name,table.records[key].gender
                           ,table.records[key].dateOfBirth,table.records[key].dateOfAdmission,table.records[key].disease,
                           table.records[key].address,table.records[key].bloodType);
                }
                else                    // if the record is not found, show an error message
                    printf("No such record!");
            }
            else                        // if data has not read from file or the hash table has not loaded yet, then show an error message
                printf("No data loaded to the hash table!");

            printf("\n\nPress any key to return to main menu\n");       // returning to main menu
            getch();
            system("cls");      // clear screen
            break;

        case 15:
            system("cls");      // clear screen

            if (hashTableLoaded)            // if data has read from file and the hash table has loaded
                SaveTableToFile(table);    // Save hash table data to file
            else                            // if data has not read from file or not loaded yet to hash table, then show an error message
                printf("No data loaded to the hash table!");

            printf("\n\nPress any key to return to main menu\n");       // returning to main menu
            getch();
            system("cls");      // clear screen
            break;

        case 16:                // exit
            system("cls");      // clear screen
            break;

        default:                // if any other option has chosen, show an error message
            system("cls");      // clear screen
            printf("\t\t\t\t No such option! Enter your choice again please:\n\n");


        }
    }
    while (option != 16);

    return 0;
}

int isEmpty(AVLNode T)
{
    return T==NULL;
}

AVLNode MakeEmpty( AVLNode T )
{
    if( T != NULL )
    {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}

AVLNode createNewNode(info data)
{

    AVLNode T= (AVLNode)malloc(sizeof(struct AVLnode));
    if(T == NULL)
        printf("out of space!!");
    else
    {
        T->Left = T->Right = NULL;
        T->Height=0;

        // assigning data to the new node
        strcpy(T->data.name,data.name);
        strcpy(T->data.gender,data.gender);
        strcpy(T->data.bloodType,data.bloodType);
        T->data.dateOfAdmission=data.dateOfAdmission;
        T->data.dateOfBirth=data.dateOfBirth;
        strcpy(T->data.address,data.address);
        strcpy(T->data.disease,data.disease);
    }

    return T;
}

AVLNode search( char *str, AVLNode T )
{
    // this function is to search in the tree for the name as the key

    if(T == NULL)// if the tree has no nodes return NULL
    {
        return NULL;
        printf("the patient you are searching for does not exist\n");
    }

    else if(strcmp(str,T->data.name )> 0)
        return search(str,T->Right);

    else if (strcmp(str,T->data.name)<0)
        return search(str,T->Left);

    return T;

}
AVLNode FindMin( AVLNode T )
{
    if( T == NULL )
        return NULL;
    else if( T->Left == NULL )
        return T;
    else
        return FindMin( T->Left );
}
int Height( AVLNode P )
{
    if( P == NULL )
        return -1;
    else
        return P->Height;
}


int Max( int Lhs, int Rhs )
{
    return Lhs >= Rhs ? Lhs : Rhs;
}

AVLNode SingleRotateWithLeft( AVLNode K2 )
{
    AVLNode  K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;
}
AVLNode SingleRotateWithRight( AVLNode K1 )
{
    AVLNode K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;
}
AVLNode DoubleRotateWithLeft( AVLNode K3 )
{
    K3->Left = SingleRotateWithRight( K3->Left );
    return SingleRotateWithLeft( K3 );
}
AVLNode DoubleRotateWithRight( AVLNode K1 )
{
    K1->Right = SingleRotateWithLeft( K1->Right );
    return SingleRotateWithRight( K1 );
}
AVLNode Insert( info data, AVLNode T )
{
    if(isEmpty(T))
        return createNewNode(data);

    else if(strcmp(data.name,T->data.name )> 0)
    {
        T->Right=Insert(data,T->Right);//recursion call

        if( Height( T->Right ) - Height( T->Left ) == 2 )
        {
            if(strcmp(data.name,T->Right->data.name )> 0)
                T = SingleRotateWithRight(T);
            else
                T= DoubleRotateWithRight(T);
        }

    }
    else if (strcmp(data.name,T->data.name)<0)
    {
        T->Left=Insert(data,T->Left);
        if( Height( T->Left ) - Height( T->Right ) == 2 )
        {
            if(strcmp(data.name,T->Left->data.name)<0)
                T =SingleRotateWithLeft( T );
            else
                T = DoubleRotateWithLeft( T );
        }

    }


    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;

    return T;
}
AVLNode elimination(AVLNode T, info data) // this function is to delete a node from the tree
{

    if(isEmpty(T))// if the tree has no nodes to delete, return NULL
        return NULL;

    else if(strcmp(data.name,T->data.name )> 0)// if the value we want to delete is less than the node we are standing at, go right
        T->Right=elimination(T->Right,data);//recursion call

    else if (strcmp(data.name,T->data.name)<0)// if the value we want to delete is less than the node we are standing at, go left
        T->Left=elimination(T->Left,data);
    else
    {
        // NO CHILDRENS
        if(T->Right==NULL && T->Left==NULL)
        {
            free(T);
            T=NULL;
        }

        //ONE RIGHT CHILDREN
        else if(T->Right!=NULL && T->Left == NULL)
        {
            AVLNode temp=T;
            T = T->Right;
            free(temp);
        }

        //ONE LEFT CHILDREN
        else if(T->Right==NULL && T->Left != NULL)
        {
            AVLNode temp = T;
            T = T->Left;
            free(temp);
        }

        //TWO CHILDRENS LEFT AND RIGHT
        else
        {
            //The node that can be replaced by the root is the minimum node in its subtree

            AVLNode minRight= FindMin(T->Right);
            T->data=minRight->data;
            T->Right=elimination(T->Right,minRight->data);

        }
    }
    return T;
}
void readFile()
{

    FILE *in = fopen("patients.txt","r");
    while (in == NULL)
    {
        system("cls");// clear screen
        printf("Error! File not Found!\n\n");
    }



    char line[300];
    while(fgets(line,100,in))
    {
        char *split="#\n";
        char *token=strtok(line,split);
        int word=0;//flag
        info datum;

        while(token != NULL)
        {

            if(word==0)
                strcpy(datum.name,token);

            else if(word==1)//gender consists if single char what shall i do ?
                strcpy(datum.gender,token);

            else if(word==2)
            {
                datum.dateOfAdmission=0;
                for(int i=0; token[i]!='\0'; i++) //'0'=48 "ASCII CODE" example token[1]=49
                    datum.dateOfAdmission=(token[i]-48)+(datum.dateOfAdmission*10);
            }
            else if(word==3)
            {
                datum.dateOfBirth=0;
                for(int i=0; token[i]!='\0'; i++)
                    datum.dateOfBirth=(token[i]-48)+(datum.dateOfBirth*10);//conversion from binary to decimal
            }

            else if(word==4)
                strcpy(datum.disease,token);

            else if(word==5)
                strcpy(datum.address,token);

            else if(word==6)
                strcpy(datum.bloodType,token);

            word++;

            if(word==7)
            {
                tree=Insert(datum,tree);
                word=0;
            }


            token=strtok(NULL,split);
        }

    }
    fclose(in);
}
char * make_dashes(int length)
{
    char *dashes = malloc(length+1);
    for(int i=0; i<length; i++)
        dashes[i]='-';
    dashes[length]='\0';
    return dashes;
}

void printHelper()
{
    printf("\n\n\n\n");
    printf("%-20s%-15s%-20s%-20s%-15s%-15s%-10s\n","Name","Gender","Date Of Birth","Date of Admission","Disease","Address","Blood Type");
    printf("%-20s%-15s%-20s%-20s%-15s%-15s%-10s\n",make_dashes(15),make_dashes(8),make_dashes(14),make_dashes(17),make_dashes(7),make_dashes(7),make_dashes(10));

}
void printTreeInorder(AVLNode root)
{
    if (root == NULL)
        return;
    /* first recur on left child */
    printTreeInorder(root->Left);

    /* then print the data of node */
    printf("%-20s%-15s%-20d%-20d%-15s%-15s%-10s\n",root->data.name,root->data.gender,root->data.dateOfBirth,root->data.dateOfAdmission,root->data.disease,root->data.address,root->data.bloodType);

    /* now recur on right child */
    printTreeInorder(root->Right);
}
void printTree(AVLNode root)
{
    printHelper();
    printTreeInorder(root);
}
void SaveOnFile(AVLNode t,FILE *out )
{
    if(t!=NULL)
    {
        SaveOnFile(t->Left,out);

        fprintf(out,"%s/%s/%d/%d/%s/%s/%s\n",t->data.name,t->data.gender,t->data.dateOfAdmission,t->data.dateOfBirth,t->data.disease,t->data.address,t->data.bloodType);

        SaveOnFile(t->Right,out);

    }
}
void printDisease(char *str,AVLNode T)
{
    if(T == NULL)
        return;

    printDisease(str,T->Left);
    if(strcmp(str,T->data.disease)==0)
    {
        printf("%-20s%-15s%-20d%-20d%-15s%-15s%-10s\n",T->data.name,T->data.gender,T->data.dateOfBirth,T->data.dateOfAdmission,T->data.disease,T->data.address,T->data.bloodType);
    }
    printDisease(str,T->Right);


}
void ListPatientsSameIllness(char *str,AVLNode root)
{
    printHelper();
    printDisease(str,root);

}
void updateNode(AVLNode target)
{
    int option;

    AVLNode copy = createNewNode(target->data);


    do
    {
        printf("1.Name\n2.Gender\n3.Date of birth\n4.Date of admission\n5.Disease\n6.Address\n7.Blood type\n8.Exit\n");
        printf("\nPlease enter the number of info you desire to modify it:\n");

        char newData[30];
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            system("cls");//clear screen from any previous"\n"
            printf("Please enter new name:\n");
            fflush(stdin);
            fgets(newData,sizeof(newData),stdin);      // getting the patient's name from user
            strtok(newData,"\n");
            strcpy(copy->data.name,newData);
            printf("\n\nPress any key to return to choices \n");
            getch();
            system("cls");

            break;

        case 2:
            system("cls");
            printf("Please enter new gender:\n");
            fflush(stdin);
            fgets(newData,sizeof(newData),stdin);      // getting the patient's name from user
            strtok(newData,"\n");
            strcpy(copy->data.gender,newData);
            printf("\n\nPress any key to return to choices\n");
            getch();
            system("cls");
            break;

        case 3:
            system("cls");
            printf("Please enter new date of birth\n");
            fgets(newData,sizeof(newData),stdin);      // getting the patient's name from user
            copy->data.dateOfBirth=(int)strtol(newData,NULL,10);
            printf("\n\nPress any key to return to choices\n");
            getch();
            system("cls");
            break;

        case 4:
            system("cls");
            printf("Please enter new date of admission\n");
            fgets(newData,sizeof(newData),stdin);      // getting the patient's name from user
            copy->data.dateOfAdmission=(int)strtol(newData,NULL,10);
            printf("\n\nPress any key to return to choices\n");
            getch();
            system("cls");

            break;

        case 5:
            system("cls");
            printf("Please enter new disease:\n");
            fflush(stdin);
            fgets(newData,sizeof(newData),stdin);      // getting the patient's name from user
            strtok(newData,"\n");
            strcpy(copy->data.disease,newData);
            printf("\n\nPress any key to return to choices\n");
            getch();
            system("cls");
            break;

        case 6:
            system("cls");
            printf("Please enter new address\n");
            fflush(stdin);
            fgets(newData,sizeof(newData),stdin);      // getting the patient's name from user
            strtok(newData,"\n");
            strcpy(copy->data.address,newData);
            printf("\n\nPress any key to return to choices\n");
            getch();
            system("cls");
            break;

        case 7:
            system("cls");
            printf("Please enter new blood type\n");
            fflush(stdin);
            gets(newData);
            strcpy(copy->data.bloodType,newData);
            printf("\n\nPress any key to return to choices\n");
            getch();
            system("cls");
            break;
        case 8:
            elimination(tree,target->data);
            Insert(copy->data,tree);
            break;
        default:
            system("cls");
            printf(" Wrong choice, Please enter a correct choice\n");
            printf("\n\nPress any key to return to choices\n");
            getch();
            system("cls");
        }
    }
    while(option != 8);
    printTree(tree);
}

int isPrime(int num)            // this function will check if the given number is prime or not
{
    int i;

    for(i = 2 ; i <= num/2 ; i++)   // for i = 2 to num/2 if i divides num then num is not prime
        if (num % i == 0)
            return 0;

    return 1;                       // if the loop ended with no i divides num, then num is prime
}
int requiredTableSize(int n)
{
    // this function will return the required table size for the given n size of data (which is first prime > 2n)

    int requiredTableSize = 2*n + 1;    // starting from first number after 2n

    while(!isPrime(requiredTableSize))  // finding the first prime after 2n
        requiredTableSize++;

    return requiredTableSize;
}
int hashFunction(HT table, char *name)
{
    // hashing function
    int nameInAscii=0;
    for(int i=0 ; i<sizeof(name); i++)
    {
        int num =(int)name[i];
        nameInAscii=nameInAscii+num;
    }

    return (nameInAscii) % table.size;             // name mod table size
}
int quadraticHashing(HT table, char *name)      // quadratic probing function
{

    int i = 1;

    int index = hashFunction(table, name);    // find the suitable index for the given ID
    int quadIndex = index;

    while(table.records[quadIndex].status == INSERT)    // if that index is busy, keep searching for another quadratically
    {

        quadIndex = (index + i*i) % table.size;         // searching for another index quadratically ( f(x) = (h(x) + i*i) % table size )
        i++;
    }

    return quadIndex;
}

void reHash(HT *table)              // rehashing function
{

    int oldTableSize = (*table).size;                       // save the old table size in this variable
    int newTableSize = requiredTableSize(oldTableSize);     // find the new required table size->New size = the first prime > (old size * 2)
    (*table).size = newTableSize;                           // change the table size to the new required one

    info (*temp) = (*table).records;                        // saving the records in a temporary storage
    (*table).records = (info*)calloc(newTableSize, sizeof(info)); // creating new record list with the new table size

    for (int i = 0 ; i < oldTableSize ; i++)        // re-inserting the values from the old hash table to the new one
        if( temp[i].status == INSERT)
            insertToTable(table, temp[i]);

    free(temp);
    // deleting the old hash table
}
void insertToTable(HT *table,info record)
{
    // this function is to insert a new record to the hash table

    (*table).numOfRecords++;                    // increment the number of records by 1

    if ( (*table).size < requiredTableSize( (*table).numOfRecords) )// if the current table size is less than the required one, rehash the table
        reHash(table);

    record.status = INSERT;                     // set the added record's status to "INSERT" status

    int index = quadraticHashing(*table,record.name);        // find a suitable position for the new record

    (*table).records[index] = record;                       // insert the new record to the suitable position
}



int findRecord(HT table, char *name)                // this function is to search the table for a record (the name is the key)
{
    int i = 1;
    int index = hashFunction(table,name);        // find the position of the record
    int quadIndex = index;

    while(table.records[quadIndex].status != EMPTY)
    {
        /* if the position founded previously does not contain the target then keep searching for it quadratically */
        if (table.records[quadIndex].status != DELETE && (strcmp(table.records[quadIndex].name,name)==0))
            // if found, return its index
            return quadIndex;

        else // if not found, keep searching until finding it or reaching the end of the hash table
        {
            quadIndex = (index + i*i) % table.size;
            i++;
        }
    }

    return -1;// if this statement reached, then the record is not found, so return -1
}
void deleteFromTable(HT table, char *name)     // this function is to delete a record from the hash table (name is the key here)
{

    int index = findRecord(table, name);     // find the position of the record that we want to delete
    printf("%d\n",index);

    if (index != -1)                            // if found, delete it by setting its status to "DELETE" status
        table.records[index].status = DELETE;

}

void readTableFromFile(HT *table)
{
    // this function will read data from file and insert it into the given hash table

    FILE *in = fopen("patients_hash.txt","r");// opening the file for reading and splitting

    if(in == NULL)                      // if file can't be open, show an error message
    {
        system("cls"); // clear screen
        printf("Error!File is not Found, you must fill it with tree data!\n\n");
        return;
    }

    char line[100];
    int numberOfLines = 0;

    while (fgets(line,100,in) != NULL)  // counting the number of lines (size of data) in the file
        numberOfLines++;

    (*table).size= requiredTableSize(numberOfLines);// setting the table size to the required size for this data
    (*table).records = (info*)calloc((*table).size,sizeof(info));// creating a record list and give each record and initial values"NULL"

    /*The C library function void *calloc(size_t nitems, size_t size) allocates the requested memory and returns
     a pointer to it. The difference in malloc and calloc is that malloc does not set the memory to zero
     where as calloc sets allocated memory to zero.*/

    rewind(in);// returning the file pointer "in"  to indicates at the beginning of the file

    while (fgets(line,100,in) != NULL)       // reading data from file line by line until reaching NULL (end of file)
    {
        /*strtok returns a String*/

        char *name = strtok(line,"/");       // cutting the first value (name) depending on '/'
        char *gender = strtok(NULL,"/");     // cutting the second value (gender) depending on '/'
        char *strDateOfBirth = strtok(NULL,"/");      // cutting the third value (date of birth) depending on '/'
        char *strDateOfAdmission= strtok(NULL,"/");   // cutting the fourth value (date of admission) depending on '/'
        char *disease =strtok(NULL,"/");         //cutting the fifth value(disease)depending on '/'
        char *address=strtok(NULL,"/");       //cutting the sixth value(address)depending on '/'
        char *bloodType=strtok(NULL,"/\n"); //cutting the seventh value(blood type)depending on '/' and ('\n' for end of line)

        info record;         // creating a record to save the data in

        strcpy(record.name,name);        // save the name in record.name
        strcpy(record.gender, gender);   // save the gender in record.gender
        record.dateOfBirth = atoi(strDateOfBirth);      // convert the string value to integer value and save it in record.dateOfBirth
        record.dateOfAdmission = atoi(strDateOfAdmission);// convert the string value to integer value and save it in record.dateOfAdmission
        strcpy(record.disease,disease);     // save the disease in record.disease
        strcpy(record.address,address);    // save the address in record.address
        strcpy(record.bloodType,bloodType);   // save the bloodType in record.bloodType

        insertToTable(table, record);   // insert the read record to the hash table
    }

    printf("\nData loaded successfully\n");

    fclose(in);         // close the file
}

void SaveTableToFile (HT table)
{
    // this function will save the data of hash table to the file (without spaces "without empty spots")

    FILE *out = fopen("patients_hash.data", "w");       // opening the file for writing

    int i;

    for(i = 0 ; i < table.size ; i++)           // printing the table to the file
        if(table.records[i].status == INSERT)   // without the spaces or the deleted values
            fprintf(out,"%s/%s/%d/%d/%s/%s/%s\n", table.records[i].name,table.records[i].gender, table.records[i].dateOfBirth, table.records[i].dateOfAdmission,table.records[i].disease,table.records[i].address,table.records[i].bloodType);

    fclose(out);
}
void printTable(HT table)
{
    // this function will display the table on the screen (including empty spots)
    int i;

    printf("note: the data will be showed in the following form:\n");
    printf("index/Name/Gender/Date of Birth/Date of Admission/Disease/Address/Blood type/Entry Status\n\n\n");

    for(i = 0 ; i < table.size ; i++)// printing all the data in the table
    {
        if (table.records[i].status != EMPTY )
            printf("(index = %d):  %s / %s / %d / %d / %s / %s / %s   (status = %d)\n",i, table.records[i].name,table.records[i].gender, table.records[i].dateOfBirth, table.records[i].dateOfAdmission, table.records[i].disease,table.records[i].address,table.records[i].bloodType,table.records[i].status);
        else
            printf("(index = %d):\n", i);
    }
}

void printTableSize(HT table)
{
    // this function will display the table size on the screen

    printf("Table size is %d\n",table.size);
}

void printHashFunction(HT table)
{
    // this function will display the hash function used on the screen

    printf("Function used for hashing:\n");
    printf("h(x) = x %% %d\n\n",table.size);      // "%%" has used to display one '%'

    printf("function used for quadratic probing:\n");
    printf("f(x) = (h(x) + i*i) %% %d = (x %% %d + i*i) %% %d\n",table.size, table.size, table.size);      // function used for quadratic probing
}






