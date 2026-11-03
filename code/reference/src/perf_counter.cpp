#include <cstdint>
#include <cerrno>
#include <linux/perf_event.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <unistd.h>
extern "C" int p2_cycles_open(){
 perf_event_attr a{};a.size=sizeof(a);a.type=PERF_TYPE_HARDWARE;a.config=PERF_COUNT_HW_CPU_CYCLES;a.disabled=1;a.exclude_kernel=1;a.exclude_hv=1;a.read_format=PERF_FORMAT_TOTAL_TIME_ENABLED|PERF_FORMAT_TOTAL_TIME_RUNNING;
 int fd=(int)syscall(__NR_perf_event_open,&a,0,-1,-1,0);return fd<0?-errno:fd;
}
extern "C" int p2_cycles_begin(int fd){return ioctl(fd,PERF_EVENT_IOC_RESET,0)||ioctl(fd,PERF_EVENT_IOC_ENABLE,0)?-1:0;}
extern "C" int p2_cycles_end(int fd,unsigned long long*out){if(ioctl(fd,PERF_EVENT_IOC_DISABLE,0))return -1;return read(fd,out,3*sizeof(*out))==3*sizeof(*out)?0:-1;}
extern "C" void p2_cycles_close(int fd){close(fd);}
