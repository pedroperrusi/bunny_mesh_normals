#include "Mesh.h"

#include <iostream>

namespace bunny_mesh
{
/**
     * @brief Given the faces and vertices arrays, compute the normalized normal matrix to each face.
     * 
     * A face normal for a triangle mesh can be calculated as the cross product between two of its sides.
     * 
     *      Face_Normal = (v1 - v0).cross(v2 - v1)
     * 
     * Its assumed that the vertices are defined in a counter-clockwise direction.
     */
void TriangleMesh::ComputeFaceNormals()
{
    // Allocates dynamic size for face_normals matrix
    this->face_normals.resize(this->num_faces, 3);
    // iterates through each row of the faces matrix
    for (size_t i = 0; i < this->num_faces; i++)
    {
        // acquire vertex indexes information from faces
        Eigen::Vector3i verticesIdx = this->faces.row(i);
        // get vertices coordinates from vertices
        Eigen::Vector3d v0 = this->vertices.row(verticesIdx(0));
        Eigen::Vector3d v1 = this->vertices.row(verticesIdx(1));
        Eigen::Vector3d v2 = this->vertices.row(verticesIdx(2));
        // compute the normalized cross product
        this->face_normals.row(i) = ((v1 - v0).cross(v2 - v1)).normalized();
    }
}

// void TriangleMesh::ComputeVerticeNormals()
// {

// }
} // namespace bunny_mesh