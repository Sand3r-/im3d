#pragma once
#ifndef im3d_math_h
#define im3d_math_h

#include "im3d.h"

#include <cmath>

namespace Im3d {

template <typename T>
inline T Max(T _a, T _b)                                   { return _a < _b ? _b : _a; }
template <typename T>
inline T Min(T _a, T _b)                                   { return _a < _b ? _a : _b; }
template <typename T>
inline T Clamp(T _a, T _min, T _max)                       { return Max(Min(_a, _max), _min); }
template <typename T> 
inline T SignOf(T _a)                                      { return (T)((T(0) < _a) - (_a < T(0))); }
// Remap _x in [_start,_end] to [0,1].
inline float Remap(float _x, float _start, float _end)     { return Clamp(_x * (1.0f / (_end - _start)) + (-_start / (_end - _start)), 0.0f, 1.0f); }

template <typename T>
int Count();
	template <> inline int Count<Vec2>() { return 2; }
	template <> inline int Count<Vec3>() { return 3; }
	template <> inline int Count<Vec4>() { return 4; }
	template <> inline int Count<Mat4>() { return 16; }

template <typename T>
inline bool AllLess(const T& _a, const T& _b)
{
	for (int i = 0, n = Count<T>(); i < n; ++i) {
		if (_a[i] > _b[i]) {
			return false;
		}
	}
	return true;
}

// Vec2
inline Vec2  operator+(const Vec2& _lhs, const Vec2& _rhs) { return Vec2(_lhs.x + _rhs.x, _lhs.y + _rhs.y); }
inline Vec2  operator-(const Vec2& _lhs, const Vec2& _rhs) { return Vec2(_lhs.x - _rhs.x, _lhs.y - _rhs.y); }
inline Vec2  operator*(const Vec2& _lhs, const Vec2& _rhs) { return Vec2(_lhs.x * _rhs.x, _lhs.y * _rhs.y); }
inline Vec2  operator/(const Vec2& _lhs, const Vec2& _rhs) { return Vec2(_lhs.x / _rhs.x, _lhs.y / _rhs.y); }
inline Vec2  operator*(const Vec2& _lhs, float _rhs)       { return Vec2(_lhs.x * _rhs, _lhs.y * _rhs);     }
inline Vec2  operator/(const Vec2& _lhs, float _rhs)       { return Vec2(_lhs.x / _rhs, _lhs.y / _rhs);     }
inline Vec2  operator-(const Vec2& _v)                     { return Vec2(-_v.x, -_v.y);                     }
inline float Dot(const Vec2& _lhs, const Vec2& _rhs)       { return _lhs.x * _rhs.x + _lhs.y * _rhs.y;      }
inline float Length(const Vec2& _v)                        { return sqrtf(Dot(_v, _v));                     }
inline float Length2(const Vec2& _v)                       { return Dot(_v, _v);                            }
inline Vec2  Abs(const Vec2& _v)                           { return Vec2(fabs(_v.x), fabs(_v.y));           }
inline Vec2  Normalize(const Vec2& _v)                     { return _v / Length(_v);                        }

// Vec3
inline Vec3  operator+(const Vec3& _lhs, const Vec3& _rhs) { return Vec3(_lhs.x + _rhs.x, _lhs.y + _rhs.y, _lhs.z + _rhs.z); }
inline Vec3  operator-(const Vec3& _lhs, const Vec3& _rhs) { return Vec3(_lhs.x - _rhs.x, _lhs.y - _rhs.y, _lhs.z - _rhs.z); }
inline Vec3  operator*(const Vec3& _lhs, const Vec3& _rhs) { return Vec3(_lhs.x * _rhs.x, _lhs.y * _rhs.y, _lhs.z * _rhs.z); }
inline Vec3  operator/(const Vec3& _lhs, const Vec3& _rhs) { return Vec3(_lhs.x / _rhs.x, _lhs.y / _rhs.y, _lhs.z / _rhs.z); }
inline Vec3  operator*(const Vec3& _lhs, float _rhs)       { return Vec3(_lhs.x * _rhs, _lhs.y * _rhs, _lhs.z * _rhs);       }
inline Vec3  operator/(const Vec3& _lhs, float _rhs)       { return Vec3(_lhs.x / _rhs, _lhs.y / _rhs, _lhs.z / _rhs);       }
inline Vec3  operator-(const Vec3& _v)                     { return Vec3(-_v.x, -_v.y, -_v.z);                               } 
inline float Dot(const Vec3& _lhs, const Vec3& _rhs)       { return _lhs.x * _rhs.x + _lhs.y * _rhs.y + _lhs.z * _rhs.z;     }
inline float Length(const Vec3& _v)                        { return sqrtf(Dot(_v, _v));                                      }
inline float Length2(const Vec3& _v)                       { return Dot(_v, _v);                                             }
inline Vec3  Abs(const Vec3& _v)                           { return Vec3(fabs(_v.x), fabs(_v.y), fabs(_v.z));                }
inline Vec3  Normalize(const Vec3& _v)                     { return _v / Length(_v);                        }
inline Vec3  Cross(const Vec3& _a, const Vec3& _b)         
{
	return Vec3(
		_a.y * _b.z - _b.y * _a.z,
		_a.z * _b.x - _b.z * _a.x,
		_a.x * _b.y - _b.x * _a.y
		);
}

// Vec4
inline Vec4  operator+(const Vec4& _lhs, const Vec4& _rhs) { return Vec4(_lhs.x + _rhs.x, _lhs.y + _rhs.y, _lhs.z + _rhs.z, _lhs.w + _rhs.w); }
inline Vec4  operator-(const Vec4& _lhs, const Vec4& _rhs) { return Vec4(_lhs.x - _rhs.x, _lhs.y - _rhs.y, _lhs.z - _rhs.z, _lhs.w - _rhs.w); }
inline Vec4  operator*(const Vec4& _lhs, const Vec4& _rhs) { return Vec4(_lhs.x * _rhs.x, _lhs.y * _rhs.y, _lhs.z * _rhs.z, _lhs.w * _rhs.w); }
inline Vec4  operator/(const Vec4& _lhs, const Vec4& _rhs) { return Vec4(_lhs.x / _rhs.x, _lhs.y / _rhs.y, _lhs.z / _rhs.z, _lhs.w / _rhs.w); }
inline Vec4  operator*(const Vec4& _lhs, float _rhs)       { return Vec4(_lhs.x * _rhs, _lhs.y * _rhs, _lhs.z * _rhs, _lhs.w * _rhs);         }
inline Vec4  operator/(const Vec4& _lhs, float _rhs)       { return Vec4(_lhs.x / _rhs, _lhs.y / _rhs, _lhs.z / _rhs, _lhs.w / _rhs);         }
inline Vec4  operator-(const Vec4& _v)                     { return Vec4(-_v.x, -_v.y, -_v.z, -_v.w);                                         }
inline float Dot(const Vec4& _lhs, const Vec4& _rhs)       { return _lhs.x * _rhs.x + _lhs.y * _rhs.y + _lhs.z * _rhs.z + _lhs.w * _rhs.w;    }
inline float Length(const Vec4& _v)                        { return sqrtf(Dot(_v, _v));                                                       }
inline float Length2(const Vec4& _v)                       { return Dot(_v, _v);                                                              }
inline Vec4  Abs(const Vec4& _v)                           { return Vec4(fabs(_v.x), fabs(_v.y), fabs(_v.z), fabs(_v.w));                     }
inline Vec4  Normalize(const Vec4& _v)                     { return _v / Length(_v);                        }

// Mat3
inline Mat3 operator*(const Mat3& _lhs, const Mat3& _rhs)
{
	Mat3 ret;
	ret(0, 0) = _lhs(0, 0) * _rhs(0, 0) + _lhs(0, 1) * _rhs(1, 0) + _lhs(0, 2) * _rhs(2, 0);
	ret(0, 1) = _lhs(0, 0) * _rhs(0, 1) + _lhs(0, 1) * _rhs(1, 1) + _lhs(0, 2) * _rhs(2, 1);
	ret(0, 2) = _lhs(0, 0) * _rhs(0, 2) + _lhs(0, 1) * _rhs(1, 2) + _lhs(0, 2) * _rhs(2, 2);
	ret(1, 0) = _lhs(1, 0) * _rhs(0, 0) + _lhs(1, 1) * _rhs(1, 0) + _lhs(1, 2) * _rhs(2, 0);
	ret(1, 1) = _lhs(1, 0) * _rhs(0, 1) + _lhs(1, 1) * _rhs(1, 1) + _lhs(1, 2) * _rhs(2, 1);
	ret(1, 2) = _lhs(1, 0) * _rhs(0, 2) + _lhs(1, 1) * _rhs(1, 2) + _lhs(1, 2) * _rhs(2, 2);
	ret(2, 0) = _lhs(2, 0) * _rhs(0, 0) + _lhs(2, 1) * _rhs(1, 0) + _lhs(2, 2) * _rhs(2, 0);
	ret(2, 1) = _lhs(2, 0) * _rhs(0, 1) + _lhs(2, 1) * _rhs(1, 1) + _lhs(2, 2) * _rhs(2, 1);
	ret(2, 2) = _lhs(2, 0) * _rhs(0, 2) + _lhs(2, 1) * _rhs(1, 2) + _lhs(2, 2) * _rhs(2, 2);	
	return ret;
}
inline Vec3 operator*(const Mat3& _m, const Vec3& _v)
{
	return Vec3(
		_m(0, 0) * _v.x + _m(0, 1) * _v.y + _m(0, 2) * _v.z,
		_m(1, 0) * _v.x + _m(1, 1) * _v.y + _m(1, 2) * _v.z,
		_m(2, 0) * _v.x + _m(2, 1) * _v.y + _m(2, 2) * _v.z
		);
}
inline Vec4 operator*(const Mat3& _m, const Vec4& _v)
{
	return Vec4(
		_m(0, 0) * _v.x + _m(0, 1) * _v.y + _m(0, 2) * _v.z,
		_m(1, 0) * _v.x + _m(1, 1) * _v.y + _m(1, 2) * _v.z,
		_m(2, 0) * _v.x + _m(2, 1) * _v.y + _m(2, 2) * _v.z,
		_v.w
		);
}
Mat3 Rotation(const Vec3& _axis, float _rads); // _axis must be unit length
Mat3 Scale(const Vec3& _s);
Vec3 ToEulerXYZ(const Mat3& _m);
Mat3 FromEulerXYZ(Vec3& _xyz);

// Mat4
inline Mat4 operator*(const Mat4& _lhs, const Mat4& _rhs)
{
	Mat4 ret;
	ret(0, 0) = _lhs(0, 0) * _rhs(0, 0) + _lhs(0, 1) * _rhs(1, 0) + _lhs(0, 2) * _rhs(2, 0) + _lhs(0, 3) * _rhs(3, 0);
	ret(0, 1) = _lhs(0, 0) * _rhs(0, 1) + _lhs(0, 1) * _rhs(1, 1) + _lhs(0, 2) * _rhs(2, 1) + _lhs(0, 3) * _rhs(3, 1);
	ret(0, 2) = _lhs(0, 0) * _rhs(0, 2) + _lhs(0, 1) * _rhs(1, 2) + _lhs(0, 2) * _rhs(2, 2) + _lhs(0, 3) * _rhs(3, 2);
	ret(0, 3) = _lhs(0, 0) * _rhs(0, 3) + _lhs(0, 1) * _rhs(1, 3) + _lhs(0, 2) * _rhs(2, 3) + _lhs(0, 3) * _rhs(3, 3);
	ret(1, 0) = _lhs(1, 0) * _rhs(0, 0) + _lhs(1, 1) * _rhs(1, 0) + _lhs(1, 2) * _rhs(2, 0) + _lhs(1, 3) * _rhs(3, 0);
	ret(1, 1) = _lhs(1, 0) * _rhs(0, 1) + _lhs(1, 1) * _rhs(1, 1) + _lhs(1, 2) * _rhs(2, 1) + _lhs(1, 3) * _rhs(3, 1);
	ret(1, 2) = _lhs(1, 0) * _rhs(0, 2) + _lhs(1, 1) * _rhs(1, 2) + _lhs(1, 2) * _rhs(2, 2) + _lhs(1, 3) * _rhs(3, 2);
	ret(1, 3) = _lhs(1, 0) * _rhs(0, 3) + _lhs(1, 1) * _rhs(1, 3) + _lhs(1, 2) * _rhs(2, 3) + _lhs(1, 3) * _rhs(3, 3);
	ret(2, 0) = _lhs(2, 0) * _rhs(0, 0) + _lhs(2, 1) * _rhs(1, 0) + _lhs(2, 2) * _rhs(2, 0) + _lhs(2, 3) * _rhs(3, 0);
	ret(2, 1) = _lhs(2, 0) * _rhs(0, 1) + _lhs(2, 1) * _rhs(1, 1) + _lhs(2, 2) * _rhs(2, 1) + _lhs(2, 3) * _rhs(3, 1);
	ret(2, 2) = _lhs(2, 0) * _rhs(0, 2) + _lhs(2, 1) * _rhs(1, 2) + _lhs(2, 2) * _rhs(2, 2) + _lhs(2, 3) * _rhs(3, 2);
	ret(2, 3) = _lhs(2, 0) * _rhs(0, 3) + _lhs(2, 1) * _rhs(1, 3) + _lhs(2, 2) * _rhs(2, 3) + _lhs(2, 3) * _rhs(3, 3);
	ret(3, 0) = _lhs(3, 0) * _rhs(0, 0) + _lhs(3, 1) * _rhs(1, 0) + _lhs(3, 2) * _rhs(2, 0) + _lhs(3, 3) * _rhs(3, 0);
	ret(3, 1) = _lhs(3, 0) * _rhs(0, 1) + _lhs(3, 1) * _rhs(1, 1) + _lhs(3, 2) * _rhs(2, 1) + _lhs(3, 3) * _rhs(3, 1);
	ret(3, 2) = _lhs(3, 0) * _rhs(0, 2) + _lhs(3, 1) * _rhs(1, 2) + _lhs(3, 2) * _rhs(2, 2) + _lhs(3, 3) * _rhs(3, 2);
	ret(3, 3) = _lhs(3, 0) * _rhs(0, 3) + _lhs(3, 1) * _rhs(1, 3) + _lhs(3, 2) * _rhs(2, 3) + _lhs(3, 3) * _rhs(3, 3);
	return ret;
}
inline Vec3 operator*(const Mat4& _m, const Vec3& _pos)
{
	return Vec3(
		_m(0, 0) * _pos.x + _m(0, 1) * _pos.y + _m(0, 2) * _pos.z + _m(0, 3),
		_m(1, 0) * _pos.x + _m(1, 1) * _pos.y + _m(1, 2) * _pos.z + _m(1, 3),
		_m(2, 0) * _pos.x + _m(2, 1) * _pos.y + _m(2, 2) * _pos.z + _m(2, 3)
		);
}
inline Vec4 operator*(const Mat4& _m, const Vec4& _v)
{
	return Vec4(
		_m(0, 0) * _v.x + _m(0, 1) * _v.y + _m(0, 2) * _v.z + _m(0, 3) * _v.w,
		_m(1, 0) * _v.x + _m(1, 1) * _v.y + _m(1, 2) * _v.z + _m(1, 3) * _v.w,
		_m(2, 0) * _v.x + _m(2, 1) * _v.y + _m(2, 2) * _v.z + _m(2, 3) * _v.w,
		_m(3, 0) * _v.x + _m(3, 1) * _v.y + _m(3, 2) * _v.z + _m(3, 3) * _v.w
		);
}
Mat4 Inverse(const Mat4& _m);
Mat4 Transpose(const Mat4& _m);
Mat4 Translation(const Vec3& _t);
Mat4 AlignZ(const Vec3& _axis, const Vec3& _up = Vec3(0.0f, 1.0f, 0.0f)); // generate an orthonormal bases with +z as _axis, which must be unit length
Mat4 LookAt(const Vec3& _from, const Vec3& _to, const Vec3& _up = Vec3(0.0f, 1.0f, 0.0f)); // align _z with (_to - _from), set _from as translation


// Extends to infinity from m_origin in �m_direciton.
struct Line
{
	Vec3 m_origin;
	Vec3 m_direction; // unit length

