// cl: /DNDEBUG /MD /EHsc
// Real C++ reconstruction of ??0Radar@@QAE@XZ (BFME Radar constructor).
//
// IDENTITY.  The body installs the same primary vftable (0x010888AC) the
// matched Radar::~Radar at 0x00107620 installs, and the Radar-as-SubsystemInterface
// view (0x01088880) that only a Radar constructor/destructor pair writes.  Its
// one caller is ??0W3DRadar@@QAE@XZ at 0x006C1D70 -- itself a matched real-C++
// body whose `class W3DRadar : public Radar' leaves the base construction
// implicit, so a matched caller names this symbol.  The name is kept; nothing
// about it is inferred.
//
// WHY NOT game/GameEngine/Source/Common/System/Radar.cpp.  That TU is the
// class home, but it compiles against inputs/reference/shims/radar/Common/Radar.h,
// whose layout is the ZH one: BFME stores m_radarForceOn at +0x09 (proved by the
// matched ?reset@Radar@@UAEXXZ at 0x001077A0) where the shim puts it at +0x0D,
// and its nested RadarEvent is a POD with no ctor/dtor.  Retail's constructor
// needs the BFME shape, so the declaration stays local here, as the sibling
// Radar destructor body (RadarDestructorThunk.cpp) already does.
//
// WHAT THE BYTES SHOW.  0x00107FE0 pushes the SEH frame, copies `this` into
// the saved ECX slot, inlines the Snapshot base constructor (the 0x01073744
// vftable store at +0x1F), calls the real SubsystemInterface constructor, then
// runs the 64-element m_event array through the STLport `eh vector constructor
// iterator' - ??_L@YGXPAXIHP6EX0@Z1@Z with size 0x50, count 0x40 and the
// element ctor/dtor pair.  That is what a member array of a CLASS type with an
// out-of-line ctor compiles to under /EHsc, and it is why the frame carries two
// EH state stores (byte 1 before the helper, byte 2 after) and an unwind
// funclet: state 1 destroys the constructed prefix, state 2 all 64 elements.
//
// The element is RadarEvent: 0x50 bytes, its ctor (0x001075E0) writes the
// reference pointer at +0x4C and its dtor (0x001075F0) releases it, both
// proven by the matched Radar::~Radar that destroys the same array.  The dtor is
// only DECLARED here, so the array unwinds through that matched body; the ctor
// is spelled here because the element needs one, and a class cannot carry both
// the destructor name the ledger holds (??1RadarEvent@@QAE@XZ) and the
// constructor name it holds for 0x001075E0 (??0Rva001075E0@@QAE@XZ in
// game/GameEngine/Source/Common/Q1ConstantFieldConstructors.cpp).  The ten
// bytes are identical to that row's, so a later lane can retire the duplicate
// by repointing it here; until then the image carries one extra 10-byte copy.
//
// The constructor stores +0x1454/+0x1458 with 0xFFFF0001 and +0x145C/+0x1460
// with 0x0000FFFF, the same four words and the byte at +0x1464 the matched
// sibling 0x001073F0 writes on the same offsets.  Their meaning is not
// recovered, so they are named by address; the constants are the bytes.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot() {}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
// novtable so this TU references the pinned vftable instead of emitting one.
class __declspec(novtable) SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	unsigned int m_name;
};

// BFME's radar event: 0x50 bytes with a ref-counted payload at +0x4C.
struct RadarEvent
{
	int m_type;
	bool m_active;
	unsigned char m_unmodeled008[ 0x47 ];
	void *m_reference;

	// 0x001075E0: mov eax,ecx / mov dword ptr [eax+0x4c],0 / ret
	RadarEvent() : m_reference( 0 ) {}

	// 0x001075F0, the matched body in RadarDestructorThunk.cpp
	~RadarEvent();
};

struct RadarCoord3D
{
	float m_x, m_y, m_z;
};

struct Region3D
{
	RadarCoord3D m_lo, m_hi;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h
// with the BFME member offsets retail's own bodies read.
class Radar : public Snapshot, public SubsystemInterface
{
public:
	Radar();
	virtual ~Radar();

protected:
	void clearAllEvents( void );				///< the matched body at 0x001076F0

	// +0x0C and +0x0D are the two bytes retail's constructor clears.  They are
	// NOT the hide/force-on pair: the matched ?reset@Radar@@UAEXXZ at 0x001077A0
	// clears +0x09, which is where the ZH source's m_radarForceOn lives in BFME.
	// Nothing else in the tree names these two, so they stay address-derived.
	bool m_bfme000c;							///< +0x0C
	bool m_bfme000d;							///< +0x0D
	void *m_objectList;						///< +0x10, the list deleteListResources walks second
	void *m_localObjectList;					///< +0x14, and first (0x00106A90)
	float m_terrainAverageZ;					///< +0x18
	float m_waterAverageZ;					///< +0x1C
	float m_xSample;							///< +0x20
	float m_ySample;							///< +0x24
	RadarEvent m_event[ 64 ];					///< +0x28, 0x50 bytes each
	unsigned int m_unmodeled1428[ 4 ];		///< +0x1428, owned by clearAllEvents
	void *m_radarWindow;						///< +0x1438 (matched isRadarWindow)
	Region3D m_mapExtent;					///< +0x143C (matched newMap)
	unsigned int m_bfme1454;					///< +0x1454
	unsigned int m_bfme1458;					///< +0x1458
	unsigned int m_bfme145c;					///< +0x145C
	unsigned int m_bfme1460;					///< +0x1460
	bool m_bfme1464;							///< +0x1464
	unsigned int m_bfme1468;					///< +0x1468
};

// ??0Radar@@QAE@XZ
Radar::Radar( void )
{

	m_bfme1454 = 0xFFFF0001;
	m_bfme1458 = 0xFFFF0001;

	m_radarWindow = 0;
	m_objectList = 0;
	m_localObjectList = 0;
	m_bfme000c = false;
	m_bfme000d = false;
	m_terrainAverageZ = 0.0f;
	m_waterAverageZ = 0.0f;
	m_xSample = 0.0f;
	m_ySample = 0.0f;
	m_mapExtent.m_lo.m_x = 0.0f;
	m_mapExtent.m_lo.m_y = 0.0f;
	m_mapExtent.m_lo.m_z = 0.0f;
	m_mapExtent.m_hi.m_x = 0.0f;
	m_mapExtent.m_hi.m_y = 0.0f;
	m_mapExtent.m_hi.m_z = 0.0f;
	m_bfme145c = 0x0000FFFF;
	m_bfme1460 = 0x0000FFFF;
	m_bfme1464 = false;
	m_bfme1468 = 0;

	// clear the radar events
	clearAllEvents();

}  // end Radar
