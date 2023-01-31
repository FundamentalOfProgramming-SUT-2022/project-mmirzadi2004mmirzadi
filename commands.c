#include "additional.c"
;
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
    SFILE[3]='h';
    make_dirs();
    SFILE[3]='t';
    FILE* nfile;

    if(nfile=fopen(SFILE,"w"))
    {
    fclose(nfile);
    printf("File successfully created!\n");
    get_file_str();
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
    edited[strlen(SSTR)+strlen(in_file)]='\0';
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
    edited[length-SIZE]='\0';
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

    insert(0);
    printf("Have pasted successfully!\n");
return;
}

void find(){
    COUNT=0;AT=-1;BYWORD=0;ALL=0;
    get_switch();
    get_file_str();
    long finds[1000];

    int counter;

    counter=find_all(finds);

        if(!counter){
            printf("NOthing founded!\n");
            return;
        }
        if(COUNT){
            printf("COUNT -->> I found %d statements.\n",counter);

        }

        if(AT==0){
            printf("AT -->> Incurrect input!\n");
        }else if(AT>counter){
            printf("AT -->> I could not find that much!\n,%ld",counter);
        }else if(AT>0){
            printf("AT -->> THE %d th statement is on the %d position.",AT,BYWORD?which_word(finds[AT-1]):finds[AT-1]);
        }
        if(ALL){
            for(int i=0;i<counter;i++){
                if(i)
                printf(" , ");
                printf("%ld",BYWORD?which_word(finds[i]):finds[i]);
            }
            printf("\n");

        }
        if(!ALL&&AT==-1&&!COUNT){
            printf("%ld",BYWORD?which_word(finds[0]):finds[0]);
        }


}

void replace(){
    AT=-1;ALL=0;
    get_switch();
    get_file_str();
    long finds[1000];
    strcpy(SSTR,SSTR1);
    int counter=find_all(finds);

    if(AT==0){
        printf("Wrong at input!\n");
        return;
    }else if(AT>(counter)){
        printf("I could not find that much!\n");
        return;
    }
    if(AT!=-1&&ALL){
        printf("You can't use both AT and ALL!\n");
        return;
    }
    if(AT!=-1){
        replace_str(finds,AT-1,counter);
        printf("The phrase replaced successfuly!\n");
        return;

    }
    if(ALL){
        int countersave=counter;

        for(int i=0;i<countersave;i++){
            get_file_str();
            counter=find_all(finds);

            replace_str(finds,0,counter);
        }
        printf("Replaced all phrases!\n");
        return;
    }
        replace_str(finds,0,counter);
        printf("The phrase replaced successfuly!\n");
        return;
}

void grep(){
    L=0;C=0;
    get_switch();

    for(int i=0;i<filenums;i++){
        strcpy(SFILE,SFILES[i]);
        if(file_not_exists()){
            return;
        }
    }
    if(strlen(SSTR)==0){
        printf("Your sting can't be empty!\n");
        return;
    }

    long shomare_line=1;
    int check,linecount;
    if(C&L){
            printf("You can't use both -c and -l");
            return;
    }
    if(!L&&!C){
        int counter;
        for(int i=0;i<filenums;i++){


            char line[200];
            counter=0;
            shomare_line=1;
            while(linecount=get_file_line(line,SFILES[i],shomare_line)){

                if(exists_in_str(line,SSTR)){
                    counter++;
                }
                shomare_line++;
            }
                if(counter>0){
                    printf("%s : ",SFILES[i]+5);
                }

            shomare_line=1;


            while(linecount=get_file_line(line,SFILES[i],shomare_line)){

                if(exists_in_str(line,SSTR)){
                    printf("%s\n",line);
                }
                shomare_line++;
            }

        }
        return;
    }

    if(C){
        int counter=0;
        for(int i=0;i<filenums;i++){

            char line[200];

            while(linecount=get_file_line(line,SFILES[i],shomare_line)){

                if(exists_in_str(line,SSTR)){
                    counter++;
                }
                shomare_line++;
            }

            }
            printf("%d\n",counter);
        return;

    }
    if(L){
        int counter;
        for(int i=0;i<filenums;i++){


            char line[200];
            counter=0;
            while(linecount=get_file_line(line,SFILES[i],shomare_line)){

                if(exists_in_str(line,SSTR)){
                    counter++;
                }
                shomare_line++;
            }
                if(counter>0){
                    printf("%s\n",SFILES[i]+5);
                }
            }

        return;

    }

return;
}

