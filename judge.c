#include "utils.c"

int main()
{
    welcome(1);
    if (compileCode())
    {
        if(generateOutput(1)){
            judgeOutputs();
        }
    }
    return 0;
}
