#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <vector>

using namespace std;

vector< vector<double> > matrixTranspose(const vector< vector<double> > &A, const unsigned int &n, const unsigned int &m);

vector< vector<double> > matrixAdd(const vector< vector<double> > &A, const vector< vector<double> > &B, const unsigned int &n, const unsigned int &m);

vector< vector<double> > matrixMultiply(const vector< vector<double> > &A, const vector< vector<double> > &B, const unsigned int &n, const unsigned int &m, const unsigned int &p);

vector<double> vectorAdd(const vector<double> &a, const vector<double> &b, const unsigned int &n);

double vectorDotProduct(const vector<double> &a, const vector<double> &b, const unsigned int &n);

vector<double> scalarVectorMultiply(const double &scale, const vector<double> &a, const unsigned int &n);
vector< vector<double> > scalarMatrixMultiply(const double &scale, const vector< vector<double> > &A, const unsigned int &n, const unsigned int &m);

vector<double> matrixVectorMultiply(const vector< vector<double> > &A, const vector<double> &b, const unsigned int &n, const unsigned int &m);

double vectorMaxDiff(const vector<double> &a, const vector<double> &b, const unsigned int &n);

vector<double> vectorCopy(const vector<double> &a, const unsigned int &n);

vector<double> zeroVector(const unsigned int &n);
vector< vector<double> > identityMatrix(const unsigned int &n);

double sumOfElements(const vector<double> &v, const unsigned int &n);


#endif

