/**
 * @file test_Mesh.cc
 * @brief Unitest module for the bunny_mesh/Mesh.h file.
 * @version 1.0
 * @date 2019-02-10
 * 
 * @copyright Copyright (c) 2019 Pedro Henrique S. Perrusi
 * 
 */
#include "gtest/gtest.h"

#include "bunny_mesh/data_io.h"
#include "bunny_mesh/Mesh.h"

#include <Eigen/Dense>
#include <math.h>
#include <iostream>

using namespace bunny_mesh;

// eigen default value for a very small number
const double precision = Eigen::NumTraits<double>::dummy_precision();
    

TEST(Mesh, SingleFaceNormal)
{
    // defines simple vertices matrix
    bunny_dataIO::Point3DMatrixType vertices(3,3);
    vertices << 0.0, 0.0, 0.0, // (x=0,y=0,z=0)
                1.0, 0.0, 0.0, // (x=1,y=0,z=0)
                0.0, 1.0, 0.0; // (x=0,y=1,z=0)

    // denines a single face
    bunny_dataIO::IndexMatrixType faces(1, 3);
    faces << 0, 1, 2;

    // Create a triangle mesh
    TriangleMesh singleFaceMesh(vertices, faces);
    singleFaceMesh.ComputeNormals();

    // define expected output:
    bunny_dataIO::Point3DMatrixType expectedFaceNormals(1,3);
    expectedFaceNormals << 0.0, 0.0, 1.0;

    bunny_dataIO::Point3DMatrixType expectedVerticeNormals(3,3);
    expectedVerticeNormals << 0.0, 0.0, 1.0,
                              0.0, 0.0, 1.0,
                              0.0, 0.0, 1.0;

    // test them...
    // size assertions:
    ASSERT_EQ(faces.rows(), singleFaceMesh.getFaceNormals().rows());
    ASSERT_EQ(vertices.rows(), singleFaceMesh.getVerticeNormals().rows());
    // norm assertions:
    ASSERT_TRUE(expectedFaceNormals.isApprox(singleFaceMesh.getFaceNormals()));
    ASSERT_TRUE(expectedVerticeNormals.isApprox(singleFaceMesh.getVerticeNormals()));
}

TEST(Mesh, SingleFaceNormalized)
{
    // defines simple vertices matrix
    bunny_dataIO::Point3DMatrixType vertices(3,3);
    vertices << 0.0, 0.0, 0.0,  // (x=0,y=0,z=0)
                10.0, 0.0, 0.0, // (x=10,y=0,z=0)
                0.0, 10.0, 0.0; // (x=0,y=10,z=0)

    // denines a single face
    bunny_dataIO::IndexMatrixType faces(1, 3);
    faces << 0, 1, 2;

    // Create a triangle mesh
    TriangleMesh singleFaceMesh(vertices, faces);
    singleFaceMesh.ComputeNormals();

    // define expected output:
    bunny_dataIO::Point3DMatrixType expectedFaceNormals(1,3);
    expectedFaceNormals << 0.0, 0.0, 1.0;

    bunny_dataIO::Point3DMatrixType expectedVerticeNormals(3,3);
    expectedVerticeNormals << 0.0, 0.0, 1.0,
                              0.0, 0.0, 1.0,
                              0.0, 0.0, 1.0;

    // test them...
    // size assertions:
    ASSERT_EQ(faces.rows(), singleFaceMesh.getFaceNormals().rows());
    ASSERT_EQ(vertices.rows(), singleFaceMesh.getVerticeNormals().rows());
    // norm assertions:
    ASSERT_TRUE(expectedFaceNormals.isApprox(singleFaceMesh.getFaceNormals()));
    ASSERT_TRUE(expectedVerticeNormals.isApprox(singleFaceMesh.getVerticeNormals()));
}

TEST(MESH, ObjectAngle)
{
    // Simple object:
    bunny_dataIO::Point3DMatrixType vertices(3,3);
    vertices << 0.0, 0.0, 0.0, // (x=0,y=0,z=0)
                1.0, 0.0, 0.0, // (x=1,y=0,z=0)
                0.0, 1.0, 0.0; // (x=0,y=1,z=0)

    // denines a single face
    bunny_dataIO::IndexMatrixType faces(1, 3);
    faces << 0, 1, 2;

    // Add a orientation:
    bunny_dataIO::Point3DType orientation;
    orientation << 0.0, 1.0, 0.0;

    // expected angle
    double angle = M_PI_2;

    // create Mesh
    TriangleMesh singleFaceMesh(vertices, faces);
    // set orientation
    singleFaceMesh.setOrientation(orientation);

    // eigen default value for a very small number
    const double precision = Eigen::NumTraits<double>::dummy_precision();

    ASSERT_TRUE(abs(singleFaceMesh.objectAngle() - M_PI_2) < precision);
}

