/* Description:  "Identify existing memory leaks and fix them."
   Creation date: September 12,2022
   Code creator:  Jaret Mohamet Melendez Perez
*/
// ----- Libraries -----
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

// ----- Principal Function -----
void main(){
	char *path = NULL;
// ----- Infinite Loop -----
	while(1) {
		path = malloc(100);// -> Reserve a blockof memory
		free(path);// -> Free previously allocated memory in "path"
		path = NULL;
		path = strdup("STRING");// -> The "strdup" function also performs a similar effect to "malloc" in that memory must be freed
		free(path);// -> Free previously allocated memory in "path"
		path = NULL;
	}

}
