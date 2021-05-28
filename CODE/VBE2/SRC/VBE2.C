#include "VBE2.H"

#include <assert.h>
#include <dos.h>
#include <string.h>

#define VALID_INSTANCE (1<<0)
#define INSTANCE_ACQUIRED (1<<1)
#define STALLED (1<<2)

struct VBE2Instance {
  jword flags;
} static instance_ = { VALID_INSTANCE };

struct VBE2DummyInstance {
  jword flags;
} static invalidInstance_ = { 0 };

VBE2 VBE2_Acquire() {
  if ((instance_.flags & INSTANCE_ACQUIRED) == 0) {
    instance_.flags |= INSTANCE_ACQUIRED;
    return &instance_;
  }
  else {
    return (VBE2) &invalidInstance_;
  }
}

void VBE2_Release(VBE2 vbe2) {
  assert(vbe2);
  vbe2->flags &= ~INSTANCE_ACQUIRED;
}

int VBE2_IsValid(VBE2 vbe2) {
  return vbe2->flags & VALID_INSTANCE;
}

int VBE2_GetInfo(VBE2 vbe2, VBE2_Info* info) {

  struct SREGS sRegs;
  union REGS regs;

  assert(vbe2);
  assert(info);

  if (!(vbe2->flags & VALID_INSTANCE)) { return VBE2_ERR_NOT_A_VALID_INSTANCE; }
  if (vbe2->flags & STALLED) { return VBE2_ERR_STALLED; }

  segread(&sRegs);

  regs.w.ax = 0x4F00;
  regs.w.di = FP_OFF(info);
  sRegs.es = FP_SEG(info);

  memcpy(&info->VbeSignature, "VBE2", 4);

  int86x(0x10, &regs, &regs, &sRegs);

  if (regs.w.ax != 0x004F) {
    return VBE2_ERR_FAILED;
  }

  return 0;
}

int VBE2_GetModeInfo(VBE2 vbe2, jword mode, VBE2_ModeInfo* info) {

  struct SREGS sRegs;
  union REGS regs;

  assert(vbe2);
  assert(info);

  if (!(vbe2->flags & VALID_INSTANCE)) { return VBE2_ERR_NOT_A_VALID_INSTANCE; }
  if (vbe2->flags & STALLED) { return VBE2_ERR_STALLED; }

  segread(&sRegs);

  regs.w.ax = 0x4F01;
  regs.w.cx = mode;
  regs.w.di = FP_OFF(info);
  sRegs.es = FP_SEG(info);

  int86x(0x10, &regs, &regs, &sRegs);

  if (regs.w.ax != 0x004F) {
    return VBE2_ERR_FAILED;
  }

  return 0;
}
