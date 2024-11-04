// p3p - position 3d-point
// appendices-file

#pragma once
#include<iostream>

// out-stream-friend 
template <typename T>
std::ostream& operator << (std::ostream& os, const p3p<T>& obj)
{
	return os
		<< "{" 
		<< obj.get_x() << "," 
		<< obj.get_y() << "," 
		<< obj.get_z() 
		<< "}";
}

template <typename T>
std::ostream& operator << (std::ostream& os, const p3p<T>* obj)
{
	return os
		<< "{"
		<< (*obj).get_x() << ","
		<< (*obj).get_y() << ","
		<< (*obj).get_z()
		<< "}";
}

namespace p3p_app
{
	// p3p-relative-projection
	template <typename T>
	p3p<T> projection_rel(const p3p<T>& point1, const p3p<T>& point2)
	{
		p3p<T> projection
		{
			point1.get_x() - point2.get_x(),
			point1.get_y() - point2.get_y(),
			point1.get_z() - point2.get_z()
		};

		return projection;
	}

	// p3p-absolute-projection
	template <typename T>
	p3p<T> projection_abs(const p3p<T>& point1, const p3p<T>& point2)
	{
		p3p<T> projection
		{
			abs(point1.get_x() - point2.get_x()),
			abs(point1.get_y() - point2.get_y()),
			abs(point1.get_z() - point2.get_z())
		};

		return projection;
	}

	template <typename T>
	T distance(const p3p<T>& point1, const p3p<T>& point2)
	{
		T dx = abs(point1.get_x() - point2.get_x());
		T dy = abs(point1.get_y() - point2.get_y());
		T dz = abs(point1.get_z() - point2.get_z());

		T distance = sqrt(dx * dx + dy * dy + dz * dz);

		return distance;
	}
}