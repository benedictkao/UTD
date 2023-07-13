#pragma once

#include <benchmark/benchmark.h>

class CustomMemoryManager : public benchmark::MemoryManager {
public:
  int64_t num_allocs;
  int64_t max_bytes_used;

  void Start() BENCHMARK_OVERRIDE;

  void Stop(Result& result) BENCHMARK_OVERRIDE;
};


char get_random_char();

void generate_c_str(char*, size_t, bool);