void indent(){
    char check=get_input(SFILE);
    if(check==' '){
        printf("Wrong input!\n");
        return;
    }
    char root[50];
    strcpy(root,"root/");
    long kroshnum=0;
    strcat(root,SFILE);
    strcpy(SFILE,root);
    long length=get_file_str();
    edited=malloc(length*2);
    long k=0;
    for(int i=0;i<length;i++){
        if(in_file[i]=='{'){

            if(i&&in_file[i-1]!=' '){
                edited[k]=' ';
                k++;

            }else if(i>1){
                int s=2;
                while(i>=s&&in_file[i-s]==' '){
                    k--;
                    s++;
                }
                if(i>=s&&in_file[i-s]=='\n'){
                    k--;
                }
            }else{

            }
            if(in_file[i+1]==' '){
                edited[k]=in_file[i];
                k++;
                while(i<length&&in_file[i+1]==' '){
                    i++;
                }
            }
            if(in_file[i+1]!='\n'){
                edited[k]=in_file[i];
                k++;
                i++;
                edited[k]='\n';
                k++;
            }else if(i+2<length&&in_file[i+2]=='}'){
                edited[k]=in_file[i];
                k++;
                i++;
                edited[k]='\n';
                k++;
            }
        }
        else if(in_file[i]=='}'){
                if(i&&in_file[i-1]!='\n'){
                    edited[k]='\n';
                    k++;
                }
                if(in_file[i+1]!='\n'){
                    edited[k]=in_file[i];
                    k++;
                    i++;
                    edited[k]='\n';
                    k++;
                }
        }
        edited[k]=in_file[i];
        k++;
    }

    edited[k]='\0';
    char *edited2;
    edited2=malloc(strlen(edited)+1000);
    k=0;
    int m=0;
    while(in_file[m]==' '){
        m++;
    }
    kroshnum=0;
    for(int i=m;i<strlen(edited);i++){
        if(edited[i]=='{'){
            kroshnum++;
        }
        if(edited[i]=='}'){
            kroshnum--;
        }
        edited2[k]=edited[i];
        k++;
        if(edited[i]=='\n'){
            while(i+1<strlen(edited)&&edited[i+1]==' '){
                i++;
            }
            for(int j=0;j<kroshnum*4;j++){
                edited2[k]=' ';
                k++;
            }

        }
    }
    edited2[k]='\0';
    strcpy(edited,edited2);
    save_edited();
return;
}

void compare(){
        SFILES[0]=(char*)malloc(100);
        SFILES[1]=(char*)malloc(100);
        int shomare_line;
       get_input(SFILES[0]);
       char root[50];
            strcpy(root,"root/");
            strcat(root,SFILES[0]);
            strcpy(SFILES[0],root);
       int cline1,cline2;
       char check=get_input(SFILES[1]);
            strcpy(root,"root/");
            strcat(root,SFILES[1]);
            strcpy(SFILES[1],root);

       if(check!='\n'){
        printf("Wrong input!\n");
        return;
       }
            char line[200];

            shomare_line=1;
            char line2[200];

            while(get_file_line(line,SFILES[0],shomare_line)){
            cline1=get_file_line(line2,SFILES[1],shomare_line);
                if(strcmp(line,line2)){
                    printf("------------ LINE %d ----------\n FILE %s : %s\n File %s : %s\n",shomare_line,SFILES[0]+5,line,SFILES[1]+5,cline1?line2:"Empty line");
                }

                shomare_line++;
            }
            while(get_file_line(line2,SFILES[1],shomare_line)){
                cline1=get_file_line(line,SFILES[0],shomare_line);
                if(strcmp(line,line2)){
                    printf("------------ LINE %d ----------\n FILE %s : %s\n File %s : %s\n",shomare_line,SFILES[0]+5,cline1?line:"Empty line",SFILES[1]+5,line2);
                }

                shomare_line++;
            }

return;
}

void undo(){
    get_switch();
    if(file_not_exists()){
        return;
    }
    long length=get_undo_file_str();
    edited=malloc(length);
    strcpy(edited,in_undo_file);

    get_file_str();


    if((in_file=="")&&(in_undo_file=="")){
        printf("There is no undo state.\n");
        return;
    }



    save_edited();
    printf("The file returned to previous state.\n");
return;
}

void tree(){

    int depth,mini=0;
    scanf("%d",&depth);

    show_list(depth-1,"root/",1);
    printf("\n");
return;
}
