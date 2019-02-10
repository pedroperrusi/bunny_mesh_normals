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
    // iterates through each row of the faces matrix
    for (size_t i = 0; i < num_faces; i++)
    {
        // acquire vertex indexes information from faces ith row
        bunny_dataIO::Index3DType vertices_idx = faces.row(i);

        // get vertices coordinates from vertices
        bunny_dataIO::Point3DType v0 = vertices.row(vertices_idx(0));
        bunny_dataIO::Point3DType v1 = vertices.row(vertices_idx(1));
        bunny_dataIO::Point3DType v2 = vertices.row(vertices_idx(2));

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

double TriangleMesh::objectAngle()
{
    double angle = acos(getOrientation().dot(orientationDefault));
    return angle;
}

} // namespace bunny_mesh