// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Open-BFME7: retail 0x000E92B0 (109 bytes), the wide twin of
// GameSpyStagingRoom::setPingString (GameSpyGameSlot_setPingString.cpp): a by-value
// UnicodeString is assigned into the member at +0x2E8, then two non-virtual members
// recompute the ints at +0x2EC and +0x2F0.  Same StringBase<unsigned short> forwarder
// shape as the AsciiString one in the landed TU.

#include "string_base.h"

typedef int Int;

class UnicodeString
{
public:
	__forceinline UnicodeString() : m_data(0) {}
	__forceinline UnicodeString(const UnicodeString &other)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&other);
	}
	~UnicodeString();
	__forceinline UnicodeString &operator=(const UnicodeString &other)
	{
		((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&other);
		return *this;
	}
private:
	unsigned short *m_data;
};

class Rva000E92B0Owner
{
public:
	void setWideString(UnicodeString text);
private:
	Int computeFirst();
	Int computeSecond();

	unsigned char m_unmodelled_000[0x2E8];
	UnicodeString m_text;		// +0x2E8
	Int m_first;				// +0x2EC
	Int m_second;				// +0x2F0
};

void Rva000E92B0Owner::setWideString(UnicodeString text)
{
	m_text = text;
	m_first = computeFirst();
	m_second = computeSecond();
}
