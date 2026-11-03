#pragma once
#include <immintrin.h>
#include <cstddef>
template<int M,int V,bool Packed,bool First> static __attribute__((always_inline)) inline void fresh_tile(const float* __restrict__ x,const float*w,const float*b,float* __restrict__ y,int C,int XS,int YS,int kb,int ke){
 if constexpr(M==1&&V==1){
  __m256 a0_0=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+0);
  for(int k=kb;k<ke;++k){
   __m256 x0=_mm256_loadu_ps(x+(size_t)k*XS+0);
   __m256 q0=_mm256_set1_ps(Packed?w[(size_t)k*5+0]:w[(size_t)0*C+k]);
   a0_0=_mm256_fmadd_ps(x0,q0,a0_0);
  }
  _mm256_storeu_ps(y+(size_t)0*YS+0,a0_0);
 }
 if constexpr(M==1&&V==2){
  __m256 a0_0=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+0);
  __m256 a0_1=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+8);
  for(int k=kb;k<ke;++k){
   __m256 x0=_mm256_loadu_ps(x+(size_t)k*XS+0);
   __m256 x1=_mm256_loadu_ps(x+(size_t)k*XS+8);
   __m256 q0=_mm256_set1_ps(Packed?w[(size_t)k*5+0]:w[(size_t)0*C+k]);
   a0_0=_mm256_fmadd_ps(x0,q0,a0_0);
   a0_1=_mm256_fmadd_ps(x1,q0,a0_1);
  }
  _mm256_storeu_ps(y+(size_t)0*YS+0,a0_0);
  _mm256_storeu_ps(y+(size_t)0*YS+8,a0_1);
 }
 if constexpr(M==2&&V==1){
  __m256 a0_0=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+0);
  __m256 a1_0=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+(size_t)1*YS+0);
  for(int k=kb;k<ke;++k){
   __m256 x0=_mm256_loadu_ps(x+(size_t)k*XS+0);
   __m256 q0=_mm256_set1_ps(Packed?w[(size_t)k*5+0]:w[(size_t)0*C+k]);
   a0_0=_mm256_fmadd_ps(x0,q0,a0_0);
   __m256 q1=_mm256_set1_ps(Packed?w[(size_t)k*5+1]:w[(size_t)1*C+k]);
   a1_0=_mm256_fmadd_ps(x0,q1,a1_0);
  }
  _mm256_storeu_ps(y+(size_t)0*YS+0,a0_0);
  _mm256_storeu_ps(y+(size_t)1*YS+0,a1_0);
 }
 if constexpr(M==2&&V==2){
  __m256 a0_0=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+0);
  __m256 a0_1=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+8);
  __m256 a1_0=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+(size_t)1*YS+0);
  __m256 a1_1=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+(size_t)1*YS+8);
  for(int k=kb;k<ke;++k){
   __m256 x0=_mm256_loadu_ps(x+(size_t)k*XS+0);
   __m256 x1=_mm256_loadu_ps(x+(size_t)k*XS+8);
   __m256 q0=_mm256_set1_ps(Packed?w[(size_t)k*5+0]:w[(size_t)0*C+k]);
   a0_0=_mm256_fmadd_ps(x0,q0,a0_0);
   a0_1=_mm256_fmadd_ps(x1,q0,a0_1);
   __m256 q1=_mm256_set1_ps(Packed?w[(size_t)k*5+1]:w[(size_t)1*C+k]);
   a1_0=_mm256_fmadd_ps(x0,q1,a1_0);
   a1_1=_mm256_fmadd_ps(x1,q1,a1_1);
  }
  _mm256_storeu_ps(y+(size_t)0*YS+0,a0_0);
  _mm256_storeu_ps(y+(size_t)0*YS+8,a0_1);
  _mm256_storeu_ps(y+(size_t)1*YS+0,a1_0);
  _mm256_storeu_ps(y+(size_t)1*YS+8,a1_1);
 }
 if constexpr(M==3&&V==1){
  __m256 a0_0=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+0);
  __m256 a1_0=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+(size_t)1*YS+0);
  __m256 a2_0=First?_mm256_set1_ps(b[2]):_mm256_loadu_ps(y+(size_t)2*YS+0);
  for(int k=kb;k<ke;++k){
   __m256 x0=_mm256_loadu_ps(x+(size_t)k*XS+0);
   __m256 q0=_mm256_set1_ps(Packed?w[(size_t)k*5+0]:w[(size_t)0*C+k]);
   a0_0=_mm256_fmadd_ps(x0,q0,a0_0);
   __m256 q1=_mm256_set1_ps(Packed?w[(size_t)k*5+1]:w[(size_t)1*C+k]);
   a1_0=_mm256_fmadd_ps(x0,q1,a1_0);
   __m256 q2=_mm256_set1_ps(Packed?w[(size_t)k*5+2]:w[(size_t)2*C+k]);
   a2_0=_mm256_fmadd_ps(x0,q2,a2_0);
  }
  _mm256_storeu_ps(y+(size_t)0*YS+0,a0_0);
  _mm256_storeu_ps(y+(size_t)1*YS+0,a1_0);
  _mm256_storeu_ps(y+(size_t)2*YS+0,a2_0);
 }
 if constexpr(M==3&&V==2){
  __m256 a0_0=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+0);
  __m256 a0_1=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+8);
  __m256 a1_0=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+(size_t)1*YS+0);
  __m256 a1_1=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+(size_t)1*YS+8);
  __m256 a2_0=First?_mm256_set1_ps(b[2]):_mm256_loadu_ps(y+(size_t)2*YS+0);
  __m256 a2_1=First?_mm256_set1_ps(b[2]):_mm256_loadu_ps(y+(size_t)2*YS+8);
  for(int k=kb;k<ke;++k){
   __m256 x0=_mm256_loadu_ps(x+(size_t)k*XS+0);
   __m256 x1=_mm256_loadu_ps(x+(size_t)k*XS+8);
   __m256 q0=_mm256_set1_ps(Packed?w[(size_t)k*5+0]:w[(size_t)0*C+k]);
   a0_0=_mm256_fmadd_ps(x0,q0,a0_0);
   a0_1=_mm256_fmadd_ps(x1,q0,a0_1);
   __m256 q1=_mm256_set1_ps(Packed?w[(size_t)k*5+1]:w[(size_t)1*C+k]);
   a1_0=_mm256_fmadd_ps(x0,q1,a1_0);
   a1_1=_mm256_fmadd_ps(x1,q1,a1_1);
   __m256 q2=_mm256_set1_ps(Packed?w[(size_t)k*5+2]:w[(size_t)2*C+k]);
   a2_0=_mm256_fmadd_ps(x0,q2,a2_0);
   a2_1=_mm256_fmadd_ps(x1,q2,a2_1);
  }
  _mm256_storeu_ps(y+(size_t)0*YS+0,a0_0);
  _mm256_storeu_ps(y+(size_t)0*YS+8,a0_1);
  _mm256_storeu_ps(y+(size_t)1*YS+0,a1_0);
  _mm256_storeu_ps(y+(size_t)1*YS+8,a1_1);
  _mm256_storeu_ps(y+(size_t)2*YS+0,a2_0);
  _mm256_storeu_ps(y+(size_t)2*YS+8,a2_1);
 }
 if constexpr(M==4&&V==1){
  __m256 a0_0=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+0);
  __m256 a1_0=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+(size_t)1*YS+0);
  __m256 a2_0=First?_mm256_set1_ps(b[2]):_mm256_loadu_ps(y+(size_t)2*YS+0);
  __m256 a3_0=First?_mm256_set1_ps(b[3]):_mm256_loadu_ps(y+(size_t)3*YS+0);
  for(int k=kb;k<ke;++k){
   __m256 x0=_mm256_loadu_ps(x+(size_t)k*XS+0);
   __m256 q0=_mm256_set1_ps(Packed?w[(size_t)k*5+0]:w[(size_t)0*C+k]);
   a0_0=_mm256_fmadd_ps(x0,q0,a0_0);
   __m256 q1=_mm256_set1_ps(Packed?w[(size_t)k*5+1]:w[(size_t)1*C+k]);
   a1_0=_mm256_fmadd_ps(x0,q1,a1_0);
   __m256 q2=_mm256_set1_ps(Packed?w[(size_t)k*5+2]:w[(size_t)2*C+k]);
   a2_0=_mm256_fmadd_ps(x0,q2,a2_0);
   __m256 q3=_mm256_set1_ps(Packed?w[(size_t)k*5+3]:w[(size_t)3*C+k]);
   a3_0=_mm256_fmadd_ps(x0,q3,a3_0);
  }
  _mm256_storeu_ps(y+(size_t)0*YS+0,a0_0);
  _mm256_storeu_ps(y+(size_t)1*YS+0,a1_0);
  _mm256_storeu_ps(y+(size_t)2*YS+0,a2_0);
  _mm256_storeu_ps(y+(size_t)3*YS+0,a3_0);
 }
 if constexpr(M==4&&V==2){
  __m256 a0_0=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+0);
  __m256 a0_1=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+8);
  __m256 a1_0=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+(size_t)1*YS+0);
  __m256 a1_1=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+(size_t)1*YS+8);
  __m256 a2_0=First?_mm256_set1_ps(b[2]):_mm256_loadu_ps(y+(size_t)2*YS+0);
  __m256 a2_1=First?_mm256_set1_ps(b[2]):_mm256_loadu_ps(y+(size_t)2*YS+8);
  __m256 a3_0=First?_mm256_set1_ps(b[3]):_mm256_loadu_ps(y+(size_t)3*YS+0);
  __m256 a3_1=First?_mm256_set1_ps(b[3]):_mm256_loadu_ps(y+(size_t)3*YS+8);
  for(int k=kb;k<ke;++k){
   __m256 x0=_mm256_loadu_ps(x+(size_t)k*XS+0);
   __m256 x1=_mm256_loadu_ps(x+(size_t)k*XS+8);
   __m256 q0=_mm256_set1_ps(Packed?w[(size_t)k*5+0]:w[(size_t)0*C+k]);
   a0_0=_mm256_fmadd_ps(x0,q0,a0_0);
   a0_1=_mm256_fmadd_ps(x1,q0,a0_1);
   __m256 q1=_mm256_set1_ps(Packed?w[(size_t)k*5+1]:w[(size_t)1*C+k]);
   a1_0=_mm256_fmadd_ps(x0,q1,a1_0);
   a1_1=_mm256_fmadd_ps(x1,q1,a1_1);
   __m256 q2=_mm256_set1_ps(Packed?w[(size_t)k*5+2]:w[(size_t)2*C+k]);
   a2_0=_mm256_fmadd_ps(x0,q2,a2_0);
   a2_1=_mm256_fmadd_ps(x1,q2,a2_1);
   __m256 q3=_mm256_set1_ps(Packed?w[(size_t)k*5+3]:w[(size_t)3*C+k]);
   a3_0=_mm256_fmadd_ps(x0,q3,a3_0);
   a3_1=_mm256_fmadd_ps(x1,q3,a3_1);
  }
  _mm256_storeu_ps(y+(size_t)0*YS+0,a0_0);
  _mm256_storeu_ps(y+(size_t)0*YS+8,a0_1);
  _mm256_storeu_ps(y+(size_t)1*YS+0,a1_0);
  _mm256_storeu_ps(y+(size_t)1*YS+8,a1_1);
  _mm256_storeu_ps(y+(size_t)2*YS+0,a2_0);
  _mm256_storeu_ps(y+(size_t)2*YS+8,a2_1);
  _mm256_storeu_ps(y+(size_t)3*YS+0,a3_0);
  _mm256_storeu_ps(y+(size_t)3*YS+8,a3_1);
 }
 if constexpr(M==5&&V==1){
  __m256 a0_0=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+0);
  __m256 a1_0=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+(size_t)1*YS+0);
  __m256 a2_0=First?_mm256_set1_ps(b[2]):_mm256_loadu_ps(y+(size_t)2*YS+0);
  __m256 a3_0=First?_mm256_set1_ps(b[3]):_mm256_loadu_ps(y+(size_t)3*YS+0);
  __m256 a4_0=First?_mm256_set1_ps(b[4]):_mm256_loadu_ps(y+(size_t)4*YS+0);
  for(int k=kb;k<ke;++k){
   __m256 x0=_mm256_loadu_ps(x+(size_t)k*XS+0);
   __m256 q0=_mm256_set1_ps(Packed?w[(size_t)k*5+0]:w[(size_t)0*C+k]);
   a0_0=_mm256_fmadd_ps(x0,q0,a0_0);
   __m256 q1=_mm256_set1_ps(Packed?w[(size_t)k*5+1]:w[(size_t)1*C+k]);
   a1_0=_mm256_fmadd_ps(x0,q1,a1_0);
   __m256 q2=_mm256_set1_ps(Packed?w[(size_t)k*5+2]:w[(size_t)2*C+k]);
   a2_0=_mm256_fmadd_ps(x0,q2,a2_0);
   __m256 q3=_mm256_set1_ps(Packed?w[(size_t)k*5+3]:w[(size_t)3*C+k]);
   a3_0=_mm256_fmadd_ps(x0,q3,a3_0);
   __m256 q4=_mm256_set1_ps(Packed?w[(size_t)k*5+4]:w[(size_t)4*C+k]);
   a4_0=_mm256_fmadd_ps(x0,q4,a4_0);
  }
  _mm256_storeu_ps(y+(size_t)0*YS+0,a0_0);
  _mm256_storeu_ps(y+(size_t)1*YS+0,a1_0);
  _mm256_storeu_ps(y+(size_t)2*YS+0,a2_0);
  _mm256_storeu_ps(y+(size_t)3*YS+0,a3_0);
  _mm256_storeu_ps(y+(size_t)4*YS+0,a4_0);
 }
 if constexpr(M==5&&V==2){
  __m256 a0_0=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+0);
  __m256 a0_1=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+8);
  __m256 a1_0=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+(size_t)1*YS+0);
  __m256 a1_1=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+(size_t)1*YS+8);
  __m256 a2_0=First?_mm256_set1_ps(b[2]):_mm256_loadu_ps(y+(size_t)2*YS+0);
  __m256 a2_1=First?_mm256_set1_ps(b[2]):_mm256_loadu_ps(y+(size_t)2*YS+8);
  __m256 a3_0=First?_mm256_set1_ps(b[3]):_mm256_loadu_ps(y+(size_t)3*YS+0);
  __m256 a3_1=First?_mm256_set1_ps(b[3]):_mm256_loadu_ps(y+(size_t)3*YS+8);
  __m256 a4_0=First?_mm256_set1_ps(b[4]):_mm256_loadu_ps(y+(size_t)4*YS+0);
  __m256 a4_1=First?_mm256_set1_ps(b[4]):_mm256_loadu_ps(y+(size_t)4*YS+8);
  for(int k=kb;k<ke;++k){
   __m256 x0=_mm256_loadu_ps(x+(size_t)k*XS+0);
   __m256 x1=_mm256_loadu_ps(x+(size_t)k*XS+8);
   __m256 q0=_mm256_set1_ps(Packed?w[(size_t)k*5+0]:w[(size_t)0*C+k]);
   a0_0=_mm256_fmadd_ps(x0,q0,a0_0);
   a0_1=_mm256_fmadd_ps(x1,q0,a0_1);
   __m256 q1=_mm256_set1_ps(Packed?w[(size_t)k*5+1]:w[(size_t)1*C+k]);
   a1_0=_mm256_fmadd_ps(x0,q1,a1_0);
   a1_1=_mm256_fmadd_ps(x1,q1,a1_1);
   __m256 q2=_mm256_set1_ps(Packed?w[(size_t)k*5+2]:w[(size_t)2*C+k]);
   a2_0=_mm256_fmadd_ps(x0,q2,a2_0);
   a2_1=_mm256_fmadd_ps(x1,q2,a2_1);
   __m256 q3=_mm256_set1_ps(Packed?w[(size_t)k*5+3]:w[(size_t)3*C+k]);
   a3_0=_mm256_fmadd_ps(x0,q3,a3_0);
   a3_1=_mm256_fmadd_ps(x1,q3,a3_1);
   __m256 q4=_mm256_set1_ps(Packed?w[(size_t)k*5+4]:w[(size_t)4*C+k]);
   a4_0=_mm256_fmadd_ps(x0,q4,a4_0);
   a4_1=_mm256_fmadd_ps(x1,q4,a4_1);
  }
  _mm256_storeu_ps(y+(size_t)0*YS+0,a0_0);
  _mm256_storeu_ps(y+(size_t)0*YS+8,a0_1);
  _mm256_storeu_ps(y+(size_t)1*YS+0,a1_0);
  _mm256_storeu_ps(y+(size_t)1*YS+8,a1_1);
  _mm256_storeu_ps(y+(size_t)2*YS+0,a2_0);
  _mm256_storeu_ps(y+(size_t)2*YS+8,a2_1);
  _mm256_storeu_ps(y+(size_t)3*YS+0,a3_0);
  _mm256_storeu_ps(y+(size_t)3*YS+8,a3_1);
  _mm256_storeu_ps(y+(size_t)4*YS+0,a4_0);
  _mm256_storeu_ps(y+(size_t)4*YS+8,a4_1);
 }
 if constexpr(M==6&&V==1){
  __m256 a0_0=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+0);
  __m256 a1_0=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+(size_t)1*YS+0);
  __m256 a2_0=First?_mm256_set1_ps(b[2]):_mm256_loadu_ps(y+(size_t)2*YS+0);
  __m256 a3_0=First?_mm256_set1_ps(b[3]):_mm256_loadu_ps(y+(size_t)3*YS+0);
  __m256 a4_0=First?_mm256_set1_ps(b[4]):_mm256_loadu_ps(y+(size_t)4*YS+0);
  __m256 a5_0=First?_mm256_set1_ps(b[5]):_mm256_loadu_ps(y+(size_t)5*YS+0);
  for(int k=kb;k<ke;++k){
   __m256 x0=_mm256_loadu_ps(x+(size_t)k*XS+0);
   __m256 q0=_mm256_set1_ps(Packed?w[(size_t)k*5+0]:w[(size_t)0*C+k]);
   a0_0=_mm256_fmadd_ps(x0,q0,a0_0);
   __m256 q1=_mm256_set1_ps(Packed?w[(size_t)k*5+1]:w[(size_t)1*C+k]);
   a1_0=_mm256_fmadd_ps(x0,q1,a1_0);
   __m256 q2=_mm256_set1_ps(Packed?w[(size_t)k*5+2]:w[(size_t)2*C+k]);
   a2_0=_mm256_fmadd_ps(x0,q2,a2_0);
   __m256 q3=_mm256_set1_ps(Packed?w[(size_t)k*5+3]:w[(size_t)3*C+k]);
   a3_0=_mm256_fmadd_ps(x0,q3,a3_0);
   __m256 q4=_mm256_set1_ps(Packed?w[(size_t)k*5+4]:w[(size_t)4*C+k]);
   a4_0=_mm256_fmadd_ps(x0,q4,a4_0);
   __m256 q5=_mm256_set1_ps(Packed?w[(size_t)k*5+5]:w[(size_t)5*C+k]);
   a5_0=_mm256_fmadd_ps(x0,q5,a5_0);
  }
  _mm256_storeu_ps(y+(size_t)0*YS+0,a0_0);
  _mm256_storeu_ps(y+(size_t)1*YS+0,a1_0);
  _mm256_storeu_ps(y+(size_t)2*YS+0,a2_0);
  _mm256_storeu_ps(y+(size_t)3*YS+0,a3_0);
  _mm256_storeu_ps(y+(size_t)4*YS+0,a4_0);
  _mm256_storeu_ps(y+(size_t)5*YS+0,a5_0);
 }
 if constexpr(M==6&&V==2){
  __m256 a0_0=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+0);
  __m256 a0_1=First?_mm256_set1_ps(b[0]):_mm256_loadu_ps(y+(size_t)0*YS+8);
  __m256 a1_0=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+(size_t)1*YS+0);
  __m256 a1_1=First?_mm256_set1_ps(b[1]):_mm256_loadu_ps(y+(size_t)1*YS+8);
  __m256 a2_0=First?_mm256_set1_ps(b[2]):_mm256_loadu_ps(y+(size_t)2*YS+0);
  __m256 a2_1=First?_mm256_set1_ps(b[2]):_mm256_loadu_ps(y+(size_t)2*YS+8);
  __m256 a3_0=First?_mm256_set1_ps(b[3]):_mm256_loadu_ps(y+(size_t)3*YS+0);
  __m256 a3_1=First?_mm256_set1_ps(b[3]):_mm256_loadu_ps(y+(size_t)3*YS+8);
  __m256 a4_0=First?_mm256_set1_ps(b[4]):_mm256_loadu_ps(y+(size_t)4*YS+0);
  __m256 a4_1=First?_mm256_set1_ps(b[4]):_mm256_loadu_ps(y+(size_t)4*YS+8);
  __m256 a5_0=First?_mm256_set1_ps(b[5]):_mm256_loadu_ps(y+(size_t)5*YS+0);
  __m256 a5_1=First?_mm256_set1_ps(b[5]):_mm256_loadu_ps(y+(size_t)5*YS+8);
  for(int k=kb;k<ke;++k){
   __m256 x0=_mm256_loadu_ps(x+(size_t)k*XS+0);
   __m256 x1=_mm256_loadu_ps(x+(size_t)k*XS+8);
   __m256 q0=_mm256_set1_ps(Packed?w[(size_t)k*5+0]:w[(size_t)0*C+k]);
   a0_0=_mm256_fmadd_ps(x0,q0,a0_0);
   a0_1=_mm256_fmadd_ps(x1,q0,a0_1);
   __m256 q1=_mm256_set1_ps(Packed?w[(size_t)k*5+1]:w[(size_t)1*C+k]);
   a1_0=_mm256_fmadd_ps(x0,q1,a1_0);
   a1_1=_mm256_fmadd_ps(x1,q1,a1_1);
   __m256 q2=_mm256_set1_ps(Packed?w[(size_t)k*5+2]:w[(size_t)2*C+k]);
   a2_0=_mm256_fmadd_ps(x0,q2,a2_0);
   a2_1=_mm256_fmadd_ps(x1,q2,a2_1);
   __m256 q3=_mm256_set1_ps(Packed?w[(size_t)k*5+3]:w[(size_t)3*C+k]);
   a3_0=_mm256_fmadd_ps(x0,q3,a3_0);
   a3_1=_mm256_fmadd_ps(x1,q3,a3_1);
   __m256 q4=_mm256_set1_ps(Packed?w[(size_t)k*5+4]:w[(size_t)4*C+k]);
   a4_0=_mm256_fmadd_ps(x0,q4,a4_0);
   a4_1=_mm256_fmadd_ps(x1,q4,a4_1);
   __m256 q5=_mm256_set1_ps(Packed?w[(size_t)k*5+5]:w[(size_t)5*C+k]);
   a5_0=_mm256_fmadd_ps(x0,q5,a5_0);
   a5_1=_mm256_fmadd_ps(x1,q5,a5_1);
  }
  _mm256_storeu_ps(y+(size_t)0*YS+0,a0_0);
  _mm256_storeu_ps(y+(size_t)0*YS+8,a0_1);
  _mm256_storeu_ps(y+(size_t)1*YS+0,a1_0);
  _mm256_storeu_ps(y+(size_t)1*YS+8,a1_1);
  _mm256_storeu_ps(y+(size_t)2*YS+0,a2_0);
  _mm256_storeu_ps(y+(size_t)2*YS+8,a2_1);
  _mm256_storeu_ps(y+(size_t)3*YS+0,a3_0);
  _mm256_storeu_ps(y+(size_t)3*YS+8,a3_1);
  _mm256_storeu_ps(y+(size_t)4*YS+0,a4_0);
  _mm256_storeu_ps(y+(size_t)4*YS+8,a4_1);
  _mm256_storeu_ps(y+(size_t)5*YS+0,a5_0);
  _mm256_storeu_ps(y+(size_t)5*YS+8,a5_1);
 }
}
template<int M,bool First> static __attribute__((always_inline)) inline void fresh_mask(const float* __restrict__ x,const float*w,const float*b,float* __restrict__ y,int C,int XS,int YS,int kb,int ke,int valid){
 __m256i mask=_mm256_cmpgt_epi32(_mm256_set1_epi32(valid),_mm256_setr_epi32(0,1,2,3,4,5,6,7));
 if constexpr(M==1){
  __m256 a0=First?_mm256_set1_ps(b[0]):_mm256_maskload_ps(y+(size_t)0*YS,mask);
  for(int k=kb;k<ke;++k){__m256 xx=_mm256_maskload_ps(x+(size_t)k*XS,mask);
   a0=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)0*C+k]),a0);
  }
  _mm256_maskstore_ps(y+(size_t)0*YS,mask,a0);
 }
 if constexpr(M==2){
  __m256 a0=First?_mm256_set1_ps(b[0]):_mm256_maskload_ps(y+(size_t)0*YS,mask);
  __m256 a1=First?_mm256_set1_ps(b[1]):_mm256_maskload_ps(y+(size_t)1*YS,mask);
  for(int k=kb;k<ke;++k){__m256 xx=_mm256_maskload_ps(x+(size_t)k*XS,mask);
   a0=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)0*C+k]),a0);
   a1=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)1*C+k]),a1);
  }
  _mm256_maskstore_ps(y+(size_t)0*YS,mask,a0);
  _mm256_maskstore_ps(y+(size_t)1*YS,mask,a1);
 }
 if constexpr(M==3){
  __m256 a0=First?_mm256_set1_ps(b[0]):_mm256_maskload_ps(y+(size_t)0*YS,mask);
  __m256 a1=First?_mm256_set1_ps(b[1]):_mm256_maskload_ps(y+(size_t)1*YS,mask);
  __m256 a2=First?_mm256_set1_ps(b[2]):_mm256_maskload_ps(y+(size_t)2*YS,mask);
  for(int k=kb;k<ke;++k){__m256 xx=_mm256_maskload_ps(x+(size_t)k*XS,mask);
   a0=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)0*C+k]),a0);
   a1=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)1*C+k]),a1);
   a2=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)2*C+k]),a2);
  }
  _mm256_maskstore_ps(y+(size_t)0*YS,mask,a0);
  _mm256_maskstore_ps(y+(size_t)1*YS,mask,a1);
  _mm256_maskstore_ps(y+(size_t)2*YS,mask,a2);
 }
 if constexpr(M==4){
  __m256 a0=First?_mm256_set1_ps(b[0]):_mm256_maskload_ps(y+(size_t)0*YS,mask);
  __m256 a1=First?_mm256_set1_ps(b[1]):_mm256_maskload_ps(y+(size_t)1*YS,mask);
  __m256 a2=First?_mm256_set1_ps(b[2]):_mm256_maskload_ps(y+(size_t)2*YS,mask);
  __m256 a3=First?_mm256_set1_ps(b[3]):_mm256_maskload_ps(y+(size_t)3*YS,mask);
  for(int k=kb;k<ke;++k){__m256 xx=_mm256_maskload_ps(x+(size_t)k*XS,mask);
   a0=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)0*C+k]),a0);
   a1=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)1*C+k]),a1);
   a2=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)2*C+k]),a2);
   a3=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)3*C+k]),a3);
  }
  _mm256_maskstore_ps(y+(size_t)0*YS,mask,a0);
  _mm256_maskstore_ps(y+(size_t)1*YS,mask,a1);
  _mm256_maskstore_ps(y+(size_t)2*YS,mask,a2);
  _mm256_maskstore_ps(y+(size_t)3*YS,mask,a3);
 }
 if constexpr(M==5){
  __m256 a0=First?_mm256_set1_ps(b[0]):_mm256_maskload_ps(y+(size_t)0*YS,mask);
  __m256 a1=First?_mm256_set1_ps(b[1]):_mm256_maskload_ps(y+(size_t)1*YS,mask);
  __m256 a2=First?_mm256_set1_ps(b[2]):_mm256_maskload_ps(y+(size_t)2*YS,mask);
  __m256 a3=First?_mm256_set1_ps(b[3]):_mm256_maskload_ps(y+(size_t)3*YS,mask);
  __m256 a4=First?_mm256_set1_ps(b[4]):_mm256_maskload_ps(y+(size_t)4*YS,mask);
  for(int k=kb;k<ke;++k){__m256 xx=_mm256_maskload_ps(x+(size_t)k*XS,mask);
   a0=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)0*C+k]),a0);
   a1=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)1*C+k]),a1);
   a2=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)2*C+k]),a2);
   a3=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)3*C+k]),a3);
   a4=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)4*C+k]),a4);
  }
  _mm256_maskstore_ps(y+(size_t)0*YS,mask,a0);
  _mm256_maskstore_ps(y+(size_t)1*YS,mask,a1);
  _mm256_maskstore_ps(y+(size_t)2*YS,mask,a2);
  _mm256_maskstore_ps(y+(size_t)3*YS,mask,a3);
  _mm256_maskstore_ps(y+(size_t)4*YS,mask,a4);
 }
 if constexpr(M==6){
  __m256 a0=First?_mm256_set1_ps(b[0]):_mm256_maskload_ps(y+(size_t)0*YS,mask);
  __m256 a1=First?_mm256_set1_ps(b[1]):_mm256_maskload_ps(y+(size_t)1*YS,mask);
  __m256 a2=First?_mm256_set1_ps(b[2]):_mm256_maskload_ps(y+(size_t)2*YS,mask);
  __m256 a3=First?_mm256_set1_ps(b[3]):_mm256_maskload_ps(y+(size_t)3*YS,mask);
  __m256 a4=First?_mm256_set1_ps(b[4]):_mm256_maskload_ps(y+(size_t)4*YS,mask);
  __m256 a5=First?_mm256_set1_ps(b[5]):_mm256_maskload_ps(y+(size_t)5*YS,mask);
  for(int k=kb;k<ke;++k){__m256 xx=_mm256_maskload_ps(x+(size_t)k*XS,mask);
   a0=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)0*C+k]),a0);
   a1=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)1*C+k]),a1);
   a2=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)2*C+k]),a2);
   a3=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)3*C+k]),a3);
   a4=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)4*C+k]),a4);
   a5=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)5*C+k]),a5);
  }
  _mm256_maskstore_ps(y+(size_t)0*YS,mask,a0);
  _mm256_maskstore_ps(y+(size_t)1*YS,mask,a1);
  _mm256_maskstore_ps(y+(size_t)2*YS,mask,a2);
  _mm256_maskstore_ps(y+(size_t)3*YS,mask,a3);
  _mm256_maskstore_ps(y+(size_t)4*YS,mask,a4);
  _mm256_maskstore_ps(y+(size_t)5*YS,mask,a5);
 }
 if constexpr(M==7){
  __m256 a0=First?_mm256_set1_ps(b[0]):_mm256_maskload_ps(y+(size_t)0*YS,mask);
  __m256 a1=First?_mm256_set1_ps(b[1]):_mm256_maskload_ps(y+(size_t)1*YS,mask);
  __m256 a2=First?_mm256_set1_ps(b[2]):_mm256_maskload_ps(y+(size_t)2*YS,mask);
  __m256 a3=First?_mm256_set1_ps(b[3]):_mm256_maskload_ps(y+(size_t)3*YS,mask);
  __m256 a4=First?_mm256_set1_ps(b[4]):_mm256_maskload_ps(y+(size_t)4*YS,mask);
  __m256 a5=First?_mm256_set1_ps(b[5]):_mm256_maskload_ps(y+(size_t)5*YS,mask);
  __m256 a6=First?_mm256_set1_ps(b[6]):_mm256_maskload_ps(y+(size_t)6*YS,mask);
  for(int k=kb;k<ke;++k){__m256 xx=_mm256_maskload_ps(x+(size_t)k*XS,mask);
   a0=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)0*C+k]),a0);
   a1=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)1*C+k]),a1);
   a2=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)2*C+k]),a2);
   a3=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)3*C+k]),a3);
   a4=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)4*C+k]),a4);
   a5=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)5*C+k]),a5);
   a6=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)6*C+k]),a6);
  }
  _mm256_maskstore_ps(y+(size_t)0*YS,mask,a0);
  _mm256_maskstore_ps(y+(size_t)1*YS,mask,a1);
  _mm256_maskstore_ps(y+(size_t)2*YS,mask,a2);
  _mm256_maskstore_ps(y+(size_t)3*YS,mask,a3);
  _mm256_maskstore_ps(y+(size_t)4*YS,mask,a4);
  _mm256_maskstore_ps(y+(size_t)5*YS,mask,a5);
  _mm256_maskstore_ps(y+(size_t)6*YS,mask,a6);
 }
 if constexpr(M==8){
  __m256 a0=First?_mm256_set1_ps(b[0]):_mm256_maskload_ps(y+(size_t)0*YS,mask);
  __m256 a1=First?_mm256_set1_ps(b[1]):_mm256_maskload_ps(y+(size_t)1*YS,mask);
  __m256 a2=First?_mm256_set1_ps(b[2]):_mm256_maskload_ps(y+(size_t)2*YS,mask);
  __m256 a3=First?_mm256_set1_ps(b[3]):_mm256_maskload_ps(y+(size_t)3*YS,mask);
  __m256 a4=First?_mm256_set1_ps(b[4]):_mm256_maskload_ps(y+(size_t)4*YS,mask);
  __m256 a5=First?_mm256_set1_ps(b[5]):_mm256_maskload_ps(y+(size_t)5*YS,mask);
  __m256 a6=First?_mm256_set1_ps(b[6]):_mm256_maskload_ps(y+(size_t)6*YS,mask);
  __m256 a7=First?_mm256_set1_ps(b[7]):_mm256_maskload_ps(y+(size_t)7*YS,mask);
  for(int k=kb;k<ke;++k){__m256 xx=_mm256_maskload_ps(x+(size_t)k*XS,mask);
   a0=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)0*C+k]),a0);
   a1=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)1*C+k]),a1);
   a2=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)2*C+k]),a2);
   a3=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)3*C+k]),a3);
   a4=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)4*C+k]),a4);
   a5=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)5*C+k]),a5);
   a6=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)6*C+k]),a6);
   a7=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)7*C+k]),a7);
  }
  _mm256_maskstore_ps(y+(size_t)0*YS,mask,a0);
  _mm256_maskstore_ps(y+(size_t)1*YS,mask,a1);
  _mm256_maskstore_ps(y+(size_t)2*YS,mask,a2);
  _mm256_maskstore_ps(y+(size_t)3*YS,mask,a3);
  _mm256_maskstore_ps(y+(size_t)4*YS,mask,a4);
  _mm256_maskstore_ps(y+(size_t)5*YS,mask,a5);
  _mm256_maskstore_ps(y+(size_t)6*YS,mask,a6);
  _mm256_maskstore_ps(y+(size_t)7*YS,mask,a7);
 }
 if constexpr(M==9){
  __m256 a0=First?_mm256_set1_ps(b[0]):_mm256_maskload_ps(y+(size_t)0*YS,mask);
  __m256 a1=First?_mm256_set1_ps(b[1]):_mm256_maskload_ps(y+(size_t)1*YS,mask);
  __m256 a2=First?_mm256_set1_ps(b[2]):_mm256_maskload_ps(y+(size_t)2*YS,mask);
  __m256 a3=First?_mm256_set1_ps(b[3]):_mm256_maskload_ps(y+(size_t)3*YS,mask);
  __m256 a4=First?_mm256_set1_ps(b[4]):_mm256_maskload_ps(y+(size_t)4*YS,mask);
  __m256 a5=First?_mm256_set1_ps(b[5]):_mm256_maskload_ps(y+(size_t)5*YS,mask);
  __m256 a6=First?_mm256_set1_ps(b[6]):_mm256_maskload_ps(y+(size_t)6*YS,mask);
  __m256 a7=First?_mm256_set1_ps(b[7]):_mm256_maskload_ps(y+(size_t)7*YS,mask);
  __m256 a8=First?_mm256_set1_ps(b[8]):_mm256_maskload_ps(y+(size_t)8*YS,mask);
  for(int k=kb;k<ke;++k){__m256 xx=_mm256_maskload_ps(x+(size_t)k*XS,mask);
   a0=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)0*C+k]),a0);
   a1=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)1*C+k]),a1);
   a2=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)2*C+k]),a2);
   a3=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)3*C+k]),a3);
   a4=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)4*C+k]),a4);
   a5=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)5*C+k]),a5);
   a6=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)6*C+k]),a6);
   a7=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)7*C+k]),a7);
   a8=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)8*C+k]),a8);
  }
  _mm256_maskstore_ps(y+(size_t)0*YS,mask,a0);
  _mm256_maskstore_ps(y+(size_t)1*YS,mask,a1);
  _mm256_maskstore_ps(y+(size_t)2*YS,mask,a2);
  _mm256_maskstore_ps(y+(size_t)3*YS,mask,a3);
  _mm256_maskstore_ps(y+(size_t)4*YS,mask,a4);
  _mm256_maskstore_ps(y+(size_t)5*YS,mask,a5);
  _mm256_maskstore_ps(y+(size_t)6*YS,mask,a6);
  _mm256_maskstore_ps(y+(size_t)7*YS,mask,a7);
  _mm256_maskstore_ps(y+(size_t)8*YS,mask,a8);
 }
 if constexpr(M==10){
  __m256 a0=First?_mm256_set1_ps(b[0]):_mm256_maskload_ps(y+(size_t)0*YS,mask);
  __m256 a1=First?_mm256_set1_ps(b[1]):_mm256_maskload_ps(y+(size_t)1*YS,mask);
  __m256 a2=First?_mm256_set1_ps(b[2]):_mm256_maskload_ps(y+(size_t)2*YS,mask);
  __m256 a3=First?_mm256_set1_ps(b[3]):_mm256_maskload_ps(y+(size_t)3*YS,mask);
  __m256 a4=First?_mm256_set1_ps(b[4]):_mm256_maskload_ps(y+(size_t)4*YS,mask);
  __m256 a5=First?_mm256_set1_ps(b[5]):_mm256_maskload_ps(y+(size_t)5*YS,mask);
  __m256 a6=First?_mm256_set1_ps(b[6]):_mm256_maskload_ps(y+(size_t)6*YS,mask);
  __m256 a7=First?_mm256_set1_ps(b[7]):_mm256_maskload_ps(y+(size_t)7*YS,mask);
  __m256 a8=First?_mm256_set1_ps(b[8]):_mm256_maskload_ps(y+(size_t)8*YS,mask);
  __m256 a9=First?_mm256_set1_ps(b[9]):_mm256_maskload_ps(y+(size_t)9*YS,mask);
  for(int k=kb;k<ke;++k){__m256 xx=_mm256_maskload_ps(x+(size_t)k*XS,mask);
   a0=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)0*C+k]),a0);
   a1=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)1*C+k]),a1);
   a2=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)2*C+k]),a2);
   a3=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)3*C+k]),a3);
   a4=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)4*C+k]),a4);
   a5=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)5*C+k]),a5);
   a6=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)6*C+k]),a6);
   a7=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)7*C+k]),a7);
   a8=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)8*C+k]),a8);
   a9=_mm256_fmadd_ps(xx,_mm256_set1_ps(w[(size_t)9*C+k]),a9);
  }
  _mm256_maskstore_ps(y+(size_t)0*YS,mask,a0);
  _mm256_maskstore_ps(y+(size_t)1*YS,mask,a1);
  _mm256_maskstore_ps(y+(size_t)2*YS,mask,a2);
  _mm256_maskstore_ps(y+(size_t)3*YS,mask,a3);
  _mm256_maskstore_ps(y+(size_t)4*YS,mask,a4);
  _mm256_maskstore_ps(y+(size_t)5*YS,mask,a5);
  _mm256_maskstore_ps(y+(size_t)6*YS,mask,a6);
  _mm256_maskstore_ps(y+(size_t)7*YS,mask,a7);
  _mm256_maskstore_ps(y+(size_t)8*YS,mask,a8);
  _mm256_maskstore_ps(y+(size_t)9*YS,mask,a9);
 }
}
