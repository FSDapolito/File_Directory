/*
   Scrivere un programma C che
   rimuove un hard link da tutti i file regolari della directory corrente, 
   ad eccezione dell’eseguibile stesso
   e stampi il nome di ciascun file, 
   la dimensione ed i permessi di lettura, 
   scrittura ed esecuzione per il gruppo.
*/

#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){

    DIR* dp; 
    struct dirent* dirp; 
    struct stat *buf = NULL; 


    dp = opendir("."); 

    while((dirp=readdir(dp)) != NULL)
    {
     int i=0; 
    stat(dirp->d_name,buf);

      if(buf->st_mode == S_IFREG){
          printf("[%d]File\n",i+1); 
          printf("NAME: %s\n", dirp->d_name);
          printf("SIZE: %lld\n",buf->st_size); 

          printf("\nGroup PERMISSION\n") ; 
          printf("%s",buf->st_mode&S_IRGRP ? "r" : "-"); 
          printf("%s",buf->st_mode&S_IWGRP ? "W" : "-"); 
          printf("%s",buf->st_mode&S_IXGRP ? "x" : "-"); 

      }
      i++; 
      
    }
    
    return 0; 
}