#include "Mesh.h"

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
    // Allocates dynamic size for face_normals matrix
    this->face_normals.resize(this->num_faces, 3);

    // Allocates dynamic size for face_normals matrix
    this->vertices_normals.resize(this->num_vertices, 3);

    // iterates through each row of the faces matrix
    for (size_t i = 0; i < this->num_faces; i++)
    {
        // acquire vertex indexes information from faces
        Eigen::Vector3i verticesIdx = this->faces.row(i);

        // get vertices coordinates from vertices
        Eigen::Vector3d v0 = this->vertices.row(verticesIdx(0));
        Eigen::Vector3d v1 = this->vertices.row(verticesIdx(1));
        Eigen::Vector3d v2 = this->vertices.row(verticesIdx(2));

        // compute the cross product (unnormalized face normal)
        Eigen::Vector3d faceNormal = (v1 - v0).cross(v2 - v1);

        // add this value to vertex normal matrice
        this->vertices_normals.row(verticesIdx(0)) += faceNormal;
        this->vertices_normals.row(verticesIdx(1)) += faceNormal;
        this->vertices_normals.row(verticesIdx(2)) += faceNormal;

        // normalization of faces vector
        faceNormal.normalize();

        // assign to face_normal matrix, on the given row
        this->face_normals.row(i) = faceNormal;
    }
    // lastly, normalize each row (vertice) of vertices_normals matrix
    this->vertices_normals.rowwise().normalize();
    return;
}

} // namespace bunny_mesh