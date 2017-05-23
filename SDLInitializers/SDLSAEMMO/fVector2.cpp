#include "fVector2.h"

fVector2 fVector2::zero(0,0);

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

fVector2::fVector2(const fVector2 & cpy)
{
	x = cpy.x;
	y = cpy.y;
}


fVector2::~fVector2()
{
}

float fVector2::Distance(fVector2 & p2)
{
	fVector2 lhs(*this);
	return lhs.Sum(p2 * -1).Lenght();
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

fVector2 fVector2::Unit()
{
	return *this / (this->Lenght());
}

fVector2 fVector2::Rotate(float ang, fVector2 center)
{
	this->Sum(center * -1);
	this->x = (x*cosf(degToRad*ang)) - (y*sinf(degToRad*ang));
	this->y = (x*sinf(degToRad*ang)) + (y*cosf(degToRad*ang));
	this->Sum(center);
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

std::vector<fVector2> fVector2::Rotate(std::vector<fVector2>& p, fVector2 center, float ang)
{
	for (auto i : p)
	{
		i.Rotate(ang, center);
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

fVector2 fVector2::operator+=(const fVector2 & rhs)
{
	return this->Sum(rhs);
}

fVector2 fVector2::operator-=(fVector2 & rhs)
{
	return this->Sum(rhs * -1);
}

float fVector2::operator*=(const fVector2 & rhs)
{
	return this->Dot(rhs);
}

fVector2 fVector2::operator*=(const float & rhs)
{
	return this->Mult(rhs);
}

fVector2 fVector2::operator/=(const float & rhs)
{
	return this->Div(rhs);
}

fVector2 & fVector2::operator=(const fVector2 & rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	return *this;
}

bool fVector2::operator==(const fVector2 & rhs)
{
	return (x == rhs.x && y == rhs.y);
}

bool fVector2::operator!=(const fVector2 & rhs)
{
	return (x != rhs.x || y != rhs.y);
}

fVector2 operator+(fVector2 lhs, const fVector2 & rhs)
{
	return lhs.Sum(rhs);
}

fVector2 operator-(fVector2 lhs, fVector2 & rhs)
{
	return lhs.Sum(rhs * -1);
}

float operator*(fVector2 lhs, const fVector2 & rhs)
{
	return lhs.Dot(rhs);
}

fVector2 operator*(fVector2 lhs, const float & rhs)
{
	return lhs.Mult(rhs);
}

fVector2 operator/(fVector2 lhs, const float & rhs)
{
	return lhs.Div(rhs);
}
