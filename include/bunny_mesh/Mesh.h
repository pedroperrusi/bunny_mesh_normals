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
   TriangleMesh(bunny_dataIO::Point3DMatrixType &vertices, bunny_dataIO::IndexMatrixType &faces)
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
   inline bunny_dataIO::IndexMatrixType getFaces() { return this->faces; }

   /**
     * @brief Get the Vertices object
     * 
     * @return vertices private object
     */
   inline bunny_dataIO::Point3DMatrixType getVertices() { return this->vertices; }

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
   // Faces is is a matrix of size (num_faces, 3).
   // Each of its elements denotes a row index to the vertices matrix
   bunny_dataIO::IndexMatrixType faces;

   // Number of faces
   size_t num_faces;

   // Number of vertices
   size_t num_vertices;

   // Vertices is a matrix of size (num_vertices, 3) where each row represents a spatial point (x,y,z)
   bunny_dataIO::Point3DMatrixType vertices;

   // Array of normalized face normals of size (num_faces, 3)
   bunny_dataIO::Point3DMatrixType face_normals;

   // Array of normalized vertex normals of size (num_vertices, 3)
   bunny_dataIO::Point3DMatrixType vertices_normals;
};
} // namespace bunny_mesh

#endif // _BUNNY_MESH_