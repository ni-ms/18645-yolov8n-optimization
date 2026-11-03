#include "candidate.h"
#include <sys/mman.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <set>
#include <tuple>
#include <climits>
struct Guarded {
 void* map; size_t total,usable,page; float* data;
 Guarded(size_t n,bool at_end){
  page=(size_t)sysconf(_SC_PAGESIZE);usable=((n*sizeof(float)+page-1)/page)*page;total=usable+2*page;
  map=mmap(nullptr,total,PROT_NONE,MAP_PRIVATE|MAP_ANON,-1,0);if(map==MAP_FAILED)std::abort();
  char* start=(char*)map+page;if(mprotect(start,usable,PROT_READ|PROT_WRITE))std::abort();
  data=(float*)(at_end?start+usable-n*sizeof(float):start);
 }
 void protect(int p){if(mprotect((char*)map+page,usable,p))std::abort();}
 ~Guarded(){munmap(map,total);}
};
int main(){
 if(p5_validate_shape(0,1,1)!=-1||p5_validate_shape(1,-1,1)!=-1||p5_validate_shape(1,1,INT_MAX)!=-1||p5_validate_shape(INT_MAX,INT_MAX,1)!=-1)return 1;
 std::set<std::tuple<int,int,int>> cases;
 for(int C:{1,2,3,4,17,63,64,65,66,95,96,97,127,128,129,192,256,512})
  for(int S:{7,8,9,15,16,17,31,32,33,63,64,65})
   for(int O:{1,2,3,4,5,6,7,8,9,10,11,12,13})cases.emplace(C,S,O);
 for(int C:{255,257,511,513})for(int S:{15,16,17,63,64,65})for(int O:{1,4,5,6})cases.emplace(C,S,O);
 cases.emplace(80,400,80);cases.emplace(192,1600,64);cases.emplace(256,400,256);cases.emplace(512,400,256);cases.emplace(384,100,256);
 for(int C:{1,65,129})for(int valid=1;valid<=7;++valid)for(int O:{1,4,5,6}){
  cases.emplace(C,valid,O);cases.emplace(C,16+valid,O);
 }
 size_t calls=0;
 for(auto shape:cases){int C,S,O;std::tie(C,S,O)=shape;
  for(bool end:{false,true})for(bool bias:{false,true})for(int shift=0;shift<((C==256&&S==400&&O==256)?2:1);++shift){
   Guarded x((size_t)C*S,end),w((size_t)O*C,end),b(O,end),y((size_t)O*S+shift,end);
   float*output=y.data+shift;
   for(int k=0;k<C*S;++k)x.data[k]=(k%17-8)*.0625f;
   for(int k=0;k<O*C;++k)w.data[k]=(k%11-5)*.0625f;
   for(int o=0;o<O;++o)b.data[o]=o*.03125f;
   std::vector<double> ref((size_t)O*S);
   for(int o=0;o<O;++o)for(int s=0;s<S;++s){double z=bias?b.data[o]:0;for(int k=0;k<C;++k)z+=(double)x.data[k*S+s]*w.data[o*C+k];ref[o*S+s]=z;}
   void* ctx=p5_create(C,S,O,w.data,bias?b.data:nullptr);if(!ctx)return 2;
   if(p5_packed_weight_bytes(ctx)!=(((size_t)(O/5)*5+(size_t)(O/6)*6)*C+((C==384&&S==100&&O==256)?(size_t)O*C:0))*sizeof(float))return 7;
   if(p5_workspace_bytes(ctx)!=((size_t)C*96+16+(S==100?(size_t)O*112+16:0))*sizeof(float))return 6;
   if(p5_run(ctx,x.data,x.data,0)!=-1||p5_run(ctx,x.data,output,-1)!=-1||p5_run(ctx,x.data,output,p5_variant_count())!=-1)return 5;
   x.protect(PROT_READ);w.protect(PROT_NONE);b.protect(PROT_NONE);
   for(int v=0;v<p5_variant_count();++v){
    if(p5_run(ctx,x.data,output,v))return 3;
    for(int k=0;k<O*S;++k)if(!std::isfinite(output[k])||std::abs(output[k]-ref[k])>1e-4+1e-4*std::abs(ref[k])){std::fprintf(stderr,"FAIL v=%d C=%d S=%d O=%d end=%d\n",v,C,S,O,end);return 4;}
    ++calls;
   }p5_destroy(ctx);
  }
 }
 std::printf("PASS: %zu candidate-library calls across %zu shapes; leading/trailing guard pages, read-only inputs, inaccessible original weights/bias, size rejection\n",calls,cases.size());
}
