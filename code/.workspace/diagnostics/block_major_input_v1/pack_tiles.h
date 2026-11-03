#pragma once
#include <immintrin.h>
template<int Width> static __attribute__((noinline)) void pack_four_rows(const float* __restrict__ src,float* __restrict__ dst){
 static_assert(Width==16||Width==64,"valid primary panel widths");
 for(int k=0;k<256;k+=4)for(int s=0;s<Width;s+=16){
  __m256 x0_0=_mm256_loadu_ps(src+(k+0)*400+s+0);
  __m256 x0_1=_mm256_loadu_ps(src+(k+0)*400+s+8);
  __m256 x1_0=_mm256_loadu_ps(src+(k+1)*400+s+0);
  __m256 x1_1=_mm256_loadu_ps(src+(k+1)*400+s+8);
  __m256 x2_0=_mm256_loadu_ps(src+(k+2)*400+s+0);
  __m256 x2_1=_mm256_loadu_ps(src+(k+2)*400+s+8);
  __m256 x3_0=_mm256_loadu_ps(src+(k+3)*400+s+0);
  __m256 x3_1=_mm256_loadu_ps(src+(k+3)*400+s+8);
  asm volatile("" : "+x"(x0_0),"+x"(x0_1),"+x"(x1_0),"+x"(x1_1),"+x"(x2_0),"+x"(x2_1),"+x"(x3_0),"+x"(x3_1));
  _mm256_store_ps(dst+(k+0)*80+s+0,x0_0);
  _mm256_store_ps(dst+(k+0)*80+s+8,x0_1);
  _mm256_store_ps(dst+(k+1)*80+s+0,x1_0);
  _mm256_store_ps(dst+(k+1)*80+s+8,x1_1);
  _mm256_store_ps(dst+(k+2)*80+s+0,x2_0);
  _mm256_store_ps(dst+(k+2)*80+s+8,x2_1);
  _mm256_store_ps(dst+(k+3)*80+s+0,x3_0);
  _mm256_store_ps(dst+(k+3)*80+s+8,x3_1);
 }
}
#pragma once
#include <immintrin.h>
template<int Width> static __attribute__((noinline)) void pack_block_major(const float* __restrict__ src,float* __restrict__ dst){
 static_assert(Width==16||Width==64,"valid primary panel widths");
 for(int k=0;k<256;k+=4)for(int s=0;s<Width;s+=16){
  __m256 x0_0=_mm256_loadu_ps(src+(k+0)*400+s+0);
  __m256 x0_1=_mm256_loadu_ps(src+(k+0)*400+s+8);
  __m256 x1_0=_mm256_loadu_ps(src+(k+1)*400+s+0);
  __m256 x1_1=_mm256_loadu_ps(src+(k+1)*400+s+8);
  __m256 x2_0=_mm256_loadu_ps(src+(k+2)*400+s+0);
  __m256 x2_1=_mm256_loadu_ps(src+(k+2)*400+s+8);
  __m256 x3_0=_mm256_loadu_ps(src+(k+3)*400+s+0);
  __m256 x3_1=_mm256_loadu_ps(src+(k+3)*400+s+8);
  asm volatile("" : "+x"(x0_0),"+x"(x0_1),"+x"(x1_0),"+x"(x1_1),"+x"(x2_0),"+x"(x2_1),"+x"(x3_0),"+x"(x3_1));
  _mm256_store_ps(dst+(s/16)*256*16+(k+0)*16+0,x0_0);
  _mm256_store_ps(dst+(s/16)*256*16+(k+0)*16+8,x0_1);
  _mm256_store_ps(dst+(s/16)*256*16+(k+1)*16+0,x1_0);
  _mm256_store_ps(dst+(s/16)*256*16+(k+1)*16+8,x1_1);
  _mm256_store_ps(dst+(s/16)*256*16+(k+2)*16+0,x2_0);
  _mm256_store_ps(dst+(s/16)*256*16+(k+2)*16+8,x2_1);
  _mm256_store_ps(dst+(s/16)*256*16+(k+3)*16+0,x3_0);
  _mm256_store_ps(dst+(s/16)*256*16+(k+3)*16+8,x3_1);
 }
}
