#include "fVector2.h"



fVector2::fVector2()
{
	x = 0;
	y = 0;
}

fVector2::fVector2(float _x, float _y)
{
	x = _x;
	y = _y;
}


fVector2::~fVector2()
{
}

fVector3 fVector2::Cross(const fVector2 & p2)
{
	return fVector3(0,0,(x*p2.y)-(y*p2.x));
}

float fVector2::fCross(const fVector2 & p2)
{
	return (x*p2.y) - (y*p2.x);
}

fVector2 fVector2::Sum(const fVector2 & p2)
{
	this->x += p2.x;
	this->y += p2.y;
	return *this;
}

fVector2 fVector2::Mult(const float & p2)
{
	this->x *= p2;
	this->y *= p2;
	return *this;
}

fVector2 fVector2::Mult(const fVector2 & p2)
{
	this->x *= p2.x;
	this->y *= p2.y;
	return *this;
}

fVector2 fVector2::Div(const fVector2 & p2)
{
	this->x /= p2.x;
	this->y /= p2.y;
	return *this;
}

fVector2 fVector2::Div(const float & p2)
{
	this->x /= p2;
	this->y /= p2;
	return *this;
}

fVector2 fVector2::Rotate(float ang)
{
	this->x = (x*cosf(degToRad*ang)) - (y*sinf(degToRad*ang));
	this->y = (x*sinf(degToRad*ang)) + (y*cosf(degToRad*ang));
	return *this;
}

std::vector<fVector2> fVector2::Translate(std::vector<fVector2>& p, const fVector2 & p2)
{
	for (auto i : p)
	{
		i.Sum(p2);
	}
	return p;
}

std::vector<fVector2> fVector2::Rotate(std::vector<fVector2>& p, float ang)
{
	for (auto i : p)
	{
		i.Rotate(ang);
	}
	return p;
}

std::vector<fVector2> fVector2::Scale(std::vector<fVector2>& p, float scale)
{
	for (auto i : p)
	{
		i.Mult(scale);
	}
	return p;
}

fVector2 & fVector2::operator+=(const fVector2 & rhs)
{
	return Sum(rhs);
}

fVector2 & fVector2::operator-=(fVector2 & rhs)
{
	return Sum(rhs * -1);
}

float fVector2::operator*=(const fVector2 & rhs)
{
	return Dot(rhs);
}

fVector2& fVector2::operator*=(const float & rhs)
{
	return Mult(rhs);
}

fVector2& fVector2::operator/=(const float & rhs)
{
	return Div(rhs);
}

fVector2 operator+(fVector2 & lhs, const fVector2 & rhs)
{
	return lhs.Sum(rhs);
}

fVector2 operator-(fVector2 & lhs, fVector2 & rhs)
{
	return lhs.Sum(rhs * -1);
}

float operator*(fVector2 & lhs, const fVector2 & rhs)
{
	return lhs.Dot(rhs);
}

fVector2 operator*(fVector2 & lhs, const float & rhs)
{
	return lhs.Mult(rhs);
}

fVector2 operator/(fVector2 & lhs, const float & rhs)
{
	return lhs.Div(rhs);
}
