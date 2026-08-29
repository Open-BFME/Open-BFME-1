// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport

#include <bitset>
#include <string.h>

typedef int Int;
typedef unsigned char UnsignedByte;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Xfer.h
class Xfer
{
public:
	virtual void unused0() = 0;
	virtual void unused1() = 0;
	virtual void unused2() = 0;
	virtual void unused3() = 0;
	virtual void unused4() = 0;
	virtual void unused5() = 0;
	virtual void unused6() = 0;
	virtual void unused7() = 0;
	virtual void unused8() = 0;
	virtual void xferUser(void *data, Int dataSize) = 0;
};

template <size_t NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	void xfer(Xfer *xfer);

private:
	_STL::bitset<NUMBITS> m_bits;
};

template <size_t NUMBITS>
void BitFlags<NUMBITS>::xfer(Xfer *xfer)
{
	UnsignedByte packed[(NUMBITS + 7) / 8];
	memset(packed, 0, sizeof(packed));
	for (Int i = 0; i < static_cast<Int>(NUMBITS); ++i)
	{
		if (m_bits._Unchecked_test(i))
			packed[i / 8] |= (1 << (i % 8));
	}
	xfer->xferUser(packed, sizeof(packed));
}

template void BitFlags<29>::xfer(Xfer *);
