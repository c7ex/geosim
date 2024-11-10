// init fixed points
// geometric_positioning a model constellation sat

#pragma once
#include<vector>
#include<random>

#define show_prepare_distance
#define show_prepare_point

#include"p3pcr_specification.hpp"
typedef p3p<double>          pos;
typedef std::vector<double>  vec;
typedef std::vector<pos>  posvec;

typedef struct constellation_settings
{
	int n_sat;
	double distance;
	double deviation;
} conset;

// create random "guide" vector (x, y, z)
pos create_magic_coeff(pos& point, double range)
{
	auto magic = rand();                                        // random number

	double magic_x = static_cast<double>((magic >> 0) & 0x1f);  // random part x
	double magic_y = static_cast<double>((magic >> 5) & 0x1f);  // random part y
	double magic_z = static_cast<double>((magic >> 10) & 0x1f); // random part z

	double coeff_x = magic_x / (magic_x + magic_y + magic_z);
	double coeff_y = magic_y / (magic_x + magic_y + magic_z);
	double coeff_z = magic_z / (magic_x + magic_y + magic_z);

	double range_x = range * sqrt(coeff_x);
	double range_y = range * sqrt(coeff_y);
	double range_z = range * sqrt(coeff_z);

	pos magic_coeff = { range_x, range_y, range_z };

	return magic_coeff;
}

void create_geometric_positioning(const pos& ref, pos& point, double range)
{
	double ref_x = ref.get_x();
	double ref_y = ref.get_y();
	double ref_z = ref.get_z();

	pos magic_coeff = create_magic_coeff(point, range);

	double point_x = ref_x + magic_coeff.get_x();
	double point_y = ref_y + magic_coeff.get_y();
	double point_z = ref_z + magic_coeff.get_z();

	point.set(point_x, point_y, point_z);

#ifdef show_prepare_distance
	std::cout << range << "\t" << p3p_app::distance(ref, point);
#ifdef show_prepare_point
	std::cout << "\t" << point;
#endif
	std::cout << "\n";
#endif

}

// create distance
void create_ranges(vec& ranges, const conset& settings)
{
	std::mt19937 seed(1701);
	std::normal_distribution<> dst(settings.distance, settings.deviation);

	ranges.clear();
	for (auto i = 0; i < settings.n_sat; i++)
		ranges.push_back(dst(seed));
}

// create random points at a fixed distance
posvec create_constellation(const pos& ref, vec& ranges, const conset& settings)
{
	create_ranges(ranges, settings);

	posvec points(settings.n_sat);
	for (auto i = 0; i < settings.n_sat; i++)
		create_geometric_positioning(ref, points[i], ranges[i]);

	return points;
}