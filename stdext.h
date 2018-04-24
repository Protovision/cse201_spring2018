#ifndef STDEXT_H
#define STDEXT_H
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <stdexcept>

#ifndef M_PI
#define M_PI (4 * std::atan(1))
#endif

#ifndef M_E
#define M_E (std::exp(1))
#endif

void srand_time_once()
{
	static bool called = false;
	if (!called) {
		std::srand(std::time(0));
		called = true;
	}
}

int random_int(int min, int max)
{
	srand_time_once();
	return std::rand() % (max - min + 1) + min;
}

double random_double(double min, double max)
{
	srand_time_once();
	return min + (double)rand() / RAND_MAX * (max - min);
}

template <class T>
std::string to_string(const T& value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

void error(const std::string& s)
{
	throw std::runtime_error(s);
}

#endif
