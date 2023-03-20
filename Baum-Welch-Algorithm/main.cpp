#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cstdlib>
#include <cmath>
using namespace std;
 /* define parameters */
int Acol = 3; // column of the matrix
int Arow = 3; // row of the matrix
int Pcol = 3;
int Prow = 1;
int Bcol = 4;
int Brow = 3;
int num_state = Arow; // number of states
int num_Obser = Bcol; // number of observations
/* Initialize transition matrix A */
float At[] = {0.6,0.25, 0.15,
			  0.3, 0.5, 0.2,
			  0.2, 0.1, 0.7};
float** A;
/* Initialize emission matrix B */
float Bt[] =  {0.3, 0.1, 0.5, 0.1,
			  0.12, 0.38, 0.21, 0.29,
			  0.29, 0.11, 0.35, 0.25} ;
float CorrectA[3][3] = {{0.7,0.05,0.25},{0.1,0.8,0.1},{0.2,0.3,0.5}};
float CorrectB[3][4] = {{0.7,0.2,0.1,0},{0.1,0.4,0.3,0.2},{0,0.1,0.2,0.7}};
float CorrectP[3] = {1,0,0};
float** B;
float Pt[] = {0.3 , 0.2 , 0.5};
float** P;
int T ;

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
int max_iter = 300;
float* ci ;
void initializeMatrix(float**& a,float at[],int row, int col);
void initializeParameter(float**& a,int row, int col);
void checkInitialization();
void calculateAlphaset(float**& alpha,float** A,float** B,float** P,int* observation,int T,float*& ci);
void updateAlpha(float**& alpha,float** A, float** B, int Ot,int t,float*& ci);
void calculateBetaset(float**& betas,float** A,float** B, int* observation,int T,float* ci);
void updateBeta(float**& beta,float** A, float** B, int Ot_1,int t,float* ci);
void calculateGamma(float***& di_gamma,float**& gammas,float** A, float** B,float** alpha,float**betas,int* observation);
void computeLogProb(float& old_logProb,float& new_logProb,float** alpha,float*& ci);
void reestimateParameter(float**& A, float**& B, float**&P,float** gammas,float*** di_gamma,int* observation);



int main (int argc, char *argv[]){
	
/* Initial A B and P. */
initializeMatrix(A,At,Arow,Acol);
initializeMatrix(B,Bt,Brow,Bcol);
initializeMatrix(P,Pt,Prow,Pcol);
	
/* Import T */ 
cin >> T;
/* Initialize observation and store it */
observation = new int[T] ;
for(int i = 0; i < T ; i++){
	cin >> observation[i];
}
checkInitialization();
/* Initialize other variables */
// Initialize alpha
initializeParameter(alpha,T,num_state);
// Initialize beta
initializeParameter(betas,T,num_state);
// Initialize gamma 
initializeParameter(gammas,T,num_state);
// Initialize di_gamma
di_gamma = new float **[T];
for(int i = 0;i<T;i++){
	di_gamma[i] = new float * [num_state];
	for(int j = 0;j<num_state;j++){
		di_gamma[i][j] = new float[num_state];
	}
}
//Initial ci 
ci = new float[T];

 while(flag == 1){
	 	/* 1. alpha pass */
	 	//cout<<"1"<<endl;
	 	calculateAlphaset(alpha, A, B, P,observation,T,ci);
	 	/* 2. beta pass */
	 	//cout<<"2"<<endl;
	 	calculateBetaset(betas,A,B,observation,T,ci);
	 	/* 3. compute di_gamma and gammas */
	 	//cout<<"3"<<endl;
	 	calculateGamma(di_gamma,gammas,A, B,alpha,betas,observation);
	 	/* 4. reestimate model parameters */
	 	//cout<<"4"<<endl;
 		reestimateParameter(A, B,P,gammas,di_gamma,observation);
 		/* 5. Compute log(Prob) */
 		//cout<<"5"<<endl;
 		computeLogProb(old_logProb,new_logProb,alpha,ci);
 		/* 6. test if the model converge */
 		iter_time = iter_time + 1;
 

 		if(iter_time < max_iter && new_logProb >old_logProb){

 			//cout<< old_logProb << " "<< new_logProb << endl;
 			old_logProb = new_logProb;
 			flag = 1;
 		}
 		else {
 			
 			flag = 0;
 		}
 	}

 	if (iter_time == max_iter){
 		cout<<" the algorithm didn't converge."<<endl;
 	}
 	else {
 		cout<<"------------------------------------------"<<endl;
 		cout<<" number of converge time: "<<iter_time<<endl;
 	    checkInitialization();
        cout<<" mean square error calculating"<<std::endl;
        float mse = 0;
        float q = 0;
        for(int i = 0 ; i<num_state;i++){
            for(int j = 0;j<num_state;j++){
                q++;
                mse += (CorrectA[i][j] - A[i][j])*(CorrectA[i][j] - A[i][j]);
        }
            for(int j = 0;j<num_Obser;j++){
                q++;
                mse += (CorrectB[i][j] - B[i][j])*(CorrectB[i][j] - B[i][j]);
            }
            q++;
            mse += (CorrectP[i] - P[0][i])*(CorrectP[i] - P[0][i]);
        }
        mse /= q;
        cout<<"mse:"<<mse<<endl;
        
 	}
 





}

void initializeMatrix(float**& a,float at[],int row, int col){
 	a = new float*[row];
 	for(int i = 0;i<row;i++){
 		a[i] = new float[col];
 	}
 	for(int i = 0;i<row;i++){
 		for(int j = 0;j<col;j++){
 			a[i][j] = at[i*col+j];
 		}
 	}

 }
 void initializeParameter(float**& a,int row, int col){
 	a = new float*[row];
 	for(int i = 0;i<row;i++){
 		a[i] = new float[col];
 	}
 	

 }
void checkInitialization(){
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

 void calculateAlphaset(float**& alpha,float** A,float** B,float** P,int* observation,int T,float*& ci){
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
    	updateAlpha(alpha,A,B,Ot,t,ci);
 }
}
 void updateAlpha(float**& alpha,float** A, float** B, int Ot,int t,float*& ci){
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
 void calculateBetaset(float**& betas,float** A,float** B, int* observation,int T,float* ci){
 	/* Backward algorithm */
 	// first: beta[T][i] = 1
 	for(int i = 0;i<num_state;i++){
 		betas[T-1][i] = ci[T-1];
 	}
 	// second doing backward from T-2 to 0
 	for(int t = T-2 ; t >= 0;t--){
 		Ot = observation[t+1];
 		updateBeta(betas,A,B,Ot,t,ci);
 	}

 }
 void updateBeta(float**& betas,float** A, float** B, int Ot_1,int t,float* ci){
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

 void calculateGamma(float***& di_gamma,float**& gammas,float** A, float** B,float** alpha,float**betas,int* observation){
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

 void reestimateParameter(float**& A, float**& B, float**&P,float** gammas,float*** di_gamma,int* observation){
 	float denom = 0;
 	float numer = 0;
 	/* re estiamte P */
 	for(int i = 0;i<num_state;i++){
 		P[0][i] = gammas[0][i];
 	}
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
 }
 void computeLogProb(float& old_logProb,float& new_logProb,float** alpha,float*& ci){
 		new_logProb = 0;
 	for(int t = 0 ; t<T ; t++){
 		new_logProb = new_logProb + log10(ci[t]);
 	}
 	new_logProb = - new_logProb;
 }
