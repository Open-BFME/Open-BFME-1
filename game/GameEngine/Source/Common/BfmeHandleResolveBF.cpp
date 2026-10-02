// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the cached handle resolve at retail 0x0013EE70, 59 bytes.  The
// name is looked up once and then released, so the handle is what survives.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

// Retail's singleton at 0x012F6924 is ?TheMappedImageCollection@@3PAVImageCollection@@A
// and the lookup it drives is ?findImageByName@ImageCollection@@QAEPBVImage@@ABVAsciiString@@@Z
// (retail 0x0001D606, an ILT thunk to the matched 0x005D2CF0 body). No game header
// declares ImageCollection, so this TU declares only the member it calls. This local
// string view keeps the retail emptiness check inline, and its clear call goes through
// the real StringBase<char>::clear() implementation to releaseBuffer at 0x00887940.
class AsciiString;

class AsciiStringBF
{
public:
	bool bfmeEmptyBF(void) const
	{
		return (m_bfmeNarrowBF == 0) || (*(const unsigned short *)(m_bfmeNarrowBF + 4) == 0);
	}

	char *m_bfmeNarrowBF;
};

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;		// retail 0x012F6924

class BfmeHolderBF
{
public:
	void *bfmeResolveBF(void);

	char m_bfmePadABF[0x30];
	AsciiStringBF m_bfmeNameBF;
	char m_bfmePadBBF[0x35c];
	void *m_bfmeHandleBF;
};

void *BfmeHolderBF::bfmeResolveBF(void)
{
	if (!m_bfmeNameBF.bfmeEmptyBF() && TheMappedImageCollection != 0)
	{
		m_bfmeHandleBF = const_cast<void *>(reinterpret_cast<const void *>(
			TheMappedImageCollection->findImageByName(
				reinterpret_cast<const AsciiString &>(m_bfmeNameBF))));

		reinterpret_cast<StringBase<char> &>(m_bfmeNameBF).clear();
	}

	return m_bfmeHandleBF;
}
