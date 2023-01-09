/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Homework #02
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
 * add, sub, addi, sw, lw, beg
 */

#include <stdio.h>
#include <stdlib.h>


//CA: DO NOT CHANGE
const char* outputFileName = "hw02_output.txt";

//CA: Please write your code
int main() {
    //CA: YOUR NAME with Student ID
    printf("Jeong, Jisoo (2176352)\n");
    FILE* fp = fopen(outputFileName, "w");
    FILE* opf = fopen("input.txt", "r");


    if (opf == NULL) {
        return -1;
    }
    else {
        int qnum;
        fscanf(opf, "%d", &qnum);
        for (int i = 0; i < qnum; i++) {
            unsigned int a;
            fscanf(opf, "%x", &a);
           
            int imm, imm1, imm2, imm3, imm4;
            unsigned int rs1, rs2, rd, func3, func7;
            unsigned char b = 0x0000007f;
            b = b & a;
                    
            if (b == 0x00000013) {//addi
                imm = 0xfff00000;
                imm = imm & a;
                imm = imm>>20;
               
                rs1 = 0x000f8000;
                rs1 = rs1 & a;
               
                rd = 0x00000f80;
                rd = rd & a;
                
                if((imm&0x00000800)==0x00000800){
                    imm=imm+0xfffff000;
                    imm=imm-1;
                    imm=~imm;
                    imm=imm&0x00000fff;
                    fprintf(fp, "addi x%d,x%d,-%d\n", rd>>7, rs1>>15, imm);
                }
                else
                fprintf(fp, "addi x%d,x%d,%d\n", rd>>7, rs1>>15, imm);
            }
            else if (b == 0x00000003) {// lw 일때
                imm = 0xfff00000;
                imm = imm & a;
                imm = imm>>20;
              
                rs1 = 0x000f8000;
                rs1 = rs1 & a;
               
                rd = 0x00000f80;
                rd = rd & a;
                if((imm&0x0000800)==0x0000800){
                    imm=imm+0xfffff000;
                    imm=imm-1;
                    imm=~imm;
                    imm=imm&0x00000fff;
                    fprintf(fp, "lw x%d,-%d(x%d)\n", rd>>7, imm, rs1>>15);
                }
                else
                fprintf(fp, "lw x%d,%d(x%d)\n", rd>>7, imm, rs1>>15);
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
                    fprintf(fp, "sub x%d,x%d,x%d\n", rd, rs1, rs2);
                }
                else if (func7 == 0x00000000) {
                    rs2 = 0x01f00000;
                    rs2 = rs2 & a;
                    rs2 = rs2 >>20;
                   
                    rs1 = 0x000f8000;
                    rs1 = rs1 & a;
                    rs1 = rs1 >>15;
                   
                    rd = 0x00000f80;
                    rd = rd & a;
                    rd = rd >>7;
                    fprintf(fp, "add x%d,x%d,x%d\n", rd, rs1, rs2);
                }
            }
            else if (b == 0x00000023) {//sw
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
                    ofst=ofst+0xfffff000;
                    ofst=ofst-1;
                    ofst=~ofst;
                    ofst=ofst&0x00000fff;
                    fprintf(fp, "sw x%d,-%d(x%d)\n", rs2, ofst, rs1);
                }
                else
                fprintf(fp, "sw x%d,%d(x%d)\n", rs2, ofst, rs1);
            }
            else if (b == 0x00000063 ) {//beq
                imm1 = 0x00000f00;
                imm1 = imm1 & a;
                imm1 = imm1 >>8; //4~1
               
                imm2 = 0x7e000000;
                imm2 = imm2 & a;
                imm2 = imm2 >>25; //10~5
               
                imm3 = 0x00000080;
                imm3 = imm3 & a;
                imm3 = imm3 >>7; //11
               
                imm4 = 0x80000000;
                imm4 = imm4 & a;
                imm4 = imm4 >>31; //12
               
                rs2 = 0x01f00000;
                rs2 = rs2 & a;
                rs2 = rs2 >>20;
               
                rs1 = 0x000f8000;
                rs1 = rs1 & a;
                rs1 = rs1 >>15;
                
                int ofst;
                ofst = imm1+(imm2<<4)+(imm3<<10)+(imm4<<11);
                ofst = ofst<<1;
                if((ofst&0x00001000)==0x00001000){
                    ofst = ofst+0xffffe000;
                    ofst = ofst-1;
                    ofst = ~ofst;
                   ofst=ofst&0x00000fff;
                    fprintf(fp, "beq x%d,x%d,-%d\n", rs1, rs2, ofst);
                }
                else
                {ofst = ofst&0x00000fff;
                fprintf(fp, "beq x%d,x%d,%d\n", rs1, rs2, ofst);}
            }
        }
    }
    fclose(opf);
    fclose(fp);
    return 1;
}