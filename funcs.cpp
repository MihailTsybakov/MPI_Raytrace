#include "funcs.h"


float scalar_prod(std::vector<float> v1, std::vector<float> v2)
{
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

std::vector<float> normalize(std::vector<float> v)
{
	float denom = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	return { v[0] / denom, v[1] / denom, v[2] / denom };
}

std::vector<float> operator-(std::vector<float> v1, std::vector<float> v2)
{
	std::vector<float> res = { 0,0,0 };

	res[0] = v1[0] - v2[0];
	res[1] = v1[1] - v2[1];
	res[2] = v1[2] - v2[2];

	return res;
}

std::vector<float> operator+(std::vector<float> v1, std::vector<float> v2)
{
	std::vector<float> res = { 0,0,0 };

	res[0] = v1[0] + v2[0];
	res[1] = v1[1] + v2[1];
	res[2] = v1[2] + v2[2];

	return res;
}

std::vector<float> operator*(std::vector<float> v, float M)
{
	v[0] *= M;
	v[1] *= M;
	v[2] *= M;

	return v;
}

void check_mpi_errors(int error_code)
{
	std::vector<std::string> errors = { "MPI_SUCCESS", "MPI_ERR_BUFFER", "MPI_ERR_COUNT", "MPI_ERR_TYPE",
	"MPI_ERR_TAG", "MPI_ERR_COMM", "MPI_ERR_RANK", "MPI_ERR_REQUEST", "MPI_ERR_ROOT", "MPI_ERR_GROUP",
	"MPI_ERR_OP", "MPI_ERR_TOPOLOGY", "MPI_ERR_DIMS", "MPI_ERR_ARG", "MPI_ERR_UNKNOWN", "MPI_ERR_TRUNCATE",
	"MPI_ERR_OTHER", "MPI_ERR_INTERN", "MPI_ERR_IN_STATUS", "MPI_ERR_PENDING", "MPI_ERR_LASTCODE" };
	if (error_code != MPI_SUCCESS)
	{
		int rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		std::cout << " <logs> Error occured in process [" << rank << "]. Error code [" << error_code << "], error descr: [" << errors[error_code] << "]." << std::endl;
	}
}

std::vector<float> vector_prod(std::vector<float> v1, std::vector<float> v2)
{
	return {v1[1]*v2[2] - v1[2]*v2[1], v1[2]*v2[0] - v1[0]*v2[2], v1[0]*v2[1] - v1[1]*v2[0]};
}

std::vector<float> new_len(std::vector<float> v, float L)
{
	float k = sqrt((L * L) / (scalar_prod(v, v)));
	return { v[0] * k, v[1] * k, v[2] * k };
}