/*
   Remove an hard link from regular files in the current directory execpt executable file and print each file name, its size and group permissions
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
