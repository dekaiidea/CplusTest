#include<stdio.h>
int main(int argc, char const *argv[])
{
    int i,k;
    printf("Hello World!\n");
    printf("argc:%d\nargc:\n",argc);
    for(i=0;i<argc;++i)
    {
        printf("%d : %s\n",i,argv[i]);
    }
    getchar();
    return 0;
}
