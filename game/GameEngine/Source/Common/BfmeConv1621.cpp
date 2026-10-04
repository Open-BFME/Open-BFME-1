// Open-BFME5 conversions.

// The string this body returns is retail's StringBase<char>: both copy calls in
// the body go to 0x00887B60, which targets/game/reverse/functions.csv owns as
// ??0?$StringBase@D@@AAE@ABV0@@Z (game/Libraries/Source/string/StringBase.cpp).
// BfmeStrVTM keeps this ledger's placeholder spelling -- the mangled name
// ?bfmeNameVTM@BfmeOwnVTM@@QAE?AVBfmeStrVTM@@XZ depends on it -- and adds no
// data, so its implicit copy constructor forwards to that base copy and the
// only symbol the object references is the one retail calls.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class BfmeStrVTM : public AsciiString
{
};

struct BfmeNodeVTM
{
	BfmeNodeVTM *m_bfme00;
	int m_bfme04;
	BfmeStrVTM m_bfme08;
};

class BfmeHostVTM
{
public:
	char m_bfmePad000[0x174];
	BfmeNodeVTM *volatile m_bfme174;
};

// The fallback the body loads as the immediate 0x01336E50. This is the one
// spelling at that VA that game/ actually defines:
// game/GameEngine/Source/Common/Bfme/Rva00C6DC10StaticInit.cpp, and
// targets/game/reverse/dir32_addresses.csv records this exact name for it.
extern AsciiString Rva01336E50EmptyString;

class BfmeOwnVTM
{
public:
	BfmeStrVTM bfmeNameVTM();
};

BfmeStrVTM BfmeOwnVTM::bfmeNameVTM()
{
	BfmeHostVTM *host = *(BfmeHostVTM **)((char *)this - 0xe0);
	BfmeNodeVTM *head = host->m_bfme174;
	BfmeNodeVTM *node;
	int count = 0;
	const BfmeStrVTM *source;

	for (node = head->m_bfme00; node != head; node = node->m_bfme00)
		++count;

	if (count == 1)
		source = &host->m_bfme174->m_bfme00->m_bfme08;
	else
		source = (const BfmeStrVTM *)&Rva01336E50EmptyString;

	return *source;
}