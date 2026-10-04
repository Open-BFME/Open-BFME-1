// ?bfmeInvoke@Gen_006CDF70Target@@QAEXPAX0@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include
// stlport

#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#include "rendobj.h"
#include "scene.h"
#include "dx8wrapper.h"

extern void j_0003c93e();

class Rva006DED60RoadBuffer
{
};

class Gen_006CDF70Target : public RenderObjClass
{
protected:
	unsigned char m_unmodeledBaseHeightMap[0x2ff4 - sizeof(RenderObjClass)];
	void *m_map;
	unsigned char m_unmodeled2FF8[0x304c - 0x2ff8];
	VertexMaterialClass *m_vertexMaterialClass;
	unsigned char m_unmodeled3050[0x30b4 - 0x3050];
	Rva006DED60RoadBuffer *m_roadBuffer;

public:
	void bfmeInvoke(void *, void *);
};

void Gen_006CDF70Target::bfmeInvoke(void *first, void *second)
{
	if (m_map == 0)
		return;
	if (Scene == 0)
		return;
	if (m_roadBuffer == 0)
		return;

	Matrix3D transform(Transform);
	DX8Wrapper::Set_Transform(D3DTS_WORLD, transform);
	DX8Wrapper::Set_Material(m_vertexMaterialClass);
	typedef void (Rva006DED60RoadBuffer::*Fn)(void *, void *);
	union { void (*fn)(); Fn call; } u = { j_0003c93e };
	(m_roadBuffer->*u.call)(first, second);
}
