// ?shutdown@W3DShaderManager@@SAXXZ
// partial score=0.58 date=2026-09-02
// cl: /DNDEBUG /MD

class BfmeShaderShutdown
{
public:
	static void releaseDependentResources();
};

class RefCountedTexture
{
public:
	virtual void Delete_This();
	int NumRefs;

	void Release_Ref()
	{
		--NumRefs;
		if (NumRefs == 0)
			Delete_This();
	}
};

struct Direct3DSurface
{
	void **VTable;
};

typedef unsigned long (__stdcall *ReleaseSurface)(Direct3DSurface *);

class ShaderInterface
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual void shutdown();
};

class FilterInterface
{
public:
	virtual void unused0();
	virtual void shutdown();
};

static ShaderInterface *W3DShaders[17];
static FilterInterface *W3DFilters[10];

class W3DShaderManager
{
public:
	static void shutdown();

protected:
	static int m_currentShader;
	static int m_currentFilter;
	static RefCountedTexture *m_renderTexture;
	static Direct3DSurface *m_oldRenderSurface;
	static Direct3DSurface *m_newRenderSurface;
	static Direct3DSurface *m_oldDepthSurface;
};

void W3DShaderManager::shutdown()
{
	BfmeShaderShutdown::releaseDependentResources();
	RefCountedTexture *texture = m_renderTexture;
	m_currentShader = 0;
	m_currentFilter = 0;

	if (texture) {
		texture->Release_Ref();
		m_renderTexture = 0;
	}

	if (m_oldRenderSurface)
		((ReleaseSurface)m_oldRenderSurface->VTable[2])(m_oldRenderSurface);
	if (m_newRenderSurface)
		((ReleaseSurface)m_newRenderSurface->VTable[2])(m_newRenderSurface);
	if (m_oldDepthSurface)
		((ReleaseSurface)m_oldDepthSurface->VTable[2])(m_oldDepthSurface);

	m_oldDepthSurface = 0;
	m_oldRenderSurface = 0;
	m_newRenderSurface = 0;

	for (int i = 0; i < 17; ++i) {
		if (W3DShaders[i])
			W3DShaders[i]->shutdown();
	}

	for (int i = 0; i < 10; ++i) {
		if (W3DFilters[i])
			W3DFilters[i]->shutdown();
	}
}
