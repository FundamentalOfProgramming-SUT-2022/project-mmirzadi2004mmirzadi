#include<stdio.h>
#include<string.h>
#include<limits.h>
#include "switches.c"

#include "commands.c"


int main(){

char command[15];
char c;
while(1){
    scanf("%s",command);
    if(!strcmp(command,"createfile")){
        createfile();
    }
    else if(command=="insert"){

    }else{
    do{
        c=getchar();
    }while(c!='\n');
    printf("Invalid entery!\n");
    }

}

return 0;
}
