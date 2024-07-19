#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main() {
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;  // spremenljive lastnosti
    struct fb_fix_screeninfo finfo;  // nespremenljive lastnosti

    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) exit(1);
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) exit(2);
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) exit(3);

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres,
           vinfo.bits_per_pixel);

    // assume 32bpp
    // V pomnilniku: B, G, R, prosojnost.
    unsigned char pixel[4] = {255, 255, 0, 0}; 
    int write_size = 4;
    if (vinfo.bits_per_pixel != 32) { // assume 16bpp
        // V pomnilniku: [B, G], [R, prosojnost].
        pixel[1] = 0; // {255, 0}
        int write_size = 2;
    }

    // izpišimo 2^20 pikslov modro-zelene barve (0, 255, 255)
    for (int i = 0; i < 1<<20; i++) {
        write(fbfd, pixel, write_size);
    }

    printf("Press enter to exit...\n");
    getchar();    // Čakamo na izhod.
    close(fbfd);
    return 0;
}
