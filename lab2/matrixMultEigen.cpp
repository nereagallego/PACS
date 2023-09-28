#include <iostream>
#include <Eigen/Dense>
#include <ctime>
#include <iomanip>

int main(int argc, char* argv[])
{
    if(argc < 2){
        cerr << "Usage ./matrixMultEigen.cpp <N>" << endl;
    }

    clock_t time;
    time = clock();
    int N = int(argc[1]); 

    Eigen::MatrixXd mat = Eigen::MatrixXd::Random(N,N);
    Eigen::MatrixXd result(N,N);
    result = mat*mat;
    time = clock() - time;
    cout << "Seconds: " << fixed << setprecision(4)
        << ((float)time)/CLOCKS_PER_SEC << endl;
}