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
#include "bunny_mesh/data_io.h"
#include "bunny_mesh/Mesh.h"

#include <iostream>
#include <string>

// Input faces file path
const std::string facesFilePath = "data/bunny_faces.npy";
// Input vertices file path
const std::string verticesFilePath = "data/bunny_vertices.npy";
// Output normalized face normals file path
const std::string normFacesFilePath = "data/face_normals.npy";
// Output normalized vertices normals file path
const std::string normVerticesFilePath = "data/vertex_normals.npy";

/**
 * @brief Brief introduction to Bunny Mesh Normals executable file.
 */
void help()
{
    std::cout
    << "\n" 
    << "This program computes the normalized face normals and normalized vertices normals from a given model.\n"
    << "The application inputs are:\n"
    << "\t - '" << facesFilePath      << "'\n"
    << "\t - '" << verticesFilePath   << "'\n"
    << "Output files are written to:\n"
    << "\t - '" << normFacesFilePath     << "'\n"
    << "\t - '" << normVerticesFilePath  << "'\n"
    << std::endl;
}

/**
 * @brief Main function of bunny_mesh_normals project
 */
int main()
{
    help();
    // Loads Bunny data into Eigen matrices
    bunny_dataIO::IndexMatrixType faces;    // integer type matrix
    bunny_dataIO::Point3DMatrixType vertices; // floating point type matrix
    try
    {
        // Read Faces Matrix
        faces = bunny_dataIO::readIntNumPyArray(facesFilePath);
        // Read vertices matrix
        vertices = bunny_dataIO::readFloatNumPyArray(verticesFilePath);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    // take a look...
    // bunny_dataIO::printArray(faces);
    // bunny_dataIO::printArray(vertices);

    // Create a bunny mesh object based on vertices and faces information
    bunny_mesh::TriangleMesh bunnyMesh(vertices, faces);

    // its possible to set an arbitrary orientation to bunnyMesh.
    // the default orientation is z = (0,0,1)
    // example:
    // bunnyMesh.setOrientation(bunny_dataIO::Point3DType(0,1,0));

    // Compute normalized face normals and normalized vertices normals
    bunnyMesh.ComputeNormals();

    // Get faces normal
    bunny_dataIO::Point3DMatrixType face_normals = bunnyMesh.getFaceNormals();
    // take a look...
    // bunny_dataIO::printArray(face_normals);

    // Get vertices normal
    bunny_dataIO::Point3DMatrixType verices_normals = bunnyMesh.getVerticeNormals();
    // take a look...
    // bunny_dataIO::printArray(verices_normals);

    // Save matrices as numpy arrays
    bunny_dataIO::saveMatrixToNumpyArray(normFacesFilePath, face_normals);
    bunny_dataIO::saveMatrixToNumpyArray(normVerticesFilePath, verices_normals);

    std::cout << "Normalized normals matrices written with success." << std::endl;

    return EXIT_SUCCESS;
}
