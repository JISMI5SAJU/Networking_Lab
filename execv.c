#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
void main()
{
char *args[]={"./new",NULL};
execvp(args[0],args);
printf("System call successfully completed");
}
