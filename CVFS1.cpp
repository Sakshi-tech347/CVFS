//////////////////////////////////////////////////////////
//
//  Header File Inclusion
//
//////////////////////////////////////////////////////////

#include <stdio.h>
#include<string.h>
#include<stdlib.h>

//////////////////////////////////////////////////////////
//
//  User Defined Macros
//
//////////////////////////////////////////////////////////


#define MAXOPENFILES 20
#define MAXINODES 5

//////////////////////////////////////////////////////////
//
//  User Defined Structures
//
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
//
//  Structure Name :    BootBlock
//  Description :       Holds the information to boot the OS
//
//////////////////////////////////////////////////////////
struct BootBlock
{
    char Information[100];
};

//////////////////////////////////////////////////////////
//
//  Structure Name :    SuperBlock
//  Description :       Holds the information about the file system
//
//////////////////////////////////////////////////////////  

struct SuperBlock
{
    int freeInode;
    int TotalInode;

};
//////////////////////////////////////////////////////////
//
//  Structure Name :    Inode
//  Description :       Holds the information about file
//
//////////////////////////////////////////////////////////

#pragma pack(1)
struct Inode
{
    char FileName[20];
    int inodenumber;
    
    int FileSize;
    int permisson;

    int refferenceCount;
    char *buffer;

    struct Inode* next;
};

typedef struct Inode INODE;
typedef struct Inode * PINODE;
typedef struct Inode ** PPINODE;

//////////////////////////////////////////////////////////
//
//  Structure Name :    FileTable
//  Description :       Holds the information about opened file
//
//////////////////////////////////////////////////////////


struct FileTable
{
    int readoffset;
    int writeoffset;

    int mode;
    PINODE  prtinode;

};
typedef struct FileTable FILETABLE;
typedef struct FileTable *PFILETABLE;

//////////////////////////////////////////////////////////
//
//  Structure Name :    UAREA
//  Description :       Holds the information about process file
//
//////////////////////////////////////////////////////////

struct Uarea
{
    char ProcessName[20];
    PFILETABLE UFDT[MAXOPENFILES];
};

//////////////////////////////////////////////////////////
//
//  Global variables or objects used in the project
//
//////////////////////////////////////////////////////////

BootBlock bootboj;
SuperBlock Superobj;
Uarea Uareaobj;

PINODE head = NULL;




//////////////////////////////////////////////////////////
//
//  Function Name :     InitialiseSuperBlock
//  Description :       It is used to initialise Super block members
//  Author :            Sakshi laxman kachate
//  Date :              3/04/2026
//
//////////////////////////////////////////////////////////

void InitialliseSuperBlock()
{
    Superobj.freeInode = MAXINODES;
    Superobj.TotalInode = MAXINODES;
}

//////////////////////////////////////////////////////////
//
//  Function Name :     InitialiseUAREA
//  Description :       It is used to initialise UAREA members
//  Author :            Sakshi laxman kachate
//  Date :              3/04/2026
//
//////////////////////////////////////////////////////////

void InitialiseUarea()
{
    strcpy(Uareaobj.ProcessName,"myexe");
    int i = 0;

    for (i = 0 ; i < MAXOPENFILES ;  i++)
    {
        Uareaobj.UFDT[i] = NULL;
    }
    printf("CVFS : Uarea get initialised succefully \n ");
}

//////////////////////////////////////////////////////////
//
//  Function Name :     CreateDILB
//  Description :       It is used to create Linkedlist of inodes
//  Author :            Sakshi laxman kachate
//  Date :              3/04/2026
//
//////////////////////////////////////////////////////////

void createDILB()
{
    int i = 0;

    PINODE newn = NULL;
    PINODE temp = head;

    for(i = 1 ; i <MAXINODES ; i++)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        strcpy(newn->FileName,"\0");
        newn->FileSize =0;
        newn ->inodenumber = i;
        newn->permisson = 0;
        newn ->refferenceCount = 0;
        newn->buffer = NULL;
        newn ->next = NULL;

        if( temp == NULL)
        {
            head = newn ;
            temp = head ;
        }
        else
        {
            temp ->next = newn ;
            temp = temp -> next ;
        }

    }
}

//////////////////////////////////////////////////////////
//
//  Function Name :     StartAuxillaryDataInitilisation
//  Description :       It is used to call all such functions which are
//                      used to initialise auxillary data
//  Author :            Sakshi laxman kachate
//  Date :              3/04/2026
//
//////////////////////////////////////////////////////////
void StartAuxillayDataInitiallisation()
{   
    strcpy(bootboj.Information,"Booting process of CVFS is Done.. \n");

    printf( "%s \n",bootboj.Information);

    InitialliseSuperBlock();
    createDILB();
    InitialiseUarea();

    printf("Auxillary data initialised sucessfully \n");
}

//////////////////////////////////////////////////////////
//
//  Entry Point function of the project
//
//////////////////////////////////////////////////////////


int main()
{
    char str[80] = {"\0"};

    char command [4][20];
    int icount = 0;

    StartAuxillayDataInitiallisation();
    
    printf("-----------------------------------------------\n");
    printf("--------CVFS started succesfully --------------\n");
    printf("-----------------------------------------------\n");

    while(1)
    {
            fflush(stdin);
            strcpy(str,"");
            printf("\n CVFS : >");
            fgets(str,sizeof(str),stdin);
    }

    return 0;

}
