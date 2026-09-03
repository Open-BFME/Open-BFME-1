// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// BFME buffer-owner draw/release helper at 0x007C1BF0.  The owner name is
// address-derived: retail exposes the two write-lock destructors and the
// buffer layout, but no named caller for this wrapper.

typedef bool Bool;

class VertexBufferLockClass
{
protected:
	void *m_vertexBuffer;
	void *m_vertices;
};

class VertexBufferClass
{
public:
	class WriteLockClass : public VertexBufferLockClass
	{
	public:
		__declspec(noinline) ~WriteLockClass();
	};
};

class IndexBufferClass
{
public:
	class WriteLockClass
	{
		void *m_indexBuffer;
		unsigned short *m_indices;

	public:
		__declspec(noinline) ~WriteLockClass();
	};
};

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

class ShaderClass
{
public:
	static ShaderClass _PresetOpaqueShader;
};

namespace Debug_Statistics
{
	class ShaderClass;
}

extern void d_009373a0();
typedef void (__cdecl *BfmeRecordStatistics)(int, int,
	const Debug_Statistics::ShaderClass &);

extern IDirect3DDevice9 *TheD3DDevice;
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
		reinterpret_cast<const Debug_Statistics::ShaderClass &>(ShaderClass::_PresetOpaqueShader));

	IDirect3DDevice9 *device = TheD3DDevice;
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
