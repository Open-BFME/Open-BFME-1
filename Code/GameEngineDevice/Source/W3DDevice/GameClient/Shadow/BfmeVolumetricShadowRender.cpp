// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef int Bool;

#define FALSE 0
#define TRUE 1

class FrustumClass
{
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class AABoxClass
{
public:
	Vector3 Center;
	Vector3 Extent;
};

class BaseHeightMapRenderObjClass
{
public:
	bool getMaximumVisibleBox(const FrustumClass &frustum,
		AABoxClass *box, bool ignoreMaxHeight);
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern const FrustumClass *shadowCameraFrustum;

class GlobalData
{
	unsigned char m_unreconstructed_000[0x64];

public:
	unsigned char m_useShadowVolumes;
};

extern GlobalData *TheWritableGlobalData;

class W3DVolumetricShadow
{
public:
	bool intersectsVisibleBounds(const AABoxClass &box) const;
	void updateShadowState();
	bool bfmeIntersectsVisibleBounds(const AABoxClass &box) const;
	void buildBuffer();
	void renderBuffer();

	void *m_vtable;
	unsigned char m_isEnabled;
	unsigned char m_isInvisibleEnabled;
	unsigned char m_unreconstructed_006[0x66];
	W3DVolumetricShadow *m_next;
	W3DVolumetricShadow *m_bufferNext;
};

class IDirect3DDevice8
{
};

typedef long (__stdcall *BfmeSetRenderState)(IDirect3DDevice8 *, unsigned, unsigned);

class W3DRadarFormatCaps
{
	unsigned char m_unreconstructed_000[0x90];

public:
	unsigned m_caps;
};

extern W3DRadarFormatCaps *TheW3DRadarFormatCaps;
extern IDirect3DDevice8 *TheD3DDevice;
extern AABoxClass g_bfmeVisibleShadowBounds;

class W3DVolumetricShadowManager
{
public:
	void setupShadowBuffers();
	void setShadowStencil(Bool frontFace);
	void drawAndRelease(Bool frontFace);
	void renderShadows(void);

private:
	unsigned char m_bfmeBufferFields[8];
	W3DVolumetricShadow *m_shadowList;
	void *m_dynamicShadowVolumesToRender;
};

void W3DVolumetricShadowManager::renderShadows(void)
{
	AABoxClass bbox;

	TheTerrainRenderObject->getMaximumVisibleBox(*shadowCameraFrustum,
		&bbox, TRUE);
	bool setupDone = false;

	if (TheWritableGlobalData->m_useShadowVolumes)
	{
		W3DVolumetricShadow *shadow = m_shadowList;
		W3DVolumetricShadow *bufferedShadow = 0;
		bool stencilDone = false;

		if (shadow)
		{
		for (; shadow; shadow = shadow->m_next)
			{
				if (shadow->m_isEnabled && !shadow->m_isInvisibleEnabled)
				{
					if (shadow->intersectsVisibleBounds(bbox))
					{
						shadow->updateShadowState();
						if (shadow->bfmeIntersectsVisibleBounds(g_bfmeVisibleShadowBounds))
						{
							shadow->m_bufferNext = bufferedShadow;
							bufferedShadow = shadow;
						}
						else
						{
							if (!setupDone)
							{
								setupDone = TRUE;
								setupShadowBuffers();
							}
							if (!stencilDone)
							{
								stencilDone = TRUE;
								setShadowStencil(FALSE);
							}
							shadow->buildBuffer();
						}
					}
				}
		}
		}

		if (m_dynamicShadowVolumesToRender)
			drawAndRelease(FALSE);

		if (bufferedShadow)
			{
				if (!setupDone)
				{
					setupDone = TRUE;
					setupShadowBuffers();
				}
				setShadowStencil(TRUE);
				for (shadow = bufferedShadow; shadow; shadow = shadow->m_bufferNext)
					shadow->renderBuffer();

				if (m_dynamicShadowVolumesToRender)
					drawAndRelease(TRUE);
			}
	}

	if (TheW3DRadarFormatCaps->m_caps & 0x100)
	{
		IDirect3DDevice8 *device = TheD3DDevice;
		(*(BfmeSetRenderState **)device)[57](device, 0xB9, 0);
	}
}
