// p3pcr - position 3d-point with "clock reading"
// specification-file

#pragma once
#include"p3p_specification.hpp"

#define p3pcr_init 0

template <typename T>
class p3pcr
{
// [coord-3d] & [current time]
private:
	p3p<T> coord_3d;
	T clock_reading;

// geters
public:
	const p3p<T>& get_coord_3d() const { return coord_3d; }
	T get_clock_reading() const { return clock_reading; }

// seters
public:
	void set(T init_x, T init_y, T init_z, T init_clock_reading)
	{
		coord_3d.set(init_x, init_y, init_z);
		clock_reading = init_clock_reading;
	}

	void set(const p3p<T>& init_coord_3d, T init_clock_reading)
	{
		coord_3d = init_coord_3d;
		clock_reading = init_clock_reading;
	}

// constructors
public:
	p3pcr() :
		clock_reading(p3pcr_init)
	{}

	p3pcr(T init_x, T init_y, T init_z, T init_clock_reading)
	{
		coord_3d.set(init_x, init_y, init_z);
		clock_reading = init_clock_reading;
	}

	p3pcr(const p3p<T>& init_coord_3d, T init_clock_reading)
	{
		coord_3d = init_coord_3d;
		clock_reading = init_clock_reading;
	}
};

// out-stream-friend 
template <typename T>
std::ostream& operator << (std::ostream& os, const p3pcr<T>& obj)
{
	return os
		<< "{"
		<< obj.get_coord_3d().get_x() << ","
		<< obj.get_coord_3d().get_y() << ","
		<< obj.get_coord_3d().get_z() << ","
		<< obj.get_clock_reading()
		<< "}";
}