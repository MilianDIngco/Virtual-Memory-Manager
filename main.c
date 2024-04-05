#include <stdlib.h>
#include <stdio.h>

int check(int* bitmap, int pos) {
    return *bitmap & (1 << pos);
}

int main(int argc, char** argv) {

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
	fp = fopen("addresses.txt", "rt");
	int logical_address = 0;
	while(fscanf(fp, "%d", &logical_address) != -1) {
    /* read logical address from file addresses.txt */
	
			printf("%d\n", logical_address);

    // extract offset value teehee
		int offset = 0;
		for(int i = 0; i < 8; i++){
			offset += check(&logical_address, i);
		}
 
	// extract page number hoohoo
		int page_num = 0;
		for(int i = 8; i < 16; i++) {
			page_num += check(&logical_address, i);
		}

    /* check TLB */
    //increment TLB hit

    /* if TLB miss check page table */

    /* if page fault, load from backing store */
    //increment page fault

    // remove page from stack and use it

    /* get physical address */

    /* compare logical and physical address from correct array  */

    /* sprintf logical address to out1.txt */

    /* sprintf physical address to out2.txt */

    /* sprintf byte value to out3.txt */

	}

    // FIGURE OUT PAGE REPLACEMENT LOL


    return 0;

}
