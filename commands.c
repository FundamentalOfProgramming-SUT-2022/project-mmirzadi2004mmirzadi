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

void insert(int c){
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
    if(c)
    printf("Added successfully!\n");
return;
}

void cat(){
    get_switch();
    long length=get_file_str();
    printf("%s\n",in_file);

return;
}

void removestr(int c){
    get_switch();
    int length=get_file_str();
    long pos=find_pos();
    edited=malloc(length-SIZE);
    if(DIRECTION){
        for(int i=0;i<pos;i++){
            edited[i]=in_file[i];
        }
        for(int i=0;i<(length-pos-SIZE);i++){
            edited[i+pos]=in_file[pos+SIZE+i];
        }
    }else{
        for(int i=0;i<pos-SIZE;i++){
            edited[i]=in_file[i];
        }
        for(int i=0;i<(length-pos);i++){
            edited[i+pos-SIZE]=in_file[pos+i];
        }
    }
    save_edited();
    if(c)
    printf("Removed successfully!\n");
return;
}

void copystr(){
    get_switch();
    get_file_str();
    copy_str();
    printf("String copied.\n");
return;
}

void cutstr(){
    get_switch();
    copy_str();
    removestr(0);

    printf("String cut.\n");


return;
}

void pastestr(){
    get_switch();
    if(copied==NULL){
        printf("Nothing have been copied!\n");
        return;
    }
    strcpy(SSTR,copied);
    printf("__%s__",copied);
    insert(0);
    printf("Have pasted successfully!\n");
return;
}

void find(){
    COUNT=0;AT=-1;BYWORD=0;ALL=0;
    get_switch();
    get_file_str();
    long finds[1000];
    if(!BYWORD){
    find_all(finds);
        if(COUNT){
            printf("COUNT -->> I found %d statements.\n",sizeof(finds)/4);

        }
        if(AT==0){
            printf("AT -->> Incurrect input!\n");
        }else if(AT>sizeof(finds)/4){
            printf("AT -->> I could not find that much!\n");
        }else{
            printf("AT -->> THE %d th statement is on the %d position.",AT,finds[AT-1]);
        }
        if(ALL){
            for(int i=0;i<sizeof(finds)/4;i++){
                if(i)
                printf(" , ");
                printf("%ld",&finds[i]);
            }
            printf("\n");
        }
    }

}


void replace(){
    AT
    get_switch();
    get_file_str();
    long finds[1000];
    strcpy(SSTR,SSTR1);
    find_all(finds);
    if(AT==0){
        printf("Wrong at input!\n");
        return;
    }else if(AT>sizeof(finds)/4){
        printf("I could not find that much!\n");
        return;
    }
    if(AT&&ALL){
        printf("You can't use both AT and ALL!\n");
        return;
    }
    if(AT){

    }
return;
}
