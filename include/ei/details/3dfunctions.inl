﻿// ************************************************************************* //
inline float volume(const Sphere& _sphere)
{
    return 4.0f / 3.0f * PI * _sphere.radius * _sphere.radius * _sphere.radius;
}

inline float volume(const Box& _box)
{
    Vec3 size = _box.max - _box.min;
    return size.x * size.y * size.z;
}

inline float volume(const Thetrahedron& _thetrahedron)
{
    return dot(_thetrahedron.v3-_thetrahedron.v0, cross(_thetrahedron.v2-_thetrahedron.v0, _thetrahedron.v1-_thetrahedron.v0)) / 6.0f;
}

inline float volume(const Triangle& _triangle)
{
    return 0.0f;
}

inline float volume(const Disc& _disc)
{
    return 0.0f;
}

inline float volume(const Plane& _plane)
{
    return 0.0f;
}

inline float volume(const DOP& _dop)
{
    return 0.0f;
}

inline float volume(const Ellipsoid& _ellipsoid)
{
    return 4.0f / 3.0f * PI * _ellipsoid.radii.x * _ellipsoid.radii.y * _ellipsoid.radii.z;
}

inline float volume(const Ray& _ray)
{
    return 0.0f;
}

inline float volume(const Segment& _line)
{
    return 0.0f;
}

inline float volume(const Capsule& _capsule)
{
    return PI * sq(_capsule.radius) * (_capsule.radius*4.0f/3.0f + len(_capsule.seg.b-_capsule.seg.a));
}

// ************************************************************************* //
inline float surface(const Sphere& _sphere)
{
    return 4.0f * PI * sq(_sphere.radius);
}

inline float surface(const Box& _box)
{
    Vec3 size = _box.max - _box.min;
    return 2.0f * (size.x * size.y + size.x * size.z + size.y * size.z);
}

inline float surface(const Thetrahedron& _thetra)
{
    // Analogous to a triangle (repeated four times)
    Vec3 a = _thetra.v1 - _thetra.v0;
    Vec3 b = _thetra.v2 - _thetra.v0;
    Vec3 c = _thetra.v3 - _thetra.v0;
    Vec3 d = _thetra.v2 - _thetra.v1;
    Vec3 e = _thetra.v3 - _thetra.v1;
    return 0.5f * (len( cross(a, b) )
                 + len( cross(a, c) )
                 + len( cross(b, c) )
                 + len( cross(d, e) ));
}

inline float surface(const Triangle& _triangle)
{
    // Heron's formula is much more expensive than cross product because
    // the 3 side lengths must be computed first.
    return len( cross(_triangle.v1 - _triangle.v0, _triangle.v2 - _triangle.v0) ) * 0.5f;
}

inline float surface(const Disc& _disc)
{
    return PI * _disc.radius;
}

inline float surface(const Plane& _plane)
{
    return INF;
}

inline float surface(const DOP& _dop)
{
    return INF;
}

inline float surface(const Ellipsoid& _ellipsoid)
{
    // Use approximation (Knud Thomsen's formula) only! Everything else is a
    // lot larger.
    Vec3 pr( pow(_ellipsoid.radii.x, 1.6075f),
             pow(_ellipsoid.radii.y, 1.6075f),
             pow(_ellipsoid.radii.z, 1.6075f) );
    return 4.0f * PI * pow((pr.x * pr.y + pr.x * pr.z + pr.y * pr.z) / 3.0f, 0.622083981f);
}

inline float surface(const Ray& _ray)
{
    return 0.0f;
}

inline float surface(const Segment& _line)
{
    return 0.0f;
}

inline float surface(const Capsule& _capsule)
{
    return 2 * PI * _capsule.radius * (2 * _capsule.radius + len(_capsule.seg.b-_capsule.seg.a));
}

// ************************************************************************* //
inline float distance(const Vec3& _point0, const Vec3& _point1)
{
    return len(_point1 - _point0);
}

// ************************************************************************* //
inline float distance(const Vec3& _point, const Sphere& _sphere)
{
    return distance(_sphere.center, _point) - _sphere.radius;
}

// ************************************************************************* //
inline float distance(const Vec3& _point, const Capsule& _capsule)
{
    return distance(_point, _capsule.seg) - _capsule.radius;
}

// ************************************************************************* //
inline float distance(const Sphere& _sphere, const Segment& _segment)
{
    return max(0.0f, distance(_sphere.center, _segment) - _sphere.radius);
}

// ************************************************************************* //
inline float distance(const Sphere& _sphere, const Capsule& _capsule)
{
    return max(0.0f, distance(_sphere.center, _capsule.seg) - _capsule.radius - _sphere.radius);
}

// ************************************************************************* //
inline float distance(const Capsule& _capsule0, const Capsule& _capsule1)
{
    return max(0.0f, distance(_capsule0.seg, _capsule1.seg) - _capsule0.radius - _capsule1.radius);
}