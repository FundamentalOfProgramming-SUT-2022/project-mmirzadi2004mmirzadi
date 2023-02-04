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
    make_dirs();

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

int Bremovestr(){
    long pos=find_pos();
    if(pos<0){
    //printf("The position not found!\n");
    return 0;
    }
    int length=get_file_str();
    if(SSIZE==0||(DIRECTION&&SSIZE+pos>=length)||(!DIRECTION&&SSIZE>pos)){

        return 0;
    }

    edited=malloc(length-SSIZE);
    if(DIRECTION){
        for(int i=0;i<pos;i++){
            edited[i]=in_file[i];
        }
        for(int i=0;i<(length-pos-SSIZE);i++){
            edited[i+pos]=in_file[pos+SSIZE+i];
        }
    }else{
        for(int i=0;i<pos-SSIZE;i++){
            edited[i]=in_file[i];
        }
        for(int i=0;i<(length-pos);i++){
            edited[i+pos-SSIZE]=in_file[pos+i];
        }
    }
    edited[length-SSIZE]='\0';
 return 1;
}

int replace_vim(){
    int x1,y1;
                    AT=-1;ALL=0;
                  get_switch();
                  strcpy(SSTR,SSTR1);
                  long finds[100];

                  long counter=find_all(finds);
                    if(AT==0){
                     //   printf("Wrong at input!\n");
                        return 0;
                    }else if(AT>(counter)){
                     //   printf("I could not find that much!\n");
                        return 0;
                    }
                    if(AT!=-1&&ALL){
                     //   printf("You can't use both AT and ALL!\n");
                        return 0;
                    }


//printf("fsjdsja;dfd;ajs");

                  x1=wherex(); y1=wherey();
                    if(ALL){
                        int countersave=counter;

                        for(int i=0;i<countersave;i++){
                            get_file_str();
                            counter=find_all(finds);

                            replace_str(finds,0,counter);
                        }
                        //printf("Replaced all phrases!\n");
                        gotopos(edited,finds[counter-1]);

                           // normalmode();

                        return 1;
                    }else if(AT!=-1){
                        replace_str(finds,AT-1,counter);
                        gotopos(edited,finds[AT-1]);
                        return 1;
                    }


return 1;
}

int Bindent(char str[]){
   edited=malloc(strlen(str)*2);
    long k=0;

    for(int i=0;i<strlen(str);i++){
        if(str[i]=='{'){

            if(i&&str[i-1]!=' '){
                edited[k]=' ';
                k++;

            }else if(i>1){
                int s=2;
                while(i>=s&&str[i-s]==' '){
                    k--;
                    s++;
                }
                if(i>=s&&str[i-s]=='\n'){
                    k--;
                }
            }else{

            }
            if(str[i+1]==' '){
                edited[k]=str[i];
                k++;
                while(i<strlen(str)&&str[i+1]==' '){
                    i++;
                }
            }
            if(i<strlen(str)-1&&str[i+1]!='\n'){
                edited[k]=str[i];
                k++;
                i++;
                edited[k]='\n';
                k++;
            }else if(i+2<strlen(str)&&str[i+2]=='}'){
                edited[k]=str[i];
                k++;
                i++;
                edited[k]='\n';
                k++;
            }
        }
        else if(str[i]=='}'){
                int s=1;
                while(i&str[i-s]==' '){
                    k--;
                    s++;
                }

                if(i&&str[k-1]!='\n'){
                      //  printf("_____%c_____",in_file[k-1]);
                    edited[k]='\n';
                    k++;
                }

                if(str[i+1]!='\n'){
                    edited[k]=str[i];
                    k++;
                    i++;
                    edited[k]='\n';
                    k++;
                }
        }
        edited[k]=str[i];
        k++;
    }

    edited[k]='\0';
 //   printf("%s\n",edited);
    char *edited2;
    edited2=malloc(strlen(edited)+1000);
    k=0;
    int m=0;
    while(edited[m]==' '){
        m++;
    }
    int kroshnum=0;
    int upordown=1;
    int space[1000];

    for(int i=m;i<strlen(edited);i++){

        if(edited[i]=='{'){
            kroshnum+=4;
            upordown=1;
        }
        if(edited[i]=='}'){
            kroshnum-=4;
            upordown=-1;
        }
        edited2[k]=edited[i];
        k++;
      //  kroshnum=kroshnum+(upordown);
        if(edited[i]=='\n'){
            while(i+1<strlen(edited)&&edited[i+1]==' '){
                i++;
            }
            if(i+1<strlen(edited)&&edited[i+1]=='}'){
                    for(int j=0;j<kroshnum-4;j++){
                        edited2[k]=' ';
                        k++;
                    }
                    edited2[k]=edited[i+1];
                    k++; i++;
                    kroshnum-=4;
            }
            else{
            for(int j=0;j<kroshnum;j++){
                edited2[k]=' ';
                k++;
            }

            }
        }
        }

    edited2[k]='\0';

    edited=edited2;


return 1;
}

