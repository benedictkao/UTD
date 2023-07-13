#include <benchmark/benchmark.h>
#include <iostream>
#include <memory>

#include "../src/data-structures/vector.h"
#include "./helper.h"
#include <string>
#include <vector>

// Create Vector (int)
static void BM_create_utd_vector(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(utd::vector<int>(state.range(0), 1));
  }

  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_create_utd_vector)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();


static void BM_create_std_vector(benchmark::State& state) {
  for (auto _ : state)
    std::vector<int> v(state.range(0), 1);

  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_create_std_vector)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();


struct random_struct {
  int       item1;
  float     item2;
  long long item3;
  int       item4;
  float     item5;
  long long item6;
  int       item7;
  float     item8;
  long long item9;
  long long item10;
};

// Create Vector (class)
static void BM_create_utd_vector_struct(benchmark::State& state) {
  for (auto _ : state)
    benchmark::DoNotOptimize(
      utd::vector<random_struct>(state.range(0),
                                 random_struct{ rand(),
                                                (float) rand(),
                                                rand(),
                                                rand(),
                                                (float) rand(),
                                                rand(),
                                                rand(),
                                                (float) rand(),
                                                rand(),
                                                rand() }));


  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_create_utd_vector_struct)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

static void BM_create_std_vector_struct(benchmark::State& state) {
  for (auto _ : state)
    benchmark::DoNotOptimize(
      std::vector<random_struct>(state.range(0),
                                 random_struct{ rand(),
                                                (float) rand(),
                                                rand(),
                                                rand(),
                                                (float) rand(),
                                                rand(),
                                                rand(),
                                                (float) rand(),
                                                rand(),
                                                rand() }));

  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_create_std_vector_struct)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

static void BM_create_utd_vector_string(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(
      utd::vector<std::string>(state.range(0), std::string()));
  }

  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_create_utd_vector_string)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();


static void BM_create_std_vector_string(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(
      std::vector<std::string>(state.range(0), std::string()));
  }

  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_create_std_vector_string)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();


// Vector Push Back
static void BM_push_back_utd_vector(benchmark::State& state) {
  utd::vector<int> v;

  for (auto _ : state)
    for (int i = 0; i < state.range(0); i++)
      v.push_back(rand());

  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_push_back_utd_vector)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

static void BM_push_back_std_vector(benchmark::State& state) {
  std::vector<int> v;

  for (auto _ : state)
    for (int i = 0; i < state.range(0); i++)
      v.push_back(rand());

  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_push_back_std_vector)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();


// Vector - A set of operations
static void BM_utd_vector_operations(benchmark::State& state) {
  utd::vector<int> v;

  for (auto _ : state) {
    for (int i = 0; i < state.range(0); i++) {
      v.push_back(rand());
    }

    for (int i = 0; i < state.range(0); i++) {
      v.pop_back();
    }

    for (int i = 0; i < state.range(0); i++) {
      v.push_back(rand());
    }

    v.clear();
  }

  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_utd_vector_operations)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

static void BM_std_vector_operations(benchmark::State& state) {
  std::vector<int> v;

  for (auto _ : state) {
    for (int i = 0; i < state.range(0); i++) {
      v.push_back(rand());
    }

    for (int i = 0; i < state.range(0); i++) {
      v.pop_back();
    }

    for (int i = 0; i < state.range(0); i++) {
      v.push_back(rand());
    }

    v.clear();
  }

  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_std_vector_operations)
  ->RangeMultiplier(2)
  ->Range(1 << 0, 1 << 15)
  ->Complexity();

int main(int argc, char** argv) {
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
}
