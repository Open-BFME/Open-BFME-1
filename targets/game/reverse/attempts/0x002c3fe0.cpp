// ?d_002c3fe0@@YAXXZ
// partial score=0.72 date=2026-09-27
// ?method@Rva002C3FE0Owner@@QAEXPAX00@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
//
// Opaque owner for the retail body at RVA 0x002C3FE0 (332 B, ret 8). The body
// is reached only through the ILT thunk at 0x0002A991 by its sibling at
// 0x002C3E00, and it calls only the pinned/matched callees callees.py
// resolves for it: the GeometryInfo copy at 0x000FFD10 (j_0002b355), the
// GeometryInfo destructor at 0x000FFCA0 (j_000309f4), the KindOf-mask
// three-index constructor at 0x002BD5A0 (j_0003284e), the KindOf
// accept-filter constructor at 0x000C3DD0 (j_000382fd), the four-argument
// partition query wrapper at 0x009F26A0, and
// GeometryInfo::getMaxHeightAbovePosition at 0x0087E000. The lacking
// caller/vtable identity is not a blocker: this lands under an
// address-derived opaque name describing what the bytes prove.
//
// Frame reading: argc is 2 (ret 8). The first stack argument is the queried
// position, the second a scratch dword the partition wrapper reads. The
// terrain ground-height call stores its float at esp+0x0C and compares it
// against the -1.#QNAN slot at esp+0xF4; the GeometryInfo copy of
// *(this+0x1C)+0x10)+0xAC lives at esp+0x70; the three-index mask at
// esp+0xDC (bits 7/10/11) and the accept filter at esp+0x18 drive the
// partition query whose Object* result returns in EAX; the second
// GeometryInfo copy at esp+0x14 feeds getMaxHeightAbovePosition before the
// four destructor calls unwind the filter, mask, and two geometry copies.
// The explicit second parameter keeps retail's esp+0xEC argument slot and
// the ret-8 cleanup.

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

extern Rva002C3FE0TerrainLogic *TheTerrainLogic;

template <size_t NUMBITS>
class Rva002C3FE0Mask
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	Rva002C3FE0Mask(BogusInitType, Int a, Int b, Int c);

private:
	unsigned int m_words[NUMBITS / 32];
};

typedef Rva002C3FE0Mask<192> KindOfMaskType;

extern const KindOfMaskType KINDOFMASK_NONE;

class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &source);
	~GeometryInfo();
	Real getMaxHeightAbovePosition() const;

private:
	unsigned char m_body[0x58];
};

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
	PartitionFilterAcceptByKindOf(const Rva002C3FE0MaskBlock &mustBeSet,
		const Rva002C3FE0MaskBlock &mustBeClear);
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
	void method(void *arg1, void *arg2, void *arg3);

private:
	unsigned char m_pad00[0x1c];
	Object *m_object1c;
};

void Rva002C3FE0Owner::method(void *arg1, void *arg2, void * /*arg3*/)
{
	const Coord3D *position = (const Coord3D *)arg1;
	Real ground = TheTerrainLogic->getGroundHeight(position->x, position->y, 0);
	if (ground > -1e30f)
		return;
	Object *owner = *(Object **)((char *)m_object1c + 0x10);
	GeometryInfo geometry(*(const GeometryInfo *)((char *)owner + 0xac));
	KindOfMaskType mustBeSet(KindOfMaskType::kInit, 7, 10, 11);
	PartitionFilterAcceptByKindOf filter(
		*(const Rva002C3FE0MaskBlock *)&mustBeSet,
		*(const Rva002C3FE0MaskBlock *)&KINDOFMASK_NONE);
	Object *found = ThePartitionManager->getClosestObject(position,
		*(Real *)&arg2, 0, &filter);
	if (found == 0)
		return;
	GeometryInfo foundGeometry(*(const GeometryInfo *)((char *)found + 0xac));
	if (ground + foundGeometry.getMaxHeightAbovePosition() > -1e30f)
		return;
}
