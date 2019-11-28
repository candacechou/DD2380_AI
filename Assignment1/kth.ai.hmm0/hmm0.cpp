#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cstdlib>
using namespace std;
int num_state; // number of states
int num_Obser; // number of observations
int col; // column of the matrix
int row; // row of the matrix
int Pcol;
int Prow;
void Matrix_Initialization(float* a,float**& m,int arow,int acol);
void Initial_Matrix(float**& a,int row, int col);
void Copy_Matrix(float**& a, float**& b,int row,int col);
void States_Evaluation(float**& P, float**& temp_P,float**& A);
void Observation_Evaluation(float**& P, float**& P_ob, float**& B);
int main (int argc, char *argv[]) {
  ifstream myfile(argv[1],ios::in);
  
  string line; // larger line when reading the file
  string smline; // smaller line when reading the file
  // counting the times we read the file in order to initialize A , B and P
  int i;// for iteration
  int n; // the length of string after getline
  int k; // the length of the string for reading number
  int sig = 1; // to see which matrix's information is reading 0 is transition matrix,1 is emission matrix and 2 is initial state

  
  float a[100]; // the array that store the number after converting from string for each matrix
  float iternum;
  float** A;
  float** B;
  float** P;
  float** temp_P;
  float** P_ob; // probability of current observation;
  //// Import the matrices from files
  	 if(myfile){
  	 	while(getline(myfile, line)) 
  	 	{
  	 		// cout<<line<<endl;
  	 		n = line.size();
  	 		k = 0;
  	 		smline.clear();

  	 		for(i=0;i<n;i++){
  	 			while (line[i] != ' ' && i < n){
  	 				smline = smline + line[i];
  	 				i++;
  	 			}
  	 			a[k] = stod(smline);
  	 			smline.clear();
  	 			k++;
  	 		}
  	 		col = a[1];
  	 		row = a[0];
  	 		if(sig ==1){
  	 			num_state = row;
  	 			Matrix_Initialization(a,A,row,col);
  	 			sig = 2;
  	 			
  	 		}
  	 		else if (sig == 2){
  	 			num_Obser = col;
  	 			Matrix_Initialization(a,B,row,col);
  	 			Initial_Matrix(P_ob, 1 , num_Obser);
  	 			sig = 3;
  	 			


  	 		}
  	 		else if (sig ==3){
  	 			Matrix_Initialization(a,P,row,col);
  	 			sig = 4;
  	 			Prow = row;
  	 			Pcol = col;
  	 			// cout<<"-----P-----"<<endl;
  	 			Initial_Matrix(temp_P,row,col);
  	 		}
  	 	}
  	 }
  	 	
  else {cout << "Unable to open file";}
  myfile.close(); 
  	States_Evaluation(P,temp_P,A);
  	Observation_Evaluation(P, P_ob, B);

   cout<< Prow <<' '<<Pcol<<' ';
   for(i = 0;i<Prow;i++){
   		for(int j = 0; j < Pcol ; j++){
   			cout<< P_ob[i][j] <<' ';
   		}
   }
   

  	 
 
	
  	
  	 
 
   return 0; 
  }

  ////////////// to Initial the matrix A B and P when reading the files
  void Matrix_Initialization(float* a,float**& m,int arow,int acol){
	// double m[arow][acol];
	// m = new double*[arow];
	// for(int i =0;i<arow;i++){
	// 	m[i] = new double[acol];
	// }
	Initial_Matrix(m,arow,acol);
	int k = 2;// interation of the string
	for (int i = 0 ; i < arow ; i++){
		for(int j = 0 ; j < acol ; j++){
			m[i][j] = a[k];
			k++;
			// cout<< resultm[i][j] << ' ';
		}
		// cout<<endl;
	}
	// return m
}
////////////// When we assignment the matrix, try to initialize it
 void Initial_Matrix(float**& a,int row, int col){
 	a = new float*[row];
 	for(int i = 0;i<row;i++){
 		a[i] = new float[col];
 	}

 }
 //////////// copy matrix
 void Copy_Matrix(float**& a, float**& b,int row,int col ){
 	// make b the same as a
 	for(int i = 0;i<row;i++){
 		for(int j = 0;j<col;j++){
 			b[i][j] = a[i][j];
 		}
 	}

 }
 void States_Evaluation(float**& P, float**& temp_P, float**& A){
 	float mat_ele = 0;
 	for (int i = 0;i< num_state;i++){
  	 			mat_ele = 0;
  	 			for(int j = 0;j< num_state;j++){
  	 				// cout<<"current P element"<<endl;
  	 				// cout<<P[0][j]<<endl;
  	 				mat_ele = mat_ele + P[0][j]*A[j][i];
  	 				// cout<<mat_ele<<endl;
  	 			}

  	 		    temp_P[0][i] = mat_ele;
  	 		    // cout<<"temp_P"<<endl;
  	 		    }
  	 		   // copy temp_P to P
  	 	       Copy_Matrix(temp_P,P,row,num_state);
  	 }
 
void Observation_Evaluation(float**& P, float**& P_ob, float**& B){
	float mat_ele = 0;
	for(int i = 0;i<num_Obser;i++){
		mat_ele = 0;
		for(int j = 0;j<num_state;j++){
			mat_ele = mat_ele + P[0][j]*B[j][i];
		}
		P_ob[0][i] = mat_ele;
	}

}
