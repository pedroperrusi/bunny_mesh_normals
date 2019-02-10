/**
 * @file test_IO.cc
 * @author Pedro Henrique S. Perrusi (pedro.perrusi@gmail.com)
 * @brief Unitest module for the bunny_mesh/data_io.h file.
 * @version 1.0
 * @date 2019-02-10
 * 
 * @copyright Copyright (c) 2019 Pedro Henrique S. Perrusi
 * 
 */
#include "gtest/gtest.h"
#include "bunny_mesh/data_io.h"

#include <Eigen/Dense>
#include <iostream>

using namespace bunny_dataIO;

/**
 * @brief Tests writing and reading integers between numpy array and eigen
 */
TEST(IO, Write_Read_Int)
{
    const std::string filename = "test/data/sequential_int.npy";
    // loads a simple matrix
    IndexMatrixType matEigen(3,3); 
    matEigen << 1, 2, 3,
                4, 5, 6,
                7, 8, 9;
    // writes it to file
    saveIntMatrixToNumpyArray(filename, matEigen);
    
    // reads same matrix from file
    IndexMatrixType matNumpy;
    matNumpy = readIntNumPyArray(filename);
    
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
    Point3DMatrixType matEigen(3,3); 
    matEigen << 1.1, 2.2, 3.3,
                4.4, 5.5, 6.6,
                7.7, 8.8, 9.9;
    // writes it to file
    saveMatrixToNumpyArray(filename, matEigen);
    
    // reads same matrix from file
    Point3DMatrixType matNumpy;
    matNumpy = readFloatNumPyArray(filename);
    
    // Begin testing...
    ASSERT_EQ(matEigen.rows(), matNumpy.rows());
    ASSERT_EQ(matEigen.cols(), matNumpy.cols());
    ASSERT_TRUE(matEigen.isApprox(matNumpy));
}