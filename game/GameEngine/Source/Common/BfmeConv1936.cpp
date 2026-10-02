// Retail's temporary here is a narrow StringBase: its constructor is the shared
// StringBase<char>(const char *) body at 0x00888BC0 and its destructor forwards
// to the shared releaseBuffer at 0x00887940. So it is spelled through the real
// AsciiString (ascii_string.h), whose inline ctor and destructor reference
// ??0?$StringBase@D@@AAE@PBD@Z and ?releaseBuffer@?$StringBase@D@@AAEXXZ -- both
// bodies game/Libraries/Source/string/StringBase.cpp defines. The TU-local
// BFMERetailAsciiString shim it replaces spelled releaseBufferDE, i.e.
// ?releaseBufferDE@BFMERetailAsciiString@@QAEXXZ, which nothing defines. Only
// the references change: the constructor and destructor calls, and the length of
// the scope-exit unwind state, are identical.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class BfmeImageDE;

// Retail's singleton is ?TheMappedImageCollection@@3PAVImageCollection@@A and the
// lookup it drives is ?findImageByName@ImageCollection@@QAEPBVImage@@ABVAsciiString@@@Z
// (retail 0x0001D606, the pin both spellings shared). No game header declares
// ImageCollection -- its Zero Hour GameClient/Image.h cannot be used here -- so
// this TU declares the one member it calls.
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
		const AsciiString &text = AsciiString(name);

		return const_cast<BfmeImageDE *>(reinterpret_cast<const BfmeImageDE *>(
			TheMappedImageCollection->findImageByName(text)));
	}

	return 0;
}