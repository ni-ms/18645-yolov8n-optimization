#pragma once
#include <immintrin.h>
using V8=__m256;
inline V8 ld(const float* p){return _mm256_loadu_ps(p);}
inline V8 bc(float v){return _mm256_set1_ps(v);}
inline V8 fm(V8 x,V8 w,V8 a){return _mm256_fmadd_ps(x,w,a);}
inline V8 ma(V8 x,V8 w,V8 a){return _mm256_add_ps(_mm256_mul_ps(x,w),a);}
inline void st(float* p,V8 a){_mm256_storeu_ps(p,a);}
