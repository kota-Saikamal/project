#include <stdio.h>
#include "storage.h"
#include "validation.h"

void packet_save(const uint8_t *buffer, size_t size, const char *filename) 
{
   FILE *file = fopen(filename,"wb");

   if(!(validate_extension(filename)) )
   {
      printf("Insert file with proper path\n");
      return;
   }
   
   fwrite(buffer,1,size,file);

   fclose(file);
   printf("Data as written to %s\n",filename);
   
 }


int packet_upload(uint8_t *buffer, size_t size, const char *filename)
{ 

   
   FILE *file = fopen(filename,"rd");

   if(!(validate_extension(filename)) )
   {
     printf("Insert file with proper path\n");
     return 0;
   }

  size_t bytes = fread(buffer,1,size,file);

  fclose(file);
  return (int)bytes;
}

