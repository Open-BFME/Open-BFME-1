// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc-

typedef bool Bool;
typedef int Int;

class Geometry
{
public:
	Geometry()
		: m_vertices(0),
		  m_indices(0),
		  m_numPolygons(0),
		  m_numVertices(0),
		  m_numActivePolygons(0),
		  m_numActiveVertices(0),
		  m_flags(0),
		  m_visibleState(8)
	{
	}

	Int Create(Int numVertices, Int numPolygons);
	void scalarDeletingDestructor(unsigned int flags);
	Int GetFlags() { return m_flags; }

	void *m_vertices;
	void *m_indices;
	Int m_numPolygons;
	Int m_numVertices;
	Int m_numActivePolygons;
	Int m_numActiveVertices;
	Int m_flags;
	char m_padding[0x28];
	Int m_visibleState;
};

class Rva007B12F0Base
{
public:
	void *m_vtable;
	Bool m_isEnabled;
	Bool m_isInvisibleEnabled;
	char m_padding[0x52];
};

struct BfmeVolumetricShadowRenderTask
{
	void *m_nextTask;
	void *m_parentShadow;
	unsigned char m_meshIndex;
	unsigned char m_lightIndex;
	char m_padding[2];
};

class W3DVolumetricShadow : public Rva007B12F0Base
{
	char m_padding58[0x28];
	Geometry *m_shadowVolume[1][160];
	void *m_shadowVolumeVB[1][160];
	void *m_shadowVolumeIB[1][160];
	BfmeVolumetricShadowRenderTask m_shadowVolumeRenderTask[160];
	Int m_shadowVolumeCount[160];
	char m_lightPosHistory[160 * 12];
	char m_objectXformHistory[160 * 64];
	void *m_silhouetteIndex[160];
	short m_numSilhouetteIndices[160];
	short m_maxSilhouetteEntries[160];

protected:
	Bool allocateShadowVolume(Int volumeIndex, Int meshIndex, Int flags);
};

Bool W3DVolumetricShadow::allocateShadowVolume(Int volumeIndex, Int meshIndex, Int flags)
{
	Int numVertices, numPolygons;
	Geometry *shadowVolume;

	if (volumeIndex < 0 || volumeIndex >= 1)
		return 0;

	if ((shadowVolume = m_shadowVolume[volumeIndex][meshIndex]) == 0)
	{
		Geometry *newShadowVolume = new Geometry;
		shadowVolume = newShadowVolume;
		m_shadowVolumeCount[meshIndex]++;
	}

	if (shadowVolume == 0)
	{
		m_shadowVolumeCount[meshIndex]--;
		return 0;
	}

	m_shadowVolume[volumeIndex][meshIndex] = shadowVolume;
	numPolygons = m_maxSilhouetteEntries[meshIndex];
	numVertices = m_maxSilhouetteEntries[meshIndex] * 2;
	shadowVolume->m_flags |= flags;
	if (shadowVolume->GetFlags() & 1)
	{
		if (!shadowVolume->Create(numVertices, numPolygons))
		{
			shadowVolume->scalarDeletingDestructor(1);
			return 0;
		}
	}

	return 1;
}
