// cl: /EHsc
// stlport
// Open-BFME: GeometryInfo copy constructor, retail 0x000FFD10.
//
// BFME's GeometryInfo is larger than the older reference declaration: it has
// two STL vectors at +0x2C and +0x38, followed by the cached extent fields.
// The first vector's 0x24-byte element contains a StringBase<char> at +0x1C;
// the second vector's 0x10-byte element contains one at +0x0C.  These are the
// two member-copy calls visible in the retail constructor.  Their owning
// StringBase<char> members are non-trivial: normal GeometryInfo destruction
// destroys the record vector through 0x000FF7D0, then the shape vector through
// 0x000FF700.  The copy constructor's unwind map destroys an already-built
// shape vector if record copying throws; each vector copy constructor owns its
// partial-construction cleanup.  Both vector destructor loops call
// releaseBuffer at 0x00887940.

#include <vector>

typedef bool Bool;

template <typename T>
class StringBase
{
public:
	~StringBase()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	void *m_data;
};

struct GeometryShape
{
	int m_type;
	float m_height;
	float m_majorRadius;
	char m_unmodelled00c[0x0C];
	float m_offsetZ;
	StringBase<char> m_name;
	Bool m_enabled;
	char m_unmodelled21[0x03];
};

struct GeometryRecord
{
	int m_first;
	int m_second;
	int m_third;
	StringBase<char> m_name;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Geometry.h
class GeometryInfo : public Snapshot
{
public:
private:
	Bool m_isSmall;
	int m_scalar08;
	int m_scalar0c;
	int m_scalar10;
	int m_scalar14;
	int m_scalar18;
	int m_scalar1c;
	int m_scalar20;
	int m_scalar24;
	int m_scalar28;
	std::vector<GeometryShape> m_shapes;
	std::vector<GeometryRecord> m_records;
	int m_cached44;
	int m_cached48;
	int m_cached4c;
	int m_cached50;
	int m_cached54;
	int m_cached58;
};

// Force emission of GeometryInfo's compiler-generated copy constructor.
GeometryInfo copyGeometryInfo(const GeometryInfo &other)
{
	return other;
}
