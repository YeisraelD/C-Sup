#include<iostream>
using namespace std;
const int row=3, col=3;

void buildMatrix(int mat[][col]){
    for(int i=0; i<row; i++)
       for (int j=0; j< col; j++){
          cout<< "Enter mattrix element Row "<< i+1<<" colomn " << j+1<< ": ";
          cin >> mat[i][j];
       }  
        cout << endl;
}
void displayMatrix(int mat[][col]){
    for (int i=0;i<row;i++){
        for (int j = 0; j< col; j++){
            cout << mat[i][j]<< " ";
           }
        cout << endl;
    }
}
int main()
{
    int matrix[row][col];
    buildMatrix(matrix);
    displayMatrix(matrix);



   return 0;
}