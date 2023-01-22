#include "validation.c"



char get_input(char a[]){
    a[0]='\0';
    memset(a,0,strlen(a));
    char g,k;
    int len=0;
    do{
    scanf("%c",&g);

    }while(g==' ');
    if(g=='"'){
        while(1){
            g=getchar();
            if(g=='"'){
                k=getchar();
                if(k==' '||k=='\n'){
                        a[len]='\0';
                    return k;
                }else{
                    a[len]=g;
                    len++;
                    g=k;
                }
            }
            if(g=='\n'){
                printf("->");

            }


            a[len]=g;
            len++;
        }
    }
    else{
            a[len]=g;
            len++;
            while(1){
            g=getchar();
            if(g==' '||g=='\n'){
                    a[len]='\0';
                    return g;

            }


            a[len]=g;
            len++;
        }
    }
    return;
}

void get_switch(){
    char g;
    char check;
    while(1){
    if(g=='\n'){
        return;
    }

    int len=0;
    do{
    g=getchar();
    if(g=='\n'){
        return;
    }
    }while(g==' ');
    char type[15];
    memset(type,0,strlen(type));
    type[0]='\0';
    while(g!=' '){
        type[len]=g;
        len++;
        g=getchar();
    }
    type[len]='\0';
    if(!strcmp(type,"--file")){
        check=get_input(SFILE);
        char root[15];
        strcpy(root,  "root/");
        strcpy(SFILE,strcat(root,SFILE));
    }else if(!strcmp(type,"--str")){
        check=get_input(SSTR);



    }else if(!strcmp(type,"--pos")){
        scanf("%d:%d",&SPOS[0],&SPOS[1]);

    }
    if(check=='\n'){
        return;
    }
    }

}

int make_dirs(){
    char dirs[100];

    memset(dirs,0,strlen(dirs));
    int count=0;
    dirs[0]='\0';

    for(int i=0;i<strlen(SFILE);i++){

        if(SFILE[i]=='/'){
            if(count==0){
                return 0;
            }
            count=0;
        }
        dirs[i]=SFILE[i];
        count++;
    }
    memset(dirs,0,strlen(dirs));

    dirs[0]='\0';

    dirs[strlen(dirs)]='\0';
    int first=1;
    for(int i=0;i<strlen(SFILE);i++){

        if(SFILE[i]=='/'){
            if(!first){

            mkdir(dirs);}
            first=0;

        }
        dirs[strlen(dirs)]=SFILE[i];

    }
    return 1;
}

long get_file_str(){


    long length;
    FILE * nfile = fopen (SFILE, "rb");

    if (nfile)
    {
      fseek (nfile, 0, SEEK_END);
      length = ftell (nfile);
      fseek (nfile, 0, SEEK_SET);
      in_file = malloc (length);
      if (in_file)
      {
        fread (in_file, 1, length, nfile);
      }
      fclose (nfile);
    }
return length;
}


long find_pos(){
    long length=get_file_str();

    long counter=1,save=-1;

    for(int i=0;i<length;i++){
        if(in_file[i]=='\n'){
            counter++;
        }
        if(counter>=SPOS[0]){
            save=i;
            break;
        }
    }
    if(save==-1){
        printf("The position not found!\n");
        return -1;
    }

    for(int i=0;i<SPOS[1];i++){
        if(in_file[i+save+1]=='\n'){
            printf("The position not found!!\n");
            return -1;
        }
    }
    return SPOS[1]+save;
}

void save_edited(){
    FILE* nfile=fopen(SFILE,"w");
    fprintf(nfile,"%s",edited);
    fclose(nfile);

return;
}
