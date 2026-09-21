// ?containsUserNamed@Rva003A95D0Owner@@QBE_NPBVAsciiString@@@Z
// partial score=0.28 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: retail 0x003A95D0 (249 B). Scans an inline vector of 0xDC
// (220) byte User records for one whose GetName() (pinned ILT 0x0000CA95,
// User::GetName) compares equal to the incoming name. The comparison
// itself is the classic StringBase<char>::compare shape spelled out
// inline (two lengths as halfwords at +4, repe cmpsb over the shorter
// side via the intrinsic memcmp, then the length difference as tiebreak)
// -- see Code/Libraries/Source/WWVegas/WWLib/RvaTreeFindAsciiString.cpp
// for the identical pattern.

#include <string.h>

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	const char *text() const
	{
		return m_data ? (const char *)m_data + 8 : "";
	}
	unsigned short length() const
	{
		return m_data ? *(unsigned short *)((char *)m_data + 4) : 0;
	}

private:
	void *m_data;
};

class User
{
public:
	AsciiString GetName() const;

	unsigned char m_pad00[0xdc];
};

class Rva003A95D0Owner
{
public:
	bool containsUserNamed(const AsciiString *name) const;

private:
	unsigned char m_pad00[0xc];
	User *m_begin;
	User *m_end;
};

bool Rva003A95D0Owner::containsUserNamed(const AsciiString *name) const
{
	const Rva003A95D0Owner *self = this;
	unsigned count = (unsigned)(self->m_end - self->m_begin);

	unsigned index = 0;
	User *cur = self->m_begin;
	for (; index < count; )
	{
		AsciiString local = cur->GetName();

		unsigned short localLen = local.length();
		unsigned short argLen = name->length();
		const char *localText = local.text();
		const char *argText = name->text();

		unsigned minLen = (localLen < argLen) ? localLen : argLen;
		int cmpResult = memcmp(localText, argText, minLen);
		int result = (cmpResult != 0) ? cmpResult : (localLen - argLen);

		if (result == 0)
			return true;

		++index;
		++cur;
	}

	return false;
}

// @?containsUserNamed@Rva003A95D0Owner@@QBE_NPBVAsciiString@@@Z 0x003A95D0
