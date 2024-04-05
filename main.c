#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define TLB_SIZE 16
#define P_MEM_SIZE 65536
#define PAGE_SIZE 256
#define N_PAGE 256

int TLB[TLB_SIZE][2];		//[PAGE #][FRAME #]
int PAGE_TABLE[N_PAGE][2];	//[PAGE #][VALID/INVALID BIT]
int AVAIL_FRAME[N_PAGE];
int stack_head = N_PAGE;	
char P_MEM[P_MEM_SIZE];
int n_pagefault = 0;

int check(int* bitmap, int pos) {
    return *bitmap & (1 << pos);
}

int pop() {
	return AVAIL_FRAME[stack_head--];
}

void push(int frame_num) {
	AVAIL_FRAME[++stack_head] = frame_num;
}

int is_empty() {
	return stack_head == 0;
}

int main(int argc, char** argv) {

	/* set all valid/invalid bits to false */
	for(int i = 0; i < N_PAGE; i++) {
		PAGE_TABLE[i][1] = 0;
	}

	/* set available frame stack*/
	for(int i = 0; i < N_PAGE; i++) {
		AVAIL_FRAME[i] = i;
	}

    /* store correct.txt into a 2d int array */
	int n_row = 1000;
	int n_col = 3;
	int correct_array[1000][3]; 

	FILE* fp = fopen("correct.txt", "rt");
	char* buffer = (char*)malloc(20 * sizeof(char));
	int count = 0;
	int array_count = 0;
	while(fscanf(fp, "%s", buffer) != -1) {
		if(count % 8 == 2) {
			//Virtual Address
			correct_array[array_count][0] = atoi(buffer);
		} else if(count % 8 == 5) {
			//Physical Address
			correct_array[array_count][1] = atoi(buffer);
		} else if(count % 8 == 7) {
			//Value
			correct_array[array_count++][2] = atoi(buffer);
		}
		count++;
	}
	

	for(int i = 0; i < n_row; i++) {
		//printf("V: %d  ", correct_array[i][0]);
		//printf("P: %d  ", correct_array[i][1]);
		//printf("Val: %d\n", correct_array[i][2]);
	}

	fclose(fp);
	free(buffer);
	
    /* create stack with all available frames */

    /* while loop */
	fp = fopen(argv[1], "rt");
	int logical_address = 0;
	while(fscanf(fp, "%d", &logical_address) != -1) {
    /* read logical address from file addresses.txt */
	
			printf("%d\n", logical_address);

    // extract offset value teehee, digits 0-7
		int offset = 0;
		for(int i = 0; i < 8; i++){
			offset += check(&logical_address, i);
		}
 
	// extract page number hoohoo, digits 8-15
		int page_num = 0;
		for(int i = 8; i < 16; i++) {
			page_num += ((check(&logical_address, i) != 0) ? pow(2, i - 8) : 0);
		}

    /* check TLB */
    //increment TLB hit

    /* if TLB miss check page table */
	//USES INVERTED PAGE TABLE
	// loop through page table until find page number, return index
	int frame_num = -1;
	for(int i = 0; i < N_PAGE; i++) {
		if(PAGE_TABLE[i][0] == page_num && PAGE_TABLE[i][1] != 0) {
			frame_num = i;
			break;
		}
	}

    /* if page fault, load from backing store */
    if(frame_num == -1) {
		//increment page fault
		n_pagefault++;
		// remove page from stack and use it
		if(!is_empty()) {
			frame_num = pop();
		} else {
			//select frame to replace using page replacement algorithm
			frame_num = 0; 	//FOR NOW JUST REPLACES FRAME 0 
		}
		
		//randomly seek to certian positions of BACKING_STORE
		int physical_address = frame_num << 8;

		FILE* bstore_fp = fopen("BACKING_STORE.bin", "rb");
		fseek(bstore_fp, physical_address, SEEK_SET);

		char buffer[PAGE_SIZE]; //page

		// size_t bytes_read = fread(buffer, 1, sizeof(buffer), bstore_fp);
		char test_byte = fread(&test_byte, 1, 1, bstore_fp);
		
		printf("Testing One Byte: %02x\n", test_byte);
		fclose(bstore_fp);
		//LOADS FRAME INTO PHYSICAL MEMORY


	}
    /* get physical address */

    /* compare logical and physical address from correct array  */

    /* sprintf logical address to out1.txt */

    /* sprintf physical address to out2.txt */

    /* sprintf byte value to out3.txt */

	}

    // FIGURE OUT PAGE REPLACEMENT LOL


    return 0;

}