TEST(MESH, ObjectAngleNormalized)
{
    // Simple object:
    bunny_dataIO::Point3DMatrixType vertices(3,3);
    vertices << 0.0, 0.0, 0.0, // (x=0,y=0,z=0)
                1.0, 0.0, 0.0, // (x=1,y=0,z=0)
                0.0, 1.0, 0.0; // (x=0,y=1,z=0)

    // denines a single face
    bunny_dataIO::IndexMatrixType faces(1, 3);
    faces << 0, 1, 2;

    // Add a orientation:
    bunny_dataIO::Point3DType orientation;
    orientation << 0.0, 10.0, 0.0;

    // expected angle
    double angle = M_PI_2;

    // create Mesh
    TriangleMesh singleFaceMesh(vertices, faces);
    // set orientation
    singleFaceMesh.setOrientation(orientation);

    // eigen default value for a very small number
    const double precision = Eigen::NumTraits<double>::dummy_precision();

    ASSERT_TRUE(abs(singleFaceMesh.objectAngle() - M_PI_2) < precision);
}

TEST(MESH, RotationAxis_orientationY)
{
    // Simple object:
    bunny_dataIO::Point3DMatrixType vertices(3,3);
    vertices << 0.0, 0.0, 0.0, // (x=0,y=0,z=0)
                1.0, 0.0, 0.0, // (x=1,y=0,z=0)
                0.0, 1.0, 0.0; // (x=0,y=1,z=0)

    // denines a single face
    bunny_dataIO::IndexMatrixType faces(1, 3);
    faces << 0, 1, 2;

    // Add a orientation:
    bunny_dataIO::Point3DType orientation;
    orientation << 0.0, 1.0, 0.0;

    // create Mesh
    TriangleMesh singleFaceMesh(vertices, faces);
    // set orientation
    singleFaceMesh.setOrientation(orientation);

    // expected result
    bunny_dataIO::Point3DType expected;
    expected << -1, 0, 0;

    ASSERT_TRUE(expected.isApprox(singleFaceMesh.RotationAxis()));
}

TEST(MESH, RotationAxis_orientationX)
{
    // Simple object:
    bunny_dataIO::Point3DMatrixType vertices(3,3);
    vertices << 0.0, 0.0, 0.0, // (x=0,y=0,z=0)
                1.0, 0.0, 0.0, // (x=1,y=0,z=0)
                0.0, 1.0, 0.0; // (x=0,y=1,z=0)

    // denines a single face
    bunny_dataIO::IndexMatrixType faces(1, 3);
    faces << 0, 1, 2;

    // Add a orientation:
    bunny_dataIO::Point3DType orientation;
    orientation << 1.0, 0.0, 0.0;

    // create Mesh
    TriangleMesh singleFaceMesh(vertices, faces);
    // set orientation
    singleFaceMesh.setOrientation(orientation);

    // expected result
    bunny_dataIO::Point3DType expected;
    expected << 0, 1, 0;

    ASSERT_TRUE(expected.isApprox(singleFaceMesh.RotationAxis()));
}

TEST(MESH, RotationAxisNormalized)
{
    // Simple object:
    bunny_dataIO::Point3DMatrixType vertices(3,3);
    vertices << 0.0, 0.0, 0.0, // (x=0,y=0,z=0)
                1.0, 0.0, 0.0, // (x=1,y=0,z=0)
                0.0, 1.0, 0.0; // (x=0,y=1,z=0)

    // denines a single face
    bunny_dataIO::IndexMatrixType faces(1, 3);
    faces << 0, 1, 2;

    // Add a orientation:
    bunny_dataIO::Point3DType orientation;
    orientation << 0.0, 10.0, 0.0;

    // create Mesh
    TriangleMesh singleFaceMesh(vertices, faces);
    // set orientation
    singleFaceMesh.setOrientation(orientation);

    // expected result
    bunny_dataIO::Point3DType expected;
    expected << -1, 0, 0;

    ASSERT_TRUE(expected.isApprox(singleFaceMesh.RotationAxis()));
}

TEST(MESH, matchObjectOrientationX)
{
    // Simple object:
    bunny_dataIO::Point3DMatrixType vertices(3,3);
    vertices << 0.0, 0.0, 0.0, // (x=0,y=0,z=0)
                1.0, 0.0, 0.0, // (x=1,y=0,z=0)
                0.0, 1.0, 0.0; // (x=0,y=1,z=0)

    // denines a single face
    bunny_dataIO::IndexMatrixType faces(1, 3);
    faces << 0, 1, 2;

    // Add a orientation:
    bunny_dataIO::Point3DType orientation;
    orientation << 1.0, 0.0, 0.0;

    // create Mesh
    TriangleMesh singleFaceMesh(vertices, faces);
    // set orientation
    singleFaceMesh.setOrientation(orientation);

    // array to transform
    bunny_dataIO::Point3DType verticeX, verticeY, verticeZ;
    verticeX << 1, 0, 0;
    verticeY << 0, 1, 0;
    verticeZ << 0, 0, 1;

    // expected result
    bunny_dataIO::Point3DType expectedX, expectedY, expectedZ;
    expectedX << 0, 0, -1;
    expectedY << 0, 1, 0;
    expectedZ << 1, 0, 0;

    ASSERT_TRUE(expectedX.isApprox(singleFaceMesh.matchObjectOrientation(verticeX)));
    ASSERT_TRUE(expectedY.isApprox(singleFaceMesh.matchObjectOrientation(verticeY)));
    ASSERT_TRUE(expectedZ.isApprox(singleFaceMesh.matchObjectOrientation(verticeZ)));
}

