/**
 * @file Mesh.h
 * @author Pedro Henrique S. Perrusi (pedro.perrusi@gmail.com)
 * @brief Definition of Mesh classes and Methods related to Bunny Mesh Normals project.
 * @version 1.0
 * @date 2019-02-07
 * 
 * @copyright Copyright (c) 2019 Pedro Henrique S. Perrusi
 * 
 */
#ifndef _BUNNY_MESH_
#define _BUNNY_MESH_

#include "data_io.h"

#include <Eigen/Geometry> 
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
public:
  /**
     * @brief Construct a new Triangle Mesh object.
     * 
     * @param vertices: vector of 3D points in the world space; 
     * @param faces : vector of 3 vertices idexes which composes a triangular face.
     */
  TriangleMesh(const bunny_dataIO::Point3DMatrixType &vertices, const bunny_dataIO::IndexMatrixType &faces)
  {
    setFaces(faces);
    setVertices(vertices);
    this->num_faces = this->faces.rows();
    this->num_vertices = this->vertices.rows();
    // Allocates dynamic size for face_normals matrix
    this->face_normals = bunny_dataIO::Point3DMatrixType::Zero(num_faces, 3);
    // Allocates dynamic size for face_normals matrix
    this->vertices_normals = bunny_dataIO::Point3DMatrixType::Zero(num_vertices, 3);
    // Sets default orientation
    setOrientation(orientationDefault);
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
    * @brief Computes the angle between object orientation and its default orientation.
    * 
    * @return double radians angle value.
    */
   inline double objectAngle() { return acos(getOrientation().dot(orientationDefault)); }

   /**
    * @brief Computes the rotation axis between object orientation and its default orientation.
    * 
    * @return Normalized Array normal to the rotation.
    */
   inline bunny_dataIO::Point3DType RotationAxis() { return (orientationDefault.cross(getOrientation())).normalized(); }

   /**
    * @brief Apply a rotation transform in the array to convert from relative coordinates to world coordinates.
    * 
    * @param array : relative position of a point to the object.
    * @return 
    */
   bunny_dataIO::Point3DType matchObjectOrientation(const bunny_dataIO::Point3DType& point)
   { 
      Eigen::Affine3d affineRotation(Eigen::AngleAxisd(objectAngle(), RotationAxis()));
      bunny_dataIO::Point3DType newPoint = point * affineRotation.rotation();
      return newPoint; 
   };

  /**
     * @brief Get the Faces object
     * 
     * @return faces private object 
     */
  inline bunny_dataIO::IndexMatrixType getFaces() { return this->faces; }

  /**
     * @brief Set the Faces object 
     */
  inline void setFaces(const bunny_dataIO::IndexMatrixType &faces) { this->faces = faces; }

  /**
     * @brief Get the Vertices object
     * 
     * @return vertices private object
     */
  inline bunny_dataIO::Point3DMatrixType getVertices() { return this->vertices; }

  /**
     * @brief Set the Vertices object 
     */
  inline void setVertices(const bunny_dataIO::Point3DMatrixType &vertices) { this->vertices = vertices; }

  /**
     * @brief Get the Vertices object
     * 
     * @return vertices private object
     */
  inline bunny_dataIO::Point3DType getOrientation(){ return this->orientation; };

  /**
     * @brief Set the Vertices object 
     */
  inline void setOrientation(const bunny_dataIO::Point3DType &orientation) { this->orientation = orientation.normalized(); }

  /**
     * @brief Get the faces normalized normals object
     * 
     * @return face_normals private object
     */
  inline bunny_dataIO::Point3DMatrixType getFaceNormals() { return this->face_normals; }

  /**
     * @brief Get the vertices normalized normals object
     * 
     * @return vertices_normals private object
     */
  inline bunny_dataIO::Point3DMatrixType getVerticeNormals() { return this->vertices_normals; }

private:
  // Number of faces
  size_t num_faces;

  // Number of vertices
  size_t num_vertices;

  // orientation is a 3D array which gives the object orientation. Default value is (x,y,z) = (0,0,1)
  bunny_dataIO::Point3DType orientation;
  const bunny_dataIO::Point3DType orientationDefault = bunny_dataIO::Point3DType(0, 0, 1);

  // Faces is is a matrix of size (num_faces, 3).
  // Each of its elements denotes a row index to the vertices matrix
  bunny_dataIO::IndexMatrixType faces;

  // Vertices is a matrix of size (num_vertices, 3) where each row represents a spatial point (x,y,z)
  bunny_dataIO::Point3DMatrixType vertices;

  // Array of normalized face normals of size (num_faces, 3)
  bunny_dataIO::Point3DMatrixType face_normals;

  // Array of normalized vertex normals of size (num_vertices, 3)
  bunny_dataIO::Point3DMatrixType vertices_normals;
};
} // namespace bunny_mesh

#endif // _BUNNY_MESH_