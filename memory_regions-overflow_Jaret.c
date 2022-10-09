/* Description:  "Changed the code called "memory_regions.c" in such a way executing it causes a stack overflow."
   Creation date: September 09,2022
   Code creator:  Jaret Mohamet Melendez Perez
*/
// ----- Libraries -----
#include <stdio.h>
#include <stdlib.h>
// ----- Declaration of global variables -----
int var3 = 0;
// ----- Foo2 function -----
void foo2(void) 
{
    printf("I've just printfed \n");
}
// ----- Foo function -----
void foo(int var4) 
{
    static int var1 = 0;
    int var2 = 0;
    int* var5;
    void (*var6)(void) = &foo2;
    var1++;
    var2++;
    var3++;
    var4++;
    
    var5 = (int*)malloc(sizeof(int));
    
    (*var5)++;
// ----- Print result in terminal -----
    printf("var1: %d at %p\n",var1, &var1);
    printf("var2: %d at %p\n",var2, &var2);
    printf("var3: %d at %p\n",var3, &var3);
    printf("var4: %d at %p\n",var4, &var4);
    printf("var5: %d at %p\n",*var5, var5);
    printf("var6: - at %p\n", var6);
    printf("--------------------------\n");
// ----- call function "foo" -----
    foo(0);    
}
// ----- Principal function -----
int main()
{
// ----- Creating an infinite loop -----
	while (1)
// ----- Call function "foo" -----
        foo(0);
    return 0;
}
// ----- Answer to question before session -----
/* -> Answer to the first question, because "var1" performs a behavior similar to that of a global variable, 
      only this variable does not reset its value until it is used and initialized in another function.
   -> Answer to the second question, the change between addresses is only the last two digits.
   -> Answer to the last question, In this question, this line corresponds to the end bracket of the main fuction*/

// ----- Answer to question after session -----
/* -> In this case the function "foo" what it does is reserve memory, the first thing that was done to change the "for" loop
      to a "while" loop inside the main function, to create an infinite loop. Inside the "while" loop, the function "foo" is called
	  indefinitely and in turn inside this function the function "foo" is called again to perform the function processing and cause 
	  the stack saturation and as a consequence cause the stack overflow, in this program the overflow is archived in the iteration 130906.*/