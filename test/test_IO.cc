#include "gtest/gtest.h"
#include "bunny_mesh/data_io.h"

#include <Eigen/Dense>
#include <iostream>

/**
 * @brief Tests writing and reading integers between numpy array and eigen
 */
TEST(IO, Write_Read_Int)
{
    const std::string filename = "test/data/sequential_int.npy";
    // loads a simple matrix
    Eigen::MatrixX3i matEigen(3,3); 
    matEigen << 1, 2, 3,
                4, 5, 6,
                7, 8, 9;
    // writes it to file
    bunny_dataIO::saveIntMatrixToNumpyArray(filename, matEigen);
    
    // reads same matrix from file
    Eigen::MatrixX3i matNumpy;
    matNumpy = bunny_dataIO::readIntNumPyArray(filename);
    
    // Begin testing...
    ASSERT_EQ(matEigen.rows(), matNumpy.rows());
    ASSERT_EQ(matEigen.cols(), matNumpy.cols());
    ASSERT_TRUE(matEigen.isApprox(matNumpy));
}

/**
 * @brief Tests writing and reading doubles between numpy array and eigen
 */
TEST(IO, Write_Read_Double)
{
    const std::string filename = "test/data/sequential_double.npy";
    // loads a simple matrix
    Eigen::MatrixX3d matEigen(3,3); 
    matEigen << 1.1, 2.2, 3.3,
                4.4, 5.5, 6.6,
                7.7, 8.8, 9.9;
    // writes it to file
    bunny_dataIO::saveMatrixToNumpyArray(filename, matEigen);
    
    // reads same matrix from file
    Eigen::MatrixX3d matNumpy;
    matNumpy = bunny_dataIO::readFloatNumPyArray(filename);
    
    // Begin testing...
    ASSERT_EQ(matEigen.rows(), matNumpy.rows());
    ASSERT_EQ(matEigen.cols(), matNumpy.cols());
    ASSERT_TRUE(matEigen.isApprox(matNumpy));
}