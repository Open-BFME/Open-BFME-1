// FILE: AsciiString_endsWith_BfmeTwin.cpp
// Desc: Twin body for AsciiString::endsWith: BFME's AsciiStringData stores the
// current length as a WORD at data+2 (not the ZH int m_currentLength via
// getLength()/peek()), and the char buffer starts at data+8. The tail pointer
// is computed as data+8+(storedLen-lenThat), and the compare reduces to
// memcmp(tail, p, lenThat) == 0 -- the classic repe-cmpsb/sete intrinsic
// expansion, not a call out to CRT strncmp as the ZH source spells it. strlen
// is the CRT intrinsic too (#pragma intrinsic), which is what gives the
// unguarded do/while byte scan retail has instead of a while-loop's leading
// test. The "*p == 0 -> return true" special case in the ZH source needs no
// explicit branch here: with lenThat == 0, xor eax,eax sets ZF and repe cmpsb
// with a zero count never runs, so sete al still yields true.
//
// ?endsWith@AsciiString@@QBE_NPBD@Z

#include <string.h>
#pragma intrinsic(strlen, memcmp)

struct AsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_length;
	int m_pad;
	char m_buffer[1];
};

class AsciiString
{
public:
	AsciiStringData* m_data;
	bool endsWith(const char* p) const;
};

bool AsciiString::endsWith(const char* p) const
{
	unsigned storedLen = m_data->m_length;
	unsigned lenThat = (unsigned)strlen(p);
	if (storedLen < lenThat)
		return false;
	const char* tail = m_data->m_buffer + (storedLen - lenThat);
	return memcmp(tail, p, lenThat) == 0;
}
