// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

// Open-BFME7: retail 0x0096CF60 (80 bytes) is MeshMatDescClass::Disable_Backface_Culling with
// BFME's shader layout: alpha test takes bits 18-19 there, so the cull-mode bit is bit 20
// (the port's shader.h still keeps ZH's bit 19, which the other landed rows rely on).  The
// member is defined on a derived view of the class so nothing shared changes; same loop
// over the pass shaders and the per-triangle shader arrays.

#include "winbase_shim.h"
#include "meshmatdesc.h"

class Rva0096CF60MatDesc : public MeshMatDescClass
{
public:
	void disableBackfaceCullingBfme(void);
};

static inline void clearCullBfme(ShaderClass &shader)
{
	*reinterpret_cast<unsigned int *>(&shader) &= ~(1u << 20);
}

void Rva0096CF60MatDesc::disableBackfaceCullingBfme(void)
{
	for (int pass = 0; pass < PassCount; pass++) {
		clearCullBfme(Shader[pass]);
		if (ShaderArray[pass]) {
			for (int tri = 0; tri < ShaderArray[pass]->Get_Count(); tri++) {
				clearCullBfme(ShaderArray[pass]->Get_Element(tri));
			}
		}
	}
}
