// p3p - position 3d-point
// specification-file

#pragma once
#define p3p_init 0

template <typename T>
class p3p
{
// 3d-coordination
private:
	T x;
	T y;
	T z;

// geters
public:
	T get_x() const { return x; }
	T get_y() const { return y; }
	T get_z() const { return z; }

// seters
public:
	void set(T init_x, T init_y, T init_z)
	{
		x = init_x;
		y = init_y;
		z = init_z;
	}

	p3p<T>& operator = (const p3p<T>& other)
	{
		this->x = other.get_x();
		this->y = other.get_y();
		this->z = other.get_z();
		return *this;
	}

// constructors
public:
	p3p() : 
		x(p3p_init), y(p3p_init), z(p3p_init)
	{}

	p3p(T init_x, T init_y, T init_z) :
		x(init_x), y(init_y), z(init_z) 
	{}
};

#include"p3p_appendices.hpp"