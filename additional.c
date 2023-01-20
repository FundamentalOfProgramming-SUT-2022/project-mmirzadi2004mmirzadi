#include "validation.c"


void get_input(char a[]){
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
                    return;
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
                    return;

            }


            a[len]=g;
            len++;
        }
    }
    return;
}

void get_switch(){
    char g;
    int len=0;
    do{
    g=getchar();
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
        get_input(SFILE);

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
    char root[15];
    strcpy(root,  "root/");
    strcpy(dirs,root);
    dirs[strlen(dirs)]='\0';
    for(int i=0;i<strlen(SFILE);i++){

        if(SFILE[i]=='/'){
                printf("____%s___",dirs);
                mkdir(dirs);
        }
        dirs[strlen(dirs)]=SFILE[i];

    }
    return 1;
}


