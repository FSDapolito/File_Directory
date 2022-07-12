/*
	C program that, having received the name of a file, looks for it in the
	current directory and if it is a regular file larger than 1Kb make it possibly
	the cut and paste into the directory pointed to by a symbolic link in the current directory.
*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *arv[])
{
	char name[1024];
	DIR *dp;
	struct dirent *dirp;
	char cwd[30];
	struct stat buf;
	struct stat linkbuf;

	printf("File to search: ");
	scanf("%s", name);
	getcwd(cwd,sizeof(cwd));

	printf("Directory: %s.\n", cwd);			
	if( (dp=opendir(cwd)) == NULL )				
	{
		printf("Could not open directory.\n");
		exit(0);
	}
	char link[1024];
	int finddir = 1, findfile = 1;
	while( (dirp=readdir(dp)) != NULL && (finddir || findfile))			
	{
	
		if( lstat(dirp->d_name, &buf) < 0 )	
		{
			printf("Lstat error.\n");
			closedir(dp);
			exit(0);
		}
		printf("Processing of ......  %s\n",dirp->d_name);
		if(findfile)								
		{
			if(strcmp(dirp->d_name,name) == 0)	
			{
				if(S_ISREG(buf.st_mode) && buf.st_size > 1000)	
				{
					printf("File [%s] is regular with size over 1Kb.\n",name);
					findfile = 0;
				}
			} 
		}
		if(finddir)									
		{
			if(S_ISLNK(buf.st_mode))						
			{
				
				readlink(dirp->d_name,link, sizeof(link));		
				link[strlen(link)]='\0';
				printf("LINK: %s.\n",link);
				if( stat(link, &linkbuf) < 0)				
				{
					link[strlen(link)-1]='\0';
						printf("Stat error.\n"); 
				}
				if( S_ISDIR(linkbuf.st_mode) )					
				{
					printf("The link %s points to the file %s that is a directory.\n", dirp->d_name, link);
					finddir=0;
				}
			}
		}
	}	


	
	if(findfile)					
	{
		printf("File not found or its size is less 1Kb.\n");
	}
	else if(finddir)			
	{
		printf("Symbolic Link not found.\n");
	}
	else
	{
		printf("Cut the file %s and put it in a directory: %s.\n",name,link);	
		int fd1, fd2;
		fd1=open(nome,O_RDONLY);			
		chdir(link);						
		fd2=open(nome,O_WRONLY|O_CREAT);	
		int nread;
		char car;
		
		while((nread=read(fd1,&car,1)) > 0)	
		{
			write(fd2,&car,1);
		}
		close(fd2);
		chdir("..");						
		close(fd1);
		unlink(name);				
	}
	closedir(dp);	
	exit(0);
}
