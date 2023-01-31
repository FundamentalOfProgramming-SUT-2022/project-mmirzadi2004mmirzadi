#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>
#include "switches.c"
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "commands.c"
// insertstr --file test.txt --str ggggg --pos 1:1
// removestr --file test.txt --pos 2:4 -size 2 -f


int main(){

char command[15];
char c;

while(1){
    have_got_switch=0;
    first_in_file=1;
    scanf("%s",command);
    if(!strcmp(command,"createfile")){
        createfile();
    }
    else if(!strcmp(command,"insertstr")){
        insert(1);
    }else if(!strcmp(command,"cat")){
        cat();
    }else if(!strcmp(command,"removestr")){
        removestr(1);
    }else if(!strcmp(command,"copystr")){
        copystr();
    }else if(!strcmp(command,"cutstr")){
        cutstr();
    }else if(!strcmp(command,"pastestr")){
        pastestr();
    }else if(!strcmp(command,"find")){
        find();
    }else if(!strcmp(command,"replace")){
        replace();
    }else if(!strcmp(command,"grep")){
        grep();
    }else if(!strcmp(command,"compare")){
        compare();
    }else if(!strcmp(command,"auto-indent")){
        indent();
    }else if(!strcmp(command,"undo")){
        undo();
    }else if(!strcmp(command,"tree")){
        tree();
    }
    else{
    do{
        c=getchar();
    }while(c!='\n');
    printf("Invalid entery!\n");
    }

}

return 0;
}
