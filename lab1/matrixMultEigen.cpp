#include <iostream>
#include <Eigen/Dense>

int main()
{
    int N = 3000; 

    Eigen::MatrixXd mat = Eigen::MatrixXd::Random(N,N);
    Eigen::MatrixXd result(N,N);
    result = mat*mat;

}