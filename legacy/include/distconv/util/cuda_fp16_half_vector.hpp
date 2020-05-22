#ifndef __CUDA_FP16_HALF_VECTOR_H__
#define __CUDA_FP16_HALF_VECTOR_H__

#include <cuda_fp16.hpp>

#if defined(__CUDACC__)
#define __CUDA_HOST_DEVICE__ __host__ __device__
#define __CUDA_ALIGN__(align) __align__(align)

#else // __CUDACC__
#define __CUDA_HOST_DEVICE__
#define __CUDA_ALIGN__(n) alignas(n)

#endif // __CUDACC__

#define __HALF2_TO_UI(var) *(reinterpret_cast<unsigned int *>(&(var)))
#define __HALF2_TO_CUI(var) *(reinterpret_cast<const unsigned int *>(&(var)))
#define __HALF4_TO_UL(var) *(reinterpret_cast<unsigned long *>(&(var)))
#define __HALF4_TO_CUL(var) *(reinterpret_cast<const unsigned long *>(&(var)))

typedef struct __CUDA_ALIGN__(4) {
  unsigned short x, y;
} __dc_half2_raw;

typedef struct __CUDA_ALIGN__(8) {
  unsigned short x, y, z, w;
} __dc_half4_raw;

struct __CUDA_ALIGN__(4) __dc_half2 {
  __half x, y;

public:
  __dc_half2() = default;
  __CUDA_HOST_DEVICE__ __dc_half2(__dc_half2 &&src) { __HALF2_TO_UI(*this) = std::move(__HALF2_TO_CUI(src)); }
  __CUDA_HOST_DEVICE__ __dc_half2 &operator=(__dc_half2 &&src) { __HALF2_TO_UI(*this) = std::move(__HALF2_TO_CUI(src)); return *this; }
  __CUDA_HOST_DEVICE__ __dc_half2(const __half &a, const __half &b) : x(a), y(b) { }
  __CUDA_HOST_DEVICE__ __dc_half2(const __dc_half2 &src) { __HALF2_TO_UI(*this) = __HALF2_TO_CUI(src); }
  __CUDA_HOST_DEVICE__ __dc_half2 &operator=(const __dc_half2 &src) { __HALF2_TO_UI(*this) = __HALF2_TO_CUI(src); return *this; }
  __CUDA_HOST_DEVICE__ __dc_half2(const __dc_half2_raw &h2r ) { __HALF2_TO_UI(*this) = __HALF2_TO_CUI(h2r); }
  __CUDA_HOST_DEVICE__ __dc_half2 &operator=(const __dc_half2_raw &h2r) { __HALF2_TO_UI(*this) = __HALF2_TO_CUI(h2r); return *this; }
  __CUDA_HOST_DEVICE__ operator __dc_half2_raw() const { __dc_half2_raw ret; __HALF2_TO_UI(ret) = __HALF2_TO_CUI(*this); return ret; }
};

struct __CUDA_ALIGN__(8) __dc_half4 {
  __half x, y, z, w;

public:
  __dc_half4() = default;
  __CUDA_HOST_DEVICE__ __dc_half4(__dc_half4 &&src) { __HALF4_TO_UL(*this) = std::move(__HALF4_TO_CUL(src)); }
  __CUDA_HOST_DEVICE__ __dc_half4 &operator=(__dc_half4 &&src) { __HALF4_TO_UL(*this) = std::move(__HALF4_TO_CUL(src)); return *this; }
  __CUDA_HOST_DEVICE__ __dc_half4(const __half &a, const __half &b, const __half &c, const __half &d) : x(a), y(b), z(c), w(d) { }
  __CUDA_HOST_DEVICE__ __dc_half4(const __dc_half4 &src) { __HALF4_TO_UL(*this) = __HALF4_TO_CUL(src); }
  __CUDA_HOST_DEVICE__ __dc_half4 &operator=(const __dc_half4 &src) { __HALF4_TO_UL(*this) = __HALF4_TO_CUL(src); return *this; }
  __CUDA_HOST_DEVICE__ __dc_half4(const __dc_half4_raw &h2r ) { __HALF4_TO_UL(*this) = __HALF4_TO_CUL(h2r); }
  __CUDA_HOST_DEVICE__ __dc_half4 &operator=(const __dc_half4_raw &h2r) { __HALF4_TO_UL(*this) = __HALF4_TO_CUL(h2r); return *this; }
  __CUDA_HOST_DEVICE__ operator __dc_half4_raw() const { __dc_half4_raw ret; __HALF4_TO_UL(ret) = __HALF4_TO_CUL(*this); return ret; }
};

#if defined(__CUDACC__)
static __inline__ __host__ __device__ __dc_half2 make_dc_half2(__half x, __half y) {
  __dc_half2 t; t.x = x; t.y = y; return t;
}
static __inline__ __host__ __device__ __dc_half4 make_dc_half4(__half x, __half y, __half z, __half w) {
  __dc_half4 t; t.x = x; t.y = y; t.z = z; t.w = w; return t;
}
#endif // __CUDACC__

typedef __dc_half2 dc_half2;
typedef __dc_half4 dc_half4;

#undef __CUDA_HOST_DEVICE__
#undef __CUDA_ALIGN__

#endif
