/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Homework #04
 *
 *        Version:  1.0
 *        Created:  2022-09-17
 *       Revision:  none
 *       Compiler:  g++
 *
 * 	 Student Name: 
 * 	   Student ID: 
 *   Organization:  Ewha Womans University
 *
 * =====================================================================================
 */

 /*
 * ********** Please read the instructions below carefully ********** 
 * Your name and student ID must be printed when this project is executed
 * Do not print anything other than your name and student ID (Delete printf functions used for debugging when submitting this homework)
 * - If not, there will be 20% penalty
 * Run make clean command before submitting your homework
 * Change this project folder name to studentID_yourname (EX: 1234567_myungkukyoon)
 * You must compress this project folder (not the files in this folder)
 * - If not, there will be 20% penalty
 * - Use ZIP compression utility (DO NOT USE TAR COMMAND)
 * The name of ZIP file must be studentID_yourname.zip (EX: 1234567_myungkukyoon.zip)
 * All the tests must be done in 5 seconds
 * - If not, you will get 0%
 */

#include <stdio.h>
#include <math.h>
//#define BLOCKSMAX 512
#define BLOCKS 512

//CA: DO NOT CHANGE
const char *outputFileName="hw04_output.txt";

unsigned long long cacheHit;
unsigned long long cacheMiss;

void init(){
	cacheHit = 0;
	cacheMiss = 0;
}

void ratio(FILE *fp){
	unsigned long long total = cacheHit + cacheMiss;
	fprintf(fp, "Hit: %3.2f\n", (float)cacheHit/total * 100);
	fprintf(fp, "Miss: %3.2f\n", (float)cacheMiss/total * 100);
}


//CA: Please write your code
int main(){
	//CA: YOUR NAME with Student 	
	printf("Jeong, Jisoo (2176352)\n");
	//init();
	FILE *fp = fopen(outputFileName, "w");
    FILE *opf = fopen("input.txt", "r");
    
    if (opf == NULL) {
        return -1;
    }
    
    else {
        int qnum;
        fscanf(opf, "%d", &qnum);
        
        for (int i=0;i<qnum;i++) {
            int blocks, blockSize, addressNumber, blocksBit, blockofstBit;
            unsigned int address;
            //bool valid;
            int tag, data, valid, index, tagfield, field;
            init();
            
            fscanf(opf, "%d", &blocks);
            blocksBit=log2(blocks);
            
            fscanf(opf, "%d", &blockSize);
            blockofstBit=blockSize/4;
            blockofstBit=log2(blockofstBit);
            
            int cache[BLOCKS] = {0};
            for(int t=0;t<BLOCKS;t++){
                cache[t]=-1;
            }
            
            fscanf(opf, "%d", &addressNumber);
            
           
            for (int j=0;j<addressNumber;j++) {
                fscanf(opf,"%x", &address);
                tag=address>>(2+blocksBit+blockofstBit);
                
                index=address>>(2+blockofstBit);
                index=index&(blocks-1);
                
                tagfield=16-(blockofstBit+blocksBit+2);
                field=1+tagfield;
                
                if(cache[index]==address){
                    cacheHit+=1;
                }
                else{
                    cacheMiss+=1;
                    cache[index]=address;
                }
                
            }
            ratio(fp);
        }
    }
    
	//ratio(fp);
	fclose(fp);
    fclose(opf);
	return 0;
}

