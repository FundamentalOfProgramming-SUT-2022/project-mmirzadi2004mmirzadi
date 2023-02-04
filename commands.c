#include "basecommands.c"

;
void createfile(){
    SFILE[0]='\0';
    get_switch();

    if(is_empty(SFILE,"file address")){
        return;
    }

    if(file_exists()){

        return;
    }

    if(Bcreatefile()){
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
    if(!Binsert()){
        printf("The position not found!\n");
        return;
    }
    if(c)
    printf("Added successfully!\n");
return;
}

void cat(){
    get_switch();
    if(file_not_exists()){
        return;
    }
    if(!Bcat()){
        printf("Something went wrong.");
    }
    printf("\n");
return;
}

void removestr(int c){
    get_switch();

    if(file_not_exists()){
        return;
    }
    if(!Bremovestr()){
        return;
    }
    save_edited();
    if(c)
    printf("Removed successfully!\n");
return;
}

void copystr(){
    get_switch();
    if(file_not_exists()){
        return;
    }
    long length=get_file_str();
    long pos=find_pos();
    if(pos<0){
    printf("The position not found!\n");
    return;
    }

    if(SSIZE==0||(DIRECTION&&SSIZE+pos>=length)||(!DIRECTION&&SSIZE>pos)){
            printf("Not valid size!\n");
        return;
    }
    copy_str();
    printf("String copied.\n");
return;
}

void cutstr(){
    get_switch();
    long length=get_file_str();
    long pos=find_pos();
    if(pos<0){
    printf("The position not found!\n");
    return;
    }

    if(SSIZE==0||(DIRECTION&&SSIZE+pos>=length)||(!DIRECTION&&SSIZE>pos)){
            printf("Not valid size!\n");
        return;
    }
    copy_str();
    removestr(0);

    printf("String cut.\n");


return;
}

void pastestr(){
    get_switch();
    if(file_not_exists()){
        return;
    }
    long length=get_file_str();
    long pos=find_pos();
    if(pos<0){
    printf("The position not found!\n");
    return;
    }

    if(SSIZE==0||(DIRECTION&&SSIZE+pos>=length)||(!DIRECTION&&SSIZE>pos)){
            printf("Not valid size!\n");
        return;
    }
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
    if(file_not_exists()){
        return;
    }
    int counter;

    counter=find_all(finds);

        if(!counter){
            printf("Nothing founded!\n");
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
            printf("AT -->> THE %d th statement is on the %d position.\n",AT,BYWORD?which_word(finds[AT-1]):finds[AT-1]);
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
            printf("%ld\n",BYWORD?which_word(finds[0]):finds[0]);
        }


}

void replace(){
    AT=-1;ALL=0;
    get_switch();
    if(file_not_exists()){
        return;
    }
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
    char root[115];
    strcpy(root,"root/");
    long kroshnum=0;
    strcat(root,SFILE);
    strcpy(SFILE,root);
    long length=get_file_str();
    edited=malloc(length*2);
    long k=0;

    for(int i=0;i<strlen(SFILE);i++){
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
            if(i<length-1&&in_file[i+1]!='\n'){
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
                int s=1;
                while(i&in_file[i-s]==' '){
                    k--;
                    s++;
                }

                if(i&&edited[k-1]!='\n'){
                   //     printf("_____%c_____",in_file[i-1]);
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
 //   printf("%s\n",edited);
    char *edited2;
    edited2=malloc(strlen(edited)+1000);
    k=0;
    int m=0;
    while(in_file[m]==' '){
        m++;
    }
    kroshnum=0;
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
   // printf("     sadklfj   ");
    save_edited();
    printf("Success!\n");
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



// faze 2

void visualmode();
void insertmode();
void normalmode();
void choose();
void vim();
void choose(char command[]){
    //char command[50];
    //scanf("%s",command);
    char c;
    have_got_switch=0;
    first_in_file=1;
    //scanf("%s",command);
    if(!strcmp(command,"createfile")){
        createfile();
    }
    else if(!strcmp(command,"insertstr")){
        insert(1);
    }else if(!strcmp(command,"cat")){
        cat();
    }else if(!strcmp(command,"removestr")){
        removestr(1);
    }else if(!strcmp(command,"copystr")){
        copystr();
    }else if(!strcmp(command,"cutstr")){
        cutstr();
    }else if(!strcmp(command,"pastestr")){
        pastestr();
    }else if(!strcmp(command,"find")){
        find();
    }else if(!strcmp(command,"replace")){
        replace();
    }else if(!strcmp(command,"grep")){
        grep();
    }else if(!strcmp(command,"compare")){
        compare();
    }else if(!strcmp(command,"auto-indent")){
        indent();
    }else if(!strcmp(command,"undo")){
        undo();
    }else if(!strcmp(command,"tree")){
        tree();
    }else if(!strcmp(command,"vim")){
        vim();
    }else{
    do{
        c=getchar();
    }while(c!='\n');
    printf("Invalid entery!\n");
    }
}


void vim(){

    int check;


    check=get_input(SFILE);

    if(check==' '){
        printf("Wrong input!\n");
        return;
    }

    if(strlen(SFILE)>0&&SFILE[0]!='\n'){

    char root[115];
    strcpy(root,"root/");
    strcat(root,SFILE);
    strcpy(SFILE,root);
    have_file_name=1;
    }else{
        strcpy(SFILE,"new.txt");
        have_file_name=0;
    }
    if(have_file_name){
        if(!file_exists1()){
            Bcreatefile();
        }

        if(file_exists1()){
            get_file_str();
           // printf("%s\n",in_file);
        }


    }
    clrscr();
    get_file_str();
     print_line_to_line(in_file,1,26,"NORMAL",1); //0 normal 1 visual 2 insert

    y=wherey();
  //  printf("%d",y);
    textcolor(1);
  //  cprintf("\n->\n");cprintf("->\n");cprintf("->\n");cprintf("->\n");cprintf("->\n");
    long tool=strlen(in_file);
    for(int i=0;i<4;i++){
  //  in_file[tool+3*i]='\n';in_file[tool+1+3*i]='-';in_file[tool+2+3*i]='>';
    }
    in_file[12+tool]='\0';

    textcolor(WHITE);
    textbackground(BLUE);
    gotoxy(1,28);
    cprintf("NORMAL");
    textbackground(BLACK);
  //  print_in_pos(SFILE+5,20,28);
    gotoxy(1,1);
    char c;
    edited=malloc(strlen(in_file)+2000);
    strcpy(edited,in_file);
        for(int i=0;i<4;i++){

            tool=strlen(edited);

            edited[tool]='\n';
            edited[tool+1]=' ';
            edited[tool+2]='\0';
        }
    strcpy(in_file,edited);
    visualmode();


return;
}


void visualmode(){
    char c;
    int x1,y1;
        if(!have_saved){
           print_in_pos("+",60,28);
        }
    print_in_color("  VISUAL  ",WHITE,BLUE,1,28);
    print_in_pos(SFILE+5,20,28);
    int selected=0;
    long pos1,pos2;
    while(1){
            textcolor(BLUE);

            c=getch();
            if(c==13){
                gotoxy(1,29);
                normalmode();

            }else if(c=='s'){
                if(!selected){
                    SPOS[0]=wherey(); SPOS[1]=wherex()-1;
                    pos1=find_pos();
                    selected=1;
                }else{
                    SPOS[0]=wherey(); SPOS[1]=wherex()-1;
                    pos2=find_pos();
                    selected=0;
                        x1=wherex(); y1=wherey();
                        SSIZE=pos2-pos1;
                        if(SSIZE<0){
                            SSIZE=(-1)*SSIZE;
                            DIRECTION=1;
                        }else DIRECTION=0;


                        select_line_to_line(edited,1+Y,27+Y,"VISUAL",1,pos1,pos2);
                        gotoxy(x1,y1);
                 //   printf("__________%ld  %ld________",pos2,pos1);
                    c=getch();
                    if(c=='d'){

                        copy_str();
                        Bremovestr();

                      print_line_to_line(edited,1+Y,27+Y,"VISUAL",1);
                      normalmode();
                      //printf("%s\n",copied);
                      gotoxy(x1,y1);
                    }else if(c=='y'){
                        copy_str();
                        normalmode();
                    }
                }
            }
            if(c=='e'){
                insertmode();
            }

        move_on_screen(c,y);
            if(c=='k'&&y-wherey()<4){
                y++;
            }
    }
return;
}

void insertmode(){
    int y1,x1;
    char c;
    //edit mode
        have_saved=0;
        if(!have_saved){
           print_in_pos("+",60,28);
        }
            y1=wherey();
            x1=wherex();
            SPOS[0]=wherey(); SPOS[1]=wherex()-1;
            print_in_color("  INSERT  ",WHITE,BLUE,1,28);
            print_in_pos(SFILE+5,20,28);

            long pos;
            gotoxy(x1,y1);
            if(y1>27){
                gotoxy(1,1);
            }

            pos=find_pos2(edited);
           // printf("___%ld___",pos);
            while(1){

            c=getch();

            if(c==':'||c=='/'){
                normalmode();
            }else
            if(c=='\\'){
               visualmode();
            }

            insert_char(pos,c);
            pos++;
            y1=wherey();
            x1=wherex();

            gotoxy(1,wherey());
            print_line_to_line(edited,wherey()+Y,wherey()+Y,"insert",0);
            if(c!=8){
            gotoxy(x1+1,y1);}else{
            gotoxy(x1-1,y1);
            }
            }


return;
}

void normalmode(){
    int check;
    int x1,y1;
    char c;
    print_in_color(" NORMAL ",WHITE,BLUE,1,28);
   textcolor(WHITE);
    gotoxy(1,29);
    printf(":command :                                                                                             ");
    gotoxy(11,29);
    char command[15];
   // command=malloc(15);
    int commanda=0;
    while(1){
            check=0;
            commanda=0;
            textcolor(WHITE);
            gotoxy(1,29);
            printf(":command :");
        while(1){
            c=getch();
       /*     if(c=='p'){
                gotoxy(1,29);
                printf("                  ");
                textcolor(1);
                gotoxy(1,1);
                visualmode();
            } */
            if(c==8){
                if(wherex()>11){
                   // gotoxy(wherex()-1,wherey());
                    gotoxy(wherex()-1,wherey());
                    printf(" ");
                    gotoxy(wherex()-1,wherey());
                    command[commanda-1]='\0';
                    commanda--;
                }
                continue;
            }


            if(c==13||c==':'||c==' '){
                gotoxy(wherex()+1,wherey());
                break;
            }
            if(c=='='){
                x1=wherex(); y1=wherey();
                Bindent(edited);
                save_edited();
                print_line_to_line(edited,1+Y,26+Y,"NORMAL",1);
                gotoxy(x1,y1);
                normalmode();
            }
            printf("%c",c);
            command[commanda]=c;
            //printf("-%c-",c);
            commanda++;

        }
        command[commanda]='\0';


            if(!strcmp(command,"save")){
                if(have_file_name){
                    save_edited();
                }else{
                    gotoxy(11,29);
                    printf("add file name:                                      ");
                    gotoxy(25,29);
                    get_input(SFILE);
                    gotoxy(35,29);
                           char root[50];
                            strcpy(root,"root/");
                            strcat(root,SFILE);
                            strcpy(SFILE,root);
                    if(Bcreatefile()){
                         //   printf("____%s__",edited);
                        save_edited();
                        print_in_pos("       ",59,28);
                        have_saved=1;
                    }else{
                        check=-1;
                    }
                }

                check=1;
            }else
            if(!strcmp(command,"i")){
                insertmode();
                check=1;
            } else
            if(!strcmp(command,"v")){
                gotoxy(1,1);
                visualmode();
                check=1;
            }else if(!strcmp(command,"p")){

                printf("%s",copied);
                check=0;
            }else if(!strcmp(command,"saveas")){
                get_input(SFILE);
                    char root[115];
                    strcpy(root,"root/");
                    long kroshnum=0;
                    strcat(root,SFILE);
                    strcpy(SFILE,root);
                save_edited();
                print_in_pos(" ",60,28);
                have_saved=1;
                check=1;
            }else if(!strcmp(command,"open")){
                save_edited();
                vim();
            }else if(!strcmp(command,"undo")){
                    long length=get_undo_file_str();
                    edited=malloc(length);
                    strcpy(edited,in_undo_file);
                    x1=wherex(); y1=wherey();
                    get_file_str();
                    save_edited();

                    print_line_to_line(edited,1+Y,26+Y,"NORMAL",1);
                    gotoxy(x1,y1);
                    normalmode();
            }else if(command[0]=='/'){
                    strcpy(SSTR,command+1);
                    long finds[100];
                    int counter=find_all(finds);
                    x1=wherex(); y1=wherey();
                    //long finds2[100];
                    int num=0;
                   // c=getch();
                   c='n';
                        while(num<counter){

                            select_line_to_line(edited,1+Y,26+Y,"NORMAL",1,finds[num],finds[num]+strlen(SSTR));
                            gotopos(edited,finds[num]);
                          //  printf("_____%d___",finds[num]);
                            c=getch();
                            if(c=='n'){
                                num++;
                            }else{
                                print_line_to_line(edited,1+Y,26+Y,"NORMAL",1);
                                gotoxy(x1,y1);
                                normalmode();
                            }

                        }
                            print_line_to_line(edited,1+Y,26+Y,"NORMAL",1);
                            gotoxy(x1,y1);
                            normalmode();

            }else if(!strcmp(command,"replace")){
               // printf("jfjfjksdjafkdfsja");
                replace_vim();
                //visualmode();
                x1=wherex(); y1=wherey();
                print_line_to_line(edited,1+Y,26+Y,"NORMAL",1);
                gotoxy(x1,y1);
                if(getch()){
                normalmode();
                }
                check=1;
            }else{
             //   printf("%d",!strcmp(command,"createfile"));
                choose(command);
                gotoxy(11,29);

            }
            x1=wherex(); y1=wherey();
            if(check==1){

                gotoxy(1,30);
                textcolor(GREEN);
                cprintf("SUCCESS!");

                textcolor(WHITE);
                gotoxy(x1,y1);
            }else if(check==-1){
                gotoxy(1,30);
                textcolor(RED);
                cprintf("FAIL!");

                textcolor(WHITE);
                gotoxy(x1,y1);
            }
                if(getch()){
                    gotoxy(1,30);
                    cprintf("                                       ");
                  gotoxy(11,29);
                    cprintf("                                       ");
                    gotoxy(11,29);
                }


    }

return;
}

void uuu(){
    get_switch();
    long length=get_file_str();
    edited=malloc(length);

    strcpy(edited,in_file);
    printf("%s\n",edited);
    save_edited();
return;
}
