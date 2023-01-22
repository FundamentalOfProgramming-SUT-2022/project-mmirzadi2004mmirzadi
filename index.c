#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
#include "switches.c"

#include "commands.c"
// insertstr --file test.txt --str ggggg --pos 1:1

int main(){

char command[15];
char c;
while(1){
    scanf("%s",command);
    if(!strcmp(command,"createfile")){
        createfile();
    }
    else if(!strcmp(command,"insertstr")){
        insert();
    }else if(!strcmp(command,"cat")){
        cat();
    }else{
    do{
        c=getchar();
    }while(c!='\n');
    printf("Invalid entery!\n");
    }

}

return 0;
}
