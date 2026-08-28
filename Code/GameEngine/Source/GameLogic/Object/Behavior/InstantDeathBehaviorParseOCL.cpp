// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// parseOCL, retail 0x00201770, 118 bytes -- the InstantDeathBehavior sibling of
// parseFX (0x002016E0), which lives in the same file and is the same four lines
// over a different store and a different vector.
//
// The +0x4C append identifies the callback's vector slot. Retail then loads
// 0x012EF738, which GameEngine::init names TheWeaponStore, and calls the
// WeaponStore::findWeaponTemplate ILT at 0x0000D3FA. The target therefore has
// a WeaponStore lookup even though the callback remains address-derived as
// parseOCL; keep the observed pointer store and vector slot byte-for-byte.
//
// The BFME-vs-reference difference is the signature: BFME's
// findWeaponTemplate takes a BFMERetailAsciiString BY VALUE where the reference
// takes a const char *, so retail builds one from the token in the argument
// slot and never destroys it -- MSVC has the callee destroy by-value class
// parameters. Written the reference way the body is twelve bytes short with the
// construction missing.
//
// A prior pass reached 116 of 118 bytes with the correct size and closed the
// row on the remaining two: retail emits `push ecx / mov [esp+0x14],esp /
// mov ecx,esp` and the build emitted the last two reversed. That was recorded
// as MSVC unwind-store scheduling -- a compiler blocker -- after a sweep of
// /G5, /G6, -Ot, -Gy, /EHa, /EHs, /EHac and an inline-vs-declared destructor
// moved nothing. It is not a scheduling question at all: it is INLINE
// VISIBILITY of the constructor. With AsciiString's const char * constructor
// merely DECLARED, MSVC emits a plain out-of-line call and orders the two
// stores its own way; DEFINED INLINE as a forwarder to the private
// StringBase<char> base constructor -- the shape the real string class actually
// has -- the `this` load comes out of the inlined body and lands after the EH
// store, exactly as retail. Same lever as ConnectionManager::processDisconnectChat.
//
// As in parseFX, the __true_type tag must come from the vendored <vector>: a
// hand-written shim gives the tag a stack slot of its own worth one `push ecx`,
// where retail passes it by reference at the same address as the value and
// allocates no locals at all.

#include <vector>

class ObjectCreationList;
class WeaponTemplate;

template <typename T> class StringBase
{
friend class BFMERetailAsciiString;

private:
	StringBase( void );
	StringBase( const StringBase<T> &that );
	StringBase( const T *text );
	void releaseBuffer( void );

public:
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( text );
	}
	~BFMERetailAsciiString( void );

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	const char *getNextTokenOrNull( const char *seps = 0 );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate( BFMERetailAsciiString name ) const;
};

extern WeaponStore *TheWeaponStore;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/InstantDeathBehavior.h
class InstantDeathBehaviorModuleData
{
public:
	unsigned char m_unreconstructed_00[0x4C];
	_STL::vector<const ObjectCreationList *> m_ocls;			///< +0x4C
};

//-------------------------------------------------------------------------------------------------
// ?parseOCL@@YAXPAVINI@@PAX1PBX@Z
void parseOCL( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	InstantDeathBehaviorModuleData* self = (InstantDeathBehaviorModuleData*)instance;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const WeaponTemplate *weapon = TheWeaponStore->findWeaponTemplate(token);	// could be null! this is OK!
		self->m_ocls.push_back(reinterpret_cast<const ObjectCreationList *>(weapon));
	}
}