TEST(MESH, matchObjectOrientationY)
{
    // Simple object:
    bunny_dataIO::Point3DMatrixType vertices(3,3);
    vertices << 0.0, 0.0, 0.0, // (x=0,y=0,z=0)
                1.0, 0.0, 0.0, // (x=1,y=0,z=0)
                0.0, 1.0, 0.0; // (x=0,y=1,z=0)

    // denines a single face
    bunny_dataIO::IndexMatrixType faces(1, 3);
    faces << 0, 1, 2;

    // Add a orientation:
    bunny_dataIO::Point3DType orientation;
    orientation << 0.0, 1.0, 0.0;

    // create Mesh
    TriangleMesh singleFaceMesh(vertices, faces);
    // set orientation
    singleFaceMesh.setOrientation(orientation);

    // array to transform
    bunny_dataIO::Point3DType verticeX, verticeY, verticeZ;
    verticeX << 1, 0, 0;
    verticeY << 0, 1, 0;
    verticeZ << 0, 0, 1;

    // expected result
    bunny_dataIO::Point3DType expectedX, expectedY, expectedZ;
    expectedX << 1, 0, 0;
    expectedY << 0, 0, -1;
    expectedZ << 0, 1, 0;

    ASSERT_TRUE(expectedX.isApprox(singleFaceMesh.matchObjectOrientation(verticeX)));
    ASSERT_TRUE(expectedY.isApprox(singleFaceMesh.matchObjectOrientation(verticeY)));
    ASSERT_TRUE(expectedZ.isApprox(singleFaceMesh.matchObjectOrientation(verticeZ)));
}

TEST(Mesh, verticesIntoWorld)
{
    // defines simple vertices matrix
    bunny_dataIO::Point3DMatrixType vertices(3,3);
    vertices << 0.0, 0.0, 0.0, // (x=0,y=0,z=0)
                1.0, 0.0, 0.0, // (x=1,y=0,z=0)
                0.0, 1.0, 0.0; // (x=0,y=1,z=0)

    // denines a single face
    bunny_dataIO::IndexMatrixType faces(1, 3);
    faces << 0, 1, 2;

    // Create a triangle mesh
    TriangleMesh singleFaceMesh(vertices, faces);

    // define a non-standard orientation to the object
    bunny_dataIO::Point3DType orientation;
    orientation << 1.0, 0.0, 0.0;
    singleFaceMesh.setOrientation(orientation);

    // define expected output:
    bunny_dataIO::Point3DMatrixType expectedVertices(3,3);
    expectedVertices << 0.0, 0.0, 0.0,
                        0.0, 0.0, -1.0,
                        0.0, 1.0, 0.0;

    bunny_dataIO::printArray(singleFaceMesh.getVerticesIntoWorld());

    ASSERT_TRUE(expectedVertices.isApprox(singleFaceMesh.getVerticesIntoWorld()));
}

// TEST(Mesh, NonDefaultOrientationNormals)
// {
//     // defines simple vertices matrix
//     bunny_dataIO::Point3DMatrixType vertices(3,3);
//     vertices << 0.0, 0.0, 0.0, // (x=0,y=0,z=0)
//                 1.0, 0.0, 0.0, // (x=1,y=0,z=0)
//                 0.0, 1.0, 0.0; // (x=0,y=1,z=0)

//     // denines a single face
//     bunny_dataIO::IndexMatrixType faces(1, 3);
//     faces << 0, 1, 2;

//     // Create a triangle mesh
//     TriangleMesh singleFaceMesh(vertices, faces);

//     // define a non-standard orientation to the object
//     bunny_dataIO::Point3DType orientation;
//     orientation << 0, 1, 0;
//     singleFaceMesh.setOrientation(orientation);
//     // compute normals
//     singleFaceMesh.ComputeNormals();

//     // define expected output:
//     bunny_dataIO::Point3DMatrixType expectedFaceNormals(1,3);
//     expectedFaceNormals << 0.0, 1.0, 0.0;

//     bunny_dataIO::Point3DMatrixType expectedVerticeNormals(3,3);
//     expectedVerticeNormals << 1.0, 0.0, 0.0,
//                               1.0, 0.0, 0.0,
//                               1.0, 0.0, 0.0;

//     bunny_dataIO::printArray(singleFaceMesh.getFaceNormals());

//     bunny_dataIO::printArray(singleFaceMesh.getVerticeNormals());

//     // test them...
//     // size assertions:
//     ASSERT_EQ(faces.rows(), singleFaceMesh.getFaceNormals().rows());
//     ASSERT_EQ(vertices.rows(), singleFaceMesh.getVerticeNormals().rows());
//     // norm assertions:
//     ASSERT_TRUE(expectedFaceNormals.isApprox(singleFaceMesh.getFaceNormals()));
//     ASSERT_TRUE(expectedVerticeNormals.isApprox(singleFaceMesh.getVerticeNormals()));
// }