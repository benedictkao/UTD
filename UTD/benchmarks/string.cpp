#include <benchmark/benchmark.h>
#include <iostream>
#include <memory>

#include "../src/data-structures/basic_string.h"
#include "../src/data-structures/string24.h"
#include "../src/data-structures/string32.h"
#include "./helper.h"
#include <string.h>

/*
 * Define the tests that you want to run
 */
#define CTOR
//#define RAND_CTOR
//#define RAND_CTOR_DENSE
//#define SIZE
//#define C_STR
//#define COMPARE
//#define COPY

constexpr size_t STR_LENGTH_SHORT = 14;
constexpr size_t STR_LENGTH_LONG  = 200;
/*
 * BENCHMARK
 * std::string | utd::basic_string | utd::string32 | utd::string24
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

#ifdef CTOR
BENCHMARK(BM_constructor_string<utd::basic_string>)
  ->Name("Constructor <utd::basic_string>")
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
#endif

#ifdef RAND_CTOR
BENCHMARK(BM_constructor_string_random<utd::basic_string>)
  ->Name("Constructor <utd::basic_string> (random)")
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
#endif

#ifdef RAND_CTOR_DENSE
/*
 * Benchmark, String Constructor
 * - Random Characters + Small Range Steps (1 to 32, steps of 1)
 */
int Start = 1, End = 32, Step = 1;

BENCHMARK(BM_constructor_string_random<utd::basic_string>)
  ->Name("Constructor <utd::basic_string> (random, dense)")
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
#endif

/*
 * Benchmark, String Method - size()
 * - Random Characters
 */

template <class T>
static void BM_size_string_random(benchmark::State& state) {
  const size_t random_str_len = rand() % STR_LENGTH_SHORT;
  const size_t random_str_len_2 =
    rand() % (STR_LENGTH_LONG) + (2 * STR_LENGTH_SHORT);

  char* c_str = new char[random_str_len + 1];
  generate_c_str(c_str, random_str_len, true);

  char* c_str_2 = new char[random_str_len_2 + 1];
  generate_c_str(c_str_2, random_str_len_2, true);

  T v[2];
  v[0] = c_str;
  v[1] = c_str_2;

  for (auto _ : state)
    benchmark::DoNotOptimize(v[rand() % 2].size());

  delete[] c_str_2;
  delete[] c_str;
}

#ifdef SIZE
BENCHMARK(BM_size_string_random<utd::basic_string>)
  ->Name("Method size() <utd::basic_string> (random)");

BENCHMARK(BM_size_string_random<utd::string24>)
  ->Name("Method size() <utd::string24> (random)");

BENCHMARK(BM_size_string_random<utd::string32>)
  ->Name("Method size() <utd::string32> (random)");

BENCHMARK(BM_size_string_random<std::string>)
  ->Name("Method size() <std::string> (random)");
#endif


/*
 * Benchmark, String Method - c_str()
 * - Random Characters
 */

template <class T>
static void BM_c_str_string_random(benchmark::State& state) {
  const size_t random_str_len = rand() % STR_LENGTH_SHORT;
  const size_t random_str_len_2 =
    rand() % (STR_LENGTH_LONG) + (2 * STR_LENGTH_SHORT);

  char* c_str = new char[random_str_len + 1];
  generate_c_str(c_str, random_str_len, true);

  char* c_str_2 = new char[random_str_len_2 + 1];
  generate_c_str(c_str_2, random_str_len_2, true);

  T v[2];
  v[0] = c_str;
  v[1] = c_str_2;

  for (auto _ : state)
    benchmark::DoNotOptimize(v[rand() % 2].c_str());

  delete[] c_str_2;
  delete[] c_str;
}

#ifdef C_STR
BENCHMARK(BM_c_str_string_random<utd::basic_string>)
  ->Name("Method c_str() <utd::basic_string> (random)");

BENCHMARK(BM_c_str_string_random<utd::string24>)
  ->Name("Method c_str() <utd::string24> (random)");

BENCHMARK(BM_c_str_string_random<utd::string32>)
  ->Name("Method c_str() <utd::string32> (random)");

BENCHMARK(BM_c_str_string_random<std::string>)
  ->Name("Method c_str() <std::string> (random)");
#endif


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

#ifdef COMPARE
BENCHMARK(BM_compare_string_random<utd::basic_string>)
  ->Name("Operator compare == <utd::basic_string> (random)")
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
#endif

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

#ifdef COPY
BENCHMARK(BM_copy_string_random<utd::basic_string>)
  ->Name("Operator copy = <utd::basic_string> (random)")
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
#endif


int main(int argc, char** argv) {
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
}
