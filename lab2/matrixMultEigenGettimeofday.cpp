#include <iostream>
#include <Eigen/Dense>
#include <sys/time.h>
#include <iomanip>

int main(int argc, char* argv[])
{
    struct timeval start, end;
    struct timeval start2, end2;


    gettimeofday(&start, NULL);
    if(argc < 2){
        std::cerr << "Usage ./matrixMultEigen.cpp <N>" << std::endl;
    }

    int N = atoi(argv[1]); 

    Eigen::MatrixXd mat = Eigen::MatrixXd::Random(N,N);
    Eigen::MatrixXd result(N,N);

    gettimeofday(&end, NULL);
    gettimeofday(&start2, NULL);
    result = mat*mat;
    gettimeofday(&end2, NULL);
    

    double elapsed_time = (end.tv_sec - start.tv_sec) +
                          (end.tv_usec - start.tv_usec) / 1000000.0;

    std::cout << "Seconds declaration: " << std::fixed << std::setprecision(4)
        << elapsed_time << std::endl;

    double elapsed_time2 = (end2.tv_sec - start2.tv_sec) +
                          (end2.tv_usec - start2.tv_usec) / 1000000.0;

    std::cout << "Seconds multiplication: " << std::fixed << std::setprecision(4)
        << elapsed_time2 << std::endl;
}