#ifndef SPHERE
#define SPHERE

#include "funcs.h"

class sphere
{
public:
	int R, G, B;
	float x, y, z, Rad;
	sphere(int R, int G, int B, float x, float y, float z, float Rad);
	bool intersect(std::vector<float> point, std::vector<float> trace_ray, std::vector<float>& res);
	float get_rad() const;
};

typedef struct
{
	std::vector<float> camera;
	std::vector<float> light;
	std::vector<float> camera_dir;
	std::vector<float> upvector;

	float screen_dist;
	float view_range;
	int screen_width;
	int screen_height;
} scene;

#endif//SPHERE
