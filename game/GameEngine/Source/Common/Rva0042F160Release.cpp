// cl: /O2 /Ob0

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
// Retail's UnicodeString derives from a StringBase and releases through the
// base's own releaseBuffer: this site encodes 0x00887940, the 134-byte body
// functions.csv carries as ?releaseBuffer@?$StringBase@D@@AAEXXZ and also as
// ?releaseBuffer@BFMERetailAsciiString@@AAEXXZ. Spelling the member on
// UnicodeString itself emitted ?releaseBuffer@UnicodeString@@IAEXXZ, which the
// resolver takes elsewhere.
class UnicodeString;

class BFMERetailAsciiString
{
	friend void __stdcall rva0042f160(UnicodeString other);

private:
	void releaseBuffer();
};

class UnicodeString : public BFMERetailAsciiString
{
};

void __stdcall rva0042f160(UnicodeString other)
{
	other.BFMERetailAsciiString::releaseBuffer();
}
