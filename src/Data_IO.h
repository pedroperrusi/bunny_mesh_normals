#ifndef _BUNNY_DATA_IO_
#define _BUNNY_DATA_IO_

#include "cnpy.h"

#include <Eigen/Dense>
#include <iostream>
#include <string>

namespace bunny_dataIO
{
    /**
     * @brief Reads a floating number numpy array written on a file.
     * 
     * @param filename : path to the numpy file. Usual extension: '.npy'
     * @return Eigen::MatrixXd : an eigen matrix composed by the file data.
     */
    inline Eigen::MatrixXd readFloatNumPyArray(std::string filename)
    {
        using DataType = double;
        using ArrayType = Eigen::MatrixXd;
        using MapType = Eigen::Map<ArrayType, Eigen::RowMajor>;

        cnpy::NpyArray arr = cnpy::npy_load(filename);
        size_t rows = arr.shape[0];
        size_t cols = arr.shape[1];

        DataType *dataPtr = arr.data<DataType>();

        MapType mapArray(dataPtr, rows, cols);

        return mapArray;
    }

    /**
     * @brief Reads a integer numpy array written on a file.
     * 
     * @param filename : path to the numpy file. Usual extension: '.npy'
     * @return Eigen::MatrixXi : an eigen matrix composed by the file data.
     */
    inline Eigen::MatrixXi readIntNumPyArray(std::string filename)
    {
        using DataType = int;
        using ArrayType = Eigen::MatrixXi;
        using MapType = Eigen::Map<ArrayType, Eigen::RowMajor>;

        cnpy::NpyArray arr = cnpy::npy_load(filename);
        size_t rows = arr.shape[0];
        size_t cols = arr.shape[1];

        DataType *dataPtr = arr.data<DataType>();

        MapType mapArray(dataPtr, rows, cols);

        return mapArray;
    }
}
#endif // _BUNNY_DATA_IO_