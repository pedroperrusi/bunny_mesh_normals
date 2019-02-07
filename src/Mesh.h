#ifndef _BUNNY_MESH_
#define _BUNNY_MESH_

#include <Eigen/Dense>

namespace bunny_mesh
{
/**
 * @brief Triangular mesh following the face-vertex representation.
 * 
 * A face-vertex mesh represents an object as a set of faces and a set of objects.
 * So, an object may be defined by 
 *      - vertices: vector of 3D points in the world space;
 *      - faces: vector of 3 vertices idexes which composes a triangular face.
 * 
 * Given those two informations, its possible to compute the vertices normalized normal and faces normalized normal.
 * Both of these informations are essential to perform shading effects on computer graphics.
 */
class TriangleMesh
{
  private:
    // Type definition of indexes array as an integer eigen matrix
    using IndexArrayType = Eigen::MatrixXi;

    // Type definition of double floating porint array as an double eigen matrix
    using DoubleArrayType = Eigen::MatrixXd;

    // Faces is is a matrix of size (n, 3).
    // Each of its elements denotes a row index to the vertices matrix
    IndexArrayType faces;

    // Vertices is a matrix of size (n, 3) where each row represents a spatial point (x,y,z)
    DoubleArrayType vertices;

  public:
    /**
     * @brief Construct a new Triangle Mesh object.
     * 
     * @param vertices: vector of 3D points in the world space; 
     * @param faces : vector of 3 vertices idexes which composes a triangular face.
     */
    TriangleMesh(DoubleArrayType vertices, IndexArrayType faces)
    {
        this->faces = faces;
        this->vertices = vertices;
    };
};
} // namespace bunny_mesh

#endif // _BUNNY_MESH_