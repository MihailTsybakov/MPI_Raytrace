#include "raytrace.h"

void raytrace(sphere S, scene sc, std::string save_to)
{
	int rank, size, argc = 1;
	char** argv;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (sc.screen_height % size != 0)
	{
		std::cout << " Process [" << rank << "]: Error: screen height must be completely divided by number of processes." << std::endl;
		MPI_Finalize();
		return;
	}

	int process_scope = sc.screen_height / size;

	std::vector<float> ort = vector_prod(sc.upvector, sc.camera_dir);
	ort = new_len(ort, sc.screen_width / 2);
	sc.upvector = new_len(sc.upvector, sc.screen_height / 2);
	sc.camera_dir = new_len(sc.camera_dir, sc.screen_dist);

	std::vector<float> left_upper_corner = sc.camera + sc.camera_dir + sc.upvector + ort;
	sc.upvector = normalize(sc.upvector);
	ort = normalize(ort);
	std::vector<float> scope_start = left_upper_corner - sc.upvector * process_scope * rank;
	std::vector<float> curr_pixel, row_start = scope_start, res;

	int* R_channel = new int[process_scope * sc.screen_width];
	for (int y = 0; y < process_scope; ++y)
	{
		curr_pixel = row_start;
		for (int x = 0; x < sc.screen_width; ++x)
		{
			res = { 0,0,0,0,0,0 };
			std::vector<float> trace_ray = curr_pixel - sc.camera;
			if (S.intersect(sc.camera, trace_ray, res) == true)
			{
				std::vector<float> N = { res[3], res[4], res[5] };
				N = normalize(N);
				std::vector<float> intersection = { res[0], res[1], res[2] };
				std::vector<float> light = normalize(sc.light - intersection);
				float coef = scalar_prod(light, N);
				if (coef < 0) coef = 0;
				R_channel[y * sc.screen_width + x] = static_cast<int>(coef * S.R);
			}
			else
			{
				R_channel[y * sc.screen_width + x] = 0;
			}
			curr_pixel = curr_pixel - ort;
		}
		row_start = row_start - sc.upvector;
	}
	check_mpi_errors(MPI_Send(R_channel, process_scope * sc.screen_width, MPI_INT, 0, 0, MPI_COMM_WORLD));
	if (rank == 0)
	{
		int* total_pixels = new int[sc.screen_width * sc.screen_height];
		for (int process = 0; process < size; ++process)
		{
			MPI_Status st;
			check_mpi_errors(MPI_Recv(total_pixels + process_scope*sc.screen_width*process, process_scope * sc.screen_width, MPI_INT, process, MPI_ANY_TAG,
				MPI_COMM_WORLD, &st));
		}
		// All pixels recieved.
		Canvas C(640, 480);
		for (int y = 0; y < sc.screen_height; ++y)
		{
			for (int x = 0; x < sc.screen_width; ++x)
			{
				C.put_pixel(x, y, total_pixels[y * sc.screen_width + x], 0, 0);
			}
		}
		C.save(save_to);
		delete[] total_pixels;
	}
	
	std::cout << " Process [" << rank << "] finished." << std::endl;
	delete[] R_channel;
	MPI_Finalize();
}
