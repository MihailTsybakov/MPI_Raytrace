#include "sphere.h"

sphere::sphere(int R, int G, int B, float x, float y, float z, float Rad)
{
	this->R = R;
	this->G = G;
	this->B = B;

	this->x = x;
	this->y = y;
	this->z = z;

	this->Rad = Rad;
}

bool sphere::intersect(std::vector<float> point, std::vector<float> trace_ray, std::vector<float>& res)
{
	/// res = {xi, yi, zi, nx, ny, nz};
	std::vector<float> center = { x, y, z };

	float A = scalar_prod(trace_ray, trace_ray);
	float B = 2 * (scalar_prod(point, trace_ray) - scalar_prod(trace_ray, center));
	float C = scalar_prod((point - center), (point - center)) - Rad * Rad;
	float Discr = B*B - 4*A*C;

	if (Discr <= 0) return false;

	float param_1, param_2;
	param_1 = (-B - sqrt(Discr)) / (2 * A);
	param_2 = (-B + sqrt(Discr)) / (2 * A);

	std::vector<float> intersection, N;
	if (param_1 > param_2) std::swap(param_1, param_2);
	intersection = point + trace_ray * param_1;
	N = intersection - center;

	res[0] = intersection[0]; res[1] = intersection[1]; res[2] = intersection[2];
	res[3] = N[0]; res[4] = N[1]; res[5] = N[2];
	return true;
}

float sphere::get_rad() const
{
	return Rad;
}