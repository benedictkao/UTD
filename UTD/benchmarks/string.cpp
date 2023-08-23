#include <benchmark/benchmark.h>
#include <iostream>
#include <memory>

#include "../src/data-structures/string.h"
#include "../src/data-structures/string24.h"
#include "../src/data-structures/string32.h"
#include "./helper.h"
#include <string.h>

/*
 * BENCHMARK
 * std::string | utd::string | utd::string32 | utd::string24
 */
/*
 * Benchmark, String Constructor
 * - Identical Characters
 * - Random Characters
 */

template <class T>
static void BM_constructor_string(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), false);

  for (auto _ : state)
    benchmark::DoNotOptimize(T(c_str));

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

template <class T>
static void BM_constructor_string_random(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), true);

  for (auto _ : state)
    benchmark::DoNotOptimize(T(c_str));

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_constructor_string<utd::string>)
  ->Name("Constructor <utd::string>")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_constructor_string<utd::string24>)
  ->Name("Constructor <utd::string24>")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_constructor_string<utd::string32>)
  ->Name("Constructor <utd::string32>")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_constructor_string<std::string>)
  ->Name("Constructor <std::string>")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_constructor_string_random<utd::string>)
  ->Name("Constructor <utd::string> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_constructor_string_random<utd::string24>)
  ->Name("Constructor <utd::string24> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_constructor_string_random<utd::string32>)
  ->Name("Constructor <utd::string32> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_constructor_string_random<std::string>)
  ->Name("Constructor <std::string> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

/*
 * Benchmark, String Constructor
 * - Random Characters + Small Range Steps (1 to 32, steps of 1)
 */
int Start = 1, End = 32, Step = 1;

BENCHMARK(BM_constructor_string_random<utd::string>)
  ->Name("Constructor <utd::string> (random, dense)")
  ->DenseRange(Start, End, Step)
  ->Complexity();

BENCHMARK(BM_constructor_string_random<utd::string24>)
  ->Name("Constructor <utd::string24> (random, dense) ")
  ->DenseRange(Start, End, Step)
  ->Complexity();

BENCHMARK(BM_constructor_string_random<utd::string32>)
  ->Name("Constructor <utd::string32> (random, dense) ")
  ->DenseRange(Start, End, Step)
  ->Complexity();

BENCHMARK(BM_constructor_string_random<std::string>)
  ->Name("Constructor <std::string> (random, dense) ")
  ->DenseRange(Start, End, Step)
  ->Complexity();


/*
 * Benchmark, String Method - size()
 * - Random Characters
 */

template <class T>
static void BM_size_string_random(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), true);
  T v(c_str);

  for (auto _ : state)
    benchmark::DoNotOptimize(v.size());

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_size_string_random<utd::string>)
  ->Name("Method size() <utd::string> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_size_string_random<utd::string24>)
  ->Name("Method size() <utd::string24> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_size_string_random<utd::string32>)
  ->Name("Method size() <utd::string32> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_size_string_random<std::string>)
  ->Name("Method size() <std::string> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

/*
 * Benchmark, String Method - c_str()
 * - Random Characters
 */

template <class T>
static void BM_c_str_string_random(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), true);
  T v(c_str);

  for (auto _ : state)
    benchmark::DoNotOptimize(v.c_str());

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_c_str_string_random<utd::string>)
  ->Name("Method c_str() <utd::string> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_c_str_string_random<utd::string24>)
  ->Name("Method c_str() <utd::string24> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_c_str_string_random<utd::string32>)
  ->Name("Method c_str() <utd::string32> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_c_str_string_random<std::string>)
  ->Name("Method c_str() <std::string> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

/*
 * Benchmark, Operator compare - ==
 * - Random Characters
 * utd::string24 not included as operator == is not supported
 */

template <class T>
static void BM_compare_string_random(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), true);
  T v_1(c_str);
  T v_2(c_str);

  for (auto _ : state)
    benchmark::DoNotOptimize(v_1 == v_2);

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_compare_string_random<utd::string>)
  ->Name("Operator compare == <utd::string> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_compare_string_random<utd::string32>)
  ->Name("Operator compare == <utd::string32> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_compare_string_random<std::string>)
  ->Name("Operator compare == <std::string> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

/*
 * Benchmark, Operator copy - =
 * - Random Characters
 */

template <class T>
static void BM_copy_string_random(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), true);
  T v_1(c_str);
  T v_2;

  for (auto _ : state)
    benchmark::DoNotOptimize(v_2 = v_1);

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_copy_string_random<utd::string>)
  ->Name("Operator copy = <utd::string> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_copy_string_random<utd::string24>)
  ->Name("Operator copy = <utd::string24> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_copy_string_random<utd::string32>)
  ->Name("Operator copy = <utd::string32> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

BENCHMARK(BM_copy_string_random<std::string>)
  ->Name("Operator copy = <std::string> (random)")
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();


int main(int argc, char** argv) {
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
}
