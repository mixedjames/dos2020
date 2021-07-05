#include <stdio.h>
#include <dos.h>
#include "VBE2.H"

static void print_mode(VBE2, jword mode);

int main() {

  VBE2 vbe2;
  VBE2_Info vib;
  jword far* modes;

  vbe2 = VBE2_Acquire();
  if (!VBE2_IsValid(vbe2)) {
    puts("!VBE2_IsValid(...);");
  }

  VBE2_GetInfo(vbe2, &vib);

  printf("VBE version:\t%.4x\n", vib.VbeVersion);
  printf("OEM string:\t%Fs\n", vib.OemStringPtr);
  printf("Adapter memory: %d kb\n", vib.TotalMemory * 64);
  printf("Vendor name:\t%Fs\n", vib.OemVendorNamePtr);
  printf("Product name:\t%Fs\n", vib.OemProductNamePtr);
  printf("Revision:\t%Fs\n", vib.ProductRevPtr);

  modes = vib.VideoModePtr;
  for (; *modes != 0xFFFF; modes++) {
    print_mode(vbe2, *modes);
  }

  return 0;
}

static void print_mode(VBE2 vbe2, jword mode) {

  VBE2_ModeInfo mib;
  VBE2_GetModeInfo(vbe2, mode, &mib);

  if (mib.BitsPerPixel != 8) {
    return;
  }

  printf("%ux%u @ %u; ", mib.XResolution, mib.YResolution, (jword)mib.BitsPerPixel);
  printf("Attr: %.4x, Memory model: %.2x; ", mib.ModeAttributes, (jword)mib.MemoryModel);
  printf("Ptr = %.8lx\n", mib.PhysBasePtr);
}