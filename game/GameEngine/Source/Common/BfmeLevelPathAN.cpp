// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME5: the level-path builder at retail 0x004675F0, 206 bytes.  The
// level number becomes a suffix, and the result is assembled into a shared
// buffer whose address the caller gets back.
//
// The suffix is a real AsciiString: retail builds its format temporary with
// ??0?$StringBase@D@@AAE@PBD@Z (0x00888BC0), formats it with
// ?format@AsciiString@@QAAXV1@ZZ (0x00888FF0) and releases it with
// ?releaseBuffer@?$StringBase@D@@AAEXXZ (0x00887940).  str() reads the same
// ref-counted header the local bfmeTextAN() did (text at data+8).

#include "ascii_string.h"

extern char g_bfmeBufferAN[];

void bfmeAssembleAN(int a, char *buffer, const char *text, int p3, int p4, int p5,
		int p6, int p7, int p8);

class BfmeLevelAN
{
public:
	char *bfmeBuildAN(unsigned int level, int p2, int p3, int p4, int p5, int p6,
			int p7, int p8);

	char m_bfmePadAN[0x1c4];
	char m_bfmeBuiltAN;
};

char *BfmeLevelAN::bfmeBuildAN(unsigned int level, int p2, int p3, int p4, int p5,
		int p6, int p7, int p8)
{
	g_bfmeBufferAN[0] = 0;

	if (level < 12)
	{
		AsciiString suffix;

		suffix.format(AsciiString("/_level%d"), level);

		bfmeAssembleAN(p2, g_bfmeBufferAN, suffix.str(), p3, p4, p5, p6, p7, p8);

		m_bfmeBuiltAN = 1;
	}

	return g_bfmeBufferAN;
}
