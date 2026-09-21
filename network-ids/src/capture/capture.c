
#include "capture.h"
#include "ids_types.h"
#include "parser.h"
#include <unistd.h>

#include <pcap.h>

#include <signal.h>

#include <stdio.h>

static volatile sig_atomic_t running=1;

static void handle_sigint(int signal)
{
  (void)signal;
  
  running=0;

}

int ids_capture_live(const char *interface)
{

  char errbuf[PCAP_ERRBUF_SIZE];

  signal(SIGINT, handle_sigint);
  
  pcap_t *handle = pcap_open_live(
        interface,
        BUFSIZ,
        1,
        1000,
        errbuf
        );
        
    if( handle == NULL) 
     {
        fprintf(stderr, "pcap_open_live failed: %s\n",errbuf);
        return -1;
     }
     
   
   printf("Capturing live packet on interface: %s\n",interface);
   printf("Press Ctrl+C to stop .\n");
   
   
   while(running)
   {
     struct pcap_pkthdr *header;
     const u_char *data;
     
     int result = pcap_next_ex(handle, &header,&data);

     
     if(result == 1 ) {
       ids_packet_t packet;
       
       ids_parse_result_t parse_result =  ids_parse_packet(data,header->caplen,&packet);        

       if(parse_result == IDS_PARSE_OK) 
           printf("EtherType: 0x%04X\n",packet.ethernet.ether_type);
       else 
           printf("Packet parsing failed.\n");
    
     }
     else if(result == 0) 
        continue;
    
     else {
        fprintf(stderr, "Capture error: %s\n",pcap_geterr(handle));
        break;
     } 
     
   }

   pcap_close(handle);
   printf("Capture stopped\n");

   return 0;

} 
