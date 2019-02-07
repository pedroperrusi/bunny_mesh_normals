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
 * Given those two informations, its possible to compute the vertices normalized normal and faces normalized normal. Both of these informations are essential to perform shading effects on computer graphics.
 * 
 * References:
 *  - https://en.wikipedia.org/wiki/Polygon_mesh
 *  - https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/shading-normals
 *  - http://www.iquilezles.org/www/articles/normals/normals.htm
 */
class TriangleMesh
{
private:
  // Type definition of indexes array as a 3 element integer eigen vector
  using Index3DType = Eigen::Vector3i;

  // Type definition of indexes array as a 3 element integer eigen vector
  using Point3DType = Eigen::Vector3d;

  // Type definition of indexes matrix as an integer eigen matrix
  using IndexMatrixType = Eigen::MatrixXi;

  // Type definition of double floating porint matrix as an double eigen matrix
  using DoubleMatrixType = Eigen::MatrixXd;

public:
  /**
     * @brief Construct a new Triangle Mesh object.
     * 
     * @param vertices: vector of 3D points in the world space; 
     * @param faces : vector of 3 vertices idexes which composes a triangular face.
     */
  TriangleMesh(DoubleMatrixType &vertices, IndexMatrixType &faces)
  {
    this->faces = faces;
    this->vertices = vertices;
    this->num_faces = this->faces.rows();
    this->num_vertices = this->vertices.rows();
    // Allocates dynamic size for face_normals matrix
    this->face_normals.resize(num_faces, 3);
    // Allocates dynamic size for face_normals matrix
    this->vertices_normals.resize(num_vertices, 3);
  };

  /**
     * @brief Destructor of Triangle Mesh object
     */
  ~TriangleMesh(){

  };

  /**
     * @brief Given the faces and vertices arrays, compute the normalized normal matrix to each face and vertice.
     */
  void ComputeNormals();

  /**
     * @brief Get the Faces object
     * 
     * @return faces private object 
     */
  inline IndexMatrixType getFaces() { return this->faces; }

  /**
     * @brief Get the Vertices object
     * 
     * @return vertices private object
     */
  inline DoubleMatrixType getVertices() { return this->vertices; }

  /**
     * @brief Get the faces normalized normals object
     * 
     * @return face_normals private object
     */
  inline DoubleMatrixType getFaceNormals() { return this->face_normals; }

  /**
     * @brief Get the vertices normalized normals object
     * 
     * @return vertices_normals private object
     */
  inline DoubleMatrixType getVerticeNormals() { return this->vertices_normals; }

private:
  // Faces is is a matrix of size (num_faces, 3).
  // Each of its elements denotes a row index to the vertices matrix
  IndexMatrixType faces;

  // Number of faces
  size_t num_faces;

  // Number of vertices
  size_t num_vertices;

  // Vertices is a matrix of size (num_vertices, 3) where each row represents a spatial point (x,y,z)
  DoubleMatrixType vertices;

  // Array of normalized face normals of size (num_faces, 3)
  DoubleMatrixType face_normals;

  // Array of normalized vertex normals of size (num_vertices, 3)
  DoubleMatrixType vertices_normals;
};
} // namespace bunny_mesh

#endif // _BUNNY_MESH_