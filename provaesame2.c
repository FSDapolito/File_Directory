/*
    SCRIVERE UN PROGRAMMA C CHE PRESA UNA DIRECTORY COME PARAMETRO DA RIGA DI COMANDO PROVVEDA A SCORRERLA ALLO SCOPO DI STAMPARE TUTTI I NOMI
    DI TUTTI I FILE REGOLARI E LE LORO DIMENSIONI CONTENUTI IN TALE DIRECTORY SE QUESTI HANNO I DIRITTI DI SCRITTURA E LETTURA
    PER IL PROPRIETARIO E PER GLI ALTRI.
*/

#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_dir(char*); 
void printf_file_name(DIR *); 
void check_permessi(struct stat); 

int main(int argc, char** argv){

    if(argc != 2){
        printf("Hai dimenticato di inserire la directory\n"); 
        exit(0); 
    }else
    {    
        check_dir(argv[1]); 
    }
    return 0; 
}

void check_dir(char* directory){
    char *dir; 
    dir = (char*)malloc(strlen(directory)* sizeof(char)); 
    strcpy(dir,directory); 
    printf("\nDirectory inserita ---> %s\n\n\n",dir);

    DIR* dp; 
    dp = opendir(dir); 
    printf_file_name(dp);      
}

void printf_file_name(DIR *dp){
    struct dirent *dirp; 
    struct stat buf; 
    int i=0; 
    while((dirp=readdir(dp))!= NULL){
        stat(dirp->d_name,&buf); 
        printf("[%d] FILE\t_____[ %s ]\t",++i,dirp->d_name); 
        check_permessi(buf); 
        printf("\n\n"); 
    }
}

void check_permessi(struct stat buf){
    if(buf.st_mode & S_IRUSR && buf.st_mode & S_IWUSR && buf.st_mode & S_IROTH && buf.st_mode & S_IWOTH )
        printf("Il file ha i permessi di lettura e scrittura per il proprietario e per gli altri"); 
}