#include "Data_IO.h"

#include <Eigen/Dense>
#include <iostream>
#include <string>

/**
 * @brief Main function of bunny_mesh_normals project
 */
int main()
{
    // Loads Bunny data into Eigen matrices 
    Eigen::MatrixXi faces;      // integer type matrix
    Eigen::MatrixXd vertices;   // floating point type matrix
    try
    {
        // Read Faces Matrix
        faces = bunny_dataIO::readIntNumPyArray("data/bunny_faces.npy");
        // Read vertices matrix
        vertices = bunny_dataIO::readFloatNumPyArray("data/bunny_vertices.npy");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    // print faces matrix
    // Eigen::IOFormat OctaveFmt(Eigen::StreamPrecision, 0, ", ", ";\n", "", "", "[", "]");
    // std::cout << faces.format(OctaveFmt) << std::endl;
    // print faces size
    std::cout << faces.rows() << ' ' << faces.cols() << std::endl;
    
    // print vertices matrix
    // Eigen::IOFormat OctaveFmt(Eigen::StreamPrecision, 0, ", ", ";\n", "", "", "[", "]");
    // std::cout << vertices.format(OctaveFmt) << std::endl;
    // print vertices size
    std::cout << vertices.rows() << ' ' << vertices.cols() << std::endl;

    return 0;
}
