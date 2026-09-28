// cl: /Iinputs/reference/shims/dx8wrapper /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WW3D2

// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "dx8wrapper.h"
#include <math.h>
struct ResolutionAccess007833E0 : DX8Wrapper { using DX8Wrapper::Get_Device_Resolution; };
// Retail copies the six floats then derives display scales from APT and DX8 dimensions.
struct Rva007845D0Transform { float m[6]; };
extern Rva007845D0Transform g_Rva00F0692CTransform;
extern Rva007845D0Transform g_Rva00F06914Transform;
extern int g_Rva0130699CDimensions[4];
extern float g_Rva012BB86CScaleX, g_Rva012BB870ScaleY;
extern float g_Rva012BB874InverseX, g_Rva012BB878InverseY;
extern int g_Rva012BB860TransformMode;
extern float Rva01126A68Threshold;
void Rva00892A00Query(void **, void **);
void setScaledTransform007833E0(const Rva007845D0Transform *transform)
{
 g_Rva00F0692CTransform = *transform;
 // One contiguous output record: bit depth, display width/height, APT width/height.
 // The existing APT query exposes its two 32-bit outputs as void **.
 int dimensions[5];
 bool windowed;
 Rva00892A00Query((void **)&dimensions[3], (void **)&dimensions[4]);
 ResolutionAccess007833E0::Get_Device_Resolution(dimensions[1],dimensions[2],dimensions[0],windowed);
 // Keeping width separately preserves the retail load scheduling.
 int width = dimensions[1];
 if ((int)dimensions[3] != g_Rva0130699CDimensions[0] ||
     (int)dimensions[4] != g_Rva0130699CDimensions[1] ||
     width != g_Rva0130699CDimensions[2] ||
     dimensions[2] != g_Rva0130699CDimensions[3]) {
  if (dimensions[3]) g_Rva012BB86CScaleX = (float)width / (int)dimensions[3];
  else g_Rva012BB86CScaleX = 1.0f;
  if (dimensions[4]) g_Rva012BB870ScaleY = (float)dimensions[2] / (int)dimensions[4];
  else g_Rva012BB870ScaleY = 1.0f;
  if (g_Rva012BB86CScaleX != 0.0f) g_Rva012BB874InverseX = 1.0f / g_Rva012BB86CScaleX;
  else g_Rva012BB874InverseX = 1.0f;
  if (g_Rva012BB870ScaleY != 0.0f) g_Rva012BB878InverseY = 1.0f / g_Rva012BB870ScaleY;
  else g_Rva012BB878InverseY = 1.0f;
  g_Rva0130699CDimensions[0] = (int)dimensions[3];
  g_Rva0130699CDimensions[1] = (int)dimensions[4];
  g_Rva0130699CDimensions[2] = width;
  g_Rva0130699CDimensions[3] = dimensions[2];
 }
 g_Rva00F0692CTransform.m[4] *= g_Rva012BB86CScaleX;
 g_Rva00F0692CTransform.m[5] *= g_Rva012BB870ScaleY;
 g_Rva00F06914Transform = g_Rva00F0692CTransform;
 g_Rva00F0692CTransform.m[0] *= g_Rva012BB86CScaleX;
 g_Rva00F0692CTransform.m[2] *= g_Rva012BB86CScaleX;
 g_Rva00F0692CTransform.m[1] *= g_Rva012BB870ScaleY;
 g_Rva00F0692CTransform.m[3] *= g_Rva012BB870ScaleY;
 // Retail accepts unordered comparisons here; do not rewrite these as <=.
 if (!(fabs(g_Rva00F0692CTransform.m[0] - 1.0f) > Rva01126A68Threshold ) && !(
     fabs(g_Rva00F0692CTransform.m[1]) > Rva01126A68Threshold ) && !(
     fabs(g_Rva00F0692CTransform.m[2]) > Rva01126A68Threshold ) && !(
     fabs(g_Rva00F0692CTransform.m[3] - 1.0f) > Rva01126A68Threshold))
  g_Rva012BB860TransformMode = 3;
 else g_Rva012BB860TransformMode = 1;
}


