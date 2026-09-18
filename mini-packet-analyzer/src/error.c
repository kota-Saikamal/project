#include <stdio.h>
#include "error.h"


void error_display(PacketError error) 
{ 
  
   switch(error)
   {
       case ERROR_NONE:
			  break;
       case ERROR_INVALID_VERSION:
       		  printf("Error: Invalid packet version\n");
       		  break;  
       case ERROR_INVALID_TYPE:
			  printf("Error: Invalid packet type\n");
			  break;
       case ERROR_NO_FLAG:
			  printf("Error: No flags in the packet \n");
			  break;
       case ERROR_ACK_FLAG:
       		  printf("Error: Only acknowledgement flag should be in the packet \n");
       		  break;
       case ERROR_DATA_FLAG:
       		  printf("Error: Only acknowledgement and  syn  flag in the packet \n");
       		  break;
       case ERROR_ERROR_FLAG:
       		  printf("Error: Only error flag in the packet \n");
       		  break;
       case ERROR_INVALID_SEQUENCE:
			  printf("Error: Invalid packet sequence\n");
			  break;
       case ERROR_INVALID_LENGTH:
       		  printf("Error: Invalid packet length\n");
       		  break;
       case ERROR_INVALID_PAYLOAD:
       		  printf("Error: Invalid packet payload\n");
       		  break;
        default:
         	  printf("Unkown Error\n");
         
   }                    
}
