#pragma once
#include <immintrin.h>
#include <cstddef>
template<int M,bool Packed,int U,int C,int XS,int YS,bool PF,bool First,bool Stream=false>
static __attribute__((always_inline)) inline void fixed_tile(const float* __restrict__ x,const float*w,const float*b,float* __restrict__ y,int kb,int ke){
 static_assert(C%U==0,"fixed shapes are unroll divisible");
 if constexpr(M==5){
  __m256 a0_0=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+0*YS+0);
  __m256 a0_1=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+0*YS+8);
  __m256 a1_0=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+1*YS+0);
  __m256 a1_1=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+1*YS+8);
  __m256 a2_0=First?_mm256_set1_ps(b[2]):_mm256_loadu_ps(y+2*YS+0);
  __m256 a2_1=First?_mm256_set1_ps(b[2]):_mm256_loadu_ps(y+2*YS+8);
  __m256 a3_0=First?_mm256_set1_ps(b[3]):_mm256_loadu_ps(y+3*YS+0);
  __m256 a3_1=First?_mm256_set1_ps(b[3]):_mm256_loadu_ps(y+3*YS+8);
  __m256 a4_0=First?_mm256_set1_ps(b[4]):_mm256_loadu_ps(y+4*YS+0);
  __m256 a4_1=First?_mm256_set1_ps(b[4]):_mm256_loadu_ps(y+4*YS+8);
  for(int k=kb;k<ke;k+=U){
   if constexpr(PF)if(k+16<ke)__builtin_prefetch(w+(size_t)(k+16)*M,0,3);
   if constexpr(U>0){
    __m256 x0=_mm256_loadu_ps(x+(size_t)(k+0)*XS+0);
    __m256 x1=_mm256_loadu_ps(x+(size_t)(k+0)*XS+8);
    __m256 q=_mm256_set1_ps(Packed?w[(size_t)(k+0)*M+0]:w[0*C+k+0]);
    a0_0=_mm256_fmadd_ps(x0,q,a0_0);
    a0_1=_mm256_fmadd_ps(x1,q,a0_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+0)*M+1]:w[1*C+k+0]);
    a1_0=_mm256_fmadd_ps(x0,q,a1_0);
    a1_1=_mm256_fmadd_ps(x1,q,a1_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+0)*M+2]:w[2*C+k+0]);
    a2_0=_mm256_fmadd_ps(x0,q,a2_0);
    a2_1=_mm256_fmadd_ps(x1,q,a2_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+0)*M+3]:w[3*C+k+0]);
    a3_0=_mm256_fmadd_ps(x0,q,a3_0);
    a3_1=_mm256_fmadd_ps(x1,q,a3_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+0)*M+4]:w[4*C+k+0]);
    a4_0=_mm256_fmadd_ps(x0,q,a4_0);
    a4_1=_mm256_fmadd_ps(x1,q,a4_1);
   }
   if constexpr(U>1){
    __m256 x0=_mm256_loadu_ps(x+(size_t)(k+1)*XS+0);
    __m256 x1=_mm256_loadu_ps(x+(size_t)(k+1)*XS+8);
    __m256 q=_mm256_set1_ps(Packed?w[(size_t)(k+1)*M+0]:w[0*C+k+1]);
    a0_0=_mm256_fmadd_ps(x0,q,a0_0);
    a0_1=_mm256_fmadd_ps(x1,q,a0_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+1)*M+1]:w[1*C+k+1]);
    a1_0=_mm256_fmadd_ps(x0,q,a1_0);
    a1_1=_mm256_fmadd_ps(x1,q,a1_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+1)*M+2]:w[2*C+k+1]);
    a2_0=_mm256_fmadd_ps(x0,q,a2_0);
    a2_1=_mm256_fmadd_ps(x1,q,a2_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+1)*M+3]:w[3*C+k+1]);
    a3_0=_mm256_fmadd_ps(x0,q,a3_0);
    a3_1=_mm256_fmadd_ps(x1,q,a3_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+1)*M+4]:w[4*C+k+1]);
    a4_0=_mm256_fmadd_ps(x0,q,a4_0);
    a4_1=_mm256_fmadd_ps(x1,q,a4_1);
   }
   if constexpr(U>2){
    __m256 x0=_mm256_loadu_ps(x+(size_t)(k+2)*XS+0);
    __m256 x1=_mm256_loadu_ps(x+(size_t)(k+2)*XS+8);
    __m256 q=_mm256_set1_ps(Packed?w[(size_t)(k+2)*M+0]:w[0*C+k+2]);
    a0_0=_mm256_fmadd_ps(x0,q,a0_0);
    a0_1=_mm256_fmadd_ps(x1,q,a0_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+2)*M+1]:w[1*C+k+2]);
    a1_0=_mm256_fmadd_ps(x0,q,a1_0);
    a1_1=_mm256_fmadd_ps(x1,q,a1_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+2)*M+2]:w[2*C+k+2]);
    a2_0=_mm256_fmadd_ps(x0,q,a2_0);
    a2_1=_mm256_fmadd_ps(x1,q,a2_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+2)*M+3]:w[3*C+k+2]);
    a3_0=_mm256_fmadd_ps(x0,q,a3_0);
    a3_1=_mm256_fmadd_ps(x1,q,a3_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+2)*M+4]:w[4*C+k+2]);
    a4_0=_mm256_fmadd_ps(x0,q,a4_0);
    a4_1=_mm256_fmadd_ps(x1,q,a4_1);
   }
   if constexpr(U>3){
    __m256 x0=_mm256_loadu_ps(x+(size_t)(k+3)*XS+0);
    __m256 x1=_mm256_loadu_ps(x+(size_t)(k+3)*XS+8);
    __m256 q=_mm256_set1_ps(Packed?w[(size_t)(k+3)*M+0]:w[0*C+k+3]);
    a0_0=_mm256_fmadd_ps(x0,q,a0_0);
    a0_1=_mm256_fmadd_ps(x1,q,a0_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+3)*M+1]:w[1*C+k+3]);
    a1_0=_mm256_fmadd_ps(x0,q,a1_0);
    a1_1=_mm256_fmadd_ps(x1,q,a1_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+3)*M+2]:w[2*C+k+3]);
    a2_0=_mm256_fmadd_ps(x0,q,a2_0);
    a2_1=_mm256_fmadd_ps(x1,q,a2_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+3)*M+3]:w[3*C+k+3]);
    a3_0=_mm256_fmadd_ps(x0,q,a3_0);
    a3_1=_mm256_fmadd_ps(x1,q,a3_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+3)*M+4]:w[4*C+k+3]);
    a4_0=_mm256_fmadd_ps(x0,q,a4_0);
    a4_1=_mm256_fmadd_ps(x1,q,a4_1);
   }
   if constexpr(U>4){
    __m256 x0=_mm256_loadu_ps(x+(size_t)(k+4)*XS+0);
    __m256 x1=_mm256_loadu_ps(x+(size_t)(k+4)*XS+8);
    __m256 q=_mm256_set1_ps(Packed?w[(size_t)(k+4)*M+0]:w[0*C+k+4]);
    a0_0=_mm256_fmadd_ps(x0,q,a0_0);
    a0_1=_mm256_fmadd_ps(x1,q,a0_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+4)*M+1]:w[1*C+k+4]);
    a1_0=_mm256_fmadd_ps(x0,q,a1_0);
    a1_1=_mm256_fmadd_ps(x1,q,a1_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+4)*M+2]:w[2*C+k+4]);
    a2_0=_mm256_fmadd_ps(x0,q,a2_0);
    a2_1=_mm256_fmadd_ps(x1,q,a2_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+4)*M+3]:w[3*C+k+4]);
    a3_0=_mm256_fmadd_ps(x0,q,a3_0);
    a3_1=_mm256_fmadd_ps(x1,q,a3_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+4)*M+4]:w[4*C+k+4]);
    a4_0=_mm256_fmadd_ps(x0,q,a4_0);
    a4_1=_mm256_fmadd_ps(x1,q,a4_1);
   }
   if constexpr(U>5){
    __m256 x0=_mm256_loadu_ps(x+(size_t)(k+5)*XS+0);
    __m256 x1=_mm256_loadu_ps(x+(size_t)(k+5)*XS+8);
    __m256 q=_mm256_set1_ps(Packed?w[(size_t)(k+5)*M+0]:w[0*C+k+5]);
    a0_0=_mm256_fmadd_ps(x0,q,a0_0);
    a0_1=_mm256_fmadd_ps(x1,q,a0_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+5)*M+1]:w[1*C+k+5]);
    a1_0=_mm256_fmadd_ps(x0,q,a1_0);
    a1_1=_mm256_fmadd_ps(x1,q,a1_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+5)*M+2]:w[2*C+k+5]);
    a2_0=_mm256_fmadd_ps(x0,q,a2_0);
    a2_1=_mm256_fmadd_ps(x1,q,a2_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+5)*M+3]:w[3*C+k+5]);
    a3_0=_mm256_fmadd_ps(x0,q,a3_0);
    a3_1=_mm256_fmadd_ps(x1,q,a3_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+5)*M+4]:w[4*C+k+5]);
    a4_0=_mm256_fmadd_ps(x0,q,a4_0);
    a4_1=_mm256_fmadd_ps(x1,q,a4_1);
   }
   if constexpr(U>6){
    __m256 x0=_mm256_loadu_ps(x+(size_t)(k+6)*XS+0);
    __m256 x1=_mm256_loadu_ps(x+(size_t)(k+6)*XS+8);
    __m256 q=_mm256_set1_ps(Packed?w[(size_t)(k+6)*M+0]:w[0*C+k+6]);
    a0_0=_mm256_fmadd_ps(x0,q,a0_0);
    a0_1=_mm256_fmadd_ps(x1,q,a0_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+6)*M+1]:w[1*C+k+6]);
    a1_0=_mm256_fmadd_ps(x0,q,a1_0);
    a1_1=_mm256_fmadd_ps(x1,q,a1_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+6)*M+2]:w[2*C+k+6]);
    a2_0=_mm256_fmadd_ps(x0,q,a2_0);
    a2_1=_mm256_fmadd_ps(x1,q,a2_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+6)*M+3]:w[3*C+k+6]);
    a3_0=_mm256_fmadd_ps(x0,q,a3_0);
    a3_1=_mm256_fmadd_ps(x1,q,a3_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+6)*M+4]:w[4*C+k+6]);
    a4_0=_mm256_fmadd_ps(x0,q,a4_0);
    a4_1=_mm256_fmadd_ps(x1,q,a4_1);
   }
   if constexpr(U>7){
    __m256 x0=_mm256_loadu_ps(x+(size_t)(k+7)*XS+0);
    __m256 x1=_mm256_loadu_ps(x+(size_t)(k+7)*XS+8);
    __m256 q=_mm256_set1_ps(Packed?w[(size_t)(k+7)*M+0]:w[0*C+k+7]);
    a0_0=_mm256_fmadd_ps(x0,q,a0_0);
    a0_1=_mm256_fmadd_ps(x1,q,a0_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+7)*M+1]:w[1*C+k+7]);
    a1_0=_mm256_fmadd_ps(x0,q,a1_0);
    a1_1=_mm256_fmadd_ps(x1,q,a1_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+7)*M+2]:w[2*C+k+7]);
    a2_0=_mm256_fmadd_ps(x0,q,a2_0);
    a2_1=_mm256_fmadd_ps(x1,q,a2_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+7)*M+3]:w[3*C+k+7]);
    a3_0=_mm256_fmadd_ps(x0,q,a3_0);
    a3_1=_mm256_fmadd_ps(x1,q,a3_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+7)*M+4]:w[4*C+k+7]);
    a4_0=_mm256_fmadd_ps(x0,q,a4_0);
    a4_1=_mm256_fmadd_ps(x1,q,a4_1);
   }
  }
  if constexpr(Stream)_mm256_stream_ps(y+0*YS+0,a0_0);else _mm256_storeu_ps(y+0*YS+0,a0_0);
  if constexpr(Stream)_mm256_stream_ps(y+0*YS+8,a0_1);else _mm256_storeu_ps(y+0*YS+8,a0_1);
  if constexpr(Stream)_mm256_stream_ps(y+1*YS+0,a1_0);else _mm256_storeu_ps(y+1*YS+0,a1_0);
  if constexpr(Stream)_mm256_stream_ps(y+1*YS+8,a1_1);else _mm256_storeu_ps(y+1*YS+8,a1_1);
  if constexpr(Stream)_mm256_stream_ps(y+2*YS+0,a2_0);else _mm256_storeu_ps(y+2*YS+0,a2_0);
  if constexpr(Stream)_mm256_stream_ps(y+2*YS+8,a2_1);else _mm256_storeu_ps(y+2*YS+8,a2_1);
  if constexpr(Stream)_mm256_stream_ps(y+3*YS+0,a3_0);else _mm256_storeu_ps(y+3*YS+0,a3_0);
  if constexpr(Stream)_mm256_stream_ps(y+3*YS+8,a3_1);else _mm256_storeu_ps(y+3*YS+8,a3_1);
  if constexpr(Stream)_mm256_stream_ps(y+4*YS+0,a4_0);else _mm256_storeu_ps(y+4*YS+0,a4_0);
  if constexpr(Stream)_mm256_stream_ps(y+4*YS+8,a4_1);else _mm256_storeu_ps(y+4*YS+8,a4_1);
 }
 if constexpr(M==6){
  __m256 a0_0=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+0*YS+0);
  __m256 a0_1=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+0*YS+8);
  __m256 a1_0=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+1*YS+0);
  __m256 a1_1=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+1*YS+8);
  __m256 a2_0=First?_mm256_set1_ps(b[2]):_mm256_loadu_ps(y+2*YS+0);
  __m256 a2_1=First?_mm256_set1_ps(b[2]):_mm256_loadu_ps(y+2*YS+8);
  __m256 a3_0=First?_mm256_set1_ps(b[3]):_mm256_loadu_ps(y+3*YS+0);
  __m256 a3_1=First?_mm256_set1_ps(b[3]):_mm256_loadu_ps(y+3*YS+8);
  __m256 a4_0=First?_mm256_set1_ps(b[4]):_mm256_loadu_ps(y+4*YS+0);
  __m256 a4_1=First?_mm256_set1_ps(b[4]):_mm256_loadu_ps(y+4*YS+8);
  __m256 a5_0=First?_mm256_set1_ps(b[5]):_mm256_loadu_ps(y+5*YS+0);
  __m256 a5_1=First?_mm256_set1_ps(b[5]):_mm256_loadu_ps(y+5*YS+8);
  for(int k=kb;k<ke;k+=U){
   if constexpr(PF)if(k+16<ke)__builtin_prefetch(w+(size_t)(k+16)*M,0,3);
   if constexpr(U>0){
    __m256 x0=_mm256_loadu_ps(x+(size_t)(k+0)*XS+0);
    __m256 x1=_mm256_loadu_ps(x+(size_t)(k+0)*XS+8);
    __m256 q=_mm256_set1_ps(Packed?w[(size_t)(k+0)*M+0]:w[0*C+k+0]);
    a0_0=_mm256_fmadd_ps(x0,q,a0_0);
    a0_1=_mm256_fmadd_ps(x1,q,a0_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+0)*M+1]:w[1*C+k+0]);
    a1_0=_mm256_fmadd_ps(x0,q,a1_0);
    a1_1=_mm256_fmadd_ps(x1,q,a1_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+0)*M+2]:w[2*C+k+0]);
    a2_0=_mm256_fmadd_ps(x0,q,a2_0);
    a2_1=_mm256_fmadd_ps(x1,q,a2_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+0)*M+3]:w[3*C+k+0]);
    a3_0=_mm256_fmadd_ps(x0,q,a3_0);
    a3_1=_mm256_fmadd_ps(x1,q,a3_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+0)*M+4]:w[4*C+k+0]);
    a4_0=_mm256_fmadd_ps(x0,q,a4_0);
    a4_1=_mm256_fmadd_ps(x1,q,a4_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+0)*M+5]:w[5*C+k+0]);
    a5_0=_mm256_fmadd_ps(x0,q,a5_0);
    a5_1=_mm256_fmadd_ps(x1,q,a5_1);
   }
   if constexpr(U>1){
    __m256 x0=_mm256_loadu_ps(x+(size_t)(k+1)*XS+0);
    __m256 x1=_mm256_loadu_ps(x+(size_t)(k+1)*XS+8);
    __m256 q=_mm256_set1_ps(Packed?w[(size_t)(k+1)*M+0]:w[0*C+k+1]);
    a0_0=_mm256_fmadd_ps(x0,q,a0_0);
    a0_1=_mm256_fmadd_ps(x1,q,a0_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+1)*M+1]:w[1*C+k+1]);
    a1_0=_mm256_fmadd_ps(x0,q,a1_0);
    a1_1=_mm256_fmadd_ps(x1,q,a1_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+1)*M+2]:w[2*C+k+1]);
    a2_0=_mm256_fmadd_ps(x0,q,a2_0);
    a2_1=_mm256_fmadd_ps(x1,q,a2_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+1)*M+3]:w[3*C+k+1]);
    a3_0=_mm256_fmadd_ps(x0,q,a3_0);
    a3_1=_mm256_fmadd_ps(x1,q,a3_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+1)*M+4]:w[4*C+k+1]);
    a4_0=_mm256_fmadd_ps(x0,q,a4_0);
    a4_1=_mm256_fmadd_ps(x1,q,a4_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+1)*M+5]:w[5*C+k+1]);
    a5_0=_mm256_fmadd_ps(x0,q,a5_0);
    a5_1=_mm256_fmadd_ps(x1,q,a5_1);
   }
   if constexpr(U>2){
    __m256 x0=_mm256_loadu_ps(x+(size_t)(k+2)*XS+0);
    __m256 x1=_mm256_loadu_ps(x+(size_t)(k+2)*XS+8);
    __m256 q=_mm256_set1_ps(Packed?w[(size_t)(k+2)*M+0]:w[0*C+k+2]);
    a0_0=_mm256_fmadd_ps(x0,q,a0_0);
    a0_1=_mm256_fmadd_ps(x1,q,a0_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+2)*M+1]:w[1*C+k+2]);
    a1_0=_mm256_fmadd_ps(x0,q,a1_0);
    a1_1=_mm256_fmadd_ps(x1,q,a1_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+2)*M+2]:w[2*C+k+2]);
    a2_0=_mm256_fmadd_ps(x0,q,a2_0);
    a2_1=_mm256_fmadd_ps(x1,q,a2_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+2)*M+3]:w[3*C+k+2]);
    a3_0=_mm256_fmadd_ps(x0,q,a3_0);
    a3_1=_mm256_fmadd_ps(x1,q,a3_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+2)*M+4]:w[4*C+k+2]);
    a4_0=_mm256_fmadd_ps(x0,q,a4_0);
    a4_1=_mm256_fmadd_ps(x1,q,a4_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+2)*M+5]:w[5*C+k+2]);
    a5_0=_mm256_fmadd_ps(x0,q,a5_0);
    a5_1=_mm256_fmadd_ps(x1,q,a5_1);
   }
   if constexpr(U>3){
    __m256 x0=_mm256_loadu_ps(x+(size_t)(k+3)*XS+0);
    __m256 x1=_mm256_loadu_ps(x+(size_t)(k+3)*XS+8);
    __m256 q=_mm256_set1_ps(Packed?w[(size_t)(k+3)*M+0]:w[0*C+k+3]);
    a0_0=_mm256_fmadd_ps(x0,q,a0_0);
    a0_1=_mm256_fmadd_ps(x1,q,a0_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+3)*M+1]:w[1*C+k+3]);
    a1_0=_mm256_fmadd_ps(x0,q,a1_0);
    a1_1=_mm256_fmadd_ps(x1,q,a1_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+3)*M+2]:w[2*C+k+3]);
    a2_0=_mm256_fmadd_ps(x0,q,a2_0);
    a2_1=_mm256_fmadd_ps(x1,q,a2_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+3)*M+3]:w[3*C+k+3]);
    a3_0=_mm256_fmadd_ps(x0,q,a3_0);
    a3_1=_mm256_fmadd_ps(x1,q,a3_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+3)*M+4]:w[4*C+k+3]);
    a4_0=_mm256_fmadd_ps(x0,q,a4_0);
    a4_1=_mm256_fmadd_ps(x1,q,a4_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+3)*M+5]:w[5*C+k+3]);
    a5_0=_mm256_fmadd_ps(x0,q,a5_0);
    a5_1=_mm256_fmadd_ps(x1,q,a5_1);
   }
   if constexpr(U>4){
    __m256 x0=_mm256_loadu_ps(x+(size_t)(k+4)*XS+0);
    __m256 x1=_mm256_loadu_ps(x+(size_t)(k+4)*XS+8);
    __m256 q=_mm256_set1_ps(Packed?w[(size_t)(k+4)*M+0]:w[0*C+k+4]);
    a0_0=_mm256_fmadd_ps(x0,q,a0_0);
    a0_1=_mm256_fmadd_ps(x1,q,a0_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+4)*M+1]:w[1*C+k+4]);
    a1_0=_mm256_fmadd_ps(x0,q,a1_0);
    a1_1=_mm256_fmadd_ps(x1,q,a1_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+4)*M+2]:w[2*C+k+4]);
    a2_0=_mm256_fmadd_ps(x0,q,a2_0);
    a2_1=_mm256_fmadd_ps(x1,q,a2_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+4)*M+3]:w[3*C+k+4]);
    a3_0=_mm256_fmadd_ps(x0,q,a3_0);
    a3_1=_mm256_fmadd_ps(x1,q,a3_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+4)*M+4]:w[4*C+k+4]);
    a4_0=_mm256_fmadd_ps(x0,q,a4_0);
    a4_1=_mm256_fmadd_ps(x1,q,a4_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+4)*M+5]:w[5*C+k+4]);
    a5_0=_mm256_fmadd_ps(x0,q,a5_0);
    a5_1=_mm256_fmadd_ps(x1,q,a5_1);
   }
   if constexpr(U>5){
    __m256 x0=_mm256_loadu_ps(x+(size_t)(k+5)*XS+0);
    __m256 x1=_mm256_loadu_ps(x+(size_t)(k+5)*XS+8);
    __m256 q=_mm256_set1_ps(Packed?w[(size_t)(k+5)*M+0]:w[0*C+k+5]);
    a0_0=_mm256_fmadd_ps(x0,q,a0_0);
    a0_1=_mm256_fmadd_ps(x1,q,a0_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+5)*M+1]:w[1*C+k+5]);
    a1_0=_mm256_fmadd_ps(x0,q,a1_0);
    a1_1=_mm256_fmadd_ps(x1,q,a1_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+5)*M+2]:w[2*C+k+5]);
    a2_0=_mm256_fmadd_ps(x0,q,a2_0);
    a2_1=_mm256_fmadd_ps(x1,q,a2_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+5)*M+3]:w[3*C+k+5]);
    a3_0=_mm256_fmadd_ps(x0,q,a3_0);
    a3_1=_mm256_fmadd_ps(x1,q,a3_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+5)*M+4]:w[4*C+k+5]);
    a4_0=_mm256_fmadd_ps(x0,q,a4_0);
    a4_1=_mm256_fmadd_ps(x1,q,a4_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+5)*M+5]:w[5*C+k+5]);
    a5_0=_mm256_fmadd_ps(x0,q,a5_0);
    a5_1=_mm256_fmadd_ps(x1,q,a5_1);
   }
   if constexpr(U>6){
    __m256 x0=_mm256_loadu_ps(x+(size_t)(k+6)*XS+0);
    __m256 x1=_mm256_loadu_ps(x+(size_t)(k+6)*XS+8);
    __m256 q=_mm256_set1_ps(Packed?w[(size_t)(k+6)*M+0]:w[0*C+k+6]);
    a0_0=_mm256_fmadd_ps(x0,q,a0_0);
    a0_1=_mm256_fmadd_ps(x1,q,a0_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+6)*M+1]:w[1*C+k+6]);
    a1_0=_mm256_fmadd_ps(x0,q,a1_0);
    a1_1=_mm256_fmadd_ps(x1,q,a1_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+6)*M+2]:w[2*C+k+6]);
    a2_0=_mm256_fmadd_ps(x0,q,a2_0);
    a2_1=_mm256_fmadd_ps(x1,q,a2_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+6)*M+3]:w[3*C+k+6]);
    a3_0=_mm256_fmadd_ps(x0,q,a3_0);
    a3_1=_mm256_fmadd_ps(x1,q,a3_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+6)*M+4]:w[4*C+k+6]);
    a4_0=_mm256_fmadd_ps(x0,q,a4_0);
    a4_1=_mm256_fmadd_ps(x1,q,a4_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+6)*M+5]:w[5*C+k+6]);
    a5_0=_mm256_fmadd_ps(x0,q,a5_0);
    a5_1=_mm256_fmadd_ps(x1,q,a5_1);
   }
   if constexpr(U>7){
    __m256 x0=_mm256_loadu_ps(x+(size_t)(k+7)*XS+0);
    __m256 x1=_mm256_loadu_ps(x+(size_t)(k+7)*XS+8);
    __m256 q=_mm256_set1_ps(Packed?w[(size_t)(k+7)*M+0]:w[0*C+k+7]);
    a0_0=_mm256_fmadd_ps(x0,q,a0_0);
    a0_1=_mm256_fmadd_ps(x1,q,a0_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+7)*M+1]:w[1*C+k+7]);
    a1_0=_mm256_fmadd_ps(x0,q,a1_0);
    a1_1=_mm256_fmadd_ps(x1,q,a1_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+7)*M+2]:w[2*C+k+7]);
    a2_0=_mm256_fmadd_ps(x0,q,a2_0);
    a2_1=_mm256_fmadd_ps(x1,q,a2_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+7)*M+3]:w[3*C+k+7]);
    a3_0=_mm256_fmadd_ps(x0,q,a3_0);
    a3_1=_mm256_fmadd_ps(x1,q,a3_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+7)*M+4]:w[4*C+k+7]);
    a4_0=_mm256_fmadd_ps(x0,q,a4_0);
    a4_1=_mm256_fmadd_ps(x1,q,a4_1);
    q=_mm256_set1_ps(Packed?w[(size_t)(k+7)*M+5]:w[5*C+k+7]);
    a5_0=_mm256_fmadd_ps(x0,q,a5_0);
    a5_1=_mm256_fmadd_ps(x1,q,a5_1);
   }
  }
  if constexpr(Stream)_mm256_stream_ps(y+0*YS+0,a0_0);else _mm256_storeu_ps(y+0*YS+0,a0_0);
  if constexpr(Stream)_mm256_stream_ps(y+0*YS+8,a0_1);else _mm256_storeu_ps(y+0*YS+8,a0_1);
  if constexpr(Stream)_mm256_stream_ps(y+1*YS+0,a1_0);else _mm256_storeu_ps(y+1*YS+0,a1_0);
  if constexpr(Stream)_mm256_stream_ps(y+1*YS+8,a1_1);else _mm256_storeu_ps(y+1*YS+8,a1_1);
  if constexpr(Stream)_mm256_stream_ps(y+2*YS+0,a2_0);else _mm256_storeu_ps(y+2*YS+0,a2_0);
  if constexpr(Stream)_mm256_stream_ps(y+2*YS+8,a2_1);else _mm256_storeu_ps(y+2*YS+8,a2_1);
  if constexpr(Stream)_mm256_stream_ps(y+3*YS+0,a3_0);else _mm256_storeu_ps(y+3*YS+0,a3_0);
  if constexpr(Stream)_mm256_stream_ps(y+3*YS+8,a3_1);else _mm256_storeu_ps(y+3*YS+8,a3_1);
  if constexpr(Stream)_mm256_stream_ps(y+4*YS+0,a4_0);else _mm256_storeu_ps(y+4*YS+0,a4_0);
  if constexpr(Stream)_mm256_stream_ps(y+4*YS+8,a4_1);else _mm256_storeu_ps(y+4*YS+8,a4_1);
  if constexpr(Stream)_mm256_stream_ps(y+5*YS+0,a5_0);else _mm256_storeu_ps(y+5*YS+0,a5_0);
  if constexpr(Stream)_mm256_stream_ps(y+5*YS+8,a5_1);else _mm256_storeu_ps(y+5*YS+8,a5_1);
 }
}
