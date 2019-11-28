#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cstdlib>
#include <cmath>
using namespace std;
/*------ process ------ */
/*
1. Initialized A B and P;
2. calculate alpha, beta, di-gamma and gamma
3. Reestimate A and B
4. If P(O|Model) increase, go to 2 
*/
int num_state; // number of states
int num_Obser; // number of observations
int Acol; // column of the A matrix
int Arow; // row of A the matrix
int Pcol; // column of the P matrix
int Prow; // row of the P matrix
int Bcol; // column of the B matrix
int Brow; // row of the B matrix
int T ;// times of observation
float** A; // transition matrix 
float** B; // emission matrix 
float** P; // current state
float** alpha;// alpha T x num_state
float** betas; // beta T x num_state
float** gammas; // T x num_state
float*** di_gamma; // T x num_state x num_state
float threshold = 0.00001; // the threshold to check if the P(O|Model) converges
float old_logProb = -100000; // the old P(O|model) 
float new_logProb = 0; // the new P(O|model)
int flag = 1; // if flag = 0 diverge ; if flag = 1 converge 
int* observation; // observation
int Ot; // current observation
int iter_time = 0;// how many iteration time for conv
int max_iter = 1000;
float* ci ;
void Initial_Matrix(float**& a,int row, int col);
void Check_Initialization();
void Calculate_alphaset(float**& alpha,float** A,float** B,float** P,int* observation,int T,float*& ci);
void Update_alpha(float**& alpha,float** A, float** B, int Ot,int t,float*& ci);
void Calculate_betaset(float**& betas,float** A,float** B, int* observation,int T,float* ci);
void Update_beta(float**& beta,float** A, float** B, int Ot_1,int t,float* ci);
void Calculate_gamma(float***& di_gamma,float**& gammas,float** A, float** B,float** alpha,float**betas,int* observation);
void Compute_logProb(float& old_logProb,float& new_logProb,float** alpha,float*& ci);
 void Reestimate_Parameter(float**& A, float**& B, float**&P,float** gammas,float*** di_gamma,int* observation);
int main (int argc, char *argv[]){
	/* 1. Initialized matrix A and B */
	cin >> Arow;
	cin >> Acol;
	num_state = Arow;
	Initial_Matrix(A,Arow,Acol);
	for(int i = 0 ; i < Arow ; i++){
		for(int j = 0; j<Acol;j++){
			cin >> A[i][j];

		}
	}


	
	cin >> Brow;
	cin >> Bcol;
	num_Obser = Bcol;
	Initial_Matrix(B,Brow,Bcol);
	for(int i = 0;i<Brow;i++){
		for(int j = 0; j<Bcol;j++){
			cin >> B[i][j];

		}
	}
	/* read the initial state*/
	cin >> Prow;
	cin >> Pcol;
	Initial_Matrix(P,Prow,Pcol);
	for(int i = 0;i<Prow;i++){
		for(int j = 0; j<Pcol;j++){
			cin >> P[i][j];
		}
	}
	//Check_Initialization();
	/*read observation sequence*/
	cin >> T;
	observation = new int[T];
	for(int i=0;i<T;i++){
		cin>> observation[i];
	}
	// Initialize alpha
	Initial_Matrix(alpha,T,num_state);
	// Initialize beta
	Initial_Matrix(betas,T,num_state);
	// Initialize gamma 
	Initial_Matrix(gammas,T,num_state);
	// Initialize di_gamma
	di_gamma = new float **[T];
	for(int i = 0;i<T;i++){
		di_gamma[i] = new float* [num_state];
		for(int j = 0;j<num_state;j++){
			di_gamma[i][j] = new float[num_state];
		}
	}
	//Initial ci 
	ci = new float[T];
	 
	 while(flag == 1){
	 	/* 1. alpha pass */
	 	//cout<<"1"<<endl;
	 	Calculate_alphaset(alpha,A,B,P,observation,T,ci);
	 	/* 2. beta pass */
	 	//cout<<"2"<<endl;
	 	Calculate_betaset(betas,A,B,observation,T,ci);
	 	/* 3. compute di_gamma and gammas */
	 	//cout<<"3"<<endl;
	 	Calculate_gamma(di_gamma,gammas,A, B,alpha,betas,observation);
	 	/* 4. reestimate model parameters */
	 	//cout<<"4"<<endl;
 		Reestimate_Parameter(A, B,P,gammas,di_gamma,observation);
 		/* 5. Compute log(Prob) */
 		//cout<<"5"<<endl;
 		Compute_logProb(old_logProb,new_logProb,alpha,ci);
 		/* 6. test if the model converge */
 		iter_time = iter_time + 1;
 

 		if(iter_time < max_iter && new_logProb >old_logProb){

 			//cout<< old_logProb << " "<< new_logProb << endl;
 			old_logProb = new_logProb;
 			flag = 1;
 		}
 		else{
 			
 			flag = 0;
 		}




	 }

	 //cout << iter_time<<endl;

	 cout << Arow << " ";
	 cout << Acol << " ";
	 for ( int i = 0;i<Arow;i++){
	 	for(int j = 0;j<Acol;j++){
	 		cout<< A[i][j]<<" ";
	 	}
	 }
	 cout<<endl;
	 cout << Brow << " ";
	 cout << Bcol << " ";
	 for ( int i = 0;i<Brow;i++){
	 	for(int j = 0;j<Bcol;j++){
	 		cout<< B[i][j]<<" ";
	 	}
	 }

	 // cout<<"iteration time:"<< iter_time << endl;
	
	
	// calculate gammas and di_gammas
	


	
	

	


}

