
#ifndef UTILS_RAND_H
#define UTILS_RAND_H

#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <type_traits>
#include <stdexcept>
#include <vector>

namespace utils_rand
{
// all declarations in the namespace utils_rand

// Returns a random integer in the range [low, high) with equal probability, 
// For instance rand_scalar(0, 5) would give 0,1,2,3,4 with equal probabili-
// ty; low, high must be integral type to be used. High must be larger than 
// low.
template<typename T>
T rand_scalar(T low, T high) {  // [) max_val exclusive
	static_assert(std::is_integral_v<T>, "type of min val and max val should be scalar");
	assert(high > low && "high must be larger than low, arguments are not valid");
	if (high <= low) {
		std::cerr << "high must be larger than low, arguments are not valid\n";
		throw std::invalid_argument("high must be larger than low, arguments are not valid");
	}
	static std::mt19937 gen(0);
	std::uniform_int_distribution<T> uni(low, high - 1);
	return uni(gen);
}

// Returns a type T vector whose elements are chosen from the range [low, high) 
// with equal probability, For instance rand_scalar(0, 5, 100) would return size 
// 100 vector<int> whose elements compose of 0,1,2,3,4 with eaual probability.
template<typename T>
std::vector<T> rand_scalar(T low, T high, int n_elem) {  // [) max_val exclusive
	static_assert(std::is_integral_v<T>, "type of min val and max val should be scalar");
	assert(n_elem >= 0, "elem num cannot be negative");
	if (n_elem < 0) {
		std::cerr << "n_elem cannot be negative\n";
		throw std::invalid_argument("n_elem cannot be negative");
	}
	std::vector<T> res(n_elem, T{});
	for (int i = 0; i < res.size(); ++i) {
		res[i] = rand_scalar(low, high);
	}
	return res;
}

// Returns a floating point(float, double) variable in the range [low, high) with
// equal probability. For instance rand(0.0, 1.0) would return a double in the range
// [0.0, 1.0) from uniform distribution.
template<typename T>
T rand(T low, T high) {  // [) max_val exclusive
	static_assert(std::is_floating_point_v<T>, "type of low and high should floating point");
	assert(high > low && "high must be larger than low, arguments are not valid");
	if (high <= low) {
		std::cerr << "high must be larger than low, arguments are not valid\n";
		throw std::invalid_argument("high must be larger than low, arguments are not valid");
	}
	static std::mt19937 gen(0);
	std::uniform_real_distribution<T> uni(low, high);
	return uni(gen);
}

// Returns a floating point(float, double) vector of size n_elem in the range [low, high)
// with equal probability. For instance rand(0.0, 1.0, 100) would return a vector<double>
// in the range [0.0, 1.0) from uniform distribution.
template<typename T>
std::vector<T> rand(T low, T high, int n_elem) {  // [) max_val exclusive
	static_assert(std::is_floating_point_v<T>, "type of low and high should floating point");
	assert(n_elem >= 0, "elem num cannot be negative");
	if (n_elem < 0) {
		std::cerr << "n_elem cannot be negative\n";
		throw std::invalid_argument("n_elem cannot be negative");
	}
	std::vector<T> res(n_elem, T{});
	for (int i = 0; i < res.size(); ++i) {
		res[i] = rand(low, high);
	}
	return res;
}

// Returns a floating point(float, double) random variable with mean, variance value 
// from the Gaussian Distribution. For instance randn(0.0, 1.0) would return a double 
// random variable from Gaussian Distribution with mean 0.0 and variance 1.0
template<typename T>
T randn(T mean, T variance) {
	static_assert(std::is_floating_point_v<T>, "Type of mean and variance should be floating point");
	assert(variance > 0 && "variance cannot be negative");
	if (variance < 0) {
		std::cerr << "variance cannot be negative\n";
		throw std::invalid_argument("variance cannot be megative");
	}
	static std::mt19937 gen(0);
	std::normal_distribution<double> normal(mean, variance);
	return normal(gen);
}

// Returns a floating point(float, double) n_elem size random vector with mean, variance
// value from the Gaussian Distribution. For instance randn(0.0, 1.0, 100) would return 
// a vector<double> with size 100 whose elements are from Gaussian Distribution with mean
// 0.0 and variance 1.0
template<typename T>
std::vector<T> randn(T mean, T variance, int n_elem) {
	static_assert(std::is_floating_point_v<T>, "Type of mean and variance should be floating point");
	assert(n_elem >= 0, "elem num cannot be negative");
	if (n_elem < 0) {
		std::cerr << "n_elem cannot be negative\n";
		throw std::invalid_argument("n_elem cannot be negative");
	}
	std::vector<T> res(n_elem, T{});
	for (int i = 0; i < res.size(); ++i) {
		res[i] = randn(mean, variance);
	}
	return res;
}

// Returns nothing. Shuffles vec in place, For instance shuffle(vec={1,2,3,4}) might make vec = {2,4,3,1}
template <typename T>
void shuffle(std::vector<T>& vec) { // shuffles in place
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
}

// Returns a vector with size n_elem whose elements are chosen randomly from vec. For instance 
// unique_sample(vec={1,2,3,4,5}, 2) might return {2, 5}. For instance unique_sample(vec={1,2,3,4,5}, 5) may 
// return {2,3,4,1,5}. It is guaranteed that it contains all elements in the vec, but ordering may be different.
// However, if unique_sample(vec={1,2,2,3,3}, 2) is called it might return {2, 2}. If input vec doesn't consist 
// of unique elements, output might not also. n_elem cannot be larger than vec.size().
template<typename T>
std::vector<T> unique_sample(std::vector<T>const& vec, int n_elem) {
	assert(n_elem >= 0, "elem num cannot be negative");
	if (n_elem < 0) {
		std::cerr << "n_elem cannot be negative\n";
		throw std::invalid_argument("n_elem cannot be negative");
	}
	assert(vec.size() >= n_elem, "cannot sample more than size of the vector");
	if (n_elem > vec.size()) {
		std::cerr << "elem num cannot be larger than size of the vector";
		throw std::invalid_argument("Invalid Syntax");
	}
	std::vector<T> res(n_elem, T{});
	std::vector<int> indices(vec.size(), 0);
	std::iota(indices.begin(), indices.end(), 0);
	shuffle(indices);
	for (int i = 0; i < n_elem; ++i) {
		res[i] = vec[indices[i]];
	}
	return res;
}

// prints to the console count of bin times char '*' for each bin  
template<typename Cont>
void hist(Cont const& cont, int n_bin=10) {
	assert(n_bin > 0 && "n_bin must be positive");
	if (n_bin <= 0) {
		std::cerr << "n_bin must be positive\n";
		throw std::invalid_argument("n_bin must be positive");
	}
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
