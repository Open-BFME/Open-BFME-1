// ?getEdges@BfmeShadowEdgeSource@@QAEPAUBfmeShadowEdge@@PAH@Z
// partial score=0.177 date=2026-09-23
// cl: /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BfmeShadowEdgeSource::getEdges (BFME MeshGeometryClass edge cache), retail
// 0x00928820 size 1727, ret 4 at +0x6BC.  Whole body in retail call order
// (43 calls line up one for one under /Ob1): Resize(faces*3/2), vector<int>
// remap + map<Gen_p12pod,int> vertex dedup keyed by (int)(float)(int)(v*100.0f)
// (the "g_bfmeScaleBC" operand is the .rdata literal 100.0f), hash_map<pair<int,
// int>,int,Rva00928590Hash,Rva00928590Eq> edge table, two triangle passes, three
// TheBfmeAwakenDebug warnings, zero-edge fallback, Resize(n).
// Remaining wall is register allocation: retail keeps this in ebp, the zero
// constant in ebx coalesced into remap._M_finish, edge in edi, and the
// quantized ints in memory; ours keeps this in ebx and a live zero in edi.
// Landing also needs pins for ctor/dtor ICF bodies 0x009281A0 (map ctor),
// 0x00927AC0 (_Rb_tree dtor), 0x009287D0 (hash_map ctor), 0x00928220
// (hashtable dtor), whose ledger names carry other placeholder types.

#include <map>
#include <vector>
#include <hash_map>

typedef unsigned int UnsignedInt;

struct Gen_p12pod
{
	int a[3];
};

inline bool compare_tail(const Gen_p12pod &a, const Gen_p12pod &b)
{
	const int a1 = a.a[1];
	return b.a[1] > a1
		|| (!(b.a[1] < a1) && a.a[2] < b.a[2]);
}

inline bool operator<(const Gen_p12pod &a, const Gen_p12pod &b)
{
	const int a0 = a.a[0];
	return b.a[0] > a0 || (!(b.a[0] < a0) && compare_tail(a, b));
}

typedef _STL::pair<int, int> Rva00928590Key;

struct Rva00928590Hash
{
	UnsignedInt operator()( const Rva00928590Key &k ) const
	{
		return ( static_cast<UnsignedInt>( k.second ) << 16 ) + static_cast<UnsignedInt>( k.first );
	}
};

struct Rva00928590Eq
{
	bool operator()( const Rva00928590Key &a, const Rva00928590Key &b ) const
	{
		return a.first == b.first && a.second == b.second;
	}
};

class BfmeAwakenLog
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual BfmeAwakenLog *slot4C(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern void _bfme_debugRecordCallsite(int kind);
extern bool _bfme_debugReportingEnabled();

template <class T> class ShareBufferClass
{
public:
	void Resize(int newsize);

	unsigned char m_head[0x0c];
	T *m_array;
	int m_count;
};

struct MeshGeometrySlot64Element_00923F70
{
	unsigned char Data[16];
};

struct BfmeShadowEdge
{
	unsigned int vertex0;
	unsigned int vertex1;
	unsigned int face0;
	unsigned int face1;
};

struct BfmeShadowTri
{
	unsigned short v[3];
};

struct BfmeShadowVertex
{
	float x;
	float y;
	float z;
};

struct BfmeShadowName
{
	unsigned char m_head[0x0c];
	const char *m_text;
};

class BfmeShadowEdgeSource
{
public:
	BfmeShadowEdge *getEdges(int *count);

private:
	unsigned char m_pad00[0x10];
	BfmeShadowName *m_name10;
	unsigned char m_pad14[0x24 - 0x14];
	int m_faceCount24;
	int m_vertexCount28;
	ShareBufferClass<BfmeShadowTri> *m_tris2c;
	ShareBufferClass<BfmeShadowVertex> *m_verts30;
	unsigned char m_unreconstructed030[0x64 - 0x34];
	ShareBufferClass<MeshGeometrySlot64Element_00923F70> *m_cache64;
};

typedef _STL::hash_map<Rva00928590Key, int, Rva00928590Hash, Rva00928590Eq> BfmeShadowEdgeMap;

BfmeShadowEdge *BfmeShadowEdgeSource::getEdges(int *count)
{
	if (m_cache64 != 0 && m_faceCount24 != 0 && m_vertexCount28 != 0)
	{
	if (m_cache64->m_count != 0)
	{
		*count = m_cache64->m_count;
		return (BfmeShadowEdge *)m_cache64->m_array;
	}

	m_cache64->Resize(m_faceCount24 * 3 / 2);
	BfmeShadowEdge *edge = (BfmeShadowEdge *)m_cache64->m_array;

	_STL::vector<int> remap;
	{
		_STL::map<Gen_p12pod, int> unique;
		const BfmeShadowVertex *vert = m_verts30->m_array;
		for (int v = 0; v < m_vertexCount28; ++v, ++vert)
		{
			BfmeShadowVertex q;
			q.x = (float)(int)(vert->x * 100.0f);
			q.y = (float)(int)(vert->y * 100.0f);
			q.z = (float)(int)(vert->z * 100.0f);
			int ix = (int)q.x;
			int iy = (int)q.y;
			int iz = (int)q.z;
			Gen_p12pod key;
			key.a[0] = ix;
			key.a[1] = iy;
			key.a[2] = iz;
			_STL::map<Gen_p12pod, int>::iterator it = unique.find(key);
			if (it == unique.end())
			{
				remap.push_back(unique.size());
				Gen_p12pod newKey;
				newKey.a[0] = ix;
				newKey.a[1] = iy;
				newKey.a[2] = iz;
				unique[newKey] = unique.size();
			}
			else
			{
				remap.push_back((*it).second);
			}
		}
	}

	BfmeShadowEdgeMap edges;
	const BfmeShadowTri *tri = m_tris2c->m_array;
	bool warned = false;
	int f;
	for (f = 0; f < m_faceCount24; ++f, ++tri)
	{
		for (int k = 0; k < 3; ++k)
		{
			int next = remap[tri->v[(k + 1) % 3]];
			int cur = remap[tri->v[k]];
			if (cur > next)
			{
				Rva00928590Key key(cur, next);
				if (!warned && edges.find(key) != edges.end())
				{
					if (_bfme_debugReportingEnabled())
					{
						_bfme_debugRecordCallsite(1);
						TheBfmeAwakenDebug->slot60();
						BfmeAwakenLog *log = TheBfmeAwakenDebug->slot6C(0, 0)->slot38("Geometry for model ");
						log->slot38(m_name10 ? m_name10->m_text : 0)
							->slot38(" shares an edge with more than two triangles, this will cause shadow bugs.")
							->slot4C(2);
					}
					warned = true;
				}
				edges[key] = f;
			}
		}
	}

	tri = m_tris2c->m_array;
	int numEdges = 0;
	warned = false;
	for (f = 0; f < m_faceCount24; ++f, ++tri)
	{
		for (int k = 0; k < 3; ++k)
		{
			int next = remap[tri->v[(k + 1) % 3]];
			int cur = remap[tri->v[k]];
			if (cur < next)
			{
				BfmeShadowEdgeMap::iterator it = edges.find(Rva00928590Key(next, cur));
				if (it == edges.end())
				{
					if (!warned)
					{
						if (_bfme_debugReportingEnabled())
						{
							_bfme_debugRecordCallsite(1);
							TheBfmeAwakenDebug->slot60();
							BfmeAwakenLog *log = TheBfmeAwakenDebug->slot6C(0, 0)->slot38("Geometry for model ");
							log->slot38(m_name10 ? m_name10->m_text : 0)
								->slot38(" contains at least one triangle that doesn't share an edge with another triangle.\nShadow bugs will occur.")
								->slot4C(2);
						}
						warned = true;
					}
				}
				else
				{
					if (numEdges < m_cache64->m_count)
					{
						edge->vertex0 = tri->v[k];
						edge->vertex1 = tri->v[(k + 1) % 3];
						edge->face0 = f;
						edge->face1 = (*it).second;
						++edge;
						++numEdges;
					}
					else
					{
						warned = true;
					}
				}
			}
		}
	}

	if (numEdges != m_faceCount24 * 3 / 2 || warned)
	{
		if (_bfme_debugReportingEnabled())
		{
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->slot60();
			BfmeAwakenLog *log = TheBfmeAwakenDebug->slot6C(0, 0)->slot38("Geometry for model ");
			log->slot38(m_name10 ? m_name10->m_text : 0)
				->slot38(" is not a valid shadow caster, it may contain T-junctions or not be closed. Shadow bugs are more than likely.")
				->slot4C(2);
		}
		if (numEdges == 0)
		{
			edge->face1 = edge->face0 = edge->vertex1 = edge->vertex0 = 0;
			numEdges = 1;
		}
		m_cache64->Resize(numEdges);
	}

	*count = m_cache64->m_count;
	return (BfmeShadowEdge *)m_cache64->m_array;
	}
	*count = 0;
	return 0;
}
