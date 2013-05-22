// Joseph Schechter Final Project c file
#include <stdio.h>
#include <string.h>
#include <malloc.h>

int size = 0;



int assemblypart(char* str){
	int sc = 0;		//the swap counter
	__asm__(
			"movl	$0, %0\n\t"
			"movb	(%1), %%al\n\t"	//1st char into al
			"addl	$1, %1\n\t"		//next mem addr
			"movb	(%1), %%bl\n\t"	//2nd char into bl
			"cmpb	%%al, %%bl\n\t"
			"jle	end\n\t"		//if the 2nd char is less or equal, jumpt to end
			"movb	%%al, (%1)\n\t"	//move 1st char into 2nd's mem addr
			"addl	$-1, %1\n\t"	//1st mem addr
			"movb	%%bl, (%1)\n\t"	//move 2nd char into 1st's mem addr
			"movl	$1, %0\n\t"		//output is 1 (swap occured, sc==1)
			"end:\n\t"				//jump here if less of equal
			:"=&r"(sc)				//output- (swap counter)
			:"r"(str)			//input- mem addr of 1st character being compared
			:"memory", "eax", "ebx"	//clobber- memory, eax and ebx are used and are not in input or output
			);
	return sc;
}




//int sort(char str[]){
int sort(char* str){
	int limit = strlen(str);
	int swapped=0;
//	int bottom = 0;
	
	do {
		swapped=0;	//reset swapped
		int j;
		for(j=0; j<limit-1; j++) {	//from the top
			swapped = swapped + assemblypart(&str[j]); //if there is a dis-order swap
		}
		if(swapped > 0) {
			swapped = 0;	//reset swapped
			for(j=limit-2; j>=0; j--) { //from the bottom to the top
				swapped = swapped + assemblypart(&str[j]); //if there is a dis-order swap
			}
		}
	} while (swapped>0);	//stops the loop when no swaps are done anymore
	
	return 0;
}




int fp() {
	int arraysize = 128;								//starting array size
	char *str = malloc(sizeof(char)*arraysize);		//make the array assign it to str
	char ch;
	int i;
	scanf("%c", &ch);								//scan it 1 char at a time
	
	if(ch == '\n'){
	printf("\nYou put in a newline only.\n");
	str[size]='\n';
	printf("The size of the string is %d characters including null and its sorted version is: %s\n", size, str);
	}
	
	else{
		while(ch != '\n'){	
			str[size] = ch;				//str[0,1,2...]= the character
			size++;						//increment
			if (size==arraysize-1) {	//if the size is getting close to over
				arraysize = 2*arraysize;
				char *newarray = malloc(sizeof(char)*arraysize);	//new array double the size
				for(i=0; i<=size; i++){
					newarray[i]=str[i];		//copy str into newarray	
				}
				free(str);
				str=newarray;		//reassigned
			}
			scanf("%c", &ch);		//next character
		}
		str[size+1] = '\n';		//the last part of the string
		
	
		printf("size of the string is %d characters (not including null)\n", size);
		printf("the string is: %s\n", str);
	
		sort(str);
		printf("\n\nThe sorted string is: %s\n", str);
	}
	size=0;
	free(str);
	return 0;
}




