// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x002C3FE0 (332 B, thiscall, ret 8): reached only through ILT 0x0002A991 from 0x002C3E00, which pushes a Coord3D* and a float and tests AL.
// Returns false when the terrain height or the nearest kind 7/10/11 object's top within the owner's geometry radius exceeds the given height.

typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;

class Rva002C3FE0TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
};

class TerrainLogic;
extern TerrainLogic *TheTerrainLogic;

extern void j_000309f4(void);

class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &source);
	// ??1Rva000FFCA0@@QAE@XZ
	~GeometryInfo()
	{
		typedef void (__fastcall *DestroyCall)(GeometryInfo *);
		((DestroyCall)j_000309f4)(this);
	}
	Real getMaxHeightAbovePosition() const;

	void *m_vtable;
	unsigned char m_body[0x10];
	Real m_boundingSphereRadius;
	unsigned char m_tail[0x44];
};

class BfmeH1166
{
public:
	BfmeH1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3);
	unsigned int m_words[6];
};

typedef BfmeH1166 KindOfMaskType;

template <size_t NUMBITS> class BitFlags
{
	unsigned int m_words[NUMBITS / 32];
};

extern const BitFlags<192> KINDOFMASK_NONE;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *object) = 0;

	PartitionFilter *m_next;
};

struct Rva002C3FE0MaskBlock
{
	unsigned int m_dword00;
	unsigned int m_dword04;
	unsigned int m_dword08;
	unsigned int m_dword0c;
	unsigned int m_dword10;
	unsigned int m_dword14;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const BitFlags<192> &mustBeSet,
		const BitFlags<192> &mustBeClear);
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *object);

	Rva002C3FE0MaskBlock m_mustBeSet;
	Rva002C3FE0MaskBlock m_mustBeClear;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real radius,
		Int distanceType, PartitionFilter *filters);
};

extern PartitionManager *ThePartitionManager;

class Rva002C3FE0Owner
{
public:
	Bool method(const Coord3D *position, Real maxHeight);

private:
	unsigned char m_pad00[0x1c];
	Object *m_object1c;
};

Bool Rva002C3FE0Owner::method(const Coord3D *position, Real maxHeight)
{
	Real ground = reinterpret_cast<Rva002C3FE0TerrainLogic *>(TheTerrainLogic)->
		getGroundHeight(position->x, position->y, 0);
	if (ground > maxHeight)
		return false;
	Object *owner = *(Object **)((char *)m_object1c + 0x10);
	GeometryInfo geometry(*(const GeometryInfo *)((char *)owner + 0xac));
	Object *found = ThePartitionManager->getClosestObject(position,
		geometry.m_boundingSphereRadius, 0,
		&PartitionFilterAcceptByKindOf(
			*(const BitFlags<192> *)&KindOfMaskType(0, 7, 10, 11),
			KINDOFMASK_NONE));
	if (found != 0)
	{
		GeometryInfo foundGeometry(*(const GeometryInfo *)((char *)found + 0xac));
		Real height = foundGeometry.getMaxHeightAbovePosition();
		if (ground + height > maxHeight)
			return false;
	}
	return true;
}
