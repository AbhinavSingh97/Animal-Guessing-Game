#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL 10

char * readline(FILE *inFile);

char * readline(FILE * inFile)
{
   char *line = NULL;
   char *tmp = NULL;
   size_t size = INITIAL;
   size_t index = 0;
   char chr = EOF;

   line = (char *)malloc(size * sizeof(char));

   while(chr)
   {
      chr = fgetc(inFile);
      if(chr == EOF || chr == '\n')
      {
         if(index == 0)
         {
            free(line);
            line = NULL;
            break;
         }
         chr = '\0';
      }
      if(size <= index)
      {
         size *= 2;
         tmp = realloc(line,size*sizeof(char));
         if(!tmp)
         {
            free(line);
            line = NULL;
            break;
         }
         line = tmp;
      }
      line[index++] = chr;
   }
   return line;
}