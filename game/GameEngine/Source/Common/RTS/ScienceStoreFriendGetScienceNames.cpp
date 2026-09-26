// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// ScienceStore::friend_getScienceNames, retail 0x000E81F0 (259 bytes).
//
// Zero Hour twin: GeneralsMD Common/RTS/Science.cpp, ported verbatim. The
// landed Science.cpp builds against an inline AsciiString shim, but retail
// here copies with a direct call to StringBase<char>'s copy constructor
// (0x00887B60) and destroys the keyToName temporary with a call to
// 0x00887940, so the body lives in a TU that uses the real ascii_string.h.
// The by-value result is built in a local and copied out through the vector
// copy constructor (0x000D2E70), then the local is destroyed (0x000658A0):
// MSVC 7.1 performs no NRVO.
//
// Layout witnessed by the bytes and matching the landed ScienceStore and
// ScienceInfo TUs: m_sciences at +8, Overridable::m_nextOverride at +4,
// ScienceInfo::m_science at +0xC.

#include <vector>
#include "ascii_string.h"

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class NameKeyGenerator
{
public:
	AsciiString keyToName( NameKeyType key );
};

extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride( void ) const
	{
		if ( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	void *m_unmodelled00;
	Overridable *m_nextOverride;
};

class ScienceInfo : public Overridable
{
public:
	Int m_unmodelled08;
	ScienceType m_science;
};

typedef std::vector<ScienceInfo *> ScienceInfoVec;

class ScienceStore
{
public:
	std::vector<AsciiString> friend_getScienceNames() const;

private:
	void *m_unmodelled00;
	Int m_unmodelled04;
	ScienceInfoVec m_sciences;
};

std::vector<AsciiString> ScienceStore::friend_getScienceNames() const
{
	std::vector<AsciiString> v;
	for ( ScienceInfoVec::const_iterator it = m_sciences.begin(); it != m_sciences.end(); ++it )
	{
		const ScienceInfo *si = (const ScienceInfo *)( *it )->getFinalOverride();
		NameKeyType nk = (NameKeyType)( si->m_science );
		v.push_back( TheNameKeyGenerator->keyToName( nk ) );
	}
	return v;
}
