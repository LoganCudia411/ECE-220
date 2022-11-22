/* Function matrix_multiply
 * matrixA, matrixB, and matrix C are matrices represented as
 * one-dimensional arrays in row-major order. This function must
 * preform matrix multiplication so that C=A*B. 
 * INPUT: matrixA, a one dimensional array of size m*k
 *        matrixB, a one dimensional double array of size k*n
 * OUTPUT: matrixC, a one dimensional double array of size m*n
 */
//matrix A = N x K, B = K x M , C = N x M 
void matrix_multiply(double *matrixA,double *matrixB,double *matrixC,int m,int k,int n)
{
    int row, col,i;
    double A=0,B =0,C=0; 
    for (row = 0; row < m; row++){
        for(col=0;col <n; col++){
            for(i = 0; i<k; i++){
                A = matrixA[row*k+i];
                B = matrixB[n*i+col];
                C += A * B;
            }
            matrixC[row*n+col] = C;
            C=0;
        }
       
    }
    
    return;
}

