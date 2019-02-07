/**
 * @file data_io.h
 * @author Pedro Henrique S. Perrusi (pedro.perrusi@gmail.com)
 * @brief Input and output operations used in Bunny Mesh Normals project
 * @version 1.0
 * @date 2019-02-07
 * 
 * @copyright Copyright (c) 2019 Pedro Henrique S. Perrusi
 * 
 */
#ifndef _BUNNY_DATA_IO_
#define _BUNNY_DATA_IO_

#include "cnpy.h"

#include <Eigen/Dense>
#include <Eigen/Core>
#include <iostream>
#include <string>
#include <stdexcept>

namespace bunny_dataIO
{

/**
 * @brief Print an Eigen array for any of Matrix Base derived objects.
 * 
 * Matrx format is based on Octave/Matlab.
 * 
 * Inspired by : 
 *      - https://eigen.tuxfamily.org/dox/structEigen_1_1IOFormat.html
 *      - https://eigen.tuxfamily.org/dox/TopicFunctionTakingEigenTypes.html
 * 
 * @tparam Derived : template which denotes Eigen::MatrixBase derived objects.
 * @param array : array, or matrix to be printed out.
 */
template <typename Derived>
inline void printArray(const Eigen::MatrixBase<Derived> &array)
{
    Eigen::IOFormat OctaveFmt(Eigen::StreamPrecision, 0, ", ", ";\n", "", "", "[", "]");
    std::cout << array.format(OctaveFmt) << std::endl;
}

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
    cnpy::NpyArray array = cnpy::npy_load(filename);

    /* check if word size corresponds to double floating point size */
    if (array.word_size != sizeof(DataType))
    {
        throw std::invalid_argument("Data IO Error: Data type of numpy array is not a Double");
    }

    // pointer to numpy array data
    DataType *dataPtr = array.data<DataType>();

    // maps numpy array into an Eigen Matrix
    size_t rows = array.shape[0];
    size_t cols = array.shape[1];
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
    cnpy::NpyArray array = cnpy::npy_load(filename);

    /* check if word size corresponds to double floating point size */
    if (array.word_size != sizeof(DataType))
    {
        throw std::invalid_argument("Data IO Error: Data type of numpy array is not a integer");
    }

    // pointer to numpy array data
    DataType *dataPtr = array.data<DataType>();

    // maps numpy array into an Eigen Matrix
    size_t rows = array.shape[0];
    size_t cols = array.shape[1];
    MapType mapArray(dataPtr, rows, cols);

    return mapArray;
}

inline void saveMatrixToNumpyArray(std::string filename, Eigen::MatrixX3d &eigenMatrice)
{
    // We need to be sure the Matrix is Written as RowMajor.
    // cnpy does not support ColMajor matrices until this date.
    using MapType = Eigen::Map<Eigen::MatrixX3d, Eigen::RowMajor>;
    size_t rows = eigenMatrice.rows();
    size_t cols = eigenMatrice.cols();
    // Allocate space for a row major copy of the matrix
    double *dataPtr = new double[rows*cols];

    MapType(dataPtr, rows, cols) = eigenMatrice;

    cnpy::npy_save(filename, dataPtr, {rows, cols}, "w");
}

} // namespace bunny_dataIO
#endif // _BUNNY_DATA_IO_