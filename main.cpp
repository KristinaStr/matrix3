#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
void write(float** matr, unsigned int rows3, unsigned int columns3) {
	for (unsigned int i = 0; i<rows3; i++) {
		for (unsigned int j = 0; j<columns3; j++) {
			cout << matr[i][j] << ' ';
		}
		cout << endl;
	}
}
float ** readmatr (unsigned int &rows,unsigned int &columns1,string s) {
	float** matrix = nullptr;
	char op;
	ifstream fin;
	fin.open(s.c_str());
	if ( !fin.is_open() ) {
		cerr << "404\n";
		return nullptr;
	}
	string line;
	getline(fin, line);
	istringstream stream(line);
	if (stream >> rows && stream >> op && op == ',' && stream >> columns) {
	matr = new float *[ rows1 ];
	for( unsigned int i = 0; i < rows1; ++i ) {
	 	matr[ i ] = new float[ columns1 ];
	    	for( unsigned int j = 0; j < columns1; ++j ) {
	       	 	matr[ i ][ j ] = 0.0f;
	    	}
	}
			for (unsigned int i = 0; i<rows; i++) {
				for (unsigned int j = 0; j<columns; j++) {
					fin >> matr[i][j];
			}
		}
	}
	fin.close();
	return matr;
}
bool vernvvod(string &s1, char &op, string &s2) {
	bool usp = false;
	string stroka;
	getline(cin, stroka);
	istringstream stream(stroka);
	if (stream >> s1 && stream >> op) {
		if (op == 'T' || op == 'R') {
			usp = !usp;
			return usp;
		}
		else {
			if (stream >> s2) {
				usp = !usp;
			}
		}
	};
	return usp	;
}
bool pl (float **matr1, int rows1, int columns1, float **matr2, int rows2, int columns2, float ** matr, int rows3, int columns3,bool &dop) {	
	bool succ=0.0f;
	if (rows1 == rows2 && columns1 == columns2){	
		succ=1;
		for (unsigned int i = 0; i<rows3; i++){	
	 		for (unsigned int j = 0; j<columns3; j++){
	 		  	matr[i][j] = matr1[i][j]+matr2[i][j];
			}
		}
	}
	else
	{
		cout<<"i can't do it";
		dop=false;
	}
	return succ;
}
bool min (float **matr1, int rows1, int columns1, float **matr2, int rows2, int columns2, float ** matr, int rows3, int columns3,bool &dop) {	
	bool succ=0.0f;
	if (rows1 == rows2 && columns1 == columns2){	
		succ=1;
		for (unsigned int i = 0; i<rows3; i++){	
	 		for (unsigned int j = 0; j<columns3; j++){
	 		  	matr[i][j] = matr1[i][j]-matr2[i][j];
			}
		}
	}
	else
	{
		cout<<"i can't do it";
		dop=false;
	}
	return succ;	
}
bool umn (float **matr1, int rows1, int columns1, float **matr2, int rows2, int columns2, float ** matr, int rows3, int columns3,bool &dop) {	
	bool succ=0.0f;
	if (columns1 == rows2) {	
		for(unsigned int i = 0; i < rows3; ++i ){
    			for(unsigned int j = 0; j < columns3; ++j ){
      		  		int result = 0;
      		   		for( int k = 0; k < columns3; ++k ){
       			 		result += matr1[i][k] * matr2[k][j];
      		   		}
      		  		matr[i][j] = result;
    			}
  		}
	 	cout << endl;
	 	succ=1;
	}
	else
	{
		cout<<"i can't do it";
		dop=false;
	}
	return succ;	
}
void minim(float ** matr, float **newmat, unsigned int i,unsigned int j, unsigned int N)
{
	unsigned int k = 0; unsigned int  g;
	for (unsigned int h = 0;  h<N -1; h++) { 		
		if (h == i){
			k = 1;
		}
			g = 0;
		for (unsigned int v = 0; v< N - 1; v++) {
			if (v == j){
				g = 1;
			}
			newmat[ h ][ v ] = matr[ h + k ][ v + g ];
		}
	}
}
float opredelitel(float ** matr, unsigned int N)
{
	unsigned int i=0;
	float opr=0;
	unsigned int M = N - 1;
	char step = 1;
	float ** newmat;
	newmat = new float *[N];
	for (unsigned int i = 0; i < N; i++){
		newmat[i] = new float[N];
	}
	if (N < 1){
		for (unsigned int i = 0; i < N; i++){
		    delete[] newmat[i];
	    }
	    delete newmat;
		cout << "Error";
	}
	if (N == 1){
		opr = matr[0][0];
		return(opr);
	}
	if (N == 2){
		opr = matr[0][0] * matr[1][1] - (matr[1][0] * matr[0][1]);
		for (unsigned int i = 0; i < N; i++){
		    delete[] newmat[i];
	    }
	    delete newmat;
		return(opr);
	}
	if (N>2){
		for (i = 0; i<N; i++){
			minim(matr, newmat, i, 0, N);
			opr = opr + step * matr[i][0] * opredelitel(newmat, M);
			step = -step;
		}
	}
	for (unsigned int i = 0; i < N; i++){
		    delete[] newmat[i];
	    }
	    delete newmat;
	return(opr);
}
float** obrmat(int x, float **mass, float **Obrmatr,bool &dop) {	
	int i, j, k;
	Obrmatr=new float* [x];
	for(i=0; i<x; i++) {
		Obrmatr[i]=new float [x];
		for(j=0; j<x; j++) {Obrmatr[i][j]=0;}
		Obrmatr[i][i]=1; 
	}
	float a, b;
	for(i=0; i<x; i++) {
		a=mass[i][i];
		for(j=i+1; j<x; j++) {
			b=mass[j][i];
			for(k=0; k<x; k++) {
				mass[j][k]=mass[i][k]*b-mass[j][k]*a;
				Obrmatr[j][k]=Obrmatr[i][k]*b-Obrmatr[j][k]*a; 
			} 
		} 
	}
	float sum;
	for(i=0; i<x; i++) {
		for(j=x-1; j>=0; j--) {
			sum=0;
			for(k=x-1;k>j;k--){
				sum+=mass[j][k]*Obrmatr[k][i];
				if(mass[j][j]==0) {
					for( unsigned int i = 0; i < x; ++i ) {
                    delete [] Obrmatr[ i ];
                    }
                    delete [] Obrmatr; 
                    cout << endl << "There isn't the inverse matrix for this one";
				dop = false;
				return false;
			}
				}
			}
			Obrmatr[j][i]=(Obrmatr[j][i]-sum)/mass[j][j]; 
		} 
	} 
	return Obrmatr; 
}
float **matr, **matr1, **matr2;
	int main () {
		string s1,s2;
		unsigned int rows1, rows2, rows3, columns1, columns2, columns3;
		char op;
		bool k=false;
		if (!(vernvvod(s1, op, s2))) {
		cin.get();
		return 0;
		}
		matr1=readmatr (rows1, columns1, matr1);
		if (op == 'T') {
			rows3=columns1;
			columns3=rows1;
			matr = new float *[ rows3 ];
			for( unsigned int i = 0; i < rows3; ++i ) {
	    			matr[ i ] = new float[ columns3 ];
	    			for( unsigned int j = 0; j < columns3; ++j ) {
	       	 			matr[ i ][ j ] = 0.0f;
	    			}
			}
		}
		else {	
			rows3=rows1;
			columns3=columns1;
			matr = new float *[ rows3 ];
			for( unsigned int i = 0; i < rows3; ++i ) {
	    			matr[ i ] = new float[ columns3 ];
	    			for( unsigned int j = 0; j < columns3; ++j ) {
	       	 			matr[ i ][ j ] = 0.0f;
	    			}
			}
		}	
			 if(op=='+') {
			 	bool dop=true;
				matr2=readmatr (rows2, columns2, matr2); 	
				k=pl(matr1, rows1, columns1, matr2, rows2, columns2, matr, rows3, columns3,dop);
				if (!dop) { cin.get(); return 0; }
				break;
			}
			else if(op== '-') {	
				bool dop=true; 
				matr2=readmatr (rows2, columns2, matr2); 	
				k=min(matr1, rows1, columns1, matr2, rows2, columns2, matr, rows3, columns3,dop);
				if (!dop) { cin.get(); return 0; }
				break;
			}
			else if(op== '*') {	
				bool dop=true; 
				matr2=readmatr (rows2, columns2, matr2); 	
				k=umn(matr1, rows1, columns1, matr2, rows2, columns2, matr, rows3, columns3,dop);
				if (!dop) { cin.get(); return 0; }
				break;		 
			}
			else if(op== 'T') {
				for (int i=0; i<rows1; i++){
					for (int j=0; j<columns1; j++){		
						matr[j][i]=matr1[i][j];
					}
				}
			}
			else if(op== 'R') {
				if (columns1==rows1){	float opr = opredelitel(matr1, columns1);
                if(opr!=0){
				bool dop= true;
				succ = obrmatr(rows1, matrix1, matrix, dop);
			if (!dop ) { cin.get(); return 0; }
		}
		else cout << "An error has occured while reading input data";
		break;
	}
			}
		cout << endl;
		if (op == 'T') {
		    	write(matr, rows3, columns3);
	}
	else {
		if (succ   == true) {
			write(matr, rows3, columns3);
		}
		else {
			cout << "An error has occured while reading input data";
		}
	}
		cin.get();
		return 0;
	}
