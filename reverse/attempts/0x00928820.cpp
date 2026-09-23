// ?getEdges@BfmeShadowEdgeSource@@QAEPAUBfmeShadowEdge@@PAH@Z
// partial score=0.0 date=2026-09-22
// cl: /DNDEBUG /MD

struct BfmeShadowEdge
{
	unsigned int vertex0;
	unsigned int vertex1;
	unsigned int face0;
	unsigned int face1;
};

class BfmeShadowEdgeSource
{
public:
	BfmeShadowEdge *getEdges(int *count);
	char m_unreconstructed000[0x24];
	int m_faceCount24;
	int m_vertexCount28;
	void *m_indices2c;
	char m_unreconstructed030[0x64 - 0x30];
	struct EdgeCache {
		char m_unreconstructed000[0x0c];
		BfmeShadowEdge *m_edges0c;
		int m_count10;
	} *m_cache64;
};

// Partial retail reconstruction at 0x00928820.  The caller proves this ABI,
// and the warm-cache and empty-mesh branches are direct retail observations.
BfmeShadowEdge *BfmeShadowEdgeSource::getEdges(int *count)
{
	if (m_cache64 == 0 || m_faceCount24 == 0 || m_vertexCount28 == 0) {
		*count = 0;
		return 0;
	}
	if (m_cache64->m_count10 != 0) {
		*count = m_cache64->m_count10;
		return m_cache64->m_edges0c;
	}
	*count = 0;
	return 0;
}

struct BfmeShadowMesh
{
	unsigned char unreconstructed000[ 0xC8 ];
	BfmeShadowEdgeSource *edgeSource;
};

struct BfmeSilhouetteEdge
{
	unsigned int start;
	unsigned int end;
};

class BfmeVolumetricShadowSilhouette
{
	BfmeShadowMesh *m_mesh;
	unsigned int m_unreconstructed004;
	unsigned char *m_faceStates;
	BfmeSilhouetteEdge *m_edges;
	int m_edgeCount;

public:
	void buildEdges();
};

void BfmeVolumetricShadowSilhouette::buildEdges()
{
	BfmeShadowMesh *mesh = m_mesh;
	BfmeSilhouetteEdge *out = m_edges;
	int sourceCount;
	int *sourceCountPtr = &sourceCount;
	m_edgeCount = 0;

	BfmeShadowEdgeSource *edgeSource = mesh->edgeSource;
	BfmeShadowEdge *source = edgeSource->getEdges(sourceCountPtr);
	while (sourceCount != 0)
	{
		unsigned char state0 = m_faceStates[source->face0];
		if (state0 != m_faceStates[source->face1])
		{
			if (state0 != 0)
			{
				out->start = source->vertex0;
				out->end = source->vertex1;
			}
			else
			{
				out->start = source->vertex1;
				out->end = source->vertex0;
			}
			++out;
			++m_edgeCount;
		}
		--sourceCount;
		++source;
	}
}
