#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



long long int calculate(long long int num1,long long int num2,char opt)
{
    switch (opt) {
        case '+':
            return num1+num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1*num2;
        case '/':
            if(num2 == 0)
                return 0;
            return num1/num2;

    }
}

int main()
{
    int testCase;
    scanf("%d",&testCase);
    for (int i = 1; i <=testCase ; ++i) {

        long long int num1;
        long long int num2;
        char opt;

        scanf("%lld %c %lld",&num1,&opt,&num2);

        long long int result = calculate(num1,num2,opt);

        (result == 0 && num2 == 0 ) ? printf("Case Study#%d: Divide By Zero!\n",i) : printf("Case Study#%d: %lld\n",i,result);
    }

    return 0;
}