void Initial_Matrix(float**& a,int row, int col){
 	a = new float*[row];
 	for(int i = 0;i<row;i++){
 		a[i] = new float[col];
 	}

 }

void Check_Initialization(){
 	/* check At matrix */
 	cout<<"Checking A matrix "<<endl;
 	for(int i = 0;i<Arow;i++){
 		for(int j = 0;j<Acol;j++){
 			cout<< A[i][j]<<" ";
 		}
 		cout<<endl;
 	}
 	
 	/* check B matrix */
 	cout<<"Checking B matrix "<<endl;
 	for(int i = 0;i<Brow;i++){
 		for(int j = 0;j<Bcol;j++){
 			cout<< B[i][j]<<" ";
 		}
 		cout<<endl;
 	}
 	

 	/* check Initial P matrix */
 	cout<<"Checking Initial P matrix "<<endl;
 	for(int i = 0;i<Prow;i++){
 		for(int j = 0;j<Pcol;j++){
 			cout<< P[i][j]<<" ";
 		}
 		cout<<endl;
 	}
 }
 void Calculate_alphaset(float**& alpha,float** A,float** B,float** P,int* observation,int T,float*& ci){
 	Ot = observation[0];
 	ci[0] = 0;
 	for(int i = 0;i<num_state;i++){
 		alpha[0][i] = B[i][Ot] * P[0][i];
 		ci[0] = ci[0]+alpha[0][i];
 	}
 	ci[0] = 1/ ci[0];
 	for(int i = 0; i<num_state;i++){
 		alpha[0][i] = alpha[0][i] * ci[0];
 	}
 	for(int t = 1;t<T ; t++){
    	Ot = observation[t];
    	ci[t] = 0;
    	Update_alpha(alpha,A,B,Ot,t,ci);
 }
}
 void Update_alpha(float**& alpha,float** A, float** B, int Ot,int t,float*& ci){
 	float mom = 0;
 	float sumup = 0;
 	for (int i = 0; i < num_state;i++){
 		for(int j=0;j < num_state;j++){
 			mom = mom + A[j][i] * alpha[t-1][j];
 		}
 		alpha[t][i] = B[i][Ot] * mom;
 		sumup = alpha[t][i] + sumup;
 		mom = 0;
 	}
 	ci[t] = 1/sumup;
 	for (int i = 0;i<num_state;i++){
 		alpha[t][i] = alpha[t][i]*ci[t];
 	}
 }
 void Calculate_betaset(float**& betas,float** A,float** B, int* observation,int T,float* ci){
 	/* Backward algorithm */
 	// first: beta[T][i] = 1
 	for(int i = 0;i<num_state;i++){
 		betas[T-1][i] = ci[T-1];
 	}
 	// second doing backward from T-2 to 0
 	for(int t = T-2 ; t >= 0;t--){
 		Ot = observation[t+1];
 		Update_beta(betas,A,B,Ot,t,ci);
 	}

 }
 void Update_beta(float**& betas,float** A, float** B, int Ot_1,int t,float* ci){
 	// Ot_1 means the observation on t+1  -> backward
 	float mom = 0;
 	//float sumup = 0;
 	for(int i = 0; i< num_state;i++){
 		for(int j = 0; j<num_state;j++){
 			mom = mom + betas[t+1][j]* B[j][Ot_1]*A[i][j];

 		}
 		betas[t][i] = mom * ci[t];
 		//sumup = beta[t][i] + sumup;
 		mom = 0;
 	}

 	
 }

 void Calculate_gamma(float***& di_gamma,float**& gammas,float** A, float** B,float** alpha,float**betas,int* observation){
 	// NOTICE:  No need to normalize γt(i,j) since using scaled α and β
 	for(int t = 0 ; t<T-1;t++){
 		Ot = observation[t+1];
 		for(int i = 0;i<num_state;i++){
 			gammas[t][i] = 0;
 			for(int j = 0; j<num_state;j++){
 				di_gamma[t][i][j] = alpha[t][i]*A[i][j]*B[j][Ot]*betas[t+1][j];
 				gammas[t][i] = gammas[t][i] + di_gamma[t][i][j];
 			}
 		}


 	}
 	//special case for gammas[T-1]
 	for(int i = 0 ;i<num_state;i++){
 		gammas[T-1][i] = alpha[T-1][i];
 	}
 }

 void Reestimate_Parameter(float**& A, float**& B, float**&P,float** gammas,float*** di_gamma,int* observation){
 	float denom = 0;
 	float numer = 0;
 	/* re estiamte P */
 	for(int i = 0;i<num_state;i++){
 		P[0][i] = gammas[0][i];
 	}
 	//cout<<"11"<<endl;
   /* Re estimate A */
 	for(int i = 0;i<num_state;i++){
 		denom = 0;
 		
 		for(int t = 0;t<T-1;t++){
 			denom = denom + gammas[t][i];
 		}
 		
 		for(int j = 0;j<num_state;j++){
 			numer = 0;
 			for(int t = 0;t<T-1;t++){
 				numer = numer + di_gamma[t][i][j];
 			}
 			A[i][j] = numer/denom;
 		}

 	}
 	//cout<<"22"<<endl;
  /* re estimate B */
 	for( int i = 0; i<num_state;i++){
 		denom = 0;
 		for(int t = 0;t<T;t++){
 			denom = denom + gammas[t][i];
 		}
 		for(int j = 0;j<num_Obser;j++){
 			numer = 0;
 			for(int t = 0;t<T;t++){
 				if (observation[t]==j){
 					numer = numer + gammas[t][i];
 				}
 			}
 			B[i][j] = numer /denom ;
 		}
 	}
 	//cout<<"33"<<endl;


 }
 void Compute_logProb(float& old_logProb,float& new_logProb,float** alpha,float*& ci){
 		//old_logProb = new_logProb;
 		new_logProb = 0;
 	for(int t = 0 ; t<T ; t++){
 		//cout <<"log: "<< log10(ci[t])<<endl;
 		new_logProb = new_logProb + log10(ci[t]);
 	}
 	new_logProb = - new_logProb;
 }