#include "gtest/gtest.h"
#include "bunny_mesh/Mesh.h"

#include <Eigen/Dense>
#include <iostream>

using namespace bunny_mesh;

TEST(Mesh, SingleFaceNormal)
{
    // defines simple vertices matrix
    Point3DMatrixType vertices(3,3);
    vertices << 0.0, 0.0, 0.0, // (x=0,y=0,z=0)
                1.0, 0.0, 0.0, // (x=1,y=0,z=0)
                0.0, 1.0, 0.0; // (x=0,y=1,z=0)

    // denines a single face
    IndexMatrixType faces(1, 3);
    faces << 0, 1, 2;

    // Create a triangle mesh
    TriangleMesh singleFaceMesh(vertices, faces);
    singleFaceMesh.ComputeNormals();

    // define expected output:
    Point3DMatrixType expectedFaceNormals(1,3);
    expectedFaceNormals << 0.0, 0.0, 1.0;

    Point3DMatrixType expectedVerticeNormals(3,3);
    expectedVerticeNormals << 0.0, 0.0, 1.0,
                              0.0, 0.0, 1.0,
                              0.0, 0.0, 1.0;

    // test them...
    ASSERT_TRUE(expectedFaceNormals.isApprox(singleFaceMesh.getFaceNormals()));
    ASSERT_TRUE(expectedVerticeNormals.isApprox(singleFaceMesh.getVerticeNormals()));
}