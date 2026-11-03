#include "p2.h"
#include <vector>
#include <limits>
#include <cmath>
#include <cstdint>
#include <new>
#include "tiles_generated.h"
#include "variant_count_generated.h"
#include "variant_meta_generated.h"

struct Context {
 int C,S,O,Op;
 bool packed; unsigned long long layout_calls[3]={0,0,0};
 std::vector<float> w,b,wp,bp,xp,yp;
 Context(int c,int s,int o,const float*ww,const float*bb,bool pack):C(c),S(s),O(o),Op((o+7)/8*8),packed(pack),w(ww,ww+(size_t)o*c),b(o,0),wp(pack?(size_t)Op*c:0,0),bp(pack?Op:0,0),xp(pack?(size_t)s*c:0),yp(pack?(size_t)s*Op:0){
  if(bb)for(int j=0;j<O;++j)b[j]=bb[j];
  if(packed)for(int j=0;j<O;++j){bp[j]=b[j];for(int k=0;k<C;++k)wp[((size_t)(j/8)*C+k)*8+j%8]=w[(size_t)j*C+k];}
 }
};
static bool overlap(const float* x,size_t nx,const float* y,size_t ny){
 uintptr_t a=(uintptr_t)x,b=(uintptr_t)y;
 if(nx>UINTPTR_MAX/4||ny>UINTPTR_MAX/4||a>UINTPTR_MAX-nx*4||b>UINTPTR_MAX-ny*4)return true;
 return a<b+ny*4&&b<a+nx*4;
}
extern "C" int p2_has_avx2_fma(){
#if defined(__x86_64__) || defined(__i386__)
 __builtin_cpu_init();return __builtin_cpu_supports("avx2")&&__builtin_cpu_supports("fma");
#else
 return 0;
#endif
}
extern "C" int p2_variant_count(){return P2_VARIANT_COUNT;}
extern "C" int p2_variant_M(int v){return v>=0&&v<P2_VARIANT_COUNT?p2_ms[v]:0;}
extern "C" int p2_variant_N(int v){return v>=0&&v<P2_VARIANT_COUNT?p2_ns[v]:0;}
extern "C" int p2_validate_shape(int C,int S,int O){
 if(C<=0||S<=0||O<=0||O>2147483640)return -1;
 size_t max=(size_t)PTRDIFF_MAX/sizeof(float),op=((size_t)O+7)/8*8;
 if((size_t)C>max/op||(size_t)S>max/op||(size_t)C>max/(size_t)S)return -1;
 return 0;
}
static void* create_impl(int C,int S,int O,const float*w,const float*b,bool packed){
 if(p2_validate_shape(C,S,O)||!w)return nullptr;
 try{return new Context(C,S,O,w,b,packed);}catch(...){return nullptr;}
}
extern "C" void* p2_create(int C,int S,int O,const float*w,const float*b){return create_impl(C,S,O,w,b,true);}
extern "C" void* p2_create_direct(int C,int S,int O,const float*w,const float*b){return create_impl(C,S,O,w,b,false);}
extern "C" size_t p2_packed_bytes(void*p){if(!p)return 0;auto&a=*(Context*)p;return sizeof(float)*(a.wp.size()+a.bp.size()+a.xp.size()+a.yp.size());}
extern "C" unsigned long long p2_layout_calls(void*p,int phase){return p&&phase>=0&&phase<3?((Context*)p)->layout_calls[phase]:0;}
extern "C" void p2_destroy(void*p){delete (Context*)p;}
static void plain(Context&a,const float*x,float*y){
 for(int o=0;o<a.O;++o)for(int s=0;s<a.S;++s){
  float z=a.b[o];for(int k=0;k<a.C;++k)z+=a.w[(size_t)o*a.C+k]*x[(size_t)k*a.S+s];y[(size_t)o*a.S+s]=z;
 }
}
using Tile=void(*)(const float*,const float*,const float*,float*,int,int);
static void direct(Context&a,const float*x,float*y,int M,int N,Tile tile,int panel){
 // Panel loop can be 1 full S panel (output-major) or bounded spatial-major.
 for(int p0=0;p0<a.S;){int end=p0+((a.S-p0<panel)?a.S-p0:panel);
  int o=0;
  for(;o<=a.O-M;o+=M){int s=p0;
   for(;s<=end-N;s+=N)tile(x+s,a.w.data()+(size_t)o*a.C,a.b.data()+o,y+(size_t)o*a.S+s,a.C,a.S);
   for(int m=0;m<M;++m)for(int t=s;t<end;++t){float z=a.b[o+m];for(int k=0;k<a.C;++k)z=std::fma(a.w[(size_t)(o+m)*a.C+k],x[(size_t)k*a.S+t],z);y[(size_t)(o+m)*a.S+t]=z;}
  }
  for(;o<a.O;++o){int s=p0;for(;s<=end-8;s+=8)direct_1_8(x+s,a.w.data()+(size_t)o*a.C,a.b.data()+o,y+(size_t)o*a.S+s,a.C,a.S);
   for(;s<end;++s){float z=a.b[o];for(int k=0;k<a.C;++k)z=std::fma(a.w[(size_t)o*a.C+k],x[(size_t)k*a.S+s],z);y[(size_t)o*a.S+s]=z;}
  }p0=end;
 }
}
extern "C" int p2_prepare(void*p,const float*x){if(!p||!x)return -1;auto&a=*(Context*)p;if(!a.packed)return -1;++a.layout_calls[0];
 for(int s=0;s<a.S;++s)for(int k=0;k<a.C;++k)a.xp[(size_t)s*a.C+k]=x[(size_t)k*a.S+s];return 0;}
extern "C" int p2_compute(void*p,int variant){if(!p||(variant!=6&&variant!=7))return -1;auto&a=*(Context*)p;if(!a.packed)return -1;++a.layout_calls[1];int P=variant==6?4:12;
 for(int o=0;o<a.Op;o+=8){int s=0;for(;s<=a.S-P;s+=P){
  auto t=variant==6?packed_4:packed_12;t(a.xp.data()+(size_t)s*a.C,a.wp.data()+(size_t)(o/8)*a.C*8,a.bp.data()+o,a.yp.data()+(size_t)s*a.Op+o,a.C,a.Op);
 }for(;s<a.S;++s){V8 z=ld(a.bp.data()+o);for(int k=0;k<a.C;++k)z=fm(bc(a.xp[(size_t)s*a.C+k]),ld(a.wp.data()+((size_t)(o/8)*a.C+k)*8),z);st(a.yp.data()+(size_t)s*a.Op+o,z);}}
 return 0;}
extern "C" int p2_finish(void*p,float*y){if(!p||!y)return -1;auto&a=*(Context*)p;if(!a.packed)return -1;++a.layout_calls[2];
 for(int o=0;o<a.O;++o)for(int s=0;s<a.S;++s)y[(size_t)o*a.S+s]=a.yp[(size_t)s*a.Op+o];return 0;}
extern "C" int p2_run(void*p,const float*x,float*y,int variant){
 if(!p||!x||!y||variant<0||variant>=P2_VARIANT_COUNT)return -1;auto&a=*(Context*)p;
 if(overlap(x,(size_t)a.C*a.S,y,(size_t)a.O*a.S))return -1;
 switch(variant){
 case 0:plain(a,x,y);break;
 #include "dispatch_generated.inc"
 case 6:case 7:if(!a.packed)return -1;p2_prepare(p,x);p2_compute(p,variant);p2_finish(p,y);break;
 }return 0;
}
