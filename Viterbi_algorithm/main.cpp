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
float** A; // transition matrix
float** B; // emission matrix
float** P; // current state
float** S; // the sigma matrix num_obser x num_state
float** Sidx; // the index of sigma matrix num_Obser x num_state 
int* observation; // observation
int* result;
int Ot; // current observation
void initialMatrix(float**& a,int row, int col);
void copyMatrix(float**& a, float**& b,int row,int col);
void checkInitialization();
void updateProcess(float**& S, float**& Sidx, int Ot, int t);
void findPath(float**& S,float**& Sidx,int*& result);
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
	num_state = Arow;
	/* for B matrix */
	cin >> Brow;
	cin>> Bcol;
	initialMatrix(B,Brow,Bcol);
	for (int i = 0;i<Brow;i++){
		for(int j = 0; j<Bcol;j++){
			cin >> B[i][j];
		}
	}
	num_Obser = Bcol;
	/* for P matrix */
	cin >> Prow;
	cin >> Pcol;
	initialMatrix(P,Prow,Pcol);
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
    result = new int[obser_time];
    /* Initialize S */
    initialMatrix(S,obser_time,num_state);
    Ot = observation[0];
    for (int i = 0 ; i < num_state ; i++){
    	S[0][i] = P[0][i]* B[i][Ot];
    }
    /*Initialize Sidx, if sidx[i][j]= num_Obser means multiple answers 
      since in the task, we don't consider this situation, and also, when sidx[0],
      we don't have index for this,so give it num_Obser */
    initialMatrix(Sidx,obser_time,num_state);
    for(int i = 0 ; i< num_state;i++){
    	Sidx[0][i] = num_Obser;
    }
    // Check_Initialization();
    /* Start to update S and Sidx using observation*/
    for(int t =1;t<obser_time;t++){

    	Ot = observation[t];
    	updateProcess(S,Sidx, Ot, t);
    	
    }
/* track back */
findPath(S,Sidx,result);

/* print out result */
for(int i = 0;i<obser_time;i++){
 		cout<<result[i]<<" ";
 	}
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
 void updateProcess(float**& S, float**& Sidx, int Ot, int t){
 	//t = time
 	// Ot current observation
 	int maxidx = obser_time ; //maximum idx now
 	float maxS = 0; // maximum S[i][j]
 	float tempS = 0; // tempS

 	for(int i = 0;i<num_state;i++){
 		for(int j = 0;j<num_state;j++){
 			tempS = S[t-1][j] * A[j][i];
 			if (tempS>maxS){
 				maxS = tempS;
 				maxidx = j;
 			}


 		}
 		maxS = maxS*B[i][Ot];
 		S[t][i] = maxS;
 		Sidx[t][i] = maxidx;
 		maxS = 0;
 		maxidx = obser_time;
 	}
 }
 void checkInitialization(){
 	// CHECK INITIALIZATION CORRECT
    cout<<" A matrix: "<<endl;
    for(int i = 0; i< Arow;i++){
    	for( int j = 0; j< Acol;j++){
    		cout<< A[i][j]<<" ";
    	}
    	cout<<endl;
    }
    cout<<" B matrix: "<<endl;
    for(int i = 0; i< Brow;i++){
    	for( int j = 0; j< Bcol;j++){
    		cout<< B[i][j]<<" ";
    	}
    	cout<<endl;
    }
    cout<<" P matrix: "<<endl;
    for(int i = 0; i< Prow;i++){
    	for( int j = 0; j< Pcol;j++){
    		cout<< P[i][j]<<" ";
    	}
    	cout<<endl;
    }
    cout<< " the first state of S"<<endl;

    for(int i = 0;i<num_state;i++){
    	cout<<S[0][i]<<" ";
    }
    cout<<endl;
    
    cout<< " the first state of Sidx"<<endl;
    for(int i = 0;i<num_state;i++){
    	cout<<Sidx[0][i]<<" ";
    }

 }

 void findPath(float**& S,float**& Sidx,int*& result){
 	/* trace the latest one -> find the largest Probability and the index */
 	float maxProb = 0;
 	int maxidx = num_state;
 	for(int i = 0 ;i<num_state;i++){
 		if(maxProb < S[obser_time-1][i]){
 			maxProb = S[obser_time-1][i];
 			maxidx = i;
 		}
 	}
 	result[obser_time-1] = maxidx;
 	/* trace the following path */
 	for(int t = obser_time-1;t>=1;t--){
 		result[t-1] = Sidx[t][maxidx];
 		maxidx = result[t-1];

 		
 	} 
 	
 	
 }