#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cstdlib>
using namespace std;
int num_state; // number of states
int num_Obser; // number of observations
int Acol; // column of the A matrix
int Arow; // row of A the matrix
int Pcol; // column of the P matrix
int Prow; // row of the P matrix
int Bcol; // column of the B matrix
int Brow; // row of the B matrix
int obser_time ;// times of observation
float P_o = 0;
float** A; // transition matrix
float** B; // emission matrix
float** P; // current state
int* observation; // observation
float** alpha; // alpha obser_time x num_states
int Ot; // current observation
void initialMatrix(float**& a,int row, int col);
void copyMatrix(float**& a, float**& b,int row,int col);
void updateAlpha(float**& alpha,float**& A, float**& B, int Ot,int t);

int main (int argc, char *argv[]){

	/*  for A matrix */
	cin >> Arow;
	cin >> Acol;
	initialMatrix(A,Arow,Acol);
	for (int i = 0;i<Arow;i++){
		for(int j = 0;j<Acol;j++){
			cin >> A[i][j];
		}
	}
	/* for B matrix */
	cin >> Brow;
	cin>> Bcol;
	initialMatrix(B,Brow,Bcol);
	for (int i = 0;i<Brow;i++){
		for(int j = 0; j<Bcol;j++){
			cin >> B[i][j];
		}
	}
	/* for P matrix */
	cin >> Prow;
	cin >> Pcol;
	initialMatrix(P,Prow,Pcol);
	// Initial_Matrix(temp_P,Prow,Pcol);
	for (int i = 0 ; i < Prow ; i++){
		for(int j = 0;j < Pcol; j++){
			cin >> P[i][j];
		}
	}
	num_state = Acol;
    num_Obser = Bcol;

    /* for observation matrix */
    cin >> obser_time;
    observation = new int[obser_time];
    for (int i = 0;i< obser_time;i++){
    	cin >> observation[i];

    }
    /* Intialize alpha matrix */
    initialMatrix(alpha,obser_time,num_state);
    /* Intialize alpha 1 in the beginning*/
    Ot = observation[0];
    for (int i = 0;i<num_state;i++){
    	alpha[0][i] = B[i][Ot] * P[0][i];
    }
    /* forward algorithm */
    for(int t = 1;t<obser_time ; t++){
    	Ot = observation[t];
    	updateAlpha(alpha,A,B,Ot,t);
    	
    }

    /* print out the answer */
    for(int i = 0;i < num_state;i++){
    	P_o = P_o + alpha[obser_time-1][i];
    
    }
    
	cout<<P_o;
    
}


void initialMatrix(float**& a,int row, int col){
 	a = new float*[row];
 	for(int i = 0;i<row;i++){
 		a[i] = new float[col];
 	}

 }
 void copyMatrix(float**& a, float**& b,int row,int col ){
 	// make b the same as a
 	for(int i = 0;i<row;i++){
 		for(int j = 0;j<col;j++){
 			b[i][j] = a[i][j];
 		}
 	}

 }

 void updateAlpha(float**& alpha,float**& A, float**& B, int Ot,int t){
 	float mom = 0;
 	for (int i = 0; i < num_state;i++){
 		for(int j=0;j < num_state;j++){
 			mom = mom + A[j][i]*alpha[t-1][j];
 		}
 		alpha[t][i] = B[i][Ot] * mom;
 		mom = 0;
 	}
 	
 }