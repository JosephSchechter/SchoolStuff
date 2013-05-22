#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
		int data[27], length[27];
		char str_temp[1024];
		char bin_temp[1024];
		
		int scan_ret;
		
		//scan until we reach either the end of the file
		while(scan_ret = scanf("%s %d",str_temp,&data[0]) != 2){
			if(scan_ret == EOF){
				printf("Incorrectly formatted file!\n");
				exit(-1);	
			}
		}
		
		int n=1, str_length, non_zero_char = 0, totaled_occurances=0;
		
		float total_bits = 0;
		while(scanf("%s %d %s",str_temp, &data[n], bin_temp) == 3){
			if(data[n] < 0){
					length[n] = 0;
			}else{
				str_length = strlen(bin_temp);
				if(str_length > 0){
					totaled_occurances += data[n];
					non_zero_char++;
					length[n] = strlen(bin_temp);
					total_bits += length[n] * data[n];
				}else{
					printf("Binary length of 0 with a character with > 0 number of occurences?\n");
					exit(-1);
				}
			}
			n++;
			if(n > 26){
				break;	
			}
		}
		
		if(totaled_occurances != data[0]){
			printf("Reported Occurances doesn't equal total summed occurances? (%d vs. %d)\n",data[0],totaled_occurances);
		}
		
		printf("Total Characters Reported: %d \nTotal Characters with > 0 Occurances: %d \nTotal Character Occurances: %d \nTotal bits in solution: %g\n",(n-1),non_zero_char,totaled_occurances,total_bits);

}
