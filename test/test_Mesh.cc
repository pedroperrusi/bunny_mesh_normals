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

TEST(MESH, RotationAxis)
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

TEST(MESH, matchObjectOrientation)
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
    bunny_dataIO::Point3DType vertice;
    vertice << 1, 0, 0;

    // expected result
    bunny_dataIO::Point3DType expected;
    expected << 0, 0, -1;

    ASSERT_TRUE(vertice.isApprox(singleFaceMesh.matchObjectOrientation(expected)));
}