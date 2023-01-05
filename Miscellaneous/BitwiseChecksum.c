/*
Program to compute and check the checksum over all the data of given packet to check for corrupted data
*/

include <stdio.h>
#include <stdbool.h>

struct Packet {
	short int opcode;
	int address;
	int info[10];
	short int checksum;
} ; 

typedef struct Packet packet;

int checkPacket(packet *pkt){ // if different types of ints, use sizeof(), int = 4 bytes = 32 bits, short int = 2 bytes = 16 bits
    //printf("%d\n", sizeof(pkt->opcode)); --> can get the size of the hexa by doing sizeof(variable) *2, because u need each byte can have 2 numbers, can either be short or long int, cant be mroe because max is 32 bits
	int sum = 0;
    sum = sum ^ (pkt->opcode + (pkt->opcode<<16)); // shifts it 4 digits to the left (16 bits) and duplicates the bits there
    printf("%x\n", sum);
    sum = sum ^ pkt->address;
    for (int i = 0; i < 10; i++) {
        sum = sum ^ pkt->info[i];
    }

    short int newsum = (sum >> 16); // remove 4 digits of the hex, so we only have the first 4

    printf("old sum: %x right shifted: %x\n", sum, newsum);

    if (newsum == pkt->checksum) {
        return 1;
    }
    return 0;
    
}


int main () {
	packet goodpkt = {0x201F, 0xFF2E8801, {0x59472952, 0x17273828, 0xA3472B39, 0xC3822579, 0x39A081EB, 0x5732D967, 0xFEEDBEED, 0x213759CC, 0xEE32495E, 0x01839511}, 0xAF6D};
	packet badpkt = {0x201F, 0xFF2E8801, {0x59472952, 0x172F3828, 0xA3472B39, 0xC3822579, 0x39A081EB, 0x5732D967, 0xFEEDBEED, 0x213759CC, 0xEE32495E, 0x01839511}, 0xAF6D};
	
	if (checkPacket(&goodpkt)) {
		printf("Packet 1 is good!\n");
	} else {
		printf("Packet 1 is bad!\n");
	}
	
	if (checkPacket(&badpkt)) {
		printf("Packet 2 is good!\n");
	} else {
		printf("Packet 2 is bad!\n");
	}
}
