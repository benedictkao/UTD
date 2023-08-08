
#include <benchmark/benchmark.h>
#include <iostream>
#include <memory>

#include "../src/data-structures/string.h"
#include "../src/data-structures/string24.h"
#include "../src/data-structures/string32.h"
#include "./helper.h"
#include <string.h>

static void BM_std_string_size(benchmark::State& state) {
  size_t rand_num = state.range(0);
  char*  c_str    = new char[rand_num + 1];
  generate_c_str(c_str, rand_num, true);
  std::string v(c_str);

  for (auto _ : state) {
    v.size();
  }

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_std_string_size)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

static void BM_utd_string_32_size(benchmark::State& state) {
  size_t rand_num = rand() % 52;
  char*  c_str    = new char[rand_num + 1];
  generate_c_str(c_str, rand_num, true);
  utd::string32 v(c_str);

  for (auto _ : state) {
    v.size();
  }

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_utd_string_32_size)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

static void BM_utd_string_24_size(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), true);

  utd::string24 v(c_str);

  for (auto _ : state) {
    v.size();
  }

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_utd_string_24_size)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

static void BM_std_string_c_str(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), true);

  std::string v(c_str);
  for (auto _ : state) {
    v.c_str();
  }

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_std_string_c_str)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

static void BM_utd_string_32_c_str(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), true);

  utd::string32 v(c_str);
  for (auto _ : state) {
    v.c_str();
  }

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_utd_string_32_c_str)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();


static void BM_utd_string_24_c_str(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), true);

  utd::string24 v(c_str);
  for (auto _ : state) {
    v.c_str();
  }

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_utd_string_24_c_str)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

/*
 * TODO: Add String Operations Benchmark
// String Operations
static void BM_utd_string_plus_eq(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), true);
  utd::string v(c_str);

  for (auto _ : state) {
    utd::string s;
    s += v;
  }

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_utd_string_plus_eq)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

static void BM_utd_string_32_plus_eq(benchmark::State& state) {
char* c_str = new char[state.range(0) + 1];
generate_c_str(c_str, state.range(0), true);
utd::string32 v(c_str);

for (auto _ : state) {
  utd::string32 s;
  s += v;
}

delete[] c_str;
state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_utd_string_32_plus_eq)
->RangeMultiplier(2)
->Range(1 << 0, 1 << 15)
->Complexity();

static void BM_std_string_plus_eq(benchmark::State& state) {
char* c_str = new char[state.range(0) + 1];
generate_c_str(c_str, state.range(0), true);
std::string v(c_str);

for (auto _ : state) {
  std::string s;
  s += v;
}

delete[] c_str;
state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_std_string_plus_eq)
->RangeMultiplier(2)
->Range(1 << 0, 1 << 15)
->Complexity();
*/

int main(int argc, char** argv) {
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
}
