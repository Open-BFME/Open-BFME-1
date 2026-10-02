// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME7: the destructor at 0x0012A5B0 (160 B).  Non-virtual (the
// literal "vftable" store 0x01073744 at [this+0] happens LAST, right before
// the epilogue, not first as a real C++ virtual dtor would) -- BFME's
// manual function-table-pointer idiom (see BfmeConv881.cpp's m_bfmeVft
// fields), modelled as a plain first member whose inline destructor writes
// the literal back.  Reverse member unwind: six matched AudioEventRTS
// members 0x70 bytes apart at +0x70/+0xE0/+0x150/+0x1C0/+0x230/+0x2A0, one
// vector<AsciiString> at +0x64 (0xC bytes; its matched destructor at 0x658A0
// is reached through the ILT at 0x26AB2), then the manual vft-slot restore.
// The vector's extern template declaration below keeps this TU referencing
// the matched destructor definition instead of emitting another body.

#include <vector>
#include "ascii_string.h"
extern template _STL::vector<AsciiString>::~vector();

extern "C" const void *bfmeVftSnapshot[];
#pragma comment(linker, "/alternatename:_bfmeVftSnapshot=??_7Snapshot@@6B@")

struct BfmeVftSlot0012A5B0
{
	~BfmeVftSlot0012A5B0()
	{
		m_p = (void *)bfmeVftSnapshot;
	}

	void *m_p;
};

class AudioEventRTS
{
public:
	~AudioEventRTS();

private:
	char m_body[ 0x70 ];
};

class Rva0012A5B0
{
public:
	~Rva0012A5B0();

private:
	BfmeVftSlot0012A5B0 m_vft;
	unsigned char m_unreconstructed04[ 0x64 - 4 ];
	_STL::vector<AsciiString> m_member64;
	AudioEventRTS m_audio70;
	AudioEventRTS m_audioE0;
	AudioEventRTS m_audio150;
	AudioEventRTS m_audio1C0;
	AudioEventRTS m_audio230;
	AudioEventRTS m_audio2A0;
};

// ??1Rva0012A5B0@@QAE@XZ
Rva0012A5B0::~Rva0012A5B0()
{
}
