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
 * 
 * References:
 *  - https://en.wikipedia.org/wiki/Polygon_mesh
 *  - https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/shading-normals
 *  - https://computergraphics.stackexchange.com/questions/4031/programmatically-generating-vertex-normals
 *  - http://www.iquilezles.org/www/articles/normals/normals.htm
 */
class TriangleMesh
{
private:
  // Type definition of indexes array as an integer eigen matrix
  using IndexArrayType = Eigen::MatrixXi;

  // Type definition of double floating porint array as an double eigen matrix
  using DoubleArrayType = Eigen::MatrixXd;

public:
  /**
     * @brief Construct a new Triangle Mesh object.
     * 
     * @param vertices: vector of 3D points in the world space; 
     * @param faces : vector of 3 vertices idexes which composes a triangular face.
     */
  TriangleMesh(DoubleArrayType &vertices, IndexArrayType &faces)
  {
    this->faces = faces;
    this->vertices = vertices;
    this->num_faces = this->faces.rows();
    this->num_vertices = this->vertices.rows();
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
  inline IndexArrayType getFaces() { return this->faces; }

  /**
     * @brief Get the Vertices object
     * 
     * @return vertices private object
     */
  inline DoubleArrayType getVertices() { return this->vertices; }

  /**
     * @brief Get the faces normalized normals object
     * 
     * @return face_normals private object
     */
  inline DoubleArrayType getFaceNormals() { return this->face_normals; }

  /**
     * @brief Get the vertices normalized normals object
     * 
     * @return vertices_normals private object
     */
  inline DoubleArrayType getVerticeNormals() { return this->vertices_normals; }

private:
  // Faces is is a matrix of size (num_faces, 3).
  // Each of its elements denotes a row index to the vertices matrix
  IndexArrayType faces;

  // Number of faces
  size_t num_faces;

  // Number of vertices
  size_t num_vertices;

  // Vertices is a matrix of size (num_vertices, 3) where each row represents a spatial point (x,y,z)
  DoubleArrayType vertices;

  // Array of normalized face normals of size (num_faces, 3)
  DoubleArrayType face_normals;

  // Array of normalized vertex normals of size (num_vertices, 3)
  DoubleArrayType vertices_normals;
};
} // namespace bunny_mesh

#endif // _BUNNY_MESH_