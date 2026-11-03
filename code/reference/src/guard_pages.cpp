#include "p2.h"
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
 if(p2_validate_shape(0,1,1)!=-1||p2_validate_shape(1,-1,1)!=-1||p2_validate_shape(1,1,INT_MAX)!=-1||p2_validate_shape(INT_MAX,INT_MAX,1)!=-1)return 1;
 std::set<std::tuple<int,int,int>> cases;
 for(int v=0;v<p2_variant_count();++v){int M=p2_variant_M(v),N=p2_variant_N(v);if(!M)continue;
  for(int C:{1,3,17})for(int dO:{-1,0,1})for(int dS:{-1,0,1})if(M+dO>0&&N+dS>0)cases.emplace(C,N+dS,M+dO);
 }
 for(int S:{63,64,65,255,256,257})cases.emplace(17,S,9);
 size_t calls=0;
 for(auto shape:cases){int C,S,O;std::tie(C,S,O)=shape;
  for(bool end:{false,true})for(bool bias:{false,true}){
   Guarded x((size_t)C*S,end),w((size_t)O*C,end),b(O,end),y((size_t)O*S,end);
   for(int k=0;k<C*S;++k)x.data[k]=(k%17-8)*.0625f;
   for(int k=0;k<O*C;++k)w.data[k]=(k%11-5)*.0625f;
   for(int o=0;o<O;++o)b.data[o]=o*.03125f;
   std::vector<double> ref((size_t)O*S);
   for(int o=0;o<O;++o)for(int s=0;s<S;++s){double z=bias?b.data[o]:0;for(int k=0;k<C;++k)z+=(double)x.data[k*S+s]*w.data[o*C+k];ref[o*S+s]=z;}
   void* ctx=p2_create(C,S,O,w.data,bias?b.data:nullptr);if(!ctx)return 2;
   x.protect(PROT_READ);w.protect(PROT_NONE);b.protect(PROT_NONE);
   for(int v=0;v<p2_variant_count();++v){
    if(p2_run(ctx,x.data,y.data,v))return 3;
    for(int k=0;k<O*S;++k)if(!std::isfinite(y.data[k])||std::abs(y.data[k]-ref[k])>1e-4+1e-4*std::abs(ref[k])){std::fprintf(stderr,"FAIL v=%d C=%d S=%d O=%d end=%d\n",v,C,S,O,end);return 4;}
    ++calls;
   }p2_destroy(ctx);
  }
 }
 std::printf("PASS: %zu optimized-library calls across %zu shapes; leading/trailing guard pages, read-only inputs, inaccessible original weights/bias, size rejection\n",calls,cases.size());
}
