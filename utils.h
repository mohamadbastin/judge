#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int compileCode(void);
int generateOutput(int type);
void clear(void);
int judgeOutputs(void);
void welcome(int type);
void compareTwoFile(FILE * fPtr1, FILE * fPtr2);