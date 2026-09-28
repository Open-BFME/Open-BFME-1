// ?updateBuffers@Rva006F8F00Owner@@QAEXXZ
// Retail 0x006F8F00: 264-byte body through ret; following bytes are INT3.
// Native floor list and buffer locks reproduce the retail ABI and EH lifetime.
// Preserve the banked owner/method names until independent identity is settled.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "../../../../Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h"
#include "../../../../Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.h"
#include <list>

typedef int Int;
typedef unsigned short UnsignedShort;

void W3DRadarResetLock(void);

char __cdecl bfmeUnlock1179(void);

class Rva006F8F00Payload
{
public:
	void perNode(void *indexArray, void *vertexArray, int *outIdx, int *outVtx);
};

struct Rva006F8F00ResetLock {
 Rva006F8F00ResetLock() { W3DRadarResetLock(); }
 ~Rva006F8F00ResetLock() { bfmeUnlock1179(); }
};

class Rva006F8F00Owner
{
public:
	void updateBuffers();

private:
	unsigned char m_pad0[4];
	VertexBufferClass *m_vertexBuffer;			// +4
	IndexBufferClass *m_indexBuffer;			// +8
	unsigned char m_pad0c[8];
	Int m_curVtx;						// +0x14
	Int m_curIdx;						// +0x18
	unsigned char m_pad1c[4];
	_STL::list<Rva006F8F00Payload *> m_listHead;				// +0x20 (native list sentinel pointer)
	void *m_guard24;					// +0x24
	unsigned char m_guard28;				// +0x28
};

void Rva006F8F00Owner::updateBuffers()
{
	if (m_indexBuffer == 0)
		return;
	if (m_vertexBuffer == 0)
		return;
	if (m_guard28 == 0)
		return;
	if (m_guard24 == 0)
		return;

	m_curVtx = 0;
	m_curIdx = 0;

	Rva006F8F00ResetLock resetLock;

	IndexBufferClass::WriteLockClass lockIdx(m_indexBuffer, 0x2000);
	VertexBufferClass::WriteLockClass lockVtx(m_vertexBuffer, 0x2000);

	void *vertexArray = lockVtx.Get_Vertex_Array();
	void *indexArray = lockIdx.Get_Index_Array();
	for (_STL::list<Rva006F8F00Payload *>::iterator node = m_listHead.begin(); node != m_listHead.end(); ++node)
	{
		(*node)->perNode(indexArray, vertexArray, &m_curIdx, &m_curVtx);
	}

}
