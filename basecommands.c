#include "additional.c"


int Bcreatefile(){
    SFILE[3]='h';
    make_dirs();

    FILE* nfile;

    if(nfile=fopen(SFILE,"w"))
    {
    fclose(nfile);

    get_file_str();

    }
    SFILE[3]='t';


    if(nfile=fopen(SFILE,"w"))
    {
    fclose(nfile);

    get_file_str();
    return 1;
    }
    return 0;
}

int Binsert(){
    int pos=find_pos();

    if(pos<0){

        return 0;
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
    edited[strlen(SSTR)+strlen(in_file)]='\0';
    save_edited();
return 1;
}

int Bcat(){

    long length=get_file_str();
    for(int i=0;i<length;i++){
    printf("%c",in_file[i]);
    }
    return 1;
}
