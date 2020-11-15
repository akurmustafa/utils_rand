
#ifndef UTILS_RAND_H
#define UTILS_RAND_H

#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <type_traits>
#include <vector>

namespace utils_rand
{

// all declarations in the namespace utils_rand
template<typename T>
T rand_scalar(T low, T high) {  // [) max_val exclusive
	static_assert(std::is_integral_v<T>, "type of min val and max val should be scalar");
	static std::mt19937 gen(0);
	std::uniform_int_distribution<T> uni(low, high - 1);
	return uni(gen);
}

template<typename T>
std::vector<T> rand_scalar(T low, T high, int n_elem) {  // [) max_val exclusive
	static_assert(std::is_integral_v<T>, "type of min val and max val should be scalar");
	assert(n_elem >= 0, "elem num cannot be negative");
	std::vector<T> res(n_elem, T{});
	for (int i = 0; i < res.size(); ++i) {
		res[i] = rand_scalar(low, high);
	}
	return res;
}

template<typename T>
T rand(T low, T high) {  // [) max_val exclusive
	static_assert(std::is_floating_point_v<T>, "type of low and high should floating point");
	static std::mt19937 gen(0);
	std::uniform_real_distribution<T> uni(low, high);
	return uni(gen);
}

template<typename T>
std::vector<T> rand(T low, T high, int n_elem) {  // [) max_val exclusive
	static_assert(std::is_floating_point_v<T>, "type of low and high should floating point");
	assert(n_elem >= 0, "elem num cannot be negative");
	std::vector<T> res(n_elem, T{});
	for (int i = 0; i < res.size(); ++i) {
		res[i] = rand(low, high);
	}
	return res;
}

template<typename T>
T randn(T mean, T variance) {
	static_assert(std::is_floating_point_v<T>, "Type of mean and variance should be floating point");
	static std::mt19937 gen(0);
	std::normal_distribution<double> normal(mean, variance);
	return normal(gen);
}

template<typename T>
std::vector<T> randn(T mean, T variance, int n_elem) {
	static_assert(std::is_floating_point_v<T>, "Type of mean and variance should be floating point");
	assert(n_elem >= 0, "elem num cannot be negative");
	std::vector<T> res(n_elem, T{});
	for (int i = 0; i < res.size(); ++i) {
		res[i] = randn(mean, variance);
	}
	return res;
}

template <typename T>
void shuffle(std::vector<T>& vec) { // shuffles in place
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
}

template<typename T>
std::vector<T> unique_sample(std::vector<T>const& vec, int n_elem) {
	assert(n_elem >= 0, "elem num cannot be negative");
	assert(vec.size() >= n_elem, "cannot sample more than size of the vector");
	std::vector<T> res(n_elem, T{});
	std::vector<int> indices(vec.size(), 0);
	std::iota(indices.begin(), indices.end(), 0);
	shuffle(indices);
	for (int i = 0; i < n_elem; ++i) {
		res[i] = vec[indices[i]];
	}
	return res;
}

template<typename Cont>
void hist(Cont const& cont, int n_bin=10) {
	using elem_t = typename Cont::value_type;
	std::vector<elem_t> res(cont.size(), elem_t{});
	std::copy(cont.begin(), cont.end(), res.begin());
	std::sort(res.begin(), res.end());
	elem_t bin_start = res[0];
	elem_t bin_end = res.back()+1e-6;
	double interval = (bin_end - bin_start) / n_bin;
	std::vector<int> bins(n_bin, int{});
	for (auto const& elem : res) {
		int idx_bin = std::floor((elem - bin_start) / interval);
		++bins[idx_bin];
	}
	for (auto const& cur_num : bins) {
		for (int i = 0; i < cur_num; ++i) {
			std::cout << "*";
		}
		std::cout << "\n";
	}
}

// int poisson(int lambda);

}  // namespace utils_rand

#endif  // end of UTILS_RAND_H
