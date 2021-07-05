#ifndef VBE2_H
#define VBE2_H

#define VBE2_ERR_NOT_A_VALID_INSTANCE (1);
#define VBE2_ERR_STALLED (2);
#define VBE2_ERR_FAILED (3);

typedef unsigned char jbyte;
typedef unsigned int jword;
typedef unsigned long jdword;

struct VBE2Instance;
typedef struct VBE2Instance* VBE2;

typedef struct VBE2_InfoBlock {

  char VbeSignature[4];
  jword VbeVersion;
  char far* OemStringPtr;
  jbyte Capabilities[4];
  jword far* VideoModePtr;
  jword TotalMemory;
  jword OemSoftwareRev;
  char far* OemVendorNamePtr;
  char far* OemProductNamePtr;
  char far* ProductRevPtr;
  jbyte Reserved[222];
  jbyte OemData[256];

} VBE2_Info;

typedef struct VBE_ModeInfo {
  /* Mandatory information for all VBE revisions */
  jword ModeAttributes;
  jbyte WinAAttributes;
  jbyte WinBAttributes;
  jword WinGranularity;
  jword WinSize;
  jword WinASegment;
  jword WinBSegment;
  jdword WinFuncPtr;
  jword BytesPerScanLine;

  /* Mandatory information for VBE 1.2 and above */
  jword XResolution;
  jword YResolution;
  jbyte XCharSize;
  jbyte YCharSize;
  jbyte NumberOfPlanes;
  jbyte BitsPerPixel;
  jbyte NumberOfBanks;
  jbyte MemoryModel;
  jbyte BankSize;
  jbyte NumberOfImagePages;
  jbyte Reserved1;

  /* Direct Color fields (required for direct/6 and YUV/7 memory models) */
  jbyte RedMaskSize;
  jbyte RedFieldPosition;
  jbyte GreenMaskSize;
  jbyte GreenFieldPosition;
  jbyte BlueMaskSize;
  jbyte BlueFieldPosition;
  jbyte RsvdMaskSize;
  jbyte RsvdFieldPosition;
  jbyte DirectColorModeInfo;

  /* Mandatory information for VBE 2.0 and above */
  jdword PhysBasePtr;
  jdword OffScreenMemOffset;
  jword OffScreenMemSize;
  jbyte Reserved2[206];
} VBE2_ModeInfo;

VBE2 VBE2_Acquire(void);

void VBE2_Release(VBE2);

int VBE2_IsValid(VBE2);

int VBE2_GetInfo(VBE2, VBE2_Info*);

int VBE2_GetModeInfo(VBE2, jword, VBE2_ModeInfo*);

#endif /* VBE2_H */