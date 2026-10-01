class BfmeImageDE;
class AsciiString;

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);

	~BFMERetailAsciiString() { releaseBufferDE(); }

	void releaseBufferDE();

	void *m_bfmeBufDE;
};

// Retail's singleton is ?TheMappedImageCollection@@3PAVImageCollection@@A and the
// lookup it drives is ?findImageByName@ImageCollection@@QAEPBVImage@@ABVAsciiString@@@Z
// (retail 0x0001D606, the pin both spellings shared). No game header declares
// ImageCollection -- its Zero Hour GameClient/Image.h cannot be used here -- so
// this TU declares the one member it calls. AsciiString is forward declared by
// its real name: the BFMERetailAsciiString shim above is the retail string class
// (ctor 0x00888BC0 is the shared StringBase<char>(const char *) body and its dtor
// forwards to the shared releaseBuffer 0x00887940), so the reference passes the
// shim object unchanged and nothing is reinterpreted at the ABI level.
class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

BfmeImageDE *__stdcall bfmeFindImageDE(const char *name)
{
	if (TheMappedImageCollection != 0)
	{
		const BFMERetailAsciiString &text = BFMERetailAsciiString(name);

		return const_cast<BfmeImageDE *>(reinterpret_cast<const BfmeImageDE *>(
			TheMappedImageCollection->findImageByName(
				reinterpret_cast<const AsciiString &>(text))));
	}

	return 0;
}
