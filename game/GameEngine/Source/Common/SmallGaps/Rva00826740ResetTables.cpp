// ?resetTables@Rva00826740Owner@@QAEXXZ
#include <string.h>
#define LZHLINTERNAL
#include "../../../../Libraries/Source/Compression/LZHCompress/CompLibHeader/_huff.h"
struct Rva00826740Big { int m_v[0x89]; };
struct Rva00826740Small { int m_v[0x20]; };
struct Rva00826740Owner {
	Rva00826740Big* m_zeroed;
	Rva00826740Small m_small;
	Rva00826740Big* m_big;
	void resetTables();
};
void Rva00826740Owner::resetTables()
{
	memcpy(m_big, LZHLDecoderStat::symbolTable0, sizeof(Rva00826740Big));
	memcpy(&m_small, LZHLDecoderStat::groupTable0, sizeof(Rva00826740Small));
	memset(m_zeroed, 0, sizeof(Rva00826740Big));
}
