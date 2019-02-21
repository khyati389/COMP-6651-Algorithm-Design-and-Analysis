/**
 * Author: Khyati Chaudhary
 * Programming Assignment 1
 * Algorithm Design & Analysis
 */

#include <iostream>
#include <fstream>
#include <algorithm>

#define ROOTNODE 0
#define MAXIMUM 2147483647

int minimumPathLength = MAXIMUM;

int **initMatrix(int rows_cols){
    int **matrix = new int*[rows_cols];
    for (int i = 0; i < rows_cols; i++) {
        matrix[i] = new int[rows_cols];
        for (int j = 0; j < rows_cols; j++)
            matrix[i][j] = 0;
    }
    return matrix;
}

void traverseNumbers(int *numberArray, int sizeArray, int n, int **matrix){
    if(sizeArray == 1){
        int root = ROOTNODE;
        int pathweight = 0;
        for(int i=0;i<n;i++){
            pathweight += matrix[root][numberArray[i]];
            root = numberArray[i];
        }
        pathweight = pathweight + matrix[root][ROOTNODE];
        minimumPathLength = std::min(pathweight, minimumPathLength);
    }

    for(int i=0;i<sizeArray; i++){
        traverseNumbers(numberArray, sizeArray-1, n, matrix);
        if(sizeArray%2 == 1){
            std::swap(numberArray[0], numberArray[sizeArray-1]);
        }else{
            std::swap(numberArray[i],numberArray[sizeArray-1]);
        }
    }
}

int main(int argc, char* argv[]) {
    std::ifstream fileIn(argv[1]);
    std::ofstream fileOut(argv[2]);
    if(!fileOut){
        std::cout<<"wrong argument! file can't open"<<std::endl;
        return -1;
    }
    if(fileIn){
        int datasetsM;
        fileIn>>datasetsM;
        for(int loop = 0; loop<datasetsM; ++loop){
            int noOfVertices,noOfEdges;
            fileIn>>noOfVertices>>noOfEdges;
            int *numbersLine = new int[noOfVertices - 1];
            int k =0;
            for(int i=0; i<noOfVertices-1; i++){
                numbersLine[i] = ++k;
            }
            int** matrix = initMatrix(noOfVertices);

            for(int data = 0; data<noOfEdges; data++){
                int startNode, endNode, edgeWeight;
                fileIn>>startNode>>endNode>>edgeWeight;
                matrix[startNode] [endNode] = edgeWeight;
                matrix[endNode] [startNode] = edgeWeight;
            }
            traverseNumbers(numbersLine, noOfVertices-1, noOfVertices-1, matrix);
            std::cout<<minimumPathLength<<std::endl;
            fileOut<<minimumPathLength<<std::endl;
            delete[] matrix;
            delete[] numbersLine;
            minimumPathLength = MAXIMUM;
        }
        fileIn.close();
    }else{
        std::cout<<"wrong argument! file can't open"<<std::endl;
        return -1;
    }
    return 0;
}
