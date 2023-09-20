#include <iostream>
#include <Eigen/Dense>

// #define EIGEN_DONT_VECTORIZE 1

int main()
{
    int N = 5000; 

    Eigen::MatrixXd mat = Eigen::MatrixXd::Random(N,N);
    Eigen::MatrixXd result(N,N);
    result = mat*mat;

    // std::cout << "Here is mat*mat:\n" << mat*mat << std::endl;
}