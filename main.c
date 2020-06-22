#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <error.h>

#define ROAD "..\\Source\\"
#define PATH "main.c"
#define MAX_SIZE 100   //MAXIMUM TESTCASE &ARRAY

// Function Prototype
void Complie_Code(void);
int Exist_File(void);
void MakeTestCase(void);
void sleep(int i);



int main() {

    printf("---------------------------------> Welcome To Judge <---------------------------------\n");
    sleep(2);
    Complie_Code();
    MakeTestCase();


    return 0;
}


void Complie_Code(void)
{

    int Check = Exist_File();
    FILE *PF;

    if(Check == 1) {
        printf("---------------------------------> Source File Exist:) <-------------------------------------\n");
        sleep(2);
        printf("---------------------------------> Please Waiting For Compile... <------------------------------\n");
        sleep(3);  // 3 second Wait

        system("gcc ..\\source\\main.c -o ..\\source\\mySource"); // Compile Code

        PF = fopen("..\\Source\\mySource","r");
        if(PF)
        {
            printf("\n\t\t"
                   "\t\t/*********************************************\n"
                   "\n"
                   "\t\t\t\t\tCONGRATULATION: COMPILE SUCCSEED\n"
                   "\n\t\t"
                   "\t\t*********************************************/\n\n");
        }
    }
    else if(Check == 2)
    {
        printf("Error opening file: %s\n", strerror(Exist_File()));
    }
}


int Exist_File(void)
{
    char Exist[MAX_SIZE];
    strcpy(Exist,ROAD);
    strcat(Exist,PATH);

    FILE *file = fopen(Exist,"r");
    if(!file)
    {
        return errno;
    }
    else
    {
        fclose(file);
        return 1;
    }
}


void MakeTestCase(void)
{
    printf("how many testCase Would you like Make:\n");
    char inDataBase[MAX_SIZE] = {'\0'};
    char inputResult[MAX_SIZE] = {'\0'};

    char outDataBase[MAX_SIZE] = {'\0'};
    char outputResult[MAX_SIZE] = {'\0'};

    int num;
    scanf("%d",&num);

    for (int i = 0; i < num ; ++i)
    {
        int result1 = snprintf(inDataBase,MAX_SIZE,"Input%d.txt", i+1);
        int result2 = snprintf(outDataBase,MAX_SIZE,"Output%d.txt", i+1);

        if( result1 < 0 || result1 > MAX_SIZE )
        {
            printf("MEMORY LIMIT EXCEED TO CREATE FILE:(\n");
        }
        else
        {
            // Input
            strcpy(inputResult,ROAD);
            strcat(inputResult,"testCase\\in\\");
            strcat(inputResult,inDataBase);

            // Output
            strcpy(outputResult,ROAD);
            strcat(outputResult,"testCase\\out\\");
            strcat(outputResult,outDataBase);

            FILE *input = fopen(inputResult, "w");
            FILE *output = fopen(outputResult, "w");

            if(!input) {
                printf("Error To Create File Input%d.txt",i+1);
                exit(0);
            }

            if(!output) {
                printf("Error To Create File Output%d.txt",i+1);
                exit(0);
            }

            int testCase;
            long long int first, second;
            char opt;
            char operation[5] = {'+','-','*','/','\0'};

            testCase = rand()%15;
            fprintf(input,"%d",testCase);
            fputc('\n',input);

            for (int j = 0; j <testCase; ++j) {

                first = rand()%1000 + rand()/34;
                second = rand()/10 - rand()%11 ;
                opt = operation[rand() % 4];

                fprintf(input,"%lld",first);
                for(int i = 0;i<rand()%10+1;i++)
                    fputc('\n',input);

                fputc(opt,input);
                for(int i = 0;i<rand()%20+1;i++)
                    fputc('\n',input);

                fprintf(input,"%lld",second);

                for(int i = 0;i<rand()%9+1;i++)
                    fputc('\n',input);
            }


            char Path[1000] = {'\0'};

            strcpy(Path,"..\\Source\\mySource <");
            strcat(Path,inputResult);
            strcat(Path," >");
            strcat(Path,outputResult);

            fclose(input);
            fclose(output);

            system(Path);

        }
    }
    sleep(3);
    printf("\n\t\t"
           "\t\t/*********************************************\n"
           "\n"
           "\t\t\t\t\tAll TestCase Was Created Successfuly:)\n"
           "\n\t\t"
           "\t\t*********************************************/\n\n");
}


