#include <stdio.h>
#include <string.h>
#include "input.h"


int input_get_integer(const char *prompt) {
   int value;

   printf("%s",prompt);
   scanf("%d",&value);

   return value;
}

void input_get_string(const char *prompt,char *buffer,size_t size) {
   printf("%s",prompt);

   
   if(fgets(buffer,size,stdin)!=NULL) {

       buffer[strcspn(buffer,"\n")]='\0';
    }

}

void input_set_flag(Packet *packet,char *flag_type,uint16_t flag,int *atleast){
   int choice;
   char prompt[50];
   snprintf(prompt,sizeof(prompt),"Set %s flag? (0/1): ",flag_type);

   choice = input_get_integer(prompt);
   if(choice)
     {
       packet_set_flag(packet,flag);
       atleast++;
     }
 }
   

void input_get_flags(Packet *packet) {

  int flag_enable=0;

    input_set_flag(packet,"ACK",FLAG_ACK,&flag_enable);
    
    input_set_flag(packet,"SYN",FLAG_SYN,&flag_enable);

    input_set_flag(packet,"ERROR",FLAG_ERROR,&flag_enable);

    input_set_flag(packet,"PRIORITY",FLAG_PRIORITY,&flag_enable);
   
       

    getchar();

}


PacketType input_get_type(){

   int choice;

   puts("Select packet type: ");
   printf("1. DATA\n");
   printf("2. ACK\n");
   printf("3. ERROR\n");

   choice = input_get_integer("Enter choice: ");

   switch(choice){
      case 1: 
             return PACKET_DATA;
             
      case 2: 
             return PACKET_ACK;
             
      case 3:
             return PACKET_ERROR;
      default:
             return 0;
    }
   
}


uint8_t input_get_version() 
{ 
  return (uint8_t) input_get_integer("Enter version: "); 
}


uint32_t input_get_sequence() 
{
  return (uint32_t) input_get_integer("Enter sequence: ");
}
