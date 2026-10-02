// cl: /Igame/Libraries/Source/WWVegas/WW3D2 /DNDEBUG /DWIN32 /D_WINDOWS /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
#include "dx8wrapper.h"

//
// BFME buffer-owner draw/release helper at 0x007C1BF0.  The owner name is
// address-derived: retail exposes the two write-lock destructors and the
// buffer layout, but no named caller for this wrapper.

typedef bool Bool;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.h


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8vertexbuffer.h


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8indexbuffer.h


struct IDirect3DDevice9;
typedef long (__stdcall *BfmeSetRenderState)(IDirect3DDevice9 *, unsigned, unsigned);
typedef long (__stdcall *BfmeDrawIndexedPrimitive)(IDirect3DDevice9 *, unsigned,
	unsigned, unsigned, unsigned, unsigned, unsigned);

class W3DRadarFormatCaps
{
public:
	unsigned char m_unreconstructed_00[0x90];
	unsigned m_caps;
};

class ShaderClass;
// Not _PresetOpaqueShader: retail records the shadow buffer's own shader at 0x012BBF14
// (bits 0x00101823; Opaque's are 0x0011581B), the one setupRenderState sets.
extern ShaderClass Rva012BBF14Shader;

namespace Debug_Statistics
{
	class ShaderClass;
}

extern void d_009373a0();
typedef void (__cdecl *BfmeRecordStatistics)(int, int,
	const Debug_Statistics::ShaderClass &);

extern W3DRadarFormatCaps *TheW3DRadarFormatCaps;

class BfmeVolumetricShadowBufferLocks
{
	VertexBufferClass *m_vertexBuffer;
	IndexBufferClass *m_indexBuffer;
	unsigned int m_unreconstructed_008;
	VertexBufferClass::WriteLockClass *m_vertexLock;
	IndexBufferClass::WriteLockClass *m_indexLock;
	unsigned int m_vertexCapacity;
	unsigned int m_indexCapacity;

public:
	void drawAndRelease(int frontFace);
};

void BfmeVolumetricShadowBufferLocks::drawAndRelease(int frontFace)
{
	VertexBufferClass::WriteLockClass *vertexLock = m_vertexLock;
	if (vertexLock != 0) {
		vertexLock->VertexBufferClass::WriteLockClass::~WriteLockClass();
		::operator delete(vertexLock);
	}

	IndexBufferClass::WriteLockClass *indexLock = m_indexLock;
	m_vertexLock = 0;
	if (indexLock != 0) {
		indexLock->IndexBufferClass::WriteLockClass::~WriteLockClass();
		::operator delete(indexLock);
	}

	if (m_vertexCapacity == 30000) {
		m_indexLock = 0;
		return;
	}
	m_indexLock = 0;

	unsigned int polygonCount = (30000 - m_indexCapacity) / 3;
	int vertexCount = 30000 - m_vertexCapacity;
	reinterpret_cast<BfmeRecordStatistics>(&d_009373a0)(polygonCount * 2, vertexCount * 2,
		reinterpret_cast<const Debug_Statistics::ShaderClass &>(Rva012BBF14Shader));

	IDirect3DDevice9 *device = reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());
	if (!(TheW3DRadarFormatCaps->m_caps & 0x100)) {
		if (!frontFace) {
			(*(BfmeSetRenderState **)device)[57](device, 0x16, 2);
			(*(BfmeSetRenderState **)device)[57](device, 0x37, 7);
		} else {
			(*(BfmeSetRenderState **)device)[57](device, 0x16, 2);
			(*(BfmeSetRenderState **)device)[57](device, 0x36, 7);
		}
	}
	(*(BfmeDrawIndexedPrimitive **)device)[82](device, 4, 0, 0, vertexCount, 0, polygonCount);

	if (!(TheW3DRadarFormatCaps->m_caps & 0x100)) {
		if (!frontFace) {
			(*(BfmeSetRenderState **)device)[57](device, 0x16, 3);
			(*(BfmeSetRenderState **)device)[57](device, 0x37, 8);
		} else {
			(*(BfmeSetRenderState **)device)[57](device, 0x16, 3);
			(*(BfmeSetRenderState **)device)[57](device, 0x36, 8);
		}
		(*(BfmeDrawIndexedPrimitive **)device)[82](device, 4, 0, 0, vertexCount, 0, polygonCount);
	}
}
