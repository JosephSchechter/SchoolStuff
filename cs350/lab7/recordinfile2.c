#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
//#include <cstdio.h>



typedef struct student {
char name[32];
char phone[16];
char address[128];
} student_t;

int main(int argc, char* argv[]){

	student_t st;
	char garbage[999];
	int id;
	char idin[999];
	char idstr[999+7];
	char isquit = 'n';
	char idinfile[999];
		

	FILE * pFile;
	pFile = fopen("myfile.txt", "r");
	if(pFile == NULL){//somehow failed
		printf("fopen failed\n");
		return 0;
	}
	
	
	int len;
	
	while(isquit == 'n'){
		printf("\nID >> ");
		fgets(idin, sizeof(idin), stdin);
		id = atoi(idin);
		printf("Asked for ID %d\n", id);
		
		sprintf(idstr, "ID$%d$ID\n", id);
		
		

		while( fgets(idinfile, sizeof(idinfile), pFile) != NULL){
			if(strcmp(idinfile, idstr) == 0){
				//printf("Found id\n");
				
				fgets(st.name, sizeof(st.name), pFile);
				len = strlen(st.name);
				if(st.name[len-1] == '\n'){
					st.name[len-1] = '\0';
				}
				
				fgets(st.phone, sizeof(st.phone), pFile);
				len = strlen(st.phone);
				if(st.phone[len-1] == '\n'){
					st.phone[len-1] = '\0';
				}
				
				fgets(st.address, sizeof(st.address), pFile);
				len = strlen(st.address);
				if(st.address[len-1] == '\n'){
					st.address[len-1] = '\0';
				}
				
				printf("Record: ");
				printf("%s, %s, %s\n", st.name, st.phone, st.address);
				break;
			} 
		}
		if( strcmp(idinfile, idstr) != 0){
			printf("Record: Not Found\n");
		}
		
		printf("\nQUIT (y/n) >> ");
		isquit = getchar();
		if (isquit == 'y'){
			break;
		}
		else{
			fgets(garbage, sizeof(garbage), stdin); //this captures the overflow
			fseek(pFile, 0, SEEK_SET);	//move to beginning of file again
		}	
	}
	
	fclose(pFile);


	return 0;
}