	Line() {}
	Line(const Vec3& _origin, const Vec3& _direction);
};

// Extends to infinity from m_origin in +m_direction (i.e. a line bounded at the origin).
struct Ray
{
	Vec3 m_origin;
	Vec3 m_direction; // unit length

	Ray() {}
	Ray(const Vec3& _origin, const Vec3& _direction);
};

struct LineSegment
{
	Vec3 m_start;
	Vec3 m_end;

	LineSegment() {}
	LineSegment(const Vec3& _start, const Vec3& _end);	
};

struct Sphere
{
	Vec3  m_origin;
	float m_radius;

	Sphere() {}
	Sphere(const Vec3& _origin, float _radius);	
};

struct Plane
{
	Vec3  m_normal;
	float m_offset;

	Plane() {}
	Plane(const Vec3& _normal, float _offset);
	Plane(const Vec3& _normal, const Vec3& _origin);
};

struct Capsule
{
	Vec3  m_start;
	Vec3  m_end;
	float m_radius;
	
	Capsule() {}
	Capsule(const Vec3& _start, const Vec3& _end, float _radius);
};

// Ray-primitive intersections. Use Intersects() when you don't need t0_/t1_.
bool  Intersects(const Ray& _ray, const Plane& _plane);
bool  Intersect (const Ray& _ray, const Plane& _plane, float& t0_);
bool  Intersects(const Ray& _ray, const Sphere& _sphere);
bool  Intersect (const Ray& _ray, const Sphere& _sphere, float& t0_, float& t1_);
bool  Intersects(const Ray& _ray, const Capsule& _capsule);
bool  Intersect (const Ray& _ray, const Capsule& _capsule, float& t0_, float& t1_);

void  Nearest(const Line& _line0, const Line& _line1, float& t0_, float& t1_);
void  Nearest(const Ray& _ray, const Line& _line, float& tr_, float& tl_);
/// Find point tr_ along _ray nearest to _segment, return point on segment nearest to _ray.
Vec3  Nearest(const Ray& _ray, const LineSegment& _segment, float& tr_);
float Distance2(const Ray& _ray, const LineSegment& _segment);

extern const float Pi;
extern const float TwoPi;
extern const float HalfPi;

} // namespace Im3d

#endif // im3d_math_h
