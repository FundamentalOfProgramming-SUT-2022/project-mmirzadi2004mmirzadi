#include "additional.c"

void createfile(){
    get_switch();

    if(is_empty(SFILE,"file address")){
        return;
    }

    if(file_exists()){

        return;
    }
    char root[15];
    strcpy(root,  "root/");
    if(!make_dirs()){
        printf("Worng directory!\n");
        return;
    }
    FILE* nfile;

    if(nfile=fopen(strcat(root,SFILE),"w"))
    {
    fclose(nfile);
    printf("File successfully created!\n");
    return;
    }
    printf("Something went wrong!\n");
}
