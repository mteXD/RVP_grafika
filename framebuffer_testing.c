#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>

void get_screeninfo(int *fbfd, struct fb_var_screeninfo *vinfo,
                    struct fb_fix_screeninfo *finfo) {
    // Odpre datoteko, ki predstavlja virtualni MO v načinu
    // read/write
    *fbfd = open("/dev/fb0", O_RDWR);

    if (*fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened "
           "successfully.\n");

    // Get fixed screen information
    if (ioctl(*fbfd, FBIOGET_FSCREENINFO, finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(*fbfd, FBIOGET_VSCREENINFO, vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }
}

int main() {
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;  // spremenljive lastnosti #to/do
    struct fb_fix_screeninfo finfo;   // nespremenljive lastnosti
    long int screensize = 0, location = 0;
    unsigned char *fbp = 0;
    int x = 0,
        y = 0;    // Where we are going to put the pixel

    get_screeninfo(&fbfd, &vinfo, &finfo);

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres,
           vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes (that's
    // why we divide by 8).
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (unsigned char *) mmap(
        0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);

    if ((int) fbp == -1) {
        perror("Error: failed to map framebuffer device to "
               "memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory "
           "successfully.\n");

    int x_border = 300, y_border = 100;

    // Figure out where in memory to put the pixel
    for (y = 150; y < y_border; y++) {
        for (x = 150; x < x_border; x++) {
            location =
                (x + vinfo.xoffset) * (vinfo.bits_per_pixel / 8) +
                (y + vinfo.yoffset) * finfo.line_length;

            if (vinfo.bits_per_pixel == 32) {
                *(fbp + location) = 100;                // blue
                *(fbp + location + 1) = 15+(x-100)/2;   // green
                *(fbp + location + 2) = 200-(y-100)/5;  // red
                *(fbp + location + 3) = 0;              // No transparency
            } else {                        // assume 16bpp
                int b = 10;
                int g = (x-100)/6;                      // green
                int r = 31-(y-100)/16;                  // red

                unsigned short int t = r << 11 | g << 5 | b;
                *((unsigned short int *) (fbp + location)) = t;
            }
        }
    }

    printf("Press enter to exit...\n");
    getchar();    // Čakamo na izhod.
    munmap(fbp, screensize);
    close(fbfd);
    return 0;
}
