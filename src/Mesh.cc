/**
 * @file Mesh.cc
 * @author Pedro Henrique S. Perrusi (pedro.perrusi@gmail.com)
 * @brief Source file of Mesh.h header file.
 * @version 1.0
 * @date 2019-02-07
 * 
 * @copyright Copyright (c) 2019 Pedro Henrique S. Perrusi
 * 
 */
#include "bunny_mesh/Mesh.h"

#include <iostream>

namespace bunny_mesh
{
/**
    * @brief Apply a rotation transform in the array to convert from relative coordinates to world coordinates.
    * 
    * @param array : relative position of a point to the object.
    * @return 
    */
bunny_dataIO::Point3DType TriangleMesh::matchObjectOrientation(const bunny_dataIO::Point3DType &point)
{
    Eigen::Affine3d affineRotation(Eigen::AngleAxisd(objectAngle(), -RotationAxis()));
    bunny_dataIO::Point3DType newPoint = point * affineRotation.rotation();
    return newPoint;
};

/**
 * @brief Returns the object vertices for an arbitrary object orientation.
 * 
 * @return bunny_dataIO::Point3DMatrixType 
 */
bunny_dataIO::Point3DMatrixType TriangleMesh::getVerticesIntoWorld()
{
    // If the default orientation is set, verticesWorld is just a copy of vertices
    if (orientation == orientationDefault)
    {
        return vertices;
    }
    else
    {
        bunny_dataIO::Point3DMatrixType verticesWorld;
        verticesWorld = bunny_dataIO::Point3DMatrixType::Zero(vertices.rows(), vertices.cols());
        // we must transform each relative vertex into a world equivalent
        for (size_t i = 0; i < num_vertices; i++)
        {
            bunny_dataIO::Point3DType vertice = vertices.row(i);
            verticesWorld.row(i) = matchObjectOrientation(vertice);
        }
        return verticesWorld;
    }
}

/**
     * @brief Given the faces and vertices arrays, compute the normalized normal matrix to each face and vertex.
     * 
     * A face normal for a triangle mesh can be calculated as the cross product between two of its sides.
     * 
     *      Face_Normal = normalized((v1 - v0).cross(v2 - v1))
     * 
     * A vertex normal is the sum of the unnormalized face normals connected to each vertice.
     * If a given vertice is not connected to any faces, the vertices_normal row will have not a number.
     * 
     * Its assumed that the vertices are defined in a counter-clockwise direction.
     */
void TriangleMesh::ComputeNormals()
{
    bunny_dataIO::Point3DMatrixType verticesWorld = getVerticesIntoWorld();
    // iterates through each row of the faces matrix
    for (size_t i = 0; i < num_faces; i++)
    {
        // acquire vertex indexes information from faces ith row
        bunny_dataIO::Index3DType vertices_idx = faces.row(i);

        // get vertices coordinates from vertices
        bunny_dataIO::Point3DType v0 = verticesWorld.row(vertices_idx(0));
        bunny_dataIO::Point3DType v1 = verticesWorld.row(vertices_idx(1));
        bunny_dataIO::Point3DType v2 = verticesWorld.row(vertices_idx(2));

        // compute the cross product (unnormalized face normal)
        bunny_dataIO::Point3DType faceNormal = (v1 - v0).cross(v2 - v1);

        // add this array to vertex normals matrice at given vertices indexes
        vertices_normals.row(vertices_idx(0)) += faceNormal;
        vertices_normals.row(vertices_idx(1)) += faceNormal;
        vertices_normals.row(vertices_idx(2)) += faceNormal;

        // normalization of faces vector
        faceNormal.normalize();

        // assign to face_normal matrix, on the given row
        face_normals.row(i) = faceNormal;
    }
    // lastly normalize each row (vertice) of vertices_normals matrix
    vertices_normals.rowwise().normalize();
    return;
}

} // namespace bunny_mesh