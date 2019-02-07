#ifndef _BUNNY_DATA_IO_
#define _BUNNY_DATA_IO_

#include "cnpy.h"

#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <stdexcept>

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

    // load numpy file
    cnpy::NpyArray arr = cnpy::npy_load(filename);

    /* check if word size corresponds to double floating point size */
    if (arr.word_size != sizeof(DataType))
    {
        throw std::invalid_argument("Data IO Error: Data type of numpy array is not a Double");
    }

    // pointer to numpy array data
    DataType *dataPtr = arr.data<DataType>();

    // maps numpy array into an Eigen Matrix
    size_t rows = arr.shape[0];
    size_t cols = arr.shape[1];
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

    // load numpy file
    cnpy::NpyArray arr = cnpy::npy_load(filename);

    /* check if word size corresponds to double floating point size */
    if (arr.word_size != sizeof(DataType))
    {
        throw std::invalid_argument("Data IO Error: Data type of numpy array is not a integer");
    }

    // pointer to numpy array data
    DataType *dataPtr = arr.data<DataType>();

    // maps numpy array into an Eigen Matrix
    size_t rows = arr.shape[0];
    size_t cols = arr.shape[1];
    MapType mapArray(dataPtr, rows, cols);

    return mapArray;
}
} // namespace bunny_dataIO
#endif // _BUNNY_DATA_IO_