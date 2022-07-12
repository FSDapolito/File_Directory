/*
Scrivere un programma in C che esamini il contenuto della directory corrente,
verificando per ogni file regolare se la sua estensione è .c.
In questo caso, verificarne i permessi di scrittura per il gruppo
e visualizzare sullo standard output il contenuto del secondo file di lunghezza minore.
*/
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>


int checkExt(char []); 

int main(){
    DIR* dp; 
    struct dirent* dirp; 
    struct stat buf; 
    int minore=INT_MAX,secondoMinore=INT_MAX-1;
    char fileMinore[1024]; 
    int fd;  

    dp=opendir("."); 
    if(dp==NULL){
        printf("Errore apertura directory\n"); 
        exit(0); 
    }

    while((dirp=readdir(dp)) != NULL){
        lstat(dirp->d_name,&buf); 
        if(S_ISREG(buf.st_mode)){
            if(buf.st_size < secondoMinore){
                fd = open(dirp->d_name,O_RDONLY); 
                secondoMinore = buf.st_size; 
                while(read(fd,fileMinore,1024)); 
            }else{
                minore = secondoMinore; 
            }
            //il file è regolare 
            if(checkExt(dirp->d_name)){
                 if(buf.st_mode & S_IRGRP){
                    printf("Il file %s ha i permessi di lettura per il gruppo\n",dirp->d_name); 
                }
                if(buf.st_mode & S_IWGRP){
                    printf("Il file %s ha i permessi di scrittura per il gruppo\n",dirp->d_name); 
                }
                 if(buf.st_mode & S_IXGRP){
                    printf("Il file %s ha i permessi di esecuzione per il gruppo\n",dirp->d_name); 
                }
            }
        }
    }

    puts(fileMinore); 

    return 0; 
}

int checkExt(char fileName[]){
    if((fileName[strlen(fileName)-1]) == 'c')
    return 1; 
    else 
    return 0; 
} 