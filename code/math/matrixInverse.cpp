const double eps=1e-12;

vector<vector<double>> GaussJordan(vector<vector<double>> A, double& det){
	int n=A.size();
	vector<vector<double>>inv(n,vector<double>(n));
	for(int i=0;i<n;i++){
		inv[i][i]=1;
	}
	bool swp=0;
	for(int	col=0,row=0;col<n && row<n;col++,row++){
		int sel=row;
		for(int i=row;i<n;i++){
			if(fabs(A[i][col])>fabs(A[sel][col])){
				sel=i;
			}
		}

		if(fabs(A[sel][col])<eps){
			//There is no inverse
			det=0;
			return {{}};
		}
		if(sel!=row){
			swp^=1;
			for(int j=0;j<n;j++){
				swap(A[sel][j],A[row][j]);
				swap(inv[sel][j],inv[row][j]);
			}
		}


		for(int i=0;i<n;i++){
			if(i!=row){
				double c=A[i][col]/A[row][col];

				for(int j=0;j<n;j++){
					A[i][j]-=c*A[row][j];
					inv[i][j]-=c*inv[row][j];
				}
			}
		}
	}

	//Finishing the inversion process and getting
	//the determinant through the main diagonal
	for(int i=0;i<n;i++){
		double c=A[i][i];
		det*=c;
		for(int j=0;j<n;j++){
			A[i][j]/=c;
			inv[i][j]/=c;
		}
	}
	if(swp)det*=-1;

	return inv;
}
int main(){
    int n;
    cin>>n;
    vector<vector<double>>a,inv;
    a=vector<vector<double>>(n,vector<double>(n));
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        cin>>a[i][j];
      }
    }
    double det=1;
    inv=GaussJordan(a,det);
    return 0;
}
