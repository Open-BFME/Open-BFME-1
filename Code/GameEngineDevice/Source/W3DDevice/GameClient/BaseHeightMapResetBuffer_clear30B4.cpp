// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <set>

typedef int Int;

// BFME's road-buffer reset uses the same resource-reference shape and STLport
// tree layout as the adjacent 0x006DED60 constructor / 0x006DEA80 destructor.
// The names stay local because the shared headers describe the Zero Hour road
// buffer, whose fields are a different size and order.
class BaseHeightMapRoadResource
{
public:
	virtual void Delete_This();

	void Release_Ref()
	{
		--m_refs;
		if (m_refs == 0)
			Delete_This();
	}

private:
	int m_refs;
};

struct BaseHeightMapRoadRef
{
	BaseHeightMapRoadResource *m_resource;
	unsigned int m_name;
	unsigned char m_flag;
};

// Reuse the existing four-byte tree payload declaration for the retail
// erase helper at 0x006DB690; its gameplay payload identity is unrecovered.
struct Gen_t_006db690_m4pod
{
	int a[1];
};

bool operator<(const Gen_t_006db690_m4pod &, const Gen_t_006db690_m4pod &);
typedef _STL::_Rb_tree<Gen_t_006db690_m4pod, Gen_t_006db690_m4pod,
	_STL::_Identity<Gen_t_006db690_m4pod>, _STL::less<Gen_t_006db690_m4pod>,
	_STL::allocator<Gen_t_006db690_m4pod> > BaseHeightMapRoadSet;

class BaseHeightMapResetBuffer
{
public:
	void clear30B4();

private:
	BaseHeightMapRoadResource *m_vertexBuffer;
	BaseHeightMapRoadResource *m_indexBuffer;
	int m_numRoads;
	int m_initializedRoads;
	int m_maxRoadVertices;
	int m_maxRoadIndices;
	BaseHeightMapRoadRef m_roadRefs[10];
	unsigned int m_padding90;
	BaseHeightMapRoadSet m_roadSets[10];
	unsigned char m_initialized;
};

static void releaseRoadResource(BaseHeightMapRoadResource *&resource)
{
	if (resource != 0)
	{
		resource->Release_Ref();
		resource = 0;
	}
}

void BaseHeightMapResetBuffer::clear30B4()
{
	for (Int i = 0; i < 10; ++i)
		m_roadSets[i].clear();

	m_initializedRoads = 0;
	m_numRoads = 0;
	m_maxRoadIndices = 0xea60;
	m_maxRoadVertices = 0x7530;

	for (Int i = 0; i < 10; ++i)
		releaseRoadResource(m_roadRefs[i].m_resource);

	m_padding90 = 0;
}
