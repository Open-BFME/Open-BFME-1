// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
#include "vector2.h"
// Identity: ZH GeneralsMD WW3D2/streakRender.cpp Init, identical flag switch
// and zero subdivision behavior; BFME restores tile and UV rate setters.
struct W3dEmitterLinePropertiesStruct {
 unsigned int Flags, SubdivisionLevel;
 float NoiseAmplitude, MergeAbortFactor, TextureTileFactor, UPerSec, VPerSec;
 unsigned int Reserved[9];
};
class StreakRendererClass {
public:
 void Init(const W3dEmitterLinePropertiesStruct &props);
 // Retail 0x0095C620 and EA streakRender.h both force subdivision to zero.
 void Set_Current_Subdivision_Level(unsigned int level) {
  SubdivisionLevel = level; SubdivisionLevel = 0;
 }
private:
 // Layout agrees with landed StreakRendererCtor.cpp and retail stores.
 unsigned int Texture, Shader;
 float Width, Color[3], Opacity;
 unsigned int SubdivisionLevel;
 float NoiseAmplitude, MergeAbortFactor, TextureTileFactor;
 unsigned int LastUsedSyncTime;
 Vector2 CurrentUVOffset, UVOffsetDeltaPerMS;
 unsigned int Bits;
};
void StreakRendererClass::Init(const W3dEmitterLinePropertiesStruct &props) {
 if (props.Flags & 1) Bits |= 1; else Bits &= ~1;
 if (props.Flags & 2) Bits |= 2; else Bits &= ~2;
 if (props.Flags & 4) Bits |= 4; else Bits &= ~4;
 if (props.Flags & 8) Bits |= 8; else Bits &= ~8;
 int texture_mode = (props.Flags & 0xff000000) >> 24;
 switch (texture_mode) {
 case 0: Bits &= ~0xff000000; break;
 case 1: Bits &= ~0xff000000; Bits |= 0x01000000; break;
 case 2: Bits &= ~0xff000000; Bits |= 0x02000000; break;
 }
 Set_Current_Subdivision_Level(0);
 NoiseAmplitude = props.NoiseAmplitude;
 MergeAbortFactor = props.MergeAbortFactor;
 float factor = props.TextureTileFactor;
 if (factor > 8.0f) factor = 8.0f;
 else factor = (factor > 0.0f) ? factor : 0.0f;
 TextureTileFactor = factor;
 UVOffsetDeltaPerMS = Vector2(props.UPerSec,props.VPerSec) * 0.001f;
}

