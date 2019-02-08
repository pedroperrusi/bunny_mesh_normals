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
 * @brief Save Eigen Integer Matrix as a numpy array file.
 * 
 * Up to this date, CNPY library does not support writting collumn major arrays (fortran_order).
 * As a reference, you can see this thread on CNPY issue [#20](https://github.com/rogersce/cnpy/issues/20).
 * 
 * So some attention is necessary to assure the compatibility between the Eigen Arrays, usually collumn major, and the numpy file.
 * 
 * @param filename 
 * @param eigenMatrice 
 */
inline void saveIntMatrixToNumpyArray(std::string filename, Eigen::MatrixX3i &eigenMatrice)
{
    size_t rows = eigenMatrice.rows();
    size_t cols = eigenMatrice.cols();
    // We need to assure the Matrix is Written as RowMajor.
    // cnpy does not support ColMajor matrices until this date.
    if (eigenMatrice.IsRowMajor)
    {
        // if matrix is a row major, we can just write it as a numpy file
        cnpy::npy_save(filename, eigenMatrice.data(), {rows, cols}, "w");
    }
    else
    {
        // Prepare mapping conversion to a row major matrix
        using RowMajorArray = Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
        using MapType = Eigen::Map<RowMajorArray>;
        // Allocate space for a row major copy of the matrix
        int *dataPtr = new int[rows * cols];
        // Perform memory conversion
        MapType(dataPtr, rows, cols) = eigenMatrice;
        // Save it to numpy file
        cnpy::npy_save(filename, dataPtr, {rows, cols}, "w");
        // free up memory space
        delete[] dataPtr;
    }
}

/**
 * @brief Save Eigen Matrix as a numpy array file.
 * 
 * Up to this date, CNPY library does not support writting collumn major arrays (fortran_order).
 * As a reference, you can see this thread on CNPY issue [#20](https://github.com/rogersce/cnpy/issues/20).
 * 
 * So some attention is necessary to assure the compatibility between the Eigen Arrays, usually collumn major, and the numpy file.
 * 
 * @param filename 
 * @param eigenMatrice 
 */
inline void saveMatrixToNumpyArray(std::string filename, Eigen::MatrixX3d &eigenMatrice)
{
    size_t rows = eigenMatrice.rows();
    size_t cols = eigenMatrice.cols();
    // We need to assure the Matrix is Written as RowMajor.
    // cnpy does not support ColMajor matrices until this date.
    if (eigenMatrice.IsRowMajor)
    {
        // if matrix is a row major, we can just write it as a numpy file
        cnpy::npy_save(filename, eigenMatrice.data(), {rows, cols}, "w");
    }
    else
    {
        // Prepare mapping conversion to a row major matrix
        using RowMajorArray = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
        using MapType = Eigen::Map<RowMajorArray>;
        // Allocate space for a row major copy of the matrix
        double *dataPtr = new double[rows * cols];
        // Perform memory conversion
        MapType(dataPtr, rows, cols) = eigenMatrice;
        // Save it to numpy file
        cnpy::npy_save(filename, dataPtr, {rows, cols}, "w");
        // free up memory space
        delete[] dataPtr;
    }
}

/**
* @brief Reads a floating number numpy array written on a file.
* 
* Up to this date, CNPY library does not support writting collumn major arrays (fortran_order).
* As a reference, you can see this thread on CNPY issue [#20](https://github.com/rogersce/cnpy/issues/20).
* 
* So some attention is necessary to assure the compatibility between the Eigen Arrays, usually collumn major, and the numpy file.
* 
* @param filename : path to the numpy file. Usual extension: '.npy'
* @return Eigen::MatrixXd : an eigen matrix composed by the file data.
*/
inline Eigen::MatrixXd readFloatNumPyArray(std::string filename)
{
    // Floating point numpy array type definitions
    using DataType = double;
    using ArrayType = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
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
    // Integer numpy array type definitions
    using DataType = int;
    using ArrayType = Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
    using MapType = Eigen::Map<ArrayType>;

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
} // namespace bunny_dataIO
#endif // _BUNNY_DATA_IO_