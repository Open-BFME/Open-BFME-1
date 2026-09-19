// cl: /DNDEBUG /MD /EHsc

#include <new>

void __cdecl operator delete[](void *block);

class BfmeShadowRefCount
{
public:
	virtual void Delete_This(void);
	int m_refCount;

	void Release_Ref(void)
	{
		if (--m_refCount == 0)
			Delete_This();
	}
};

struct BfmeShadowGeometry
{
	void *m_verts;
	void *m_indices;
	int m_numPolygon;
	int m_numVertex;
	int m_numActivePolygon;
	int m_numActiveVertex;

	~BfmeShadowGeometry(void)
	{
		if (m_verts)
		{
			::operator delete[](m_verts);
			m_verts = 0;
		}
		if (m_indices)
		{
			::operator delete[](m_indices);
			m_indices = 0;
		}
		m_numActivePolygon = m_numPolygon = 0;
		m_numActiveVertex = m_numVertex = 0;
	}
};

class W3DBufferManager
{
public:
	struct W3DVertexBufferSlot;
	struct W3DIndexBufferSlot;

	void releaseSlot(W3DVertexBufferSlot *slot);
	void releaseSlot(W3DIndexBufferSlot *slot);
};

struct W3DBufferManager::W3DVertexBufferSlot
{
	int unused[7];
};

struct W3DBufferManager::W3DIndexBufferSlot
{
	int unused[7];
};

extern W3DBufferManager *TheBfmeReleaseOwner;

class Rva007B12F0Base
{
public:
	virtual ~Rva007B12F0Base(void) {}

private:
	char m_padding[0x54];
};

class W3DVolumetricShadow : public Rva007B12F0Base
{
	int m_field58;
	int m_field5c;
	float m_field60;
	unsigned char m_field64;
	char m_padding65[3];

	W3DVolumetricShadow *m_next;
	BfmeShadowRefCount *m_geometry;
	void *m_robj;
	float m_shadowLengthScale;
	float m_robjExtent;
	float m_extraExtrusionPadding;

	BfmeShadowGeometry *m_shadowVolume[160];
	W3DBufferManager::W3DVertexBufferSlot *m_shadowVolumeVB[160];
	W3DBufferManager::W3DIndexBufferSlot *m_shadowVolumeIB[160];
	char m_unreconstructed_0800[0x3980];
	short *m_silhouetteIndex[160];
	short m_numSilhouetteIndices[160];
	short m_maxSilhouetteEntries[160];

public:
	virtual ~W3DVolumetricShadow(void);

private:
	void deleteSilhouette(int meshIndex)
	{
		if (m_silhouetteIndex[meshIndex])
			::operator delete[](m_silhouetteIndex[meshIndex]);
		m_silhouetteIndex[meshIndex] = 0;
		m_numSilhouetteIndices[meshIndex] = 0;
	}
};

W3DVolumetricShadow::~W3DVolumetricShadow(void)
{
	int i, j;

	for (j = 0; j < 160; ++j)
		deleteSilhouette(j);

	for (i = 0; i < 1; ++i)
	{
		for (j = 0; j < 160; ++j)
		{
			if (m_shadowVolume[i * 160 + j])
				delete m_shadowVolume[i * 160 + j];
			if (m_shadowVolumeVB[i * 160 + j])
				TheBfmeReleaseOwner->releaseSlot(m_shadowVolumeVB[i * 160 + j]);
			if (m_shadowVolumeIB[i * 160 + j])
				TheBfmeReleaseOwner->releaseSlot(m_shadowVolumeIB[i * 160 + j]);
		}
	}

	if (m_geometry)
	{
		m_geometry->Release_Ref();
		m_geometry = 0;
	}

	m_geometry = 0;
	m_robj = 0;
}
