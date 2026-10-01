// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the cached handle resolve at retail 0x0013EE70, 59 bytes.  The
// name is looked up once and then released, so the handle is what survives.

// Retail's singleton at 0x012F6924 is ?TheMappedImageCollection@@3PAVImageCollection@@A
// and the lookup it drives is ?findImageByName@ImageCollection@@QAEPBVImage@@ABVAsciiString@@@Z
// (retail 0x0001D606, an ILT thunk to the matched 0x005D2CF0 body). No game header
// declares ImageCollection -- its Zero Hour GameClient/Image.h cannot be used here --
// so this TU declares the one member it calls. AsciiString is forward declared by its
// real name: AsciiStringBF below is the retail string object (its emptiness test reads
// the length at +4 of the same 8-byte string header, and clear() forwards to the shared
// releaseBuffer 0x00887940), so the reference passes the same address and nothing is
// reinterpreted at the ABI level. The lookup's const Image* result is only stored in the
// holder's void* slot, so it is cast there rather than changing what the body does.
class AsciiString;

class AsciiStringBF
{
public:
	void bfmeClearBF(void);

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

		m_bfmeNameBF.bfmeClearBF();
	}

	return m_bfmeHandleBF;
}
