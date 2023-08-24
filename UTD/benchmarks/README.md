# Benchmark C++


## Background

Plans to benchmark unstandard library

## Requirements

[Google C++ Benchmark](https://github.com/google/benchmark)

## Build

**MacOS**
- `-DCMAKE_BUILD_TYPE=Release` ensures a production build
- `-DCMAKE_CXX_FLAGS=-DMEMORY_PROFILE` allows the measurement of memory (Optional)

```sh
cmake -B ./build -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=-DMEMORY_PROFILER
cmake --build ./build
```

## Run 

```sh
./build/main_string_benchmark --benchmark_format=<console|json|csv> 
# default is console
```



## Metrics

#### CPU Info
``` 
Example
- Run on (8 X 24 MHz CPU s)
- CPU Caches:
  - L1 Data 64 KiB
  - L1 Instruction 128 KiB
  - L2 Unified 4096 KiB (x8)
  - L3 ??
```
  
#### Performance
```
Time
    - time (Total time used to run code, nanosecond)
CPU Time
    - cpu_time (Total time code spent on CPU, nanosecond)
Memory
    - allocs_per_iter (size of memory allocations per benchmark iteration)
    - max_bytes_used (maximum no. of bytes used)
Big O Notation
    - big_o 
```
    
> Note: Multiple iterations are typically for a few reasons
> - warm up cache
> - allow readings to stabilize 
> - allow measurements of code with very small runtime...


## Measurement Methods

### Remove optimisations
- `benchmark::DoNotOptimize(x += i);`
- `benchmark::ClobberMemory();`

### Multiple Iterations

Steps in multiplication
- `BENCHMARK(BM_memcpy)->RangeMultiplier(2)->Range(8, 8<<10);`

Steps in addition
- `BENCHMARK(BM_memcpy)->DenseRange(8, 8<<10, 1);`
- `BENCHMARK(BM_memcpy)->Iterations(17);`

### Measuring for memory usage

```c++
/* 
 * Define a custom Memory Manager ( Overwrite the one provided by g benchmark )
 */
class CustomMemoryManager : public benchmark::MemoryManager {
public:
  int64_t num_allocs;
  int64_t max_bytes_used;

  void Start() BENCHMARK_OVERRIDE {}

  void Stop(Result& result) BENCHMARK_OVERRIDE {}
};

/* 
 * Define a custom malloc function
 * Track memory usage with the custom Memory Manager 
 */
#ifdef MEMORY_PROFILER
void* custom_malloc(size_t size) {
  void* p = malloc(size);
  mm.get()->num_allocs += 1;
  mm.get()->max_bytes_used += size;
  return p;
}
#define malloc(size) custom_malloc(size)
#endif

/*
 * Register the memory manager when running the benchmarks
 */
int main(int argc, char** argv) {
  benchmark::RegisterMemoryManager(mm.get());
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::RegisterMemoryManager(nullptr);
}
```

### Measuring for Time Complexity (Big O Notation)

```c++
static void BM_memory(benchmark::State& state) {
    for (auto _ : state) {
        int i = 0;
        for ( int i = 0; i < state.range(0); i++ )
            i++;
  }
  state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_memory)
    ->RangeMultiplier(2)
    ->Range(1 << 10, 1 << 15)
    ->Complexity();
```


## Examples
[Google Benchmark Examples](https://github.com/google/benchmark/blob/62edc4fb00e1aeab86cc69c70eafffb17219d047/test)

## Notes
[C++ Benchmark User Guide](https://github.com/google/benchmark/blob/main/docs/user_guide.md#running-benchmarks)
