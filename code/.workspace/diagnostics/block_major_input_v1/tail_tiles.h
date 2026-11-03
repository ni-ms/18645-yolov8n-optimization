#pragma once
#include <immintrin.h>
#include <cstddef>
template<int N,bool Force,int C,int XS,int YS>
static __attribute__((always_inline)) inline void tail_tile(const float* __restrict__ x,const float*w,const float*b,float* __restrict__ y){
 if constexpr(N==2){
  __m256 a0_0=_mm256_loadu_ps(b+0);
  __m256 a0_1=_mm256_loadu_ps(b+8);
  __m256 a1_0=_mm256_loadu_ps(b+0);
  __m256 a1_1=_mm256_loadu_ps(b+8);
  __m256 a2_0=_mm256_loadu_ps(b+0);
  __m256 a2_1=_mm256_loadu_ps(b+8);
  __m256 a3_0=_mm256_loadu_ps(b+0);
  __m256 a3_1=_mm256_loadu_ps(b+8);
  for(int k=0;k<C;++k){
   __m256 q0=_mm256_loadu_ps(w+((size_t)0*C+k)*8);
   __m256 q1=_mm256_loadu_ps(w+((size_t)1*C+k)*8);
   if constexpr(Force){__asm__ __volatile__("" : "+x"(q0),"+x"(q1));}
   __m256 xx0=_mm256_set1_ps(x[(size_t)k*XS+0]);
   a0_0=_mm256_fmadd_ps(q0,xx0,a0_0);
   a0_1=_mm256_fmadd_ps(q1,xx0,a0_1);
   __m256 xx1=_mm256_set1_ps(x[(size_t)k*XS+1]);
   a1_0=_mm256_fmadd_ps(q0,xx1,a1_0);
   a1_1=_mm256_fmadd_ps(q1,xx1,a1_1);
   __m256 xx2=_mm256_set1_ps(x[(size_t)k*XS+2]);
   a2_0=_mm256_fmadd_ps(q0,xx2,a2_0);
   a2_1=_mm256_fmadd_ps(q1,xx2,a2_1);
   __m256 xx3=_mm256_set1_ps(x[(size_t)k*XS+3]);
   a3_0=_mm256_fmadd_ps(q0,xx3,a3_0);
   a3_1=_mm256_fmadd_ps(q1,xx3,a3_1);
  }
  alignas(32) float temporary[4][16];
  _mm256_store_ps(temporary[0]+0,a0_0);
  _mm256_store_ps(temporary[0]+8,a0_1);
  _mm256_store_ps(temporary[1]+0,a1_0);
  _mm256_store_ps(temporary[1]+8,a1_1);
  _mm256_store_ps(temporary[2]+0,a2_0);
  _mm256_store_ps(temporary[2]+8,a2_1);
  _mm256_store_ps(temporary[3]+0,a3_0);
  _mm256_store_ps(temporary[3]+8,a3_1);
  for(int m=0;m<16;++m)for(int j=0;j<4;++j)y[(size_t)m*YS+j]=temporary[j][m];
 }
 if constexpr(N==3){
  __m256 a0_0=_mm256_loadu_ps(b+0);
  __m256 a0_1=_mm256_loadu_ps(b+8);
  __m256 a0_2=_mm256_loadu_ps(b+16);
  __m256 a1_0=_mm256_loadu_ps(b+0);
  __m256 a1_1=_mm256_loadu_ps(b+8);
  __m256 a1_2=_mm256_loadu_ps(b+16);
  __m256 a2_0=_mm256_loadu_ps(b+0);
  __m256 a2_1=_mm256_loadu_ps(b+8);
  __m256 a2_2=_mm256_loadu_ps(b+16);
  __m256 a3_0=_mm256_loadu_ps(b+0);
  __m256 a3_1=_mm256_loadu_ps(b+8);
  __m256 a3_2=_mm256_loadu_ps(b+16);
  for(int k=0;k<C;++k){
   __m256 q0=_mm256_loadu_ps(w+((size_t)0*C+k)*8);
   __m256 q1=_mm256_loadu_ps(w+((size_t)1*C+k)*8);
   __m256 q2=_mm256_loadu_ps(w+((size_t)2*C+k)*8);
   if constexpr(Force){__asm__ __volatile__("" : "+x"(q0),"+x"(q1),"+x"(q2));}
   __m256 xx0=_mm256_set1_ps(x[(size_t)k*XS+0]);
   a0_0=_mm256_fmadd_ps(q0,xx0,a0_0);
   a0_1=_mm256_fmadd_ps(q1,xx0,a0_1);
   a0_2=_mm256_fmadd_ps(q2,xx0,a0_2);
   __m256 xx1=_mm256_set1_ps(x[(size_t)k*XS+1]);
   a1_0=_mm256_fmadd_ps(q0,xx1,a1_0);
   a1_1=_mm256_fmadd_ps(q1,xx1,a1_1);
   a1_2=_mm256_fmadd_ps(q2,xx1,a1_2);
   __m256 xx2=_mm256_set1_ps(x[(size_t)k*XS+2]);
   a2_0=_mm256_fmadd_ps(q0,xx2,a2_0);
   a2_1=_mm256_fmadd_ps(q1,xx2,a2_1);
   a2_2=_mm256_fmadd_ps(q2,xx2,a2_2);
   __m256 xx3=_mm256_set1_ps(x[(size_t)k*XS+3]);
   a3_0=_mm256_fmadd_ps(q0,xx3,a3_0);
   a3_1=_mm256_fmadd_ps(q1,xx3,a3_1);
   a3_2=_mm256_fmadd_ps(q2,xx3,a3_2);
  }
  alignas(32) float temporary[4][24];
  _mm256_store_ps(temporary[0]+0,a0_0);
  _mm256_store_ps(temporary[0]+8,a0_1);
  _mm256_store_ps(temporary[0]+16,a0_2);
  _mm256_store_ps(temporary[1]+0,a1_0);
  _mm256_store_ps(temporary[1]+8,a1_1);
  _mm256_store_ps(temporary[1]+16,a1_2);
  _mm256_store_ps(temporary[2]+0,a2_0);
  _mm256_store_ps(temporary[2]+8,a2_1);
  _mm256_store_ps(temporary[2]+16,a2_2);
  _mm256_store_ps(temporary[3]+0,a3_0);
  _mm256_store_ps(temporary[3]+8,a3_1);
  _mm256_store_ps(temporary[3]+16,a3_2);
  for(int m=0;m<24;++m)for(int j=0;j<4;++j)y[(size_t)m*YS+j]=temporary[j][m];
 }
}
