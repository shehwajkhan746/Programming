/*
Write a program to read data from the keyboard, write it to a file called INPUT, 
again read the same data from the INPUT file, 
and copy to that another file and also display it on the screen
*/

#include<stdio.h>
#include<file.h>
main()
{
FILE *f1,*f2;
Char c;
Printf(“data input\n\n”)
f1 = fopen(“INPUT”, “w”);
while((c = gerchar())!=EOF)
Putc(c,f1);
fclose(f1);
Printf(“\ndata output\n\n”)
F1 = fopen(“INPUT”, “r”);
while((c = gerchar())!=EOF)
Putc(“%c”,c);
fclose(f1);
//copying f f1 data into f2
f1=fopen(file1,”r”)
if(f1=NULL)
{
printf(“no data”);
exit(0):
}
f2=fopen(file2,”w”);
If(f2=null)
{
Printf(“cannot able to open”);
exit(0);
}
while((ch==getc(f1)!=EOF)
putc(ch,f2);
printf(“completed”);
fclose(f1);
fclose(f2);
}