/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Homework #03
 *
 *        Version:  1.0
 *        Created:  2022-09-15
 *       Revision:  none
 *       Compiler:  g++
 *
 * 	 Student Name: 
 * 	 Student ID: 
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

 /*
 * Input instructions
 * add, sub, addi, sw, lw
 */

#include <stdio.h>
#define MAX_MEM_SIZE 1024
#define MAX_REG_SIZE 32

//CA: DO NOT CHANGE
const char *inputInstFile="input_inst.txt";
const char *inputRegFile="input_reg.txt";
const char *inputMemFile="input_mem.txt";
const char *outputFileName="hw03_output.txt";

//const unsigned MAX_REG_SIZE = 32;
//const unsigned MAX_MEM_SIZE = 1024;

unsigned Register[MAX_REG_SIZE] = {0};
unsigned Memory[MAX_MEM_SIZE] = {0};

void print_output_to_file(FILE *fp){
	for(unsigned i = 0; i < MAX_REG_SIZE; i++){
		fprintf(fp, "%08x\n", Register[i]);
	}
	for(unsigned i = 0; i < MAX_MEM_SIZE; i++){
		fprintf(fp, "%08x\n", Memory[i]);
	}
}

//CA: Please write your code
int main(){
	//CA: YOUR NAME with Student ID
	printf("Jeong, Jisoo (2176352)\n");
	FILE *fp = fopen(outputFileName, "w");
    FILE *instfp = fopen(inputInstFile,"r");
    FILE *regfp = fopen(inputRegFile,"r");
    FILE *memfp = fopen(inputMemFile,"r");
    
    for(int n=0;n<MAX_REG_SIZE;n++) 
        fscanf(regfp,"%x",&Register[n]);
    for(int k=0;k<MAX_MEM_SIZE;k++) 
        fscanf(memfp,"%x",&Memory[k]);
    
    
    if(instfp ==NULL){
        return -1;
    }        
    else {
        
        int qnum;
        int i;
        fscanf(instfp,"%d",&qnum);
        
        for (int i=0;i<qnum;i++){
            unsigned int a;
            fscanf(instfp, "%x", &a);
           
            int imm, imm1, imm2, address;
            unsigned int rs1, rs2, rd, func7;
            unsigned int b = 0x0000007f;
            b = b & a;
            
            if (b == 0x00000013) {//addi
                imm = 0xfff00000;
                imm = imm & a;
                imm = imm>>20;
               
                rs1 = 0x000f8000;
                rs1 = rs1 & a;
                rs1 = rs1>>15;
               
                rd = 0x00000f80;
                rd = rd & a;
                rd = rd>>7;
                
                if((imm&0x00000800)==0x00000800){
                    imm=0xfffff000+imm+0x00001000;
                    Register[rd]=Register[rs1]+imm;
                    
                }
                else 
                //fprintf(fp, "addi x%d,x%d,%d\n", rd, rs1, imm);
                    Register[rd]=Register[rs1]+imm;
            }
            else if (b == 0x00000003) {// lw
                //int line[10];
                imm = 0xfff00000;
                imm = imm & a;
                imm = imm>>20;
              
                rs1 = 0x000f8000;
                rs1 = rs1 & a;
                rs1 = rs1>>15;
               
                rd = 0x00000f80;
                rd = rd & a;
                rd = rd>>7;
                
                if((imm&0x00000800)==0x00000800){
                    imm=imm+0xfffff000+0x00001000;
                    address=(Register[rs1]+imm)/4;
                    Register[rd]=Memory[address];    
                }
                else //fprintf(fp, "lw x%d,%d(x%d)\n", rd, imm, rs1);
                {address=(Register[rs1]+imm)/4;
                Register[rd]=Memory[address];}
            }
            else if (b == 0x00000033) {
                func7 = 0xfe000000;
                func7 = func7 & a;
                func7 = func7 >>25;
                if (func7 == 0x00000020) {//sub
                    rs2 = 0x01f00000;
                    rs2 = rs2 & a;
                    rs2 = rs2 >>20;
                   
                    rs1 = 0x000f8000;
                    rs1 = rs1 & a;
                    rs1 = rs1 >>15;
                    
                    rd = 0x00000f80;
                    rd = rd & a;
                    rd = rd >>7;
                    //fprintf(fp, "sub x%d,x%d,x%d\n", rd, rs1, rs2);
                    Register[rd]=Register[rs1]-Register[rs2];
                }
                else if (func7 == 0x00000000) {//add
                    int first,second;
                    rs2 = 0x01f00000;
                    rs2 = rs2 & a;
                    rs2 = rs2 >>20;
                   
                    rs1 = 0x000f8000;
                    rs1 = rs1 & a;
                    rs1 = rs1 >>15;
                   
                    rd = 0x00000f80;
                    rd = rd & a;
                    rd = rd >>7;
                    //fprintf(fp, "add x%d,x%d,x%d\n", rd, rs1, rs2);
                    Register[rd]=Register[rs1]+Register[rs2];
                }
            }
            else {//if (b == 0x00000023) {//sw
                imm1 = 0xfe000000;
                imm1 = imm1 & a;
                imm1 = imm1 >>25;
               
                rs2 = 0x01f00000;
                rs2 = rs2 & a;
                rs2 = rs2 >>20;
               
                rs1 = 0x000f8000;
                rs1 = rs1 & a;
                rs1 = rs1 >>15;
               
                imm2 = 0x00000f80;
                imm2 = imm2 & a;
                imm2 = imm2 >>7;
                
                int ofst=(imm1<<5)+imm2;
                if((ofst&0x00000800)==0x00000800){
                    ofst=ofst+0xfffff000+0x00001000;
                    //ofst=ofst-1;
                    //ofst=~ofst;
                    //ofst=ofst&0x00000fff;
                    //fprintf(fp, "sw x%d,-%d(x%d)\n", rs2, ofst, rs1);
                    address=(Register[rs1]+ofst)/4;
                    Memory[address]=Register[rs2];
                }
                else 
                address=(Register[rs1]+ofst)/4;
                Memory[address]=Register[rs2];
                //fprintf(fp, "sw x%d,%d(x%d)\n", rs2, ofst, rs1);
                    
            }

        }print_output_to_file(fp);
	
    
    }
    fclose(instfp);
    fclose(regfp);
    fclose(memfp);
    fclose(fp);
	return 1;
}
