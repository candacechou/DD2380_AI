#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cstdlib>
using namespace std;
int num_state; // number of states
int num_Obser; // number of observations
int Acol; // column of the matrix
int Arow; // row of the matrix
int Pcol;
int Prow;
int Bcol;
int Brow;
float** A;
float** B;
float** P;
float** temp_P;
float** P_ob; // probability of current observation;
void initialMatrix(float**& a,int row, int col);
void copyMatrix(float**& a, float**& b,int row,int col );
void statesEvaluation(float**& P, float**& temp_P, float**& A);
void evaluateObservation(float**& P, float**& P_ob, float**& B);
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
    initialMatrix(temp_P,Prow,Pcol);
	for (int i = 0 ; i < Prow ; i++){
		for(int j = 0;j < Pcol; j++){
			cin >> P[i][j];
		}
	}
    	num_state = Acol;
    	num_Obser = Bcol;
        initialMatrix(P_ob,Prow,num_Obser);
        statesEvaluation(P, temp_P, A);

        evaluateObservation(P,P_ob,B);
 

cout << Prow <<" ";
cout<< num_Obser<<" ";
for(int i = 0; i< Prow;i++){
	for(int j = 0;j<num_Obser;j++){
		cout<< P_ob[i][j] <<" ";
	}
}

    

	return 0;

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
 void statesEvaluation(float**& P, float**& temp_P, float**& A){
 	float mom = 0;
 	for(int i = 0;i < Prow ; i++){
 		for(int j = 0; j <Acol ; j++){
 			for( int k = 0; k<Arow; k++){
 				mom = mom+ P[i][k]*A[k][j];
 			}
 			temp_P[i][j] = mom;
 			mom = 0;
 		}
 	}
     copyMatrix(temp_P,P,Prow,Pcol);
  	 }
 void evaluateObservation(float**& P, float**& P_ob, float**& B){
	float mom = 0;

	for(int i = 0;i < Prow ; i++){
 		for(int j = 0; j <Bcol ; j++){
 			for( int k = 0; k<Brow; k++){
 				mom = mom + P[i][k]*B[k][j];
 			}
 			P_ob[i][j] = mom;
 			mom = 0;
 		}
 	}

}

