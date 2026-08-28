// Retail 0x006F9800, 42 bytes, split by the ledger across its two return arms.
//
// The first argument compared against the kind word at +0x48 -- the argument
// is the one loaded into a register, so it is written first -- and then the text at
// +0x88 compared against the second through the AsciiString compare thunk,
// which has to answer zero. The sub-object's address is formed with add rather
// than lea because ecx is dead after it -- the compare is a member call on
// that text, not on this.
//
// Both exits set the whole register, so the return is int.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	int compare(const AsciiString &other) const;			// ILT 0x000220C5
};

class Gen_006f9800
{
public:
	int bfmeMatches(int kind, const AsciiString &name) const;

private:
	char m_bfmeHead[0x48];
	int m_bfmeKind;							// +0x48
	char m_bfmeMid[0x88 - 0x4C];
	AsciiString m_bfmeName;						// +0x88
};

// ?bfmeMatches@Gen_006f9800@@QBEHHABVAsciiString@@@Z
int Gen_006f9800::bfmeMatches(int kind, const AsciiString &name) const
{
	if (kind == m_bfmeKind && m_bfmeName.compare(name) == 0)
		return 1;

	return 0;
}
