#include "matrix.h"

vector< vector<double> > matrixTranspose(const vector< vector<double> > &A, const unsigned int &n, const unsigned int &m){

  vector< vector<double> > C;
  C.resize(m);
  for(unsigned int r = 0; r < m; r++){
    C[r].resize(n);
    for(unsigned int c = 0; c < n; c++){
      C[r][c] = A[c][r];
    }
  }

  return C;
}


vector< vector<double> > matrixAdd(const vector< vector<double> > &A, const vector< vector<double> > &B, const unsigned int &n, const unsigned int &m){

  vector< vector<double> > C;
  C.resize(n);
  for(unsigned int r = 0; r < n; r++){
    C[r].resize(m);
    for(unsigned int c = 0; c < m; c++){
      C[r][c] = A[r][c] + B[r][c];
    }
  }

  return C;
}

vector< vector<double> > matrixMultiply(const vector< vector<double> > &A, const vector< vector<double> > &B, const unsigned int &n, const unsigned int &m, const unsigned int &p){

  vector< vector<double> > C;
  C.resize(n);

  for(unsigned int r = 0; r < n; r++){
    C[r].resize(p);
    for(unsigned int c = 0; c < p; c++){
      C[r][c] = 0;
      for(unsigned int k = 0; k < m; k++){
	C[r][c] += A[r][k] * B[k][c];
      }
    }
  }

  return C;
}

vector<double> vectorAdd(const vector<double> &a, const vector<double> &b, const unsigned int &n){

  vector<double> c;
  c.resize(n);

  for(unsigned int r = 0; r < n; r++){
    c[r] = a[r] + b[r];
  }

  return c;

}

double vectorDotProduct(const vector<double> &a, const vector<double> &b, const unsigned int &n){

  double c = 0;

  for(unsigned int r = 0; r < n; r++){
    c += a[r] * b[r];
  }

  return c;
}

vector<double> scalarVectorMultiply(const double &scale, const vector<double> &a, const unsigned int &n){

  vector<double> c;
  c.resize(n);

  for(unsigned int r = 0; r < n; r++){
    c[r]  = scale * a[r];
  }

  return c;
}


vector< vector<double> > scalarMatrixMultiply(const double &scale, const vector< vector<double> > &A, const unsigned int &n, const unsigned int &m){

  vector< vector<double> > C;
  C.resize(n);

  for(unsigned int r = 0; r < n; r++){
    C[r].resize(m);
    for(unsigned int c = 0; c < m; c++){
      C[r][c] = scale * A[r][c];
    }
  }

  return C;
}

vector<double> matrixVectorMultiply(const vector< vector<double> > &A, const vector<double> &b, const unsigned int &n, const unsigned int &m){

  vector<double> c;
  c.resize(n);

  for(unsigned int r = 0; r < n; r++){
    c[r] = 0;
    for(unsigned int i = 0; i < m; i++){
	c[r] += A[r][i] * b[i];
    }
  }

  return c;
}

double vectorMaxDiff(const vector<double> &a, const vector<double> &b, const unsigned int &n){

  double diff = -1;
  for(unsigned int r = 0; r < n; r++){
    double d = fabs(a[r] - b[r]); 
    if(d > diff){
      diff = d;
    }
  }
  
  return diff;
}

vector<double> vectorCopy(const vector<double> &a, const unsigned int &n){

  vector<double> c;
  c.resize(n);
  for(unsigned int r = 0; r < n; r++){
    c[r] = a[r];
  }
  
  return c;
}

vector<double> zeroVector(const unsigned int &n){

  vector<double> c;
  c.resize(n);
  for(unsigned int r = 0; r < n; r++){
    c[r] = 0;
  }
  
  return c;
}

vector< vector<double> > identityMatrix(const unsigned int &n){

  vector< vector<double> > I;
  I.resize(n);
  for(unsigned int r = 0; r < n; r++){
    I[r].resize(n);

    for(unsigned int c = 0; c < n; c++){
      I[r][c] = (r == c)? 1.0 : 0;
    }

  }
  
  return I;

}

double sumOfElements(const vector<double> &v, const unsigned int &n){

  double sum = 0;
  
  for(unsigned int r = 0; r < n; r++){
    sum += v[r];
  }
  
  return sum;
}

