// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??1Eva@@: Code/GameEngine/Source/GameClient/Eva.cpp
// Open-BFME5: Eva::~Eva, spelled against the retail BFME layout.
//
// Retail's Eva is a SubsystemInterface and a Snapshot: two vtable pointers, one
// at +0x00 and one at +0x08, both of which this body installs before it unwinds
// its own members and both of which the Eva constructor at 0x004271B0 installs
// the same way.  The four parsed-table containers at +0x0c/+0x18/+0x24/+0x38
// destroy through out-of-line calls; the +0x4c check vector is a POD
// std::vector whose STLport node_alloc deallocation is inlined at the 0x80
// threshold.  Zero Hour's Eva has neither the default-copy halves nor the
// second base, so the class is spelled against the retail layout in its own
// translation unit (AGENTS.md, "Placement and integrity").
//
// Identity: it writes the same two vtables, 0x010F1FA8 at +0x00 and 0x010F1F94
// at +0x08, that every other Eva body is dispatched through -- slot 1 of the
// first is Eva::init, slot 4 is the matched reset body and slot 5 the matched
// update body -- and it tears down exactly the members those bodies use.
// Snapshot's own vtable at 0x01073744 is restored at +0x08 before the
// SubsystemInterface destructor at 0x009A1A40 runs, which is the inline empty
// ~Snapshot that pins the second base.

#include <vector>

// Retail per-message check record, 24 bytes of POD: two millisecond countdowns
// and a played flag at +0x14.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
struct EvaCheck
{
	float m_timeUntilExpire;
	float m_timeUntilNextCheck;
	char  m_rest[ 0x10 ];
};

// Each 28-byte parsed record only owns storage through this 12-byte
// subobject at +0x10: decode_calls resolves its dtor call to the same
// already-matched _Rb_tree<int, ...> body at 0x004247C0 that backs a
// generic gen_uw map instantiation elsewhere, so this is a std::map<int,
// something>'s tree, spelled opaquely here rather than re-deriving the pod
// value type this TU never otherwise touches.
class BfmeEvaCheckInfoTail
{
public:
	~BfmeEvaCheckInfoTail( void );

private:
	char m_raw[ 0x0c ];
};

struct EvaCheckInfoRecord
{
	char                 m_head[ 0x10 ];
	BfmeEvaCheckInfoTail m_tail;
};

// vector<EvaCheckInfoRecord>, 12 bytes: STLport begin/end/capacity and
// nothing else, so the base vector destructor inlines wholesale into this
// derived one -- the same capacity-vs-0x80 node_alloc/free split the +0x4c
// std::vector<EvaCheck> member gets for free below.
class EvaCheckInfoVec : public std::vector<EvaCheckInfoRecord>
{
public:
	~EvaCheckInfoVec( void ) {}
};

// The 20-byte per-side sound container; destructor out of line at 0x00424890.
class EvaSideSoundsVec
{
public:
	~EvaSideSoundsVec( void );

private:
	char m_raw[ 0x14 ];
};

// The +0x08 base.  Its destructor is inline and empty in retail -- the body
// only restores the vtable pointer -- which is why no second base destructor
// call appears.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot( void ) {}
	virtual void crc( void ) = 0;
	virtual void xfer( void ) = 0;
	virtual void loadPostProcess( void ) = 0;
};

// The primary base: vtable pointer at +0x00 and the subsystem name at +0x04,
// destroyed out of line at 0x009A1A40.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface( void );
	virtual void init( void ) = 0;

private:
	void *m_name;				// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
class Eva : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Eva( void );

private:
	EvaCheckInfoVec       m_checkInfos;		// +0x0c
	EvaCheckInfoVec       m_defaultCheckInfos;	// +0x18
	EvaSideSoundsVec      m_sideSounds;		// +0x24
	EvaSideSoundsVec      m_defaultSideSounds;	// +0x38
	std::vector<EvaCheck> m_checks;			// +0x4c
	int                   m_speechHandle;		// +0x58
	bool                  m_enabled;		// +0x5c
};

Eva::~Eva( void )
{
}
