// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Four opaque 32-byte retail twins (?dup_000af380, ?dup_00361990,
// ?dup_003ad3e0, ?dup_005bb890): return by value the string at +0x14, copied
// through the narrow StringBase<char> copy constructor 0x00887B60. Their rows
// used to sit on the pristine Zero Hour DownloadMenu.cpp under
// DownloadManager::getStatusString; the native DownloadMenu.cpp copy binds a
// different string copy, and the owner class is unproven, so the carrier keeps
// an address-derived name.

#include "ascii_string.h"

class Rva000AF380Owner
{
public:
	AsciiString getString();

	unsigned char m_pad[0x14];
	AsciiString m_string;
};

AsciiString Rva000AF380Owner::getString()
{
	return m_string;
}
