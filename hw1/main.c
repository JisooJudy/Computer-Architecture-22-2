/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Homework #01
 *
 *        Version:  1.0
 *        Created:  2022-07-23
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

#include <stdio.h>
#include <stdlib.h>
#define MAX 100 

//CA: DO NOT CHANGE
//const int MAX = 100; 
const char* outputFileName = "hw01_output.txt";

//CA: DO NOT CHANGE
int matrixOutput[MAX][MAX] = {0};

//CA: DO NOT CHANGE
void print_output_to_file(FILE* fp, int ROW, int COL) {
   for (int y = 0; y < ROW; y++) {
      for (int x = 0; x < COL; x++) {
         fprintf(fp, "%d ", matrixOutput[y][x]);
      }
      fprintf(fp, "\n");
   }
}

//CA: Please write your code
int main() {
   //CA: YOUR NAME with Student ID
   printf("Jeong, Jisoo (2176352)\n");

   FILE* opf = fopen("input.txt", "r"); //input.txt 불러오기
   FILE* fp = fopen(outputFileName, "w");

   if (opf == NULL) {
      //printf("Can't open input file\n");  //파일을 찾을 수 없다면 출력
      return -1;   
   }

   else  { //파일의 끝이 아니라면 계속 실행

      int qnum; //테스트 케이스 갯수
      fscanf(opf, "%d", &qnum);
      for (int i = 0; i < qnum; i++) {

         int n, m, k; 
         fscanf(opf, "%d %d %d", &n, &m, &k); //행렬의 크기 저장

         int arr1[n][m]; //배열에 메모리 할당
         int arr2[m][k];
         //int rslt[n][k];
  
         //행렬 값 저장
         for (int j = 0; j < n; j++){
            for (int w = 0; w < m; w++){
               fscanf(opf, "%d", &arr1[j][w]);
            }
         }

         //행렬 값 저장
         for (int j = 0; j < m; j++){
            for (int w = 0; w < k; w++){
               fscanf(opf, "%d", &arr2[j][w]);
            }
         }

         //행렬 값 계산
         for (int j = 0; j < n; j++){
            for (int w = 0; w < k; w++) {
               int sum = 0;
               for (int p = 0; p < m; p++){
                  sum += arr1[j][p] * arr2[p][w]; 
                  matrixOutput[j][w] = sum;
               }
            }  
         }
         
         print_output_to_file(fp, n, k);
         // //계산된 행렬 값 출력
         // for (int j = 0; j < n; j++)
            // for (int w = 0; w < k; w++) 
               // printf("&d ", matrixOutput[j][k])       
      }
   }
   fclose(opf);
   fclose(fp);
   
   return 1;
}

