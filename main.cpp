#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "raytrace.h"

#define DEFAULT_TAG 0

int main(int argc, char* argv[])
{
	// Warning: can process only red spheres for now
	sphere S(255, 0, 0, 100.0, 100.0, 10.0, 80.0);
	scene Sc;

	Sc.camera = { 0, 0, 0 };
	Sc.camera_dir = { 1.0, 1.0, 0 };
	Sc.light = { 0, 0, 50.0 };
	Sc.upvector = { 0, 0, 1.0 };
	Sc.screen_dist = 50.0;
	Sc.screen_width = 640;
	Sc.screen_height = 480;
	Sc.view_range = 500.0;
	
	raytrace(S, Sc, "MPI_render.bmp");

	return 0;
}