#include<stdio.h>
#include<string.h>
#include<stdlib.h>




#define MAXINODE 5
#define MAXOPENFILES 20


struct Bootblock
{
    char Information[100];
};

struct Superblock
{
    int TotalInodes;
    int FreeInode;

};

#pragma pack(1)
struct Inode
{
    char Filename[20];
    int inodenumber;
    int Filesize;
    int ActualFileSize;
    int refferncecount;
    int Permmision;
    char *Buffer;
    struct Inode*next;

};
typedef struct Inode  INODE;
typedef struct Inode * PINODE;
typedef struct Inode ** PPINODE;


struct FileTable
{
    int ReadOffset;
    int WriteOffset;
    int Mode;
    PINODE ptrinode;

};
typedef FileTable FILETABLE;
typedef FileTable * PFILETABLE;

struct UAREA
{
    char ProcessName[20];
    PFILETABLE UFDT[MAXOPENFILES];
};


Bootblock bootbobj;
Superblock superbobj;
UAREA uareaobj;

PINODE head = NULL;



void InitialiseSuperBlock()
{
superbobj.TotalInodes = MAXINODE;
superbobj.FreeInode = MAXINODE;

printf("CVFS : Superblock gets  initialised Succefully ");

}

void InitialiseUAREA()
{
    strcpy(uareaobj.ProcessName,"myexe");
    int i  = 0;

    for (i = 0; i < MAXOPENFILES ; i++)
    {
        uareaobj.UFDT[i] = NULL;

    }
    printf("CVFS : UAREA gets initialised sucessfully \n");


}

void CreateDILB()
{
    int i = 1;
    PINODE newn  = NULL;
    PINODE temp = head;

    for(i = 1 ; i <= MAXINODE ; i++)
    {
        newn = (PINODE)malloc(sizeof(Inode));

        strcpy(newn->Filename,"\0");
        newn->inodenumber = i;
        newn->Filesize = 0;
        newn->ActualFileSize = 0;
        newn->Permmision = 0;
        newn->refferncecount = 0;
        newn->next = NULL;
        newn->Buffer = NULL;

        if (temp == NULL) //ll is empty
        {
            head = newn;
            temp = head;

        }
        else    // ll contain atleast 1 node 
        {
            temp->next = newn;
            temp = temp->next;
        }

    }

    printf("CVFS : DILB created Succefully \n");
}







void StartAuxillaryDataInitialisation()
{
    strcpy(bootbobj.Information,"Booting process of CVFS is DONE ");
    printf("%s\n",bootbobj.Information);

    InitialiseSuperBlock();

    CreateDILB();

    InitialiseUAREA();

    printf("CVFS :Auxillary data initialised Succefully \n");


}

void DisplayHelp()
{
    printf("----------------------------------------------------------------\n");
    printf("----------------------CVFS Help Page----------------------------\n");
    printf("----------------------------------------------------------------\n");

    printf("man : it is use to Display man page \n");
    printf("clear :  it is use to clear the terminal\n");
    printf("create  : It is use to create  new file \n");
    printf("write   : It is use to write Data into file  \n");
    printf("read    : It is use to read Data from the file  \n");
    printf("stat    : It is use to Display statistical information \n");
    printf("unlink  : It is use to delete the file \n");
    printf("exit    : It is use to terminate Marvellous CVFS \n");

    printf("-------------------------------------------------\n");

}

void ManPageDisplay(char Name[])
{
    if(strcmp("ls",Name)== 0)
    {
        printf("About:it is used to list of all files \n  ");
    }
     else if(strcmp("man",Name)== 0)
    {
        printf("About : it is used to Display Mannual page \n");
        printf("Usage : man command_name\n");
        printf("command_name : It is the name of command\n");
    }
    else if(strcmp("exit",Name)== 0)
    {
        printf("About : it is used to terminate the shell \n");
        printf("Usage : exit\n");
    }
    else
    {
        printf("no manual entry for %s\n",Name);
    }
}

int main()
{
    char str[80] = {'\0'};
    char Command[5][20] = {{'\0'}};
    int iCount = 0;

    StartAuxillaryDataInitialisation();

    printf("----------------------------------------------------------------\n");
    printf("----------------CVFS Started Succesfully------------------------\n");
    printf("----------------------------------------------------------------\n");

    while(1)
    {
        fflush(stdin);
        strcpy(str ,"");

        printf("CVFS : >");
        fgets( str,sizeof(str),stdin);

        iCount = sscanf(str,"%s%s%s%s" ,Command[0],Command[1],Command[2],Command[3],Command[4]);

        fflush(stdin);

        if (iCount == 1 )
        {
            if(strcmp("exit",Command[0])== 0)
            {
                printf("Thank you for using CVFS\n");
                printf("Deallocating all the resources\n");

                break;

            }
            else if(strcmp("ls",Command[0])==0)
            {
                printf("Inside ls \n");
            }
            else if(strcmp("help",Command[0])==0)
            {
                DisplayHelp();

            }
        }

        else if (iCount == 2)
        {
            if(strcmp("man",Command[0])== 0);
            {
                ManPageDisplay(Command[1]);
            }
        }
        else if(iCount == 3)
        {

        }
        else if(iCount == 4)
        {

        }
        else
        {
            printf("Command Not Found \n");
            printf("Please Reffer Help option  to get more information \n");
            
        }
    }



    return 0;
}