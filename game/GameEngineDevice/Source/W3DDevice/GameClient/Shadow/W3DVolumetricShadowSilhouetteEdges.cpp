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
};

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
