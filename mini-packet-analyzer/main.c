#include <stdio.h>
#include "packet.h"
#include "parser.h"

int main(void)
{
int choice;

while (1)
{
    printf("\n");
    printf("===== MINI PACKET ANALYZER =====\n");
    printf("1. Create Packet\n");
    printf("2. Parse Packet\n");
    printf("3. Exit\n");
    printf("================================\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            create_packet();
            break;

        case 2:
            parse_packet();
            break;

        case 3:
            printf("Exiting Packet Analyzer...\n");
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
    }
}

return 0;


}
