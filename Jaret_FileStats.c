/* Description:  "Program that obtains statistics for a given file,
                  that file is used as an argument to main()."
   Creation date: September 04,2022
   Code creator:  Jaret Mohamet Melendez Perez
*/
// ----- Libraries -----
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <ctype.h>
#include <malloc.h>

// ----- Function performed for the purpose of counting characters -----
int numbercharacter (const char *filename, int bytes)
{
  char delimiter[] = "\n\t ";
  int count=0, countletters, fd;
  fd = open (filename, O_RDONLY);
  if (fd == -1)
  {
    perror ("Error opening file");
    return 0;
  }
  int sizeinfo = lseek(fd,0,SEEK_END);
  lseek(fd,0,SEEK_SET);
  char *letters = (char*)malloc(sizeinfo*sizeof(char));
  read (fd, letters, bytes);
  char *token = strtok (letters, delimiter);
  if (token != NULL)
  {
    while (token != NULL)
	  {
	    countletters = strlen (token) + countletters;
      int indicator;
      int lengthtoken = strlen(token);
      for (indicator = 0;indicator < lengthtoken; indicator++)
      {
        char current = token[indicator];
        int Word = current;
        if(Word == -95)
          Word = 160;
        else if(Word == -87)
          Word = 130;
        else if(Word == -83)
          Word = 161;
        else if(Word == -77)
          Word = 162;
        else if(Word == -70)
          Word = 163;
         else if(Word == -79)
          Word = 164;
        else if(Word == -127)
          Word = 181;
        else if(Word == -119)
          Word = 144;
        else if(Word == -115)
          Word = 214;
        else if(Word == -109)
          Word = 224;
        else if(Word == -102)
          Word = 223;
         else if(Word == -111)
          Word = 165;
        
        if(Word > 32 && Word <255)
          count++;
      }
	    token = strtok (NULL, delimiter);
	  }
  }
  close (fd);
  return count;
}
// ----- Function performed for the purpose of detecting the type of file entered -----
char* typefile(int mode, int typef)
{
  char* type = malloc(20);
  switch (mode & typef)
  {
    case S_IFBLK:
      strcpy (type, "Block device");
      break;
    case S_IFCHR:
      strcpy (type, "Character device");
      break;
    case S_IFDIR:
      strcpy (type, "Directory");
      break;
    case S_IFIFO:
      strcpy (type, "FIFO/pipe");
      break;
    case S_IFLNK:
      strcpy (type, "Simlink");
      break;
    case S_IFREG:
      strcpy (type, "Regular file");
      break;
    case S_IFSOCK:
      strcpy (type, "Socket");
      break;
    default:
      strcpy (type, "Unknown?");
      break;
  }
  return type;
}
// ----- Principal function -----
int main (int argc, char *argv[])
{
  const char *filename = argv[1];// -> The variable represents the name or path of the file to work with
  int characternumber = 0;// -> The variable represents the number of characters that the file has
  time_t t;// -> The variable represents time, so it was decided to call "t" for more practical
  char* type;// -> The variable represents the file type
  struct stat info;
  struct passwd *pws;
  stat (filename, &info);
  type = typefile(info.st_mode, S_IFMT);
  characternumber = numbercharacter(filename, info.st_size);
  // ----- Print the data to display in the terminal -----
  printf ("File o link: \t\t\t\t%s\n", filename);
  printf ("Type of file: \t\t\t\t%s\n", type);
  printf ("File size: \t\t\t\t%ld bytes\n", info.st_size);
  if ((pws = getpwuid (info.st_uid)) != NULL)
    printf ("Owner: \t\t\t\t\t%-8.8s\t-\t%ld \n", pws->pw_name,(unsigned long) info.st_uid);
  else
    printf ("Owner: \t\t\t\t\t%ld \n", (unsigned long) info.st_uid);
  printf ("Creation date:\t\t\t\t%s", ctime(&info.st_ctime));
  printf ("Modes:  \t\t\t\t%ld\n", (unsigned long) info.st_mode);
  printf ("Permissions:\t\t\t\t");
  printf ((S_ISDIR (info.st_mode)) ? "d" : "-");
  printf ((info.st_mode & S_IRUSR) ? "r" : "-");
  printf ((info.st_mode & S_IWUSR) ? "w" : "-");
  printf ((info.st_mode & S_IXUSR) ? "x" : "-");
  printf ((info.st_mode & S_IRGRP) ? "r" : "-");
  printf ((info.st_mode & S_IWGRP) ? "w" : "-");
  printf ((info.st_mode & S_IXGRP) ? "x" : "-");
  printf ((info.st_mode & S_IROTH) ? "r" : "-");
  printf ((info.st_mode & S_IWOTH) ? "w" : "-");
  printf ((info.st_mode & S_IXOTH) ? "x" : "-");
  printf ("\n");
  printf ("Number of alphanumeric characters:  \t%d\n", characternumber);
  printf ("Inode: \t\t\t\t\t%ld \n", info.st_ino);
}