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
    if(g=='\n'){
        return '\n';
    }
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
            if(g=='\\'){
                g=getchar();
                if(g=='n'){
                    a[len]='\n';
                    len++;
                    g=getchar();
                }else if(g=='"'){
                    a[len]='"';
                    len++;
                    g=getchar();
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
        return;
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
        scanf("%d",&SSIZE);
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
        fprintf(nfile,"%c",edited[i]);
    }

    fclose(nfile);

return;
}

long get_file_str(){


    long length=0;
    FILE * nfile = fopen (SFILE, "r");
    in_file=malloc(1000);
    char str[200];
    if (nfile)
    {
     // fseek (nfile, 0, SEEK_END);
    //  length = ftell (nfile);
    //  fseek (nfile, 0, SEEK_SET);
char ch;
    while (fscanf(nfile, "%c",
                  &in_file[length])
           == 1){

        length++;
           }
   fclose(nfile);

     // fclose (nfile);
    }
    in_file[length]='\0';


return length;
}

long get_undo_file_str(){


    long length=0;
    SFILE[3]='h';
    FILE * nfile = fopen (SFILE, "r");
    SFILE[3]='t';
    in_undo_file=malloc(1000);
    char str[200];
    if (nfile)
    {
     // fseek (nfile, 0, SEEK_END);
    //  length = ftell (nfile);
    //  fseek (nfile, 0, SEEK_SET);
char ch;
    while (fscanf(nfile, "%c",
                  &in_undo_file[length])
           == 1){

        length++;
           }
   fclose(nfile);

     // fclose (nfile);
    }
    in_undo_file[length]='\0';


return length;
}


long find_pos(){
    long length=get_file_str();

    long counter=1,save=-1;
    if(SPOS[0]==1&&SPOS[1]==0){
        return 0;
    }
    for(int i=0;i<length;i++){
        if(in_file[i]=='\n'){
            counter++;
        }
        if(counter>=(SPOS[0])){
            save=i;
            break;
        }
    }
    if(save==-1){

        return -1;
    }
  //  printf("__%d__",save);
    for(int i=0;i<SPOS[1];i++){
        if(in_file[i+save+1]=='\n'||i+save+1>=length){

            return -1;
        }
    }
    if(SPOS[0]==1)
    return SPOS[1]+save;
    else{
    return SPOS[1]+save+1;
    }
}

long find_pos2(char str[]){
   // long length=get_file_str();

    long counter=1,save=-1;
    if(SPOS[0]==1&&SPOS[1]==0){
        return 0;
    }
    for(int i=0;i<strlen(str);i++){
        if(str[i]=='\n'){
            counter++;
        }
        if(counter>=(SPOS[0])){
            save=i;
            break;
        }
    }
    if(save==-1){

        return -1;
    }
  //  printf("__%d__",save);
    for(int i=0;i<SPOS[1];i++){
        if(str[i+save+1]=='\n'||i+save+1>=strlen(str)){

            return -1;
        }
    }
    if(SPOS[0]==1)
    return SPOS[1]+save;
    else{
    return SPOS[1]+save+1;
    }
}


void copy_str(){
    copied=(char*)malloc(SSIZE*sizeof(char));
    int pos=find_pos();
    if(DIRECTION){
            for(int i=0;i<SSIZE;i++){
                copied[i]=in_file[i+pos];
            }
    }else{
            for(int i=0;i<SSIZE;i++){
                copied[i]=in_file[pos-SSIZE+i];
            }
        }
        copied[SSIZE]='\0';

return;
}



int find_all(long finds[]){
    int check=1,counter=0,firststar=0,laststar=0,checknospace=1,bet;
    long i,m=0;
        if(SSTR[0]=='*'){
            m=1;
            firststar=1;
        }
        if(SSTR[strlen(SSTR)-1]=='*'){
            SSTR[strlen(SSTR)-1]='\0';
            laststar=1;
        }
       for(i=0;i<strlen(in_file);i++){
            check=1;
            for(long j=m;j<strlen(SSTR);j++){
                if(SSTR[j]!=in_file[i+j-m]){
                    check=0;
                }
            }
            if(check){

                bet=0;
                if(firststar){
                  //  printf("fja");
                    while(i>0&&(in_file[i-1]!=' '&&in_file[i-1]!='\n')){
                        i--;
                        bet++;
                    }
                 //   printf("__%d__",i);
                }
                if(counter==0||finds[counter-1]!=i){
                finds[counter]=i;
                }else{
                    counter--;
                }
                i+=bet;
                if(counter>0&&laststar){
                    bet=finds[counter-1];
                    checknospace=1;
                    while(bet<=i){
                        if(in_file[bet]==' '||in_file[bet]=='\n'){
                            checknospace=0;
                        }
                        bet++;
                    }
                    if(checknospace){

                        counter--;
                    }
                }
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
  return;
}

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
    int check=1,counter=0,checknospace=1,bet;
    long i,m=0;
        if(smaller[0]=='*'){
            m=1;

        }
        if(smaller[strlen(smaller)-1]=='*'){
            smaller[strlen(smaller)-1]='\0';

        }
       for(i=0;i<strlen(bigger);i++){
            check=1;
            for(long j=m;j<strlen(smaller);j++){
                if(smaller[j]!=bigger[i+j]){
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





//-----------------------------------
void print_line_to_line(char str[],int a,int b,char mode[],int kol);

void print_in_pos(char text[],int x2,int y2){
     int y1=wherey();
     int x1=wherex();
    gotoxy(x2,y2);
    printf("%s",text);

    gotoxy(x1,y1);
return;
}

void print_in_color(char text[],int color,int bgcolor,int x2,int y2){
     int y1=wherey();
     int x1=wherex();
    textcolor(color);
    textbackground(bgcolor);
    gotoxy(x2,y2);
    cprintf("%s",text);
    textbackground(BLACK);
    textcolor(WHITE);
    gotoxy(x1,y1);
return;
}



int move_on_screen(char a,int y){

    SPOS[0]=wherey()-1;
    SPOS[1]=wherex()-1;
    long pos=find_pos();
    int y1,x1;
    if(a=='i'){
        if(wherey()>1){
            y1=wherey();
            x1=wherex();
         //   printf("__%d__",Y);
            if(wherey()<5&&Y>0){

            Y--;
            print_line_to_line(in_file,1+Y,26+Y,"visual",1);
            gotoxy(1,y1);
           // printf("->\n");

            }else{
            while(pos<0&&SPOS[1]>0){
                    SPOS[1]--;
                    gotoxy(wherex()-1,wherey());
                    pos=find_pos2(edited);
            }
            gotoxy(wherex(),wherey()-1);
            }
            return 1; }}
    if(a=='j'){if(wherex()>1){
            gotoxy(wherex()-1,wherey());
            return 1; }
    }
    SPOS[0]=wherey()+1;
    SPOS[1]=wherex()-1;
    pos=find_pos2(edited);
//    int y1,x1;
    if(a=='k'){
            y1=wherey();
            x1=wherex();
         //   printf("__%d__",Y);
            if(wherey()>=24){

            Y++;
            print_line_to_line(in_file,1+Y,26+Y,"visual",1);
            gotoxy(1,28);
            long tool=strlen(edited);
            edited[tool]='\n';
            edited[tool+1]=' ';
            edited[tool+2]=' ';
            edited[tool+3]='\0';
           // printf("->\n");

            }else if(Y==0&&y-wherey()<5){
            gotoxy(1,y-1);
             long tool=strlen(edited);
            edited[tool]='\n';
            edited[tool+1]=' ';
            edited[tool+2]=' ';
            edited[tool+3]='\0';
             //   printf("_______%d______",y);
            printf("\n->");

            }
            gotoxy(x1,y1);
        if(wherey()<24){
            while(pos<0&&SPOS[1]>0){
                    SPOS[1]--;
                    gotoxy(wherex()-1,wherey());
                    pos=find_pos2(edited);
            }

            gotoxy(wherex(),wherey()+1);
        }


        return 1;
    }
    SPOS[0]=wherey();
    SPOS[1]=wherex();
    if(SPOS[0]==1){
        SPOS[1]--;
    }
    pos=find_pos2(edited);

    if(a=='l'&&pos>=0){
        gotoxy(wherex()+1,wherey());
        return 1;
    }

}

void print_line_to_line(char str[],int a,int b,char mode[],int kol){
    int y1,x1,check;
    y1=wherey();
    x1=wherex();check=0;
    if(kol){
    gotoxy(1,1);
    clrscr();
    }
    textcolor(WHITE);
    long length=strlen(str);
    long count=1,i=0,lim=0;

    while(count<=b){
        if(i>=length){
            textcolor(BLUE);
                if(check){
                    printf("\n");
                    check=0;
                    b++;
                }
            while((lim<4||y>=24)){

                if(count>=a&&count<=b){
                        cprintf("->\n");

                        lim++;
                }
                count++;
                if(count>b){
                    break;
                }
            }

            textcolor(WHITE);
            break;
        }

        if(count>=a){
                check=1;
            printf("%c",str[i]);
        }
        if(str[i]=='\n'){
            count++;
        }
            i++;

    }
  //  printf("__%d__",wherey());
    y1=wherey();
    x1=wherex();
    textcolor(WHITE);
    textbackground(BLUE);
    gotoxy(1,28);
    cprintf("%s",mode);
    textbackground(BLACK);
    print_in_pos(SFILE+5,20,28);
    gotoxy(x1,y1);
return;
}

void select_line_to_line(char str[],int a,int b,char mode[],int kol,long c,long d){
    int y1,x1,check;
    //long shomare=0;
    y1=wherey();
    x1=wherex();check=0;
    if(kol){
    gotoxy(1,1);
    clrscr();
    }
    textcolor(WHITE);
    long length=strlen(str);
    long count=1,i=0,lim=0;
    long h;
    if(d<c){
        h=d;
        d=c;
        c=h;
    }
    while(count<=b){

                if(i==c){
                    textbackground(BLUE);
                }else if(i==d){
                    textbackground(BLACK);

                }

        if(i>=length){
            textcolor(BLUE);
                if(check){
                    printf("\n");
                    check=0;
                    b++;
                }
            while((lim<4||y>=24)){

                if(count>=a&&count<=b){
                        cprintf("->\n");

                        lim++;
                }
                count++;
                if(count>b){
                    break;
                }
            }

            textcolor(WHITE);
            break;
        }

        if(count>=a){
                check=1;
            printf("%c",str[i]);
        }
        if(str[i]=='\n'){
            count++;
        }
            i++;

    }
  //  printf("__%d__",wherey());
    y1=wherey();
    x1=wherex();
    textcolor(WHITE);
    textbackground(BLUE);
    gotoxy(1,28);
    cprintf("%s",mode);
    textbackground(BLACK);
    print_in_pos(SFILE+5,20,28);
    gotoxy(x1,y1);
return;
}

int insert_char(long pos,char a){
    //int pos=find_pos();

    if(pos<0){

        return 0;
    }
    if(a==8){
        char* edited2;
        edited2=malloc(strlen(edited));
        for(int i=0;i<pos-1;i++){
            edited2[i]=edited[i];
        }
        edited2[pos]=a;
        for(int i=0;i<(strlen(edited)-pos-1);i++){
            edited2[pos+i-1]=edited[i+pos];
        }
        edited2[strlen(edited)-1]='\0';

        strcpy(edited,edited2);
            return 1;
    }
    char* edited2;
    edited2=malloc(strlen(edited)+2);
    for(int i=0;i<pos;i++){
        edited2[i]=edited[i];
    }
    edited2[pos]=a;
    for(int i=0;i<(strlen(edited)-pos+1);i++){
        edited2[1+pos+i]=edited[i+pos];
    }
    edited2[strlen(edited)+1]='\0';

    strcpy(edited,edited2);
}


void gotopos(char str[],long pos){
    int line=1;
    long x;
    for(int i=0;i<pos;i++){
            if(str[i]=='\n'){
                line++;
                x=i;
            }
    }
    if(line==1){
        x=0;
    }
    gotoxy(pos-x,line);
  //  printf("---%d---",pos-x);
return;
}


void saveo(char str[]){
    output=malloc(strlen(str));
    strcpy(output,str);


return;
}
void savec(char str[]){
    char *str2=malloc(strlen(str)+strlen(output));
    strcpy(str2,output);
    strcat(str2,str);
    strcpy(output,str2);
return;
}

char* number_to_string(int a){
    char *x=malloc(10);
    char *y=malloc(10);
    int i=0;
    while(a>0){
        x[i]=a%10;
        a/=10;
        i++;
    }
    x[i]='\0';
    for(int j=0;j<i;i++){
        y[i-j-1]=x[j];
    }
return y;
}
