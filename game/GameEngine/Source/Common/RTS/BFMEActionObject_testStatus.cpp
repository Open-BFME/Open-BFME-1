// cl: /DNDEBUG /MD /EHsc
// Open-BFME: BFMEActionObject::testStatus, retail 0x000C4D40, 41 bytes.
//
// The out-of-line status test ActionManager.cpp already reaches through its
// ILT: a bit index split the usual way, the word picked out of an array at
// this+0x90 with a logical shift by five, the bit built with a variable shl,
// and the masked result narrowed to 0 or 1 by the neg/sbb/neg idiom MSVC uses
// for `!= 0`.
//
// The array is as much as the body shows -- nothing here bounds it -- so it is
// modelled as the one word the index reaches and no more, which is why the
// class carries the read rather than a sized member.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class BFMEActionObject
{
public:
	Bool testStatus(Int status) const;

private:
	char m_slice_pad[0x90];					// retail this+0x00 .. +0x8F, untouched
	UnsignedInt m_status[1];				// this+0x90, indexed by status >> 5
};

Bool BFMEActionObject::testStatus(Int status) const
{
	return (m_status[((UnsignedInt)status) >> 5] & (1 << (status & 0x1f))) != 0;
}
