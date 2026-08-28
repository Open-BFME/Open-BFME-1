// cl: /DNDEBUG /MD /EHsc
// readable body of ??1CrateTemplate@@MAE@XZ: Code/GameEngine/Source/GameLogic/System/CrateSystem.cpp
// Open-BFME5: CrateTemplate::~CrateTemplate at retail 0x00379EC0.
//
// Boundary evidence: vtable 0x010EA378 slot 0 -> ILT 0x0002647C ->
// via ??_GCrateTemplate at 0x0037A2F0 -> 0x0002FC70 -> 0x00379EC0.  locate.py could
// not place it because retail inlines the ~Overridable base body.
//
// THE RECORDED BLOCKER -- "BFME MemoryPoolObject::~MemoryPoolObject emits no
// vptr reset, so this is a GameMemory.h-level drift affecting every
// MemoryPoolObject destructor" -- IS REFUTED.  Nothing about GameMemory.h is
// involved.  The earlier reconstruction gave the object a MemoryPoolObject
// base UNDER Overridable, so two base vptr resets were emitted where retail
// emits one, and the extra sub-object also pushed the closing unwind state to
// 3 instead of -1.  Retail's two vptr stores are simply CrateTemplate's own at
// entry and ONE base reset; making Overridable the root polymorphic class
// reproduces all 147 bytes on the first compile, including the base vptr store
// landing between the `test ecx,ecx` and its `je` and the closing state -1.
//
// TU-scoped ABI slice: only the sub-objects this body touches are real
// (m_nextOverride at +0x04, an AsciiString at +0x0C, the node list at +0x34);
// the rest is padding at retail offsets.  The two out-of-line callees are
// declared without bodies because retail calls them out of line.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	void *m_data;
	~AsciiString( void );
};

extern void rva379ec0SmallDeallocate( void *, unsigned int );

// STLport-shaped node list: the header pointer is the only data member, the
// out-of-line clear() is retail's incremental-link thunk at 0x0000331AE, and
// the header node itself is 16 bytes.
class CrateTemplateCrateList
{
public:
	void *m_node;

	void clear( void );

	__forceinline ~CrateTemplateCrateList( void )
	{
		clear();
		void *node = m_node;
		if( node )
			rva379ec0SmallDeallocate( node, 16 );
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	Overridable *m_nextOverride;

	virtual ~Overridable( void )
	{
		if( m_nextOverride )
			delete m_nextOverride;
		m_nextOverride = 0;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/CrateSystem.h
class CrateTemplate : public Overridable
{
public:
	int m_pad08;
	AsciiString m_name;
	char m_pad10[0x24];
	CrateTemplateCrateList m_crateData;

protected:
	virtual ~CrateTemplate( void );
};

CrateTemplate::~CrateTemplate( void )
{
	m_crateData.clear();
}
