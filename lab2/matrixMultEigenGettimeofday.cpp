#include <iostream>
#include <Eigen/Dense>
#include <sys/time.h>
#include <iomanip>

int main(int argc, char* argv[])
{
    struct timeval start, end;

    gettimeofday(&start, NULL);
    if(argc < 2){
        std::cerr << "Usage ./matrixMultEigen.cpp <N>" << std::endl;
    }

    int N = atoi(argv[1]); 

    Eigen::MatrixXd mat = Eigen::MatrixXd::Random(N,N);
    Eigen::MatrixXd result(N,N);
    result = mat*mat;

    gettimeofday(&end, NULL);

    double elapsed_time = (end.tv_sec - start.tv_sec) +
                          (end.tv_usec - start.tv_usec) / 1000000.0;

    std::cout << "Seconds: " << std::fixed << std::setprecision(4)
        << elapsed_time << std::endl;
}