#include <benchmark/benchmark.h>
#include <iostream>
#include <memory>

#include "../src/data-structures/string.h"
#include "../src/data-structures/string32.h"
#include "./helper.h"
#include <string.h>

// Create string of constant char
static void BM_create_utd_string(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), false);

  for (auto _ : state)
    utd::string v(c_str);

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_create_utd_string)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();


static void BM_create_utd_string_32(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), false);

  for (auto _ : state)
    utd::string32 v(c_str);

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_create_utd_string_32)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();


static void BM_create_std_string(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), false);

  for (auto _ : state)
    std::string v(c_str);

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_create_std_string)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

// Create string of random char
static void BM_create_utd_string_random(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), true);

  for (auto _ : state)
    utd::string v(c_str);

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_create_utd_string_random)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();


static void BM_create_utd_string_32_random(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), true);

  for (auto _ : state)
    utd::string32 v(c_str);

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_create_utd_string_32_random)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();


static void BM_create_std_string_random(benchmark::State& state) {
  char* c_str = new char[state.range(0) + 1];
  generate_c_str(c_str, state.range(0), true);

  for (auto _ : state)
    std::string v(c_str);

  delete[] c_str;
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_create_std_string_random)
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
