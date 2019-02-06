#include"cnpy.h"

#include <Eigen/Dense>
#include<iostream>
#include<string>

Eigen::MatrixXd readFloatNumPyArray(std::string filename)
{
    typedef double DataType;
    typedef Eigen::MatrixXd ArrayType;
    typedef Eigen::Map<ArrayType, Eigen::RowMajor> MapType;

    cnpy::NpyArray arr = cnpy::npy_load(filename);
    size_t rows = arr.shape[0];
    size_t cols = arr.shape[1];

    DataType* dataPtr = arr.data<DataType>();

    MapType mapArray(dataPtr, rows, cols);

    return mapArray;
}

int main()
{
    Eigen::MatrixXd vertices = readFloatNumPyArray("data/bunny_vertices.npy");
    
    Eigen::IOFormat OctaveFmt(Eigen::StreamPrecision, 0, ", ", ";\n", "", "", "[", "]");
    std::cout << vertices.format(OctaveFmt) << std::endl;
    std::cout << vertices.rows() << ' ' << vertices.cols() << std::endl;
    
    return 0;
}
