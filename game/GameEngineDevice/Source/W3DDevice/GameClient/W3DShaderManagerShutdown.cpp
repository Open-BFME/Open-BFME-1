// ?shutdown@W3DShaderManager@@SAXXZ
// Retail 0x00717DA0, 187 bytes: two-phase shader-manager shutdown.
// The buffer at VA 0x012F9D1C is created at 0x00716770 by the matched
// DX8VertexBufferClass constructor at 0x0091F2F0; it is not a texture.
// Extra BFME COM-resource member names are unknown and remain address-qualified.
// cl: /DNDEBUG /MD

class BfmeShaderShutdown
{
public:
	static void releaseDependentResources();
};

// Retain the inline call boundary and the separate zero test: MSVC 7.1
// otherwise folds the decrement into a different instruction sequence.
static inline int decrementRef(int *p) { return --*p; }
class ShaderVertexBuffer
{
public:
	virtual void Delete_This();
	int NumRefs;

	void Release_Ref()
	{
		decrementRef(&NumRefs);
		if (NumRefs == 0) Delete_This();
	}
};

struct ShaderComResource
{
	void **VTable;
};

typedef unsigned long (__stdcall *ReleaseResource)(ShaderComResource *);

class ShaderInterface
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual int shutdown();
};

class FilterInterface
{
public:
	virtual void unused0();
	virtual int shutdown();
};

static ShaderInterface *W3DShaders[17];
static FilterInterface *W3DFilters[10];

enum FilterTypes { FT_NULL_FILTER = 0 };

class W3DShaderManager
{
public:
	static void shutdown();

public:
	enum ShaderTypes { ST_INVALID = 0 };

protected:
	static ShaderTypes m_currentShader;
	static FilterTypes m_currentFilter;
	static ShaderComResource *m_resource012F9D14;
	static ShaderComResource *m_resource012F9D18;
	static ShaderComResource *m_resource012F9D24;
};

class VertexBufferClass;
extern VertexBufferClass *ShaderQuadBuffer;
ShaderComResource *W3DShaderManager::m_resource012F9D14 = 0;
ShaderComResource *W3DShaderManager::m_resource012F9D18 = 0;
ShaderComResource *W3DShaderManager::m_resource012F9D24 = 0;

void W3DShaderManager::shutdown()
{
	BfmeShaderShutdown::releaseDependentResources();
	
	m_currentShader = ST_INVALID;
	m_currentFilter = FT_NULL_FILTER;

	if (ShaderQuadBuffer) {
		reinterpret_cast<ShaderVertexBuffer *>(ShaderQuadBuffer)->Release_Ref();
		ShaderQuadBuffer = 0;
	}

	if (m_resource012F9D14)
		((ReleaseResource)m_resource012F9D14->VTable[2])(m_resource012F9D14);
	if (m_resource012F9D18)
		((ReleaseResource)m_resource012F9D18->VTable[2])(m_resource012F9D18);
	if (m_resource012F9D24)
		((ReleaseResource)m_resource012F9D24->VTable[2])(m_resource012F9D24);

	m_resource012F9D24 = 0;
	m_resource012F9D14 = 0;
	m_resource012F9D18 = 0;

	for (int i = 0; i < 17; ++i) {
		if (W3DShaders[i])
			W3DShaders[i]->shutdown();
	}

	for (int i = 0; i < 10; ++i) {
		if (W3DFilters[i])
			W3DFilters[i]->shutdown();
	}
}
