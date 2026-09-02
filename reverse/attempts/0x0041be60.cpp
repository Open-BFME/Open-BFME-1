// ?updateDrawable@Drawable@@QAEXXZ
// partial score=0.08 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /Ireference/shims/sweep /Ireference/shims/locomotor /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

// Partial reconstruction of Drawable::updateDrawable at 0x0041BE60.
//
// The Zero Hour twin is the control-flow base.  Disabling synchronous C++ EH
// removes the synthetic handler from that body and changes it from 1188 bytes
// to 1061 bytes, agreeing with BFME's handler-free prologue.
//
// Retail BFME is 2437 bytes.  Its extra front half starts with:
//   - frame globals at 0x012F0898 and 0x012ED524;
//   - the attached Object at Drawable+0xFC;
//   - a dirty model-condition pass guarded by Drawable+0x3B3;
//   - module arrays at Drawable+0x150 and +0x154;
//   - transform/subobject dirty flags at +0x319 +0x3B1 and +0x3B2.
// The shared fade/decal block follows.  BFME's corresponding fields are at
// +0xA8 through +0x130 rather than the ZH header offsets, so the next pass must
// introduce the BFME Drawable layout instead of trying to tune register shape
// against the ZH class definition.  Later retail phases allocate/update the
// 0x50-byte TintEnvelope at +0x68, process tint bits 1/8/10/20, update the
// attached envelopes, then perform the final ambient-sound checks.
#include "Drawable.cpp"
