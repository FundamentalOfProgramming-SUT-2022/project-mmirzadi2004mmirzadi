#include "additional.c"

void createfile(){
    get_switch();

    if(is_empty(SFILE,"file address")){
        return;
    }

    if(file_exists()){

        return;
    }
    if(!make_dirs()){
        printf("Worng directory!\n");
        return;
    }
    FILE* nfile;

    if(nfile=fopen(SFILE,"w"))
    {
    fclose(nfile);
    printf("File successfully created!\n");
    return;
    }
    printf("Something went wrong!\n");
}

void insert(){
    get_switch();
    if(file_not_exists()){
        return;
    }
    int pos=find_pos();

    if(pos<0){
        return;
    }

    edited=malloc((strlen(SSTR)+strlen(in_file))*sizeof(char));
    for(int i=0;i<pos;i++){
        edited[i]=in_file[i];
    }
    for(int i=0;i<(strlen(SSTR));i++){
        edited[pos+i]=SSTR[i];
    }
    for(int i=0;i<(strlen(in_file)-pos);i++){
        edited[strlen(SSTR)+pos+i]=in_file[i+pos];
    }
    save_edited();
    printf("Added successfully!\n");
return;
}

void cat(){
    get_switch();
    get_file_str();
    printf("%s\n",in_file);

return;
}
