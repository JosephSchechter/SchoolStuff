#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>



typedef struct student {
char name[32];
char phone[16];
char address[128];
} student_t;


int main(int argc, char* argv[]){

	student_t st;
	char p[10];
	char isquit = 'n';
	int id = 0;
	char idstr[9999];
	
	
	FILE * pFile;
	pFile = fopen("myfile.txt", "w");
	if(pFile == NULL){//somehow failed
		printf("fopen failed\n");
		return 0;
	}
	
	while(isquit == 'n'){
		printf("\nNAME >> ");
		fgets(st.name, sizeof(st.name), stdin);
		//printf("\ninput: %s", st.name);
		
		printf("\nPHONE >> ");
		fgets(st.phone, sizeof(st.phone), stdin);
		
		printf("\nADDRESS >> ");
		fgets(st.address, sizeof(st.address), stdin);
		
		//add the ID to the output file
		sprintf(idstr, "ID$%d$ID\n", id);
		
		fprintf(pFile, "%s", idstr);
		fprintf(pFile, "%s", st.name);
		fprintf(pFile, "%s", st.phone);
		fprintf(pFile, "%s", st.address);
		
		
		
		
		printf("\nRecord created with ID: %d", id);
		
		printf("\nQUIT (y/n) >> ");
		isquit = getchar();
		if (isquit == 'y'){
			break;
		}
		else{
			fgets(p, sizeof(p), stdin); //this captures the overflow
			id++;
		}
		
	}
	
	fclose(pFile);
	
	
	return 0;
}
