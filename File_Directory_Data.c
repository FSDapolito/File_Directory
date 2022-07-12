#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
	C program that takes the path of a directory and a date as the only command line parameter
	(in the format YYYY / MM / DD, year, month and days), parse the files contained in this directory and,
	for regular files found in that directory which have -rwxrwxrwx and permissions
	which have a last modified date (st_mtime) earlier than the flag in the second parameter supplied on the command line.
*/
int main(int argc, char *argv[]) {
	DIR *dp;
	struct dirent *dirp;
	struct stat buf;
	int year, month, day;
	time_t inputDate;
	
	if (argc != 3) {
		printf("./es221021 <path_directory> <YYYY/MM/DD>\n");
		exit(-1);
	}
	
	if ((dp = opendir(argv[1])) == NULL) {
		printf("ERROR: Could not open  %s", argv[1]);
		exit(-1);
	}
	
	if(sscanf(argv[2], "%4d/%2d/%2d", &year, &month, &day) == 3) {
		struct tm time = {0};
		time.tm_year = year - 1900;
		time.tm_mon = month - 1;
		time.tm_mday = day;
		inputDate = mktime(&time);
	}
	
	while ((dirp = readdir(dp)) != NULL) {
		if(stat(dirp->d_name, &buf) < 0)
			printf("error: stat --> %s\n", dirp->d_name);
		if(S_ISREG(buf.st_mode)) { 
			if((buf.st_mode & S_IRUSR) && (buf.st_mode & S_IWUSR) && (buf.st_mode & S_IXUSR) && 
			   (buf.st_mode & S_IRGRP) && (buf.st_mode & S_IWGRP) && (buf.st_mode & S_IXGRP) && 
			   (buf.st_mode & S_IROTH) && (buf.st_mode & S_IWOTH) && (buf.st_mode & S_IXOTH)) {
			   		if(buf.st_mtime < inputDate)
			   			printf("File: %s\tLast Modified: %s\n", dirp->d_name, ctime(&buf.st_mtime));
			}
		}
	}
		
	closedir(dp);
	
	exit(0);
}
