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

    bunny_mesh::TriangleMesh bunnyMesh(vertices, faces);

    Eigen::MatrixXd face_normals = bunnyMesh.getFaceNormals();

    bunny_dataIO::printArray(face_normals);

    return 0;
}
