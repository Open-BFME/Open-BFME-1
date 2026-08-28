// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?findSpecialPowerTemplatePrivate@SpecialPowerStore@@: Code/GameEngine/Source/Common/RTS/SpecialPower.cpp
// Open-BFME: SpecialPowerStore::findSpecialPowerTemplatePrivate, retail
// 0x000EBA20, 298 bytes.
//
// The reference's body unchanged; almost all of it is one line.  getName()
// returns the string BY VALUE, so every turn of the loop builds a temporary in
// the caller's frame, compares it against the argument and destroys it again --
// which is what the SEH frame and the two-thirds of the body between the call
// and the destructor are.
//
// The comparison is string_base.h's own compare, inline: length at data+4, text
// at data+8, memcmp over the shorter of the two, then the length difference as
// an early return.  The template it walks is a plain pointer pair at +0x08 and
// +0x0C.

#define _DLL
#include <string.h>
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();						// folded onto releaseBuffer, 0x00887940

	Int compare(const char *str, Int len) const
	{
		const Int myLen = m_data ? m_data->length : 0;
		const char *data = m_data ? &m_data->data[0] : "";
		Int result = memcmp(data, str, myLen < len ? myLen : len);
		if (result != 0)
			return result;
		return myLen - len;
	}

	Int compare(const AsciiString &str) const
	{
		const Int len = str.m_data ? str.m_data->length : 0;
		const char *data = str.m_data ? &str.m_data->data[0] : "";
		return compare(data, len);
	}

private:
	struct Header {
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate
{
public:
	AsciiString getName(void) const;			// ILT 0x00005682, returns by value
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerStore
{
protected:
	SpecialPowerTemplate *findSpecialPowerTemplatePrivate( AsciiString name );

private:
	unsigned char m_unmodelled_000[8];
	_STL::vector<SpecialPowerTemplate *> m_specialPowerTemplates;	// this+0x08
};

SpecialPowerTemplate* SpecialPowerStore::findSpecialPowerTemplatePrivate( AsciiString name )
{

	// search the template list for matching name
	for( Int i = 0; i < m_specialPowerTemplates.size(); ++i )
		if( m_specialPowerTemplates[ i ]->getName() == name )
			return m_specialPowerTemplates[ i ];

	return 0;  // not found

}
