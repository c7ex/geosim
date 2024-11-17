#include"p3pcr_specification.hpp"
#include"lina_specification.hpp"
#include"constellation.hpp"

// receiver positioning
constexpr auto x_ref = 0.;
constexpr auto y_ref = 0.;
constexpr auto z_ref = 0.;

// for constellation
constexpr auto n_sat = 4;
constexpr auto distn = 3000.;
constexpr auto varnc = 100.;

void geometric_task()
{
	// create reference point
	pos reference{ x_ref, y_ref, z_ref };

	// create constellation -> geometric positioning
	vec ranges;
	conset settings = { n_sat, distn, varnc };
	posvec geo_points = create_constellation(reference, ranges, settings);
}

int main()
{
	SetLinaMode(true);

	lina::_obj<double> obj0;

	std::vector<double> r1 = { 1,2,1,1 };
	lina::_obj<double> obj1(r1);
	
	//obj1.tr();
	obj1.set_elem(13, 3, 0);

	std::cout << obj1 << "\n";

	std::vector<std::vector<double>> r2 = 
	{ 
		{ 1,6,1,1,1 }, 
		{ 1,1,6,1,1 },
		{ 1,1,1,6,1 }
	};
	
	lina::_obj<double> obj2(r2);
	//obj2.tr();
	std::cout << obj2 << "\n";

	std::vector<std::vector<double>> r3 =
	{
		{ 1,1,1,7,1 },
		{ 1,7,1,7,1 },
		{ 1,1,7,1,1 }
	};

	lina::_obj<double> obj3(r3);
	obj3.tr();
	std::cout << obj3 << "\n";

	lina::_obj<double> obj4 = obj2 * obj3;

	std::cout << obj4 << "\n";
	std::cout << !obj4 << "\n";

	lina::_obj<double> obj5 = !obj4;

	std::cout << !obj5 << "\n";

	//geometric_task();
}