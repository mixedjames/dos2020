global _startOfLockedData
global _startOfLockedCode

global _endOfLockedData
global _endOfLockedCode

group dgroup LOCKDATA LOCKDAT2 LOCKDAT3

segment LOCKDATA class=data use32
  _startOfLockedData: dd 24

segment LOCKDAT3 class=data use32

segment LOCKDAT2 class=data use32
  _endOfLockedData: dd 24

segment LOCKCODE class=code use32
  _startOfLockedCode: dd 34

segment LOCKCOD2 class=code use32
  _endOfLockedCode: dd 34

