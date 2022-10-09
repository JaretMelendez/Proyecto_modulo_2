/* Description:  "Program designed to suspend the computer after
				  reading 100 bytes of data from the mouse."
   Creation date: September 08,2022
   Code creator:  Jaret Mohamet Melendez Perez
*/
// ----- Libraries -----
#include <stdio.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// ----- Principal function -----
void main(int argc, char **argv) 
{
	int fd,sleep;// -> 
	struct input_event ev;
// ----- Commands to open flies -----
	fd = open(argv[1], O_RDONLY);
	sleep = open("/sys/power/state", O_RDWR);
	for(int i=0; i< 100; ++i)
	{
// ----- Commandsto to read mouse file -----
		read(fd, &ev, sizeof(struct input_event));
// ----- Print mouse data to display in terminal -----
		printf("############## Entry %d ##########\n", i);
		printf("value=%u\n", ev.value);
		printf("time=%li\n", ev.time.tv_sec);
		printf("type=%u\n", ev.type);
		printf("code=%u\n", ev.code);
	}
// ----- Commands to suspend the computer -----
	write(sleep,"mem",3);
	//write(sleep,"standby",7);
// ----- Commands to close files -----	
	close(fd);
	close(sleep);	
}