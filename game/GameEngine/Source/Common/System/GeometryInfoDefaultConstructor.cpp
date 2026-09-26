// cl: /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: GeometryInfo default constructor, retail 0x001B3C60.
//
// The GeometryInfo vtable at 0x01086138 is also installed by the exact copy
// constructor at 0x000FFD10.  GhostObject's constructor calls this no-argument
// constructor on its GeometryInfo member at +0x20.
//
// Both vector element types own a StringBase<char> subobject.  Retail's
// exception cleanup calls the shape-vector destructor at 0x000FF700 and the
// record-vector destructor at 0x000FF7D0; those destructors release the string
// at element offsets +0x1C and +0x0C before freeing vector storage.

#include <vector>

typedef bool Bool;
typedef float Real;

enum GeometryType
{
	GEOMETRY_SPHERE = 0,
	GEOMETRY_CYLINDER,
	GEOMETRY_BOX
};

#include "string_base.h"

struct GeometryShape
{
	int m_type;
	Real m_height;
	Real m_majorRadius;
	char m_unmodelled00c[0x0C];
	Real m_offsetZ;
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

class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void LoadPostProcess() = 0;
	virtual const char *GetSnapshotName() = 0;
	virtual void DoXfer(Xfer &xfer) = 0;
};

class GeometryInfo : public Snapshot
{
public:
	GeometryInfo();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);

	void set(GeometryType type, Bool isSmall, Real height,
		Real majorRadius, Real minorRadius);

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

// ??0GeometryInfo@@QAE@XZ
GeometryInfo::GeometryInfo()
{
	m_scalar08 = 0;
	m_scalar0c = 0;
	set(GEOMETRY_SPHERE, true, 0.1f, 0.1f, 0.1f);
}
