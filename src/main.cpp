
#include "utils/rand.h"
#include <iostream>
#include <string>

template<typename Cont>
void print_elements(Cont const& cont, std::string const& delimiter=", ", std::string const& opt_str="") {
	std::cout << opt_str;
	for (auto const& elem : cont) {
		std::cout << elem << delimiter;
	}
	std::cout << "\n";
}

int main()
{
    // std::cout << "Hello World!\n";
		std::int16_t min_val{ 0 };
		std::int16_t max_val{ 10 };
		auto res = utils_rand::rand_scalar(min_val, max_val);
		std::cout << "res: " << res << "\n";
		auto res_vec = utils_rand::rand_scalar(min_val, max_val, 10);
		print_elements(res_vec, ", ", "vec values: ");
		auto uni_rand = utils_rand::rand(0.0, 10.0, 10);
		print_elements(uni_rand, ", ", "rand res vec: ");
		auto gauss_dist = utils_rand::randn(0.0, 1.0, 10);
		print_elements(gauss_dist, ", ", "gauss dist res: ");
		auto sampled_gauss = utils_rand::unique_sample(gauss_dist, 3);
		print_elements(sampled_gauss, ", ", "gauss dist sampled: ");
		auto gauss_dist_larg = utils_rand::randn(0.0, 1.0, 500);
		utils_rand::hist(gauss_dist_larg, 11);
		return 0;
}
