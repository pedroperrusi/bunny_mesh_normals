#include "Data_IO.h"

#include <Eigen/Dense>
#include <iostream>
#include <string>

/**
 * @brief Main function of bunny_mesh_normals project
 */
int main()
{
    // Read Faces Matrix
    Eigen::MatrixXi faces = bunny_dataIO::readIntNumPyArray("data/bunny_faces.npy");

    // print faces matrix
    // Eigen::IOFormat OctaveFmt(Eigen::StreamPrecision, 0, ", ", ";\n", "", "", "[", "]");
    // std::cout << faces.format(OctaveFmt) << std::endl;
    // print faces size
    std::cout << faces.rows() << ' ' << faces.cols() << std::endl;

    // Read vertices matrix
    Eigen::MatrixXd vertices = bunny_dataIO::readFloatNumPyArray("data/bunny_vertices.npy");
    
    // print vertices matrix
    // Eigen::IOFormat OctaveFmt(Eigen::StreamPrecision, 0, ", ", ";\n", "", "", "[", "]");
    // std::cout << vertices.format(OctaveFmt) << std::endl;
    // print vertices size
    std::cout << vertices.rows() << ' ' << vertices.cols() << std::endl;

    return 0;
}
