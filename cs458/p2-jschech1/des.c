#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

/*
 Compile the program:
 gcc des.c -o des -lcrypto -I/usr/local/ssl/include -L/usr/local/ssl/lib

 run like:	./des 0123456789abcdef in.txt out.txt 1
			./des 0000000000000000 in.txt out.txt 1
 */

#define ENC 1
#define DEC 0


DES_LONG ctol(unsigned char *c) {
        DES_LONG l;
        l =((DES_LONG)(*((c)++)));
        l = l | (((DES_LONG)(*((c)++)))<<8L);
        l = l | (((DES_LONG)(*((c)++)))<<16L);
        l = l | (((DES_LONG)(*((c)++)))<<24L);
        return l;
};



ltoc(DES_LONG l, unsigned char *c) {
        *((c)++)=(unsigned char)(l&0xff);
        *((c)++)=(unsigned char)(((l)>> 8L)&0xff);
        *((c)++)=(unsigned char)(((l)>>16L)&0xff);
        *((c)++)=(unsigned char)(((l)>>24L)&0xff);
}


int main (int argc, char *argv[])
{
	
	if(argc != 5)
	{
		printf("correct implementation: ./des <key> <inputfile> <outputfile> <ENC/DEC>");
		printf("\nexiting\n");
		return 0;
	}
	
	//is key 16 chars
	if(strlen(argv[1]) != 16)
	{
		printf("the key is not long enough, or is too long (it needs to be 16 hex digits long), exiting\n");
		return 0;
	}
	

	//is key valid chars
	int i;
	for(i = 0; i<16; i++)
	{
		if( (argv[1][i] >= 48 && argv[1][i] <= 57) || (argv[1][i] >= 97 && argv[1][i] <= 102)) //0-9 or a-f
		{
			//printf("key char %d is ok\n", i);
		}
		else
		{
			printf("key char %d is not valid hex, exiting\n", i);
			return 0;
		}
	}
	
	//printf("\ntest3\n");
	
	//DES or ENC correct
	int ed;
	if(strlen(argv[4]) == 1)
	{
		//printf("\ntest4\n");
		//printf("argv[4][0] == %c", argv[4][0]);
		if((argv[4][0] == '0') || (argv[4][0] == '1'))
		{
			//printf("\ntest5\n");
			//correct values, convert to int
			char *tempC = argv[4];
			//printf("tempc == %s\n", tempC);
			ed = atoi(tempC);
			//printf("\ntest6\n");
			//printf("ed = %d\n", ed);
		}
		else
		{
			printf("your enc/dec value is incorrect, exiting\n");
		}
	}
	else
	{
		printf("your enc/dec value is incorrect, exiting\n");
	}
	
	//printf("\ntest7\n");
	
	
	char temp[2];
	int keyI = 0;
	static unsigned char cbc_key[8];
	//printf("test0\n");
	
	for(i=0; i<16; i++)
	{
		temp[0] = argv[1][i];
		i++;
		temp[1] = argv[1][i];
		
		/* Mikhail: 
		 * %x assumes an integer - hence we need a 4-byte variable. 
		 * char is only 1 byte and hence the bus error because
		 * sscanf() writes past the buffer.
		 */	
		int tmp;		
		sscanf(temp, "%x", &tmp);
		
		/* Copy the lowest byte of the integer into a character */
		cbc_key[keyI] = tmp;
		keyI++;
	}

	
//	static unsigned char cbc_key[8] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef};
	
	//testing did i get the right thing
	//printf("test1\n");
	for(i=0; i<8; i++)
	{
		//printf("%x \n", cbc_key[i]);
	}
	
	
	int k;
	des_key_schedule key;
	
	if ((k = des_set_key_checked(&cbc_key,key)) != 0)
	{
//		printf("K = %d\n", k);
		if(k == -1)
		{
			printf("your key parity is not odd\n");
		}
		else if(k == -2)
		{
			printf("your key is weak, provide a better key\n");
		}
		
			printf("Key error, exiting\n");
			return 0;
		//printf("exiting\n");
		//return 0;
	}
//	printf("K = %d\n", k);
	
	
	
	//open the input file for reading
	FILE * inFile;
	inFile = fopen(argv[2], "r");
	if(inFile == NULL){//somehow failed
		printf("fopen for your <input> file failed\n");
		return 0;
	}
	
	
	
	//open the output file for writing
	FILE * outFile;
	outFile = fopen(argv[3], "w");
	if(outFile == NULL){//somehow failed
		printf("fopen for your <output> file failed\n");
		return 0;
	}
	
	
	long in[2];
	char grabBlock[8];
	char startBlock[4];
	char endBlock[4];
	char ch;
	
	
//	char testBlock1[4] = {'a', 'b', 'f', 'g'};
//	long in1 = ctol(testBlock1);
//	printf("ctol of a,b,f,g = %ld\n",in1);
//	ltoc(in1, testBlock1);
//	printf("reverse : %c%c%c%c", testBlock1[0], testBlock1[1], testBlock1[2], testBlock1[3]);
	
	
		int reachedEnd = 1;	//bool of reached EOF or not
		while(reachedEnd == 1)
		{
			//clear grabBlock
			for(i=0; i<8; i++)
			{
				grabBlock[i] = '\0';
			}
			//printf("grabblock cleared\n");
			
			//get 8 chars
			if((fscanf(inFile, "%c", &ch)) != EOF)//grab char0
			{
			//	printf("got a %c\n",ch);
				grabBlock[0] = ch;
				
				if((fscanf(inFile, "%c", &ch)) != EOF)//grab char1
				{
			//		printf("got a %c\n",ch);
					grabBlock[1] = ch;
					
					if((fscanf(inFile, "%c", &ch)) != EOF)//grab char2
					{
			//			printf("got a %c\n",ch);
						grabBlock[2] = ch;
					
					
						if((fscanf(inFile, "%c", &ch)) != EOF)//grab char3
						{
			//				printf("got a %c\n",ch);
							grabBlock[3] = ch;
							
							
							if((fscanf(inFile, "%c", &ch)) != EOF)//grab char4
							{
			//					printf("got a %c\n",ch);
								grabBlock[4] = ch;
							
								
								if((fscanf(inFile, "%c", &ch)) != EOF)//grab char5
								{
			//						printf("got a %c\n",ch);
									grabBlock[5] = ch;
								
								
									if((fscanf(inFile, "%c", &ch)) != EOF)//grab char6
									{
			//							printf("got a %c\n",ch);
										grabBlock[6] = ch;
									
										if((fscanf(inFile, "%c", &ch)) != EOF)//grab char7
										{
			//								printf("got a %c\n",ch);
											grabBlock[7] = ch;
										}
										else
										{
											printf("reached the end at char7\n");
											grabBlock[6] = '\0';
											reachedEnd=0;
										}
									}
									else
									{
										printf("reached the end at char6\n");
										grabBlock[5] = '\0';
										reachedEnd=0;
									}
								}
								else
								{
									printf("reached the end at char5\n");
									grabBlock[4] = '\0';
									reachedEnd=0;
								}
							}
							else
							{
								printf("reached the end at char4\n");
								grabBlock[3] = '\0';
								reachedEnd=0;
							}
						}
						else
						{
							printf("reached the end at char3\n");
							grabBlock[2] = '\0';
							reachedEnd=0;
						}
						
					}
					else
					{
						printf("reached the end at char2\n");
						grabBlock[1] = '\0';
						reachedEnd=0;
					}
					
				}
				else
				{
					printf("reached the end at char1\n");
					grabBlock[0] = '\0';
					reachedEnd=0;
				}
				
			}
			else
			{
				printf("reached the end at char0\n");
				reachedEnd=0;
				goto myExit; 
			}
			
			
			//populate start and endblock
			for(i=0; i<4;i++)
			{
				startBlock[i] = grabBlock[i];
			}
			for (i=4; i<8; i++) 
			{
				endBlock[i-4] = grabBlock[i];
			}
			in[0] = ctol(startBlock);
			in[1] = ctol(endBlock);
			
			if(ed == ENC)
			{
				printf("DES Clear Text: %ld %ld\n",in[0],in[1]);
				des_encrypt1(in,key,ENC);
			
				printf("DES Encryption: %ld %ld\n",in[0],in[1]);
			
				//write to the outfile
				ltoc(in[0], startBlock);
				ltoc(in[1], endBlock);
				printf("ct: %c%c%c%c%c%c%c%c\n", startBlock[0],startBlock[1],startBlock[2],startBlock[3],endBlock[0],endBlock[1],endBlock[2],endBlock[3]);
				
				fwrite(startBlock, sizeof(char), 4*sizeof(char), outFile);
				fwrite(endBlock, sizeof(char), 4, outFile);
			}
			else if(ed == DEC)
			{
				printf("DES Encryption: %ld %ld\n",in[0],in[1]);
				des_encrypt1(in,key,DEC);
				printf("DES Decryption: %ld%ld\n",in[0],in[1]);
				//write to the outfile
				ltoc(in[0], startBlock);
				ltoc(in[1], endBlock);
				
				
				fwrite(startBlock, sizeof(char), 4*sizeof(char), outFile);
				fwrite(endBlock, sizeof(char), 4, outFile);
				
				
			}
		}
	
myExit:
		fclose(inFile);
		fclose(outFile);
 

}



/*	
	int k;
	long	in[2];
	static unsigned char cbc_key[8] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef};
	des_key_schedule key;

	if ((k = des_set_key_checked(&cbc_key,key)) != 0)
		printf("\nkey error\n");

	in[0] = 3212314;
	in[1] = 1231233;

	printf("DES Clear Text: %ld%ld\n",in[0],in[1]);
	des_encrypt1(in,key,ENC);

	printf("DES Encryption: %ld%ld\n",in[0],in[1]);

	des_encrypt1(in,key,DEC);

	printf("DES Decryption: %ld%ld\n",in[0],in[1]);
 */

