/**
 * @file main.cc
 * @author Pedro Henrique S. Perrusi (pedro.perrusi@gmail.com)
 * @brief Main file for Bunny Mesh Normals project.
 * @version 1.0
 * @date 2019-02-07
 * 
 * @copyright Copyright (c) 2019 Pedro Henrique S. Perrusi
 * 
 */
#include "data_io.h"
#include "Mesh.h"

#include <Eigen/Dense>
#include <iostream>
#include <string>

/**
 * @brief Main function of bunny_mesh_normals project
 */
int main()
{
    // Loads Bunny data into Eigen matrices
    Eigen::MatrixXi faces;    // integer type matrix
    Eigen::MatrixXd vertices; // floating point type matrix
    try
    {
        // Read Faces Matrix
        faces = bunny_dataIO::readIntNumPyArray("data/bunny_faces.npy");
        // Read vertices matrix
        vertices = bunny_dataIO::readFloatNumPyArray("data/bunny_vertices.npy");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    // Create a bunny mesh object based on vertices and faces information
    bunny_mesh::TriangleMesh bunnyMesh(vertices, faces);

    // Compute normalized face normals and normalized vertices normals
    bunnyMesh.ComputeNormals();

    // Get faces normal
    Eigen::MatrixXd face_normals = bunnyMesh.getFaceNormals();
    // take a look...
    bunny_dataIO::printArray(face_normals);

    // Get vertices normal
    Eigen::MatrixXd verices_normals = bunnyMesh.getVerticeNormals();
    // take a look...
    bunny_dataIO::printArray(verices_normals);

    return 0;
}
