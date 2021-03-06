#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "generator.h"
#include <vector>
#include <numeric>

TEST_CASE("Factorials are computed", "[factorial]") {
	REQUIRE(Factorial(1) == 1);
	REQUIRE(Factorial(2) == 2);
	REQUIRE(Factorial(3) == 6);
	REQUIRE(Factorial(10) == 3628800);
}

TEST_CASE("Check iterative generator correctness", "[generator]") {
	Generator g(6, 3);
	std::vector<int> first = { 1,1,4 };
	std::vector<std::vector<int>> tests = {
		{1, 1, 4},
		{1, 2, 3},
		{1, 3, 2},
		{1, 4, 1},
		{2, 1, 3},
		{2, 2, 2},
		{2, 3, 1},
		{3, 1, 2},
		{3, 2, 1},
		{4, 1, 1},
	};
	g.GenerateAll();
	REQUIRE(g.getCount() == tests.size());
	auto cnt = g.getCount();
	for (int i = 0; i < cnt; i++) {
		const auto& result = g.GetResult(i);
		REQUIRE(result.size() == 3);
		REQUIRE(std::accumulate(result.begin(), result.end(), 0) == 6);
		for (const auto& t : result) {
			REQUIRE(t <= 6 && t > 0);
		}
	}
	int i = 0;
	for (const auto& test : tests) {
		if (i >= cnt) break;
		auto res = g.GetResult(i);
		REQUIRE(res == test);
		i++;
	}
}

TEST_CASE("Check recursive generator correctness", "[generator]") {
	Generator g(6, 3);
	std::vector<int> first = { 1,1,4 };
	std::vector<std::vector<int>> tests = {
		{1, 1, 4},
		{1, 2, 3},
		{1, 3, 2},
		{1, 4, 1},
		{2, 1, 3},
		{2, 2, 2},
		{2, 3, 1},
		{3, 1, 2},
		{3, 2, 1},
		{4, 1, 1},
	};
	g.GenerateRecursive();
	REQUIRE(g.getCount() == tests.size());
	auto cnt = g.getCount();
	for (int i = 0; i < cnt; i++) {
		const auto& result = g.GetResult(i);
		REQUIRE(result.size() == 3);
		REQUIRE(std::accumulate(result.begin(), result.end(), 0) == 6);
		for (const auto& t : result) {
			REQUIRE(t <= 6);
		}
	}
	int i = 0;
	for (const auto& test : tests) {
		if (i >= cnt) break;
		auto res = g.GetResult(i);
		REQUIRE(res == test);
		i++;
	}
}

TEST_CASE("Check vector elements", "[vector]") {
	std::vector<std::vector<int>> v;
	v.push_back({ 1,2,3 });
	v.push_back(v[0]);

	const std::vector<int> vec = { 1, 2, 3 };
	REQUIRE(v[1] == vec);

	//v[0][1] = 0;
	REQUIRE(v[0] == vec);

	REQUIRE(v.size() == 2);

	v.resize(3);
	v[2].resize(3);
	std::fill(v[2].begin(), v[2].end(), 7);

	const std::vector<int> vec2 = { 7, 7, 7 };
	REQUIRE(v[2] == vec2);

	REQUIRE(*std::find(v[1].cbegin(), v[1].cend(), 2) == 2);
	REQUIRE(std::find(v[1].cbegin(), v[1].cend(), 27) == v[1].cend());
}