#pragma once
#include "fVector3.h"
#include <vector>
const float PI = 3.1415;
const float degToRad = PI / 180;
class fVector2
{
public:
	float x, y;
	inline float Distance(const fVector2& p2) { return (*this - p2).Lenght(); }
	fVector3 Cross(const fVector2& p2);
	float fCross(const fVector2& p2);
	inline float Dot(const fVector2& p2) { return (this->x * p2.x) + (this->y * p2.x); }
	fVector2 Sum(const fVector2& p2);
	fVector2 Mult(const float& p2);
	fVector2 Mult(const fVector2& p2);
	fVector2 Div(const fVector2& p2);
	fVector2 Div(const float& p2);
	inline float Lenght() { return sqrtf((x*x) + (y*y)); }
	inline float SqrLenght() { return (x*x) + (y*y); }
	inline fVector2 Unit() { return *this / this->Lenght(); }
	fVector2 Rotate(float ang);
	inline float angle() { return atan2f(y, x); }
	static std::vector<fVector2> Translate(std::vector<fVector2>& p, const fVector2& p2);
	static std::vector<fVector2> Rotate(std::vector<fVector2>& p, float ang);
	static std::vector<fVector2> Scale(std::vector<fVector2>& p, float scale);
	fVector2& operator+=(const fVector2& rhs);
	fVector2& operator-=(fVector2& rhs);
	float operator*=(const fVector2& rhs);
	fVector2& operator*=(const float& rhs);
	fVector2& operator/=(const float& rhs);

	fVector2();
	fVector2(float _x, float _y);
	~fVector2();
};

	fVector2 operator+(fVector2& lhs, const fVector2& rhs);
	fVector2 operator-(fVector2& lhs, const fVector2& rhs);
	float operator*(fVector2& lhs, fVector2& rhs);
	fVector2 operator*(fVector2& lhs, const float& rhs);
	fVector2 operator/(fVector2& lhs, const float& rhs);
