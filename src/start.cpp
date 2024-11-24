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
	SetLinaMode(false);
	lina::test::init<double>();
	lina::test::init_tr<double>();
	lina::test::summ<double>();
	lina::test::mult<double>();
	lina::test::tr<double>();
	lina::test::p_inv<double>();
	//geometric_task();
}