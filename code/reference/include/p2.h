#pragma once
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
/* C,S,O > 0. Batch one. C-major input C*S, O-major weights O*C,
   bias O or null, O-major output O*S. All float buffers contiguous.
   All calls on one context serialized. w/b are copied at creation.
   Input/output must not overlap and remain valid through the call.
   No stride, padding, dilation, groups or activation parameter: supported
   semantics are fixed to (1,1), 0, (1,1), 1 and identity respectively. */
void *p2_create(int C, int S, int O, const float *w, const float *b);
void p2_destroy(void *ctx);
/* Direct-only context has no packed weights, packed input or packed output. */
void *p2_create_direct(int C,int S,int O,const float*w,const float*b);
size_t p2_packed_bytes(void *ctx);
int p2_variant_count(void);
int p2_variant_M(int variant);
int p2_variant_N(int variant);
int p2_validate_shape(int C,int S,int O);
/* prepare/compute/finish invocation counters for layout verification. */
unsigned long long p2_layout_calls(void *ctx,int phase);
/* variant 0 plain C++, 1..5 direct 2x16/4x16/5x16/6x16/4x24,
   6 packed4x8, 7 packed12x8, 8 direct5x16 panel64,
   9 direct5x16 panel256. Further IDs are generated in configs/variants.json. Return 0 success, -1 invalid. */
int p2_run(void *ctx, const float *x, float *y, int variant);
/* Diagnostics 6/7: prepare converts input once, compute leaves packed output,
   finish converts packed output. p2_run includes all three. */
int p2_prepare(void *ctx,const float *x);
int p2_compute(void *ctx,int variant);
int p2_finish(void *ctx,float *y);
int p2_has_avx2_fma(void);
#ifdef __cplusplus
}
#endif
