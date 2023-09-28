#include <iostream>
#include <Eigen/Dense>
#include <ctime>
#include <iomanip>

int main(int argc, char* argv[])
{
    if(argc < 2){
        std::cerr << "Usage ./matrixMultEigen.cpp <N>" << std::endl;
    }

    clock_t time;
    time = clock();
    int N = atoi(argv[1]); 

    Eigen::MatrixXd mat = Eigen::MatrixXd::Random(N,N);
    Eigen::MatrixXd result(N,N);
    result = mat*mat;
    time = clock() - time;
    std::cout << "Seconds: " << std::fixed << std::setprecision(4)
        << ((float)time)/CLOCKS_PER_SEC << std::endl;
}