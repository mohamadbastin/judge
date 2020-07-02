#include "utils.h"
#define MAX_SIZE 10000 //MAXIMUM ARRAY SIZE

//COLORS DEFINITION
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

int percentage = 0;
int numOfIn = 0;

/**                                           START Program                                                          **/

void welcome(int type)
{
    system("clear");
    if (type == 1)
    {
        printf(GRN "---------------------------------> WELCOME TO JUDGE <---------------------------------\n" RESET);
    }
    else
    {
        printf(GRN "---------------------------------> WELCOME TO GENERATOR <---------------------------------\n" RESET);
    }
    // sleep(1);
}



int compileCode(void)
{
    /**                           GET USER MAIN FILE RELATIVE OR ABSOLUTE PATH                    **/

    printf(WHT "ENTER YOUR MAIN FILE PATH:\n" RESET);

    char filePath[MAX_SIZE];
    scanf("%s", filePath);

    FILE *file = fopen(filePath, "r");

    if (!file)
    {
        system("clear");
        printf(RED "ERROR OPENING FILE\nRESTART PROGRAM.\n" RESET);
        // sleep(2);
        return 0;
    }

   FILE *tmp = fopen("utils/userJudgeOut", "r");

   if (!tmp)
   {
   }
   else
   {
       system("rm utils/tempJudgeOut");
   }

    char compileCommand[MAX_SIZE] = "gcc ";
    strcat(compileCommand, filePath);
    strcat(compileCommand, " -o utils/adminJudgeOut");

    system("clear");
    printf(MAG "COMPILATION LOG:\n" RESET);
    system(compileCommand);
    printf("\n");

    FILE *checkOut = fopen("utils/adminJudgeOut", "r");

    if (!checkOut)
    {
        printf(RED "COMPILE FAILED\nRESTART PROGRAM.\n" RESET);
        // sleep(2);
        system("clear");
        return 0;
    }

    printf(GRN "CODE COMPILED\n" RESET);
    // sleep(1);
    // system("clear");
    return 1;
}

int generateOutput(int type)
{

    printf(WHT "ENTER PATH TO INPUTS FOLDER(WITH TRAILING SLASH):\n" RESET);

    char inputPath[MAX_SIZE];
    scanf("%s", inputPath);

    struct dirent *de;

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(inputPath);

    if (dr == NULL) // opendir returns NULL if couldn't open directory
    {
        system("clear");
        printf(RED "Could not open input directory" RESET);
        // sleep(2);
        return 0;
    }

    // the run command defines here
    char command[MAX_SIZE] = "./utils/adminJudgeOut < ";

    // for readdir()
    while ((de = readdir(dr)) != NULL)
    {

        strcpy(command, "");
        strcpy(command, "./utils/adminJudgeOut < ");
        strcat(command, inputPath);

        // ignore useless shit
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0 || strcmp(de->d_name, ".DS_Store") == 0)
        {
            continue;
        }
        else // create the full system command
        {
            char outputPath[MAX_SIZE] = "adminFile/mainTestCase/out/";
            if (type == 1){
                strcpy(outputPath, "");
                strcpy(outputPath, "userFile/out/");
            }
            strcat(outputPath, de->d_name);
            FILE *tmp = fopen(outputPath, "w");
            strcat(command, de->d_name);
            strcat(command, " > ");
            strcat(command, outputPath);
            fclose(tmp);
        }

        system(command);
    }

    closedir(dr);

    printf(GRN "\nOUTPUTS GENERATED.\nCHECK THE OUTPUTS FOLDER.\n\n" RESET);
    // sleep(2);
    // system("clear");
    return 1;
}


int judgeOutputs(void){

    struct dirent *de;
    // struct dirent *se;

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir("adminFile/mainTestCase/out/");
    // DIR *sr = opendir("tempOutputs/");


    if (dr == NULL ) // opendir returns NULL if couldn't open directory
    {
        system("clear");
        printf(RED "Could not open output directory" RESET);
        return 0;
    }

    char outputPath[MAX_SIZE] = "adminFile/mainTestCase/out/";
    char tempOutputPath[MAX_SIZE] = "userFile/out/";

    // for readdir()
    while ((de = readdir(dr)) != NULL)
    {

        // ignore useless shit
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0 || strcmp(de->d_name, ".DS_Store") == 0)
        {
            continue;
        }
        else // compare files
        {
            strcpy(outputPath, "");
            strcpy(outputPath, "adminFile/mainTestCase/out/");
            strcat(outputPath, de->d_name);

            strcpy(tempOutputPath, "");
            strcpy(tempOutputPath, "userFile/out/");
            strcat(tempOutputPath, de->d_name);

            FILE *file1 = fopen(outputPath, "r");
            FILE *file2 = fopen(tempOutputPath, "r");

            if (!file1 || !file2){
                printf(RED "SOMETHING WENT WRONG" RESET);
            }

            numOfIn++;
            compareTwoFile(file1,file2);
            

        }

    }

    printf("score: %d\n", percentage);

    return 1;
}

void compareTwoFile(FILE *fp1,FILE *fp2) {

    char ch1 = getc(fp1);
    char ch2 = getc(fp2);
    int line = 1,flag = 0,false_testCases = 0;

    while (ch1 != EOF && ch2 != EOF) {

        if (ch1 == '\n' && ch2 == '\n') {
            line++;
        }

        if (ch1 != ch2) {
            flag = 1;
            false_testCases++;
            break;
        }

        ch1 = getc(fp1);
        ch2 = getc(fp2);


    }

    printf("%d :\n", numOfIn);

    flag == 1 ? printf("Case Study#%d is Wrong\n", line) : printf("True\n");

    // printf("\n drsd: %d\n", ((n-false_testCases)/n)*100);
    percentage = ((numOfIn-false_testCases)/numOfIn)*100;

}
