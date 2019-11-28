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
void Initial_Matrix(float**& a,int row, int col);
void Copy_Matrix(float**& a, float**& b,int row,int col );
void States_Evaluation(float**& P, float**& temp_P, float**& A);
void Observation_Evaluation(float**& P, float**& P_ob, float**& B);
int main (int argc, char *argv[]){
	/*  for A matrix */
	cin >> Arow;
	cin >> Acol;
	Initial_Matrix(A,Arow,Acol);
	for (int i = 0;i<Arow;i++){
		for(int j = 0;j<Acol;j++){
			cin >> A[i][j];
		}
	}
	/* for B matrix */
	cin >> Brow;
	cin>> Bcol;
	Initial_Matrix(B,Brow,Bcol);
	for (int i = 0;i<Brow;i++){
		for(int j = 0; j<Bcol;j++){
			cin >> B[i][j];
		}
	}
	/* for P matrix */
	cin >> Prow;
	cin >> Pcol;
	Initial_Matrix(P,Prow,Pcol);
	Initial_Matrix(temp_P,Prow,Pcol);
	for (int i = 0 ; i < Prow ; i++){
		for(int j = 0;j < Pcol; j++){
			cin >> P[i][j];
		}
	}
    	num_state = Acol;
    	num_Obser = Bcol;
    	Initial_Matrix(P_ob,Prow,num_Obser);
  		States_Evaluation(P, temp_P, A);
//  cout << "print out states"<<endl;
// for(int i=0;i<Prow;i++){
// 	for(int j=0;j<Pcol;j++){
// 		cout << P[i][j]<<' ';
// 	}
// 	cout<<endl;
// }
// cout<<"print out obs states"<<endl;
Observation_Evaluation(P,P_ob,B);
 
// for(int i=0;i<Prow;i++){
// 	for(int j=0;j<num_Obser;j++){
// 		cout << P_ob[i][j]<<' ';
// 	}
// 	cout<<endl;
// }
 	/*print out answer*/
cout << Prow <<" ";
cout<< num_Obser<<" ";
for(int i = 0; i< Prow;i++){
	for(int j = 0;j<num_Obser;j++){
		cout<< P_ob[i][j] <<" ";
	}
}

    

	return 0;

}
	
void Initial_Matrix(float**& a,int row, int col){
 	a = new float*[row];
 	for(int i = 0;i<row;i++){
 		a[i] = new float[col];
 	}

 }
 void Copy_Matrix(float**& a, float**& b,int row,int col ){
 	// make b the same as a
 	for(int i = 0;i<row;i++){
 		for(int j = 0;j<col;j++){
 			b[i][j] = a[i][j];
 		}
 	}

 }
 void States_Evaluation(float**& P, float**& temp_P, float**& A){
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
  	 		   // copy temp_P to P
  	 	       Copy_Matrix(temp_P,P,Prow,Pcol);
  	 }
 void Observation_Evaluation(float**& P, float**& P_ob, float**& B){
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

