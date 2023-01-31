#include "validation.c"

void set_space(int n){
    for(int i=0;i<n;i++){
        printf(" ");
    }
return;
}

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
    return 0;
}

void get_switch(){
    if(have_got_switch){
        return;
    }
    char g;
    char check;
    while(1){
    if(g=='\n'){
        have_got_switch=1;
        return;
    }

    int len=0;
    do{
    g=getchar();
    if(g=='\n'){
        have_got_switch=1;
        return g;
    }
    }while(g==' ');
    char type[15];
    memset(type,0,strlen(type));
    type[0]='\0';
    while(g!=' '&&g!='\n'){
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
    }else if(!strcmp(type,"--files")){
        filenums=0;
        do{
        check=get_input(SFILE);

        SFILES[filenums]=(char*)malloc(100);
        char root[100];
        strcpy(root,"root/");
        strcat(root,SFILE);
        strcpy(SFILES[filenums],root);
        filenums++;
        }while(check!='\n');
    }else if(!strcmp(type,"--str")){
        check=get_input(SSTR);
    }else if(!strcmp(type,"--str1")){
        check=get_input(SSTR1);
    }else if(!strcmp(type,"--str2")){
        check=get_input(SSTR2);
    }else if(!strcmp(type,"--pos")){
        scanf("%d:%d",&SPOS[0],&SPOS[1]);
    }else if(!strcmp(type,"--size")){
        scanf("%d",&SIZE);
        //begin keys
    }else if(!strcmp(type,"-f")){
        DIRECTION=1;

    }else if(!strcmp(type,"-b")){
        DIRECTION=0;
    }else if(!strcmp(type,"-byword")){
        BYWORD=1;
    }else if(!strcmp(type,"-all")){
        ALL=1;
    }else if(!strcmp(type,"-at")){
        scanf("%d",&AT);
    }else if(!strcmp(type,"-count")){
        COUNT=1;
    }else if(!strcmp(type,"-c")){
        C=1;
    }else if(!strcmp(type,"-l")){
        L=1;
    }

    if(check=='\n'){
        have_got_switch=1;
        return;
    }
    }
    have_got_switch=1;
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

void save_edited(){
    if(first_in_file){
        SFILE[3]='h';
        FILE* nfile=fopen(SFILE,"w");
        fprintf(nfile,"%s",in_file);
        fclose(nfile);
        first_in_file=0;
        SFILE[3]='t';
    }
    FILE* nfile=fopen(SFILE,"w");
    for(int i=0;i<strlen(edited);i++){
        if(edited[i]=='\n'&&edited[i+1]=='\n'){
            i++;
        }
        fprintf(nfile,"%c",edited[i]);
    }

    fclose(nfile);

return;
}

long get_file_str(){


    long length;
    FILE * nfile = fopen (SFILE, "rb");

    if (nfile)
    {
      fseek (nfile, 0, SEEK_END);
      length = ftell (nfile);
      fseek (nfile, 0, SEEK_SET);
      in_file = (char*)malloc (length);
      if (in_file)
      {
        fread (in_file, length,1, nfile);
      }
      fclose (nfile);
    }
    in_file[length]='\0';


return length;
}

long get_undo_file_str(){


    long length;
    SFILE[3]='h';
    FILE * nfile = fopen (SFILE, "rb");
    SFILE[3]='t';
    if (nfile)
    {
      fseek (nfile, 0, SEEK_END);
      length = ftell (nfile);
      fseek (nfile, 0, SEEK_SET);
      in_undo_file = (char*)malloc (length);
      if (in_undo_file)
      {
        fread (in_undo_file, length,1, nfile);
      }
      fclose (nfile);
    }
    in_undo_file[length]='\0';

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
    if(SPOS==0)
    return SPOS[1]+save;
    else{
    return SPOS[1]+save+1;
    }
}

void copy_str(){
    copied=(char*)malloc(SIZE*sizeof(char));
    int pos=find_pos();
    if(DIRECTION){
            for(int i=0;i<SIZE;i++){
                copied[i]=in_file[i+pos];
            }
    }else{
            for(int i=0;i<SIZE;i++){
                copied[i]=in_file[pos-SIZE+i];
            }
        }

return;
}



int find_all(long finds[]){
    int check=1,counter=0;

       for(long i=0;i<strlen(in_file);i++){
            check=1;
            for(long j=0;j<strlen(SSTR);j++){
                if(SSTR[j]!=in_file[i+j]){
                    check=0;
                }
            }
            if(check){

                finds[counter]=i;
                counter++;
                i+=(strlen(SSTR)-1);
            }
       }


return counter;
}

void replace_str(long finds[],long shomare,int length){
    long pos=finds[shomare];
    edited=malloc(strlen(in_file)+strlen(SSTR2)-strlen(SSTR1)+1);
    for(int i=0;i<pos;i++){
        edited[i]=in_file[i];
    }
    for(int i=pos;i<(strlen(SSTR2)+pos);i++){
        edited[i]=SSTR2[i-pos];
    }
    for(int i=pos+strlen(SSTR2);i<strlen(in_file)+strlen(SSTR2)-strlen(SSTR1);i++){
        edited[i]=in_file[i+strlen(SSTR1)-strlen(SSTR2)];
    }
    edited[strlen(in_file)+strlen(SSTR2)-strlen(SSTR1)]='\0';

    save_edited();
return;
}

void show_list(int depth,char path[],int numspace) {

  DIR *d;
  struct dirent *dir;
  char npath[100];
  int mini,numspace1;
  numspace1=numspace;
  d = opendir(path);
 // printf("   ");
  if (d) {
        mini=0;
    while ((dir = readdir(d)) != NULL) {
        if(mini<2){
            mini++;
            continue;
        }else
        if(mini==2){

      printf(".----%s", dir->d_name);
        numspace+=(5+strlen(dir->d_name));
        }else{
        printf("\n");
        set_space(numspace1);
        printf("|\n");
        set_space(numspace1);
        printf("|\n");
        set_space(numspace1);
        printf( ".----%s", dir->d_name);

        }
                if(depth>1){

            strcpy(npath,path);
            strcat(npath,dir->d_name);
            strcat(npath,"/");

            show_list(depth-1,npath,numspace);
        }
        mini++;
    }
    closedir(d);
  }
  return(0);
}
wfrew
;
int get_file_line(char line[],char file_name[],long line_number){
    long line_num=1;
    int k=0;



        strcpy(SFILE,file_name);
        long length=get_file_str();
        k=0;
        for(int j=0;j<length;j++){
            line[k]=in_file[j];
            k++;
            if(in_file[j]=='\n'){
                line[k-1]='\0';
                if(line_number==line_num){
                   // printf("%s",line);
                    return k;
                }

                line_num++;
                k=0;
            }
        }
        if(in_file[length-1]!='\n'){
            line[k]='\0';

                if(line_number==line_num){
                        return 1;
                   // printf("%s",line);
                }else{
                return 0;
                }
                line_num++;
                k=0;

        }


return 0;
}

int exists_in_str(char bigger[],char smaller[]){
    int check=1;

            for(int j=0;j<strlen(bigger);j++){
                check=1;
                for(int s=0;s<strlen(smaller);s++){

                    if(smaller[s]!=bigger[j+s]){
                        check=0;
                    }
                }
                if(check){
                    return 1;
                }
            }
return 0;
}

long which_word(long pos){
    char last;
    long word_pos=0;
        for(int i=0;i<pos;i++){
            if((in_file[i]==' '||in_file[i]=='\n')&&!(last==' '||last=='\n')){
                word_pos++;
            }
            last=in_file[i];
        }
        return word_pos+1;
}
