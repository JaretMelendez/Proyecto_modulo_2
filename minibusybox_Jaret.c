/* 	Description: 	Implementation of a mini busybox, this mini busybox must contain some
					functions give the instructions of the activity.
	Creation date:	September 15, 2022
	Code creator: 	Jaret Mohamet Melendez Perez	*/

// ----- Libraries -----
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <ctype.h>
#include <malloc.h>
#include <dirent.h>
#include <utime.h>

// ----- cat function -----
int cat(const char *filename){
// ----- File opening -----
	int fd = open (filename, O_RDONLY);
// ----- Check if the file exists or can be opened -----
	if (fd == -1)
  	{
    	perror ("Error opening file");
    	return 0;
  	}
// ----- Get size of the file content -----
	int sizeinfo = lseek(fd,0,SEEK_END);
  	lseek(fd,0,SEEK_SET);
// ----- Reserve memory to allocate the contents of the file -----	
  	char *letters = (char*)malloc(sizeinfo*sizeof(char));
// ----- File reading -----
	read (fd, letters, sizeinfo);
// ----- Print in the terminal the content of the file -----
	printf("%s",letters);
// ----- File closure -----
	close(fd);
// ----- Freeing reserved memory -----
	free(letters);

	return 0;
}
// ----- ls function -----
void ls(const char *filename){
	char filenamels[3];
    DIR *binder;
    struct dirent *file;
// ----- Condition for election of directory or current directory -----
	if(filename == NULL){
		strcpy(filenamels,"./");
		binder = opendir(filenamels);
	}
	else {
		binder = opendir(filename);
	}
// ----- Garbage disposal and terms that are not necessary -----
	char delimiter[] = "\n \t";
    if (binder != NULL){
        while ((file = readdir(binder))) {
			char *token = strtok (file->d_name, delimiter);
			if(token != NULL){
				if(strcmp(token,"..") != 0 && strcmp(token,".") != 0)
// ----- Print the result in the terminal -----
					printf("%s\n",token);
			}
		}
// ----- File closure -----
        closedir(binder);
	}
	else
        perror ("Error al abrir el directorio ");
}
// ----- sleep function -----
int sleepf(int seg){
// ----- Use of the sleep() function -----
	sleep(seg);
}
// ----- touch function -----
int touch(const char *filename){
// ---- Open or create file -----
	int fd = open(filename,O_RDONLY|O_CREAT|O_TRUNC);
// ----- Condition that evaluates whether the file can be opened or created at given path -----
	if (fd == -1)
  	{
    	perror ("Error opening file");
    	return 0;
  	}
	else{
// ----- Update date of access and modification of the indicated file -----
		struct utimbuf actualtime;
		time(&actualtime.actime);
		time(&actualtime.modtime);
  		utime(filename,&actualtime);
	}
// ----- File closure -----
	close(fd);
}
// ----- mkdir function -----
void mkdirn(const char *filename){
	DIR *binder;
	struct dirent *File;
	int info;
// ----- File opening -----
	binder = opendir(filename);
// ----- Check if the file exists -----
	if(binder == NULL){
		info = mkdir(filename,0700);
// ----- Check if the path is valid to create the file -----
		if(info != -1)
			printf("File created successfully\n");
		else 
			perror ("Error with given path");
	}
	else 
		printf("File exists\n");
// ----- File closure -----
	closedir(binder);
}
// ----- uptime function -----
int uptime(){
	FILE * updatetimefile; 
// ----- File opening -----
	updatetimefile = fopen("/proc/uptime","r");
// ----- Declaration of variables -----
	char uptime_string[50];
	long uptime = 0;
	int auxiliary,day,hours,minutes, seconds= 0;
// ----- Open file verification -----
	if(updatetimefile == NULL){
		printf("Can't read file: /proc/uptime\n");
		return 0;
	}
	
	fgets(uptime_string,12,updatetimefile);
// ----- File close -----
	fclose(updatetimefile);
// ----- Convert string to numeric data -----
	uptime = strtol(uptime_string,NULL,10);
// ----- Transformation of data from seconds to days, hours, minutes and seconds -----
	day = uptime/86400;
	auxiliary = uptime%86400;
	hours = auxiliary/3600;
	auxiliary = auxiliary%3600;
	minutes = auxiliary/60;
	auxiliary = auxiliary%60;
	seconds = auxiliary;
	printf("%i:%i:%i:%i\n",day,hours,minutes,seconds);
}

// ----- Principal Function -----
void main(int argc, char *argv[]){
// ----- It is verified in "argv[1]" to send as a parameter in the function that requires it -----
	const char *filename = argv[1];
	int flag = 0;
// ----- It is verified in "argv[0]" that the function is going to be used and it is called -----
	if(strcmp(argv[0],"./ls") == 0){
		ls(filename);
	}
	else if(strcmp(argv[0],"./touch") == 0){
		touch(filename);
	}
	else if(strcmp(argv[0],"./cat") == 0){
		cat(filename);
	}
	else if(strcmp(argv[0],"./sleep") == 0){
// ----- The string that is not empty or has only characters that are numbers is evaluated -----
		if(argv[1] != NULL){
			int length = strlen(argv[1]);
			char auxiliar[length];
			strcpy(auxiliar,argv[1]);
			for(int count = 0;count<length;count++){
				if(isdigit(auxiliar[count])){
					flag++;
				}
				else{ 
					flag--;
				}
			}
			if(flag == length){
				int seg = atoi(argv[1]);
				sleepf(seg);
			}
			else
				printf("Error in parameters\n");
		}
		else
			printf("Error, missing parameter\n");
	}
	else if(strcmp(argv[0],"./mkdir") == 0)
		mkdirn(filename);
	else if(strcmp(argv[0],"./uptime") == 0){
		uptime();
	}
}