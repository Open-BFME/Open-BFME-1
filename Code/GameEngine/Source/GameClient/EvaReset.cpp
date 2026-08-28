// cl: /DNDEBUG /MD /EHsc
// readable body of ?reset@Eva@@: Code/GameEngine/Source/GameClient/Eva.cpp
// Open-BFME5: Eva::reset, spelled against the retail BFME layout.
//
// BFME's Eva is not Zero Hour's.  Retail keeps two pristine "default" copies of
// its parsed INI data next to the live ones and restores them wholesale on
// reset, then resizes the per-message check vector at +0x4c to one 24-byte
// record per parsed check-info and stamps every record invalid.  The Zero Hour
// GameClient/Eva.h describes none of that, so the class is spelled locally --
// see AGENTS.md, "Placement and integrity", on preferring translation-unit
// scoped shims over a shared header.
//
// Identity: this is the third slot of the Eva vtable at 0x010F1F94 (via the ILT
// entry at 0x00023682), the same table the Eva destructor at 0x00426560 and the
// Eva constructor install; SubsystemInterface::reset is what sits there.  The
// +0x58/+0x5c pair it stamps is the pair the constructor stamps identically,
// and +0x5c is the enable flag ?setEvaEnabled@Eva@@QAEX_N@Z writes.
//
// The four callees are TU-local helpers retail never named for us; they are
// pinned by ILT address under _bfme_ names that describe their observed shape.

typedef bool Bool;
typedef int Int;

// Retail per-message check record, 24 bytes: two frame stamps this body
// invalidates and a "played" flag at +0x14.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
struct EvaCheck
{
	float m_triggeredOnFrame;
	float m_timeForNextCheck;
	char  m_middle[ 0x0c ];
	Bool  m_alreadyPlayed;
	char  m_trailingPad[ 3 ];
};

// Retail parsed check-info record; only its 28-byte stride matters here, and
// the stride is what turns the vector extent into the check count.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
struct EvaCheckInfo
{
	char m_raw[ 28 ];
};

// vector<EvaCheckInfo>: begin/end/capacity at +0x0/+0x4/+0x8.
class EvaCheckInfoVec
{
public:
	// Out-of-line in retail (0x004263D0 through the ILT entry at 0x00031DBD):
	// self-assignment guarded, then a copy sized by the 28-byte stride.
	void _bfme_assign( const EvaCheckInfoVec &rhs );

	Int size( void ) const { return m_end - m_begin; }

	EvaCheckInfo *m_begin;
	EvaCheckInfo *m_end;
	EvaCheckInfo *m_capacity;
};

// vector<EvaCheck>: begin/end/capacity at +0x0/+0x4/+0x8.
class EvaCheckVec
{
public:
	// 0x00426100 through the ILT entry at 0x000153D4: builds the default
	// EvaCheck on the stack and grows/shrinks to the requested count.
	void resize( Int count );

	EvaCheck *m_begin;
	EvaCheck *m_end;
	EvaCheck *m_capacity;
};

// The 20-byte per-side sound container.  Its assignment is inlined at the call
// site in retail, so it is spelled inline here and only the two halves are
// out-of-line calls.
class EvaSideSoundsVec
{
public:
	// 0x00424300 through the ILT entry at 0x00037BF0: walks the owned pointer
	// array and releases each element.
	void _bfme_releaseElements( void );
	// 0x00424380 through the ILT entry at 0x00033E1A: deep-copies the elements
	// of another container into this one.
	void _bfme_copyElements( const EvaSideSoundsVec &rhs );

	EvaSideSoundsVec &operator=( const EvaSideSoundsVec &rhs )
	{
		if( &rhs != this )
		{
			_bfme_releaseElements();
			_bfme_copyElements( rhs );
		}
		return *this;
	}

	char m_raw[ 0x14 ];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
class Eva
{
public:
	// Slot 4 of the primary vtable at 0x010F1FA8; declared virtual so the body
	// carries retail's ?reset@Eva@@UAEXXZ decoration and the +0x00 vtable
	// pointer falls where retail's does.
	virtual void reset( void );

private:
	char             m_head[ 0x08 ];		// +0x04 pad and the +0x08 vtable pointer
	EvaCheckInfoVec  m_checkInfos;			// +0x0c
	EvaCheckInfoVec  m_defaultCheckInfos;		// +0x18
	EvaSideSoundsVec m_sideSounds;			// +0x24
	EvaSideSoundsVec m_defaultSideSounds;		// +0x38
	EvaCheckVec      m_checks;			// +0x4c
	Int              m_resetCount;			// +0x58
	Bool             m_enabled;			// +0x5c
};

void Eva::reset( void )
{
	// Restore both parsed tables from the pristine copies taken at load.
	m_checkInfos._bfme_assign( m_defaultCheckInfos );
	m_sideSounds = m_defaultSideSounds;

	// One live check record per parsed check-info, all of them invalid.
	m_checks.resize( m_checkInfos.size() );

	EvaCheck *check = m_checks.m_begin;
	EvaCheck *last = m_checks.m_end;
	while( check != last )
	{
		check->m_triggeredOnFrame = -1.0f;
		check->m_timeForNextCheck = -1.0f;
		check->m_alreadyPlayed = false;
		++check;
	}

	m_resetCount = 1;
	m_enabled = true;
}
