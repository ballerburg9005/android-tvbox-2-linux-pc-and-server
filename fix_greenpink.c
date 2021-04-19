#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>

static volatile uint32_t *mptr;

#define OSD1_HDR2_CTRL 0x38A0

int main(int argc, char **argv)
{
        int fd ;
        if ((fd = open ("/dev/mem", O_RDWR | O_SYNC) ) < 0) { printf("Unable to open /dev/mem\n"); return -1; }
        mptr = mmap(0, 0xffff, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0xff900000); // VPU
        if (mptr < 0){ printf("Mmap failed.\n"); return -1; }

        *(volatile uint32_t *)(mptr+OSD1_HDR2_CTRL) = *(volatile uint32_t *)(mptr+OSD1_HDR2_CTRL) & (0xffffffff ^ (0b1111 << 13));

        return 0;
}

// :!gcc fix_greenpink.c -o fix_greenpink && ./fix_greenpink
