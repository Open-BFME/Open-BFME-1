// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Open-BFME7: retail 0x00949D00 (164 bytes) is DX8MeshRendererClass::~DX8MeshRendererClass
// from dx8renderer.cpp as built in a TU where operator delete/delete[] are declared throw()
// (docs/shape_levers.md); the port TU cannot carry that declaration without changing its
// other rows, so the class is renamed by macro and only this member is defined here.
#define DX8MeshRendererClass Rva00949D00Renderer
void __cdecl operator delete[](void *) throw();
void __cdecl operator delete(void *) throw();
#define Matrix4x4 Matrix4  // BFME renamed it
#include "../WWLib/wwstring.h"
#define MUTEX_H
#include "dx8renderer.h"
#include "dx8wrapper.h"
#include "dx8polygonrenderer.h"
#include "dx8vertexbuffer.h"
#include "dx8indexbuffer.h"
#include "dx8fvf.h"
#include "dx8caps.h"
#include "dx8rendererdebugger.h"
#include "wwdebug.h"
#include "wwprofile.h"
#include "wwmemlog.h"
#include "rinfo.h"
#include "statistics.h"
#include "meshmdl.h"
#include "vp.h"
#include "decalmsh.h"
#include "matpass.h"
#include "camera.h"
#include "stripoptimizer.h"
#include "meshgeometry.h"

Rva00949D00Renderer::~Rva00949D00Renderer()
{
	Invalidate(true);
	Clear_Pending_Delete_Lists();
	if (texture_category_container_list_skin != NULL) {
		delete texture_category_container_list_skin;
	}
}

void Force_Rva00949D00Renderer_DeletingDestructor(Rva00949D00Renderer *value)
{
	delete value;
}
