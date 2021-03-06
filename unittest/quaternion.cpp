﻿#include "ei/vector.hpp"
#include "unittest.hpp"

#include <iostream>

using namespace ei;

bool test_quaternion()
{
    bool result = true;

    Quaternion q0( normalize(Vec3(1.0f, 2.0f, -1.0f)), PI );
    Quaternion q1( 0.3f, 0.5f, -0.7f );
    Quaternion q3( normalize(Vec3(-1.0f, -2.0f, 1.0f)), PI );
    Mat3x3 m0 = rotation( normalize(Vec3(1.0f, 2.0f, -1.0f)), PI );
    Mat3x3 m1 = rotation( 0.3f, 0.5f, -0.7f );

    TEST( approx(Mat3x3(q0), m0), "Matrix(q0) does not equals m0 as expected!" );
    TEST( approx(q0, Quaternion(m0)), "q0 does not equals Quaternion(m0) as expected!" );
    TEST( approx(Mat3x3(q1), m1), "Matrix(q1) does not equals m1 as expected!" );
    TEST( approx(q1, Quaternion(m1)), "q1 does not equals Quaternion(m1) as expected!" );
    TEST( approx(axis(q0), normalize(Vec3(1.0f, 2.0f, -1.0f))), "Axis of quaternion q0 wrongly extracted!" );
    TEST( approx(axis(q3), normalize(Vec3(-1.0f, -2.0f, 1.0f))), "Axis of quaternion q3 wrongly extracted!" );
    TEST( approx(angle(q0), PI), "Angle of quaternion q0 wrongly extracted!" );
    TEST( approx(angle(q3), PI), "Angle of quaternion q3 wrongly extracted!" );
    TEST( approx(angles(q1), Vec3(0.3f, 0.5f, -0.7f)), "Euler angles conversion of quaternion wrong!" );
    TEST( approx(xaxis(q1), Vec3(m1(0,0), m1(0,1), m1(0,2))), "X-axis of quaternion q1 wrong!" );
    TEST( approx(yaxis(q1), Vec3(m1(1,0), m1(1,1), m1(1,2))), "Y-axis of quaternion q1 wrong!" );
    TEST( approx(zaxis(q1), Vec3(m1(2,0), m1(2,1), m1(2,2))), "Z-axis of quaternion q1 wrong!" );

    TEST( approx(dot(q0, q0), 1.0f), "Quaternion dot product invalid" );
    TEST( approx(len(q0), 1.0f), "Quaternion len invalid" );
    q0 *= 2.0f;
    TEST( approx(len(q0), 2.0f), "Quaternion len after multiplication invalid" );
    q0 = normalize(q0);
    TEST( approx(len(q0), 1.0f), "Quaternion len after normalization invalid" );
    Quaternion q2 = conjugate(q0);
    TEST( q0.r == q2.r && q0.i == -q2.i && q0.j == -q2.j && q0.k == -q2.k, "Conjugated quaternion wrong!" );
    q2 = ~q0;
    TEST( q0.r == q2.r && q0.i == -q2.i && q0.j == -q2.j && q0.k == -q2.k, "Conjugated quaternion wrong!" );
    q2 = -q0;
    TEST( q0.r == -q2.r && q0.i == -q2.i && q0.j == -q2.j && q0.k == -q2.k, "Unary quaternion minus wrong!" );
    TEST( q0*qidentity() == q0, "Quaternion identity (rhs) wrong!" );
    TEST( qidentity()*q0 == q0, "Quaternion identity (lhs) wrong!" );

    Quaternion q4( 0.1f, 0.5f, -0.7f );
    Quaternion q5( 0.25f, 0.5f, -0.7f );
    // Unfortunatelly the slerp is very unprecise -> large epsilon
    TEST( approx(slerp(q1, q4, 0.25f), q5), "Slerp for quaternions failed!" );
    TEST( slerp(q1, q1, 0.33f) == q1, "Slerp (equal vectors) for quaternions failed!" );

    Vec3 v0(1.0f, 0.0f, 0.0f);
    Vec3 v1(0.0f, 1.0f, 0.0f);
    Vec3 v2 = normalize(Vec3(1.0f, 2.0f, -1.0f));
    Quaternion q6(v0, v1);
    Quaternion q7(v2, v1);
    Mat3x3 m2(q6);
    TEST( approx(m2 * v0, v1), "Quaternion From-To parametrization or matrix transformation invalid!" );
    TEST( approx(transform(v0, q6), v1), "Direct quaternion transformation v0->v1 failed!" );
    TEST( approx(transform(v2, q7), v1), "Direct quaternion transformation v2->v1 failed!" );

    // Test to encode LHS coordinate systems (include mirror stuff)
    Vec3 v3(0.0f, 0.0f, -1.0f);
    Quaternion q8(v0, v1, v3);
    Quaternion q9(v0, v1, Vec3(0.0f, 0.0f, 1.0f));
    TEST(approx(xaxis(q8), v0), "LHS-Quaternion handness of x-axis wrong!");
    TEST(approx(yaxis(q8), v1), "LHS-Quaternion handness of y-axis wrong!");
    TEST(approx(zaxis(q8), v3), "LHS-Quaternion handness of z-axis wrong!");
    q8 *= q9;
    TEST(approx(zaxis(q8), v3), "Quaternion multiplication destroys handness!");
    TEST(approx(transform(v2, q8), abs(v2)), "Transformation did not mirror correct!");

    return result;
}
