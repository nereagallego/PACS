#include <vector>
#include <random>
#include <iostream>
#include <sys/time.h>
#include <iomanip>

using namespace std;



const long max_rand = 1000000L;

double randomNumber(){
const double lower_bound = 0;
const double upper_bound = 10;  
   
   return lower_bound + (upper_bound - lower_bound) * (random() % max_rand) / max_rand;
}

void multiplyMatrix(int N, vector<vector<double>> m1, vector<vector<double>> m2, vector<vector<double>>& result){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for (int k = 0; k < N; k++){
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

int main(int argc, char *argv[]){
    struct timeval start, end;
    struct timeval start2, end2;

    gettimeofday(&start, NULL);
    if(argc < 2){
        cerr << "Usage ./matrixMultEigen.cpp <N>" << endl;
    }
    int N = atoi(argv[1]); 
    vector<vector<double>> matrix1, matrix2, result;

    int num = 1;
    for(int i = 0; i < N; i++) {
        vector<double> v1;
        vector<double> v2;
        vector<double> r;

        for(int j = 0; j < N; j++) {
            v1.push_back(randomNumber());
            v2.push_back(randomNumber());
            // v1.push_back(num);
            // v2.push_back(num);
            r.push_back(0);
        }

        num += 1;
        matrix1.push_back(v1);
        matrix2.push_back(v2);
        result.push_back(r);
    }
    gettimeofday(&end, NULL);
    gettimeofday(&start2, NULL);

    multiplyMatrix(N, matrix1, matrix2, result);
    gettimeofday(&end2, NULL);

    double elapsed_time = (end.tv_sec - start.tv_sec) +
                          (end.tv_usec - start.tv_usec) / 1000000.0;

    double elapsed_time2 = (end2.tv_sec - start2.tv_sec) +
                          (end2.tv_usec - start2.tv_usec) / 1000000.0;

    std::cout << "Seconds declaration: " << std::fixed << std::setprecision(4)
        << elapsed_time << std::endl;
    std::cout << "Seconds multiplication: " << std::fixed << std::setprecision(4)
        << elapsed_time2 << std::endl;

    return 0;
}