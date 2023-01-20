

int is_empty(char a[],char warning[]){
        if(strlen(a)==0){
            if(strlen(warning)==0){
            printf("Not empty switch!\n");
            }else{
            printf("Not empty %s!\n",warning);
            }
            return 1;
        }
        return 0;
}

int file_exists(){
    FILE *nfile;
    char root[15];
    strcpy(root,  "root/");
    if (nfile = fopen(strcat(root,SFILE), "r"))
    {

        fclose(nfile);
        printf("File have already exists!\n");
        return 1;
    }

    return 0;

}
int file_not_exists(){
    FILE *nfile;
    char root[15];
    strcpy(root,  "root/");
    if (!(nfile = fopen(strcat(root,SFILE), "r")))
    {
        fclose(nfile);
        printf("File does not exists!\n");
        return 1;
    }

    return 0;

}
