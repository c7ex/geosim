#include"p3pcr_specification.hpp"
#include"constellation.hpp"

// receiver positioning
constexpr auto x_ref = 0.;
constexpr auto y_ref = 0.;
constexpr auto z_ref = 0.;

// for constellation
constexpr auto n_sat = 14;
constexpr auto distn = 3000.;
constexpr auto varnc = 100.;

int main()
{
	// create reference point
	pos reference{ x_ref, y_ref, z_ref };

	// create constellation -> geometric positioning
	vec ranges;
	conset settings = { n_sat, distn, varnc };
	posvec g_points = create_constellation(reference, ranges, settings);
}