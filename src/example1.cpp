#include"cnpy.h"

#include <Eigen/Dense>
#include<iostream>
#include<string>

Eigen::MatrixXd readFloatNumPyArray(std::string filename)
{
    using DataType = double;
    using ArrayType = Eigen::MatrixXd;
    using MapType = Eigen::Map<ArrayType, Eigen::RowMajor>;

    cnpy::NpyArray arr = cnpy::npy_load(filename);
    size_t rows = arr.shape[0];
    size_t cols = arr.shape[1];

    DataType* dataPtr = arr.data<DataType>();

    MapType mapArray(dataPtr, rows, cols);

    return mapArray;
}

Eigen::MatrixXi readIntNumPyArray(std::string filename)
{
    using DataType = int;
    using ArrayType = Eigen::MatrixXi;
    using MapType = Eigen::Map<ArrayType, Eigen::RowMajor>;

    cnpy::NpyArray arr = cnpy::npy_load(filename);
    size_t rows = arr.shape[0];
    size_t cols = arr.shape[1];

    DataType* dataPtr = arr.data<DataType>();

    MapType mapArray(dataPtr, rows, cols);

    return mapArray;
}

int main()
{
    Eigen::MatrixXi faces = readIntNumPyArray("data/bunny_faces.npy");
    
    Eigen::IOFormat OctaveFmt(Eigen::StreamPrecision, 0, ", ", ";\n", "", "", "[", "]");
    std::cout << faces.format(OctaveFmt) << std::endl;
    std::cout << faces.rows() << ' ' << faces.cols() << std::endl;
    
    return 0;
}
