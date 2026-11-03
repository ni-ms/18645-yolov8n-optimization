#include "candidate.h"
#include <cstddef>
#include <cstdint>
#include <vector>
#include <cmath>
#include <algorithm>
#include "tuned_tiles.h"
#include <cstring>
#include "fixed_tiles.h"
#include "tail_tiles.h"
#include "pack_tiles.h"

struct P5Context {
 int C,S,O;
 std::vector<float>w,b,wp,wp6,wp8,scratch,output_scratch;
 float*output_data(){return (float*)(((uintptr_t)output_scratch.data()+63)&~(uintptr_t)63);}
 float*panel_data(){return (float*)(((uintptr_t)scratch.data()+63)&~(uintptr_t)63);}
 P5Context(int c,int s,int o,const float*ww,const float*bb):C(c),S(s),O(o),w(ww,ww+(size_t)o*c),b(o,0),wp((size_t)(o/5)*c*5),wp6((size_t)(o/6)*c*6),wp8((c==384&&s==100&&o==256)?(size_t)o*c:0),scratch((size_t)c*96+16),output_scratch(s==100?(size_t)o*112+16:0){
  if(bb)for(int j=0;j<o;++j)b[j]=bb[j];
  // Only complete groups are packed; channel tails use the owned original copy.
  for(int group=0;group<o/5;++group)for(int k=0;k<c;++k)for(int m=0;m<5;++m)
   wp[((size_t)group*c+k)*5+m]=w[(size_t)(group*5+m)*c+k];
  for(int group=0;group<o/6;++group)for(int k=0;k<c;++k)for(int m=0;m<6;++m)
   wp6[((size_t)group*c+k)*6+m]=w[(size_t)(group*6+m)*c+k];
  if(!wp8.empty())for(int group=0;group<o/8;++group)for(int k=0;k<c;++k)for(int m=0;m<8;++m)
   wp8[((size_t)group*c+k)*8+m]=w[(size_t)(group*8+m)*c+k];
 }
};
extern "C" int p5_validate_shape(int C,int S,int O){
 if(C<=0||S<=0||O<=0||O>2147483640)return -1;
 const size_t maximum=(size_t)PTRDIFF_MAX/sizeof(float);
 if((size_t)C>maximum/(size_t)O||(size_t)S>maximum/(size_t)O||
    (size_t)C>maximum/(size_t)S)return -1;
 return 0;
}
extern "C" void* p5_create(int C,int S,int O,const float*w,const float*b){
 if(!w||p5_validate_shape(C,S,O))return nullptr;
 try{return new P5Context(C,S,O,w,b);}catch(...){return nullptr;}
}
extern "C" void p5_destroy(void*p){delete (P5Context*)p;}
extern "C" int p5_variant_count(){return 2;}
static bool overlap(const float*x,size_t nx,const float*y,size_t ny){
 const uintptr_t a=(uintptr_t)x,b=(uintptr_t)y;
 if(nx>UINTPTR_MAX/4||ny>UINTPTR_MAX/4||a>UINTPTR_MAX-nx*4||b>UINTPTR_MAX-ny*4)return true;
 return a<b+ny*4&&b<a+nx*4;
}
template<int M,int V> static __attribute__((always_inline)) inline void apply_fresh(const float*x,const float*w,const float*b,float*y,int C,int XS,int YS,int kb,int ke,bool first){
 if(first)fresh_tile<M,V,false,true>(x,w,b,y,C,XS,YS,kb,ke);
 else fresh_tile<M,V,false,false>(x,w,b,y,C,XS,YS,kb,ke);
}
template<int R> static __attribute__((always_inline)) inline void tuned_remainder(const float*x,const float*w,const float*b,float*y,int C,int XS,int YS,int width,int kb,int ke,bool first){
 int s=0;
 for(;s<=width-16;s+=16)apply_fresh<R,2>(x+s,w,b,y+s,C,XS,YS,kb,ke,first);
 for(;s<=width-8;s+=8)apply_fresh<R,1>(x+s,w,b,y+s,C,XS,YS,kb,ke,first);
}
template<int R> static __attribute__((always_inline)) inline void apply_mask(const float*x,const float*w,const float*b,float*y,int C,int XS,int YS,int kb,int ke,bool first,int valid){
 if(first)fresh_mask<R,true>(x,w,b,y,C,XS,YS,kb,ke,valid);
 else fresh_mask<R,false>(x,w,b,y,C,XS,YS,kb,ke,valid);
}
template<int M,int V,bool WP> static __attribute__((always_inline)) inline void compute_group(P5Context&a,const float*in,float*y,int XS,int p0,int s,int o,int kb,int ke,bool first){
 const float*w=WP?a.wp.data()+(size_t)(o/5)*a.C*5:a.w.data()+(size_t)o*a.C;
 const float*b=a.b.data()+o;float*out=y+(size_t)o*a.S+p0+s;
 if(first)fresh_tile<M,V,WP,true>(in+s,w,b,out,a.C,XS,a.S,kb,ke);
 else fresh_tile<M,V,WP,false>(in+s,w,b,out,a.C,XS,a.S,kb,ke);
}
template<int Main,int V,bool WP> static __attribute__((always_inline)) inline void all_channels(P5Context&a,const float*in,float*y,int XS,int p0,int s,int kb,int ke,bool first){
 int o=0;for(;o<=a.O-Main;o+=Main)compute_group<Main,V,WP>(a,in,y,XS,p0,s,o,kb,ke,first);
 if(o<a.O){const float*w=a.w.data()+(size_t)o*a.C;const float*b=a.b.data()+o;float*out=y+(size_t)o*a.S+p0+s;
 switch(a.O-o){
 case 1:apply_fresh<1,V>(in+s,w,b,out,a.C,XS,a.S,kb,ke,first);break;
 case 2:apply_fresh<2,V>(in+s,w,b,out,a.C,XS,a.S,kb,ke,first);break;
 case 3:apply_fresh<3,V>(in+s,w,b,out,a.C,XS,a.S,kb,ke,first);break;
 case 4:apply_fresh<4,V>(in+s,w,b,out,a.C,XS,a.S,kb,ke,first);break;
 case 5:apply_fresh<5,V>(in+s,w,b,out,a.C,XS,a.S,kb,ke,first);break;
 }}
}
template<int M,int KC,int Panel,int PackStride,bool PackedW,bool SpatialOuter>
static __attribute__((always_inline)) inline void tuned_driver(P5Context&a,const float*x,float*y){
 static_assert(!PackedW||M==5,"packed weights match five-channel groups");
 static_assert(PackStride==0||PackStride>=Panel,"input-panel extent");
 for(int p0=0;p0<a.S;){
  const int width=std::min(Panel,a.S-p0);const float*in=x+p0;int XS=a.S;
  if constexpr(PackStride>0){
   float*packed=a.panel_data();
   for(int k=0;k<a.C;++k){
    const float*from=x+(size_t)k*a.S+p0;float*to=packed+(size_t)k*PackStride;
    int s=0;for(;s<=width-8;s+=8)_mm256_store_ps(to+s,_mm256_loadu_ps(from+s));
    for(;s<width;++s)to[s]=from[s];
   }
   in=packed;XS=PackStride;
  }
  for(int kb=0;kb<a.C;){
   const int ke=KC==0?a.C:kb+std::min(KC,a.C-kb);const bool first=kb==0;
   if constexpr(SpatialOuter){
    int s=0;for(;s<=width-16;s+=16)all_channels<M,2,PackedW>(a,in,y,XS,p0,s,kb,ke,first);
    for(;s<=width-8;s+=8)all_channels<M,1,false>(a,in,y,XS,p0,s,kb,ke,first);
   }else{
   int o=0;
   for(;o<=a.O-M;o+=M){
    const float*w=PackedW?a.wp.data()+(size_t)(o/5)*a.C*5:a.w.data()+(size_t)o*a.C;
    const float*b=a.b.data()+o;float*out=y+(size_t)o*a.S+p0;
    int s=0;for(;s<=width-16;s+=16){
     if(first)fresh_tile<M,2,PackedW,true>(in+s,w,b,out+s,a.C,XS,a.S,kb,ke);
     else fresh_tile<M,2,PackedW,false>(in+s,w,b,out+s,a.C,XS,a.S,kb,ke);
    }
    // The 8-position cleanup uses original weights even with packed full tiles.
    for(;s<=width-8;s+=8)apply_fresh<M,1>(in+s,a.w.data()+(size_t)o*a.C,b,out+s,a.C,XS,a.S,kb,ke,first);
   }
   if(o<a.O){
   const float*wr=a.w.data()+(size_t)o*a.C;const float*br=a.b.data()+o;float*yr=y+(size_t)o*a.S+p0;
   switch(a.O-o){
    case 1:tuned_remainder<1>(in,wr,br,yr,a.C,XS,a.S,width,kb,ke,first);break;
    case 2:tuned_remainder<2>(in,wr,br,yr,a.C,XS,a.S,width,kb,ke,first);break;
    case 3:tuned_remainder<3>(in,wr,br,yr,a.C,XS,a.S,width,kb,ke,first);break;
    case 4:tuned_remainder<4>(in,wr,br,yr,a.C,XS,a.S,width,kb,ke,first);break;
    case 5:tuned_remainder<5>(in,wr,br,yr,a.C,XS,a.S,width,kb,ke,first);break;
   }
   }
   }
   const int tail=width%8;
   if(tail){
    const int s=width-tail;int channel=0;
    for(;channel<=a.O-10;channel+=10)apply_mask<10>(in+s,a.w.data()+(size_t)channel*a.C,a.b.data()+channel,y+(size_t)channel*a.S+p0+s,a.C,XS,a.S,kb,ke,first,tail);
    if(channel<a.O){
    const float*w=a.w.data()+(size_t)channel*a.C;const float*b=a.b.data()+channel;float*yy=y+(size_t)channel*a.S+p0+s;
    switch(a.O-channel){
     case 1:apply_mask<1>(in+s,w,b,yy,a.C,XS,a.S,kb,ke,first,tail);break;
     case 2:apply_mask<2>(in+s,w,b,yy,a.C,XS,a.S,kb,ke,first,tail);break;
     case 3:apply_mask<3>(in+s,w,b,yy,a.C,XS,a.S,kb,ke,first,tail);break;
     case 4:apply_mask<4>(in+s,w,b,yy,a.C,XS,a.S,kb,ke,first,tail);break;
     case 5:apply_mask<5>(in+s,w,b,yy,a.C,XS,a.S,kb,ke,first,tail);break;
     case 6:apply_mask<6>(in+s,w,b,yy,a.C,XS,a.S,kb,ke,first,tail);break;
     case 7:apply_mask<7>(in+s,w,b,yy,a.C,XS,a.S,kb,ke,first,tail);break;
     case 8:apply_mask<8>(in+s,w,b,yy,a.C,XS,a.S,kb,ke,first,tail);break;
     case 9:apply_mask<9>(in+s,w,b,yy,a.C,XS,a.S,kb,ke,first,tail);break;
    }
   }
   }
   kb=ke;
  }
  p0+=width;
 }
}
extern "C" size_t p5_packed_weight_bytes(void*p){return p?(((P5Context*)p)->wp.size()+((P5Context*)p)->wp6.size()+((P5Context*)p)->wp8.size())*sizeof(float):0;}
extern "C" size_t p5_workspace_bytes(void*p){return p?(((P5Context*)p)->scratch.size()+((P5Context*)p)->output_scratch.size())*sizeof(float):0;}
static __attribute__((noinline)) void current_driver(P5Context&a,const float*x,float*y){
 if(a.C==80&&a.S==400&&a.O==80)tuned_driver<5,128,64,0,true,true>(a,x,y);
 else if(a.C==384&&a.S==100&&a.O==256)tuned_driver<5,0,64,80,true,true>(a,x,y);
 else tuned_driver<5,256,64,80,true,true>(a,x,y);
}
template<int C,int S,int O,int M,int U,int Block,bool Chunk,bool Tail6,int Panel,int PS,bool PF,bool Balance,bool TailVec,bool Force,bool Direct=false,bool Batch=false,bool Stream=false>
static __attribute__((always_inline)) inline void chunk_driver(P5Context&a,const float*x,float*y){
 constexpr int XS=Direct?S:PS;
 constexpr int KC=Block==0?(C==384?384:256):Block;
 constexpr int Full=Balance&&M==6&&O%6==4?O-10:(Tail6&&O%5==1?O-6:(O/M)*M);
 for(int p0=0;p0<S;p0+=Panel){const int width=std::min(Panel,S-p0);float*packed=a.panel_data();
  if constexpr(!Chunk&&!Direct){
   if constexpr(Batch){static_assert(C==256&&S==400&&PS==80,"exact primary pack geometry");
    if(width==64)pack_four_rows<64>(x+p0,packed);else pack_four_rows<16>(x+p0,packed);
   }else{for(int k=0;k<C;++k){int s=0;
    for(;s<=width-8;s+=8)_mm256_store_ps(packed+(size_t)k*PS+s,_mm256_loadu_ps(x+(size_t)k*S+p0+s));
    for(;s<width;++s)packed[(size_t)k*PS+s]=x[(size_t)k*S+p0+s];
   }}
  }
  for(int kb=0;kb<C;kb+=KC){const int len=std::min(KC,C-kb);const bool first=kb==0;
   if constexpr(Chunk&&!Direct){for(int k=0;k<len;++k){int s=0;
    for(;s<=width-8;s+=8)_mm256_store_ps(packed+(size_t)k*PS+s,_mm256_loadu_ps(x+(size_t)(kb+k)*S+p0+s));
    for(;s<width;++s)packed[(size_t)k*PS+s]=x[(size_t)(kb+k)*S+p0+s];
   }}
   const float*in=Direct?x+p0+(size_t)kb*S:(Chunk?packed:packed+(size_t)kb*PS);
   int s=0;for(;s<=width-16;s+=16){
    const float*wp=M==5?a.wp.data():a.wp6.data();
    for(int o=0;o<Full;o+=M){const float*w=wp+(size_t)(o/M)*C*M+(size_t)kb*M;
     if(first)fixed_tile<M,true,U,C,XS,S,PF,true,Stream>(in+s,w,a.b.data()+o,y+(size_t)o*S+p0+s,0,len);
     else fixed_tile<M,true,U,C,XS,S,PF,false,Stream>(in+s,w,a.b.data()+o,y+(size_t)o*S+p0+s,0,len);
    }
    if constexpr(Balance&&M==6&&O%6==4){
     apply_fresh<5,2>(in+s,a.w.data()+(size_t)Full*C+kb,a.b.data()+Full,y+(size_t)Full*S+p0+s,C,XS,S,0,len,first);
     apply_fresh<5,2>(in+s,a.w.data()+(size_t)(Full+5)*C+kb,a.b.data()+Full+5,y+(size_t)(Full+5)*S+p0+s,C,XS,S,0,len,first);
    }
    else if constexpr(Tail6&&O%5==1)apply_fresh<6,2>(in+s,a.w.data()+(size_t)Full*C+kb,a.b.data()+Full,y+(size_t)Full*S+p0+s,C,XS,S,0,len,first);
    else if constexpr(O%M>0)apply_fresh<O%M,2>(in+s,a.w.data()+(size_t)Full*C+kb,a.b.data()+Full,y+(size_t)Full*S+p0+s,C,XS,S,0,len,first);
   }
   if(s<width){
    if constexpr(TailVec&&C==384&&S==100&&O==256){
     // This exact path has fullC, four final positions and8-divisible outputs.
     if(first){int o=0;for(;o<=O-24;o+=24)tail_tile<3,Force,C,XS,S>(in+s,a.wp8.data()+(size_t)(o/8)*C*8,a.b.data()+o,y+(size_t)o*S+p0+s);
     if constexpr(O%24==16)tail_tile<2,Force,C,XS,S>(in+s,a.wp8.data()+(size_t)(o/8)*C*8,a.b.data()+o,y+(size_t)o*S+p0+s);}
    }else{int o=0;const int valid=width-s;
    for(;o<=O-10;o+=10)apply_mask<10>(in+s,a.w.data()+(size_t)o*C+kb,a.b.data()+o,y+(size_t)o*S+p0+s,C,XS,S,0,len,first,valid);
    if constexpr(O%10>0)apply_mask<O%10>(in+s,a.w.data()+(size_t)o*C+kb,a.b.data()+o,y+(size_t)o*S+p0+s,C,XS,S,0,len,first,valid);
   }}
  }
 }
}
// Correspondence: proofs/block_major_input_v1/cpp_correspondence.json.
template<bool Compact,bool Stream> static __attribute__((always_inline)) inline void primary_layout(P5Context&a,const float*x,float*y){
 constexpr int C=256,S=400,XS=Compact?16:80;
 float*packed=a.panel_data();
 for(int p0=0;p0<S;p0+=64){
  const int width=std::min(64,S-p0);
  if constexpr(Compact){if(width==64)pack_block_major<64>(x+p0,packed);else pack_block_major<16>(x+p0,packed);}
  else{if(width==64)pack_four_rows<64>(x+p0,packed);else pack_four_rows<16>(x+p0,packed);}
  for(int s=0;s<width;s+=16){
   const float*in=Compact?packed+(size_t)(s/16)*C*16:packed+s;
   for(int o=0;o<252;o+=6)
    fixed_tile<6,true,4,C,XS,S,false,true,Stream>(in,a.wp6.data()+(size_t)(o/6)*C*6,a.b.data()+o,y+(size_t)o*S+p0+s,0,C);
   apply_fresh<4,2>(in,a.w.data()+(size_t)252*C,a.b.data()+252,y+(size_t)252*S+p0+s,C,XS,S,0,C,true);
  }
 }
}
template<int C,int S,int O,int Mode> static __attribute__((always_inline)) inline void select_tail(P5Context&a,const float*x,float*y){
 if constexpr(C==256&&S==400&&O==256){
  if(((uintptr_t)y&63)==0){primary_layout<Mode==1,true>(a,x,y);_mm_sfence();return;}
  primary_layout<Mode==1,false>(a,x,y);
 }
 else if constexpr(C==384&&S==100&&O==256)chunk_driver<C,S,O,5,1,0,false,true,64,80,false,false,true,false>(a,x,y);
 else if constexpr(C==80)chunk_driver<C,S,O,5,2,0,false,false,64,80,false,false,false,false>(a,x,y);
 else chunk_driver<C,S,O,6,2,0,false,false,64,80,false,false,false,false>(a,x,y);
}
template<int Mode> static __attribute__((always_inline)) inline void dispatch_tail(P5Context&a,const float*x,float*y){
 if(a.C==256&&a.S==400&&a.O==256)select_tail<256,400,256,Mode>(a,x,y);else if(a.C==192&&a.S==1600&&a.O==64)select_tail<192,1600,64,Mode>(a,x,y);else if(a.C==512&&a.S==400&&a.O==256)select_tail<512,400,256,Mode>(a,x,y);else if(a.C==80&&a.S==400&&a.O==80)select_tail<80,400,80,Mode>(a,x,y);else if(a.C==384&&a.S==100&&a.O==256)select_tail<384,100,256,Mode>(a,x,y);else current_driver(a,x,y);
}
#define TAIL_VARIANT(ID) extern "C" __attribute__((noinline)) void p5_unroll_##ID(P5Context&a,const float*x,float*y){dispatch_tail<ID>(a,x,y);}
TAIL_VARIANT(0)
TAIL_VARIANT(1)
extern "C" int p5_run(void*p,const float*x,float*y,int v){if(!p||!x||!y||v<0||v>=2)return -1;auto&a=*(P5Context*)p;if(overlap(x,(size_t)a.C*a.S,y,(size_t)a.O*a.S))return -1;switch(v){case 0:p5_unroll_0(a,x,y);break;case 1:p5_unroll_1(a,x,y);break;}return 0;}
