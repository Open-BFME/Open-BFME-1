// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the player-table palantir write at retail 0x0052B540, 125 bytes.
// The value is handed in by the caller here; only the key is built, from a row
// and a column.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class UnicodeStringZG;

class WindowManager
{
public:
	void bfme_setAptText(const AsciiString &key, const UnicodeString &value);
};

// ILT 0x0000BDCA reaches WindowManager::bfme_setAptText at 0x0046CBF0.
extern WindowManager *g_rva012F19E8WindowManager;	// retail 0x012F19E8

// ?bfmePlayerTableZG@@YGXHHABVUnicodeStringZG@@@Z
void __stdcall bfmePlayerTableZG(int row, int column, const UnicodeStringZG &value)
{
	AsciiString key;

	key.format(AsciiString("PlayerTable:%d:%d"), row, column);

	g_rva012F19E8WindowManager->bfme_setAptText(
		key, reinterpret_cast<const UnicodeString &>(value));
}
