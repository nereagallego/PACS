#include <iostream>
#include <Eigen/Dense>

#define EIGEN_DONT_VECTORIZE

int main()
{
    int N = 20000; 

    Eigen::MatrixXd mat = Eigen::MatrixXd::Random(N,N);
    // std::cout << "Here is mat*mat:\n" << mat*mat << std::endl;
}