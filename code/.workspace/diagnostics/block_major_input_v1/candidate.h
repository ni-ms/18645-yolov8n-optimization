#pragma once
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
/* Separate experimental ABI. Dense FP32 NCHW; positive C,S,O; w/b copied.
   Input/output must not overlap. Calls on a context must be serialized.
   Input panels may be copied/packed during p5_run; every such copy is part
   of the repeated public call. No allocation occurs during p5_run. */
void* p5_create(int C,int S,int O,const float*w,const float*b);
void p5_destroy(void*);
int p5_validate_shape(int C,int S,int O);
int p5_variant_count(void);
size_t p5_packed_weight_bytes(void*);
size_t p5_workspace_bytes(void*);
int p5_run(void*,const float*x,float*y,int variant);
#ifdef __cplusplus
}
#endif
