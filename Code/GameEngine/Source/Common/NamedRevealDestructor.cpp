// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: NamedReveal's destructor, retail 0x00339C30, 89 bytes. The body
// carried only a machine byte-dump row; the symbols.csv pin names it, and the
// __copy over this element type at 0x0033A9F0 is already ledgered beside it.
//
// Three AsciiStrings, destroyed at +0x0C, +0x04 and +0x00, which is reverse
// declaration order. The word at +0x08 between the second and the third is left
// alone -- whatever it is, it has no destructor.
//
// No vptr store at the top and no base call, so the class has neither. The
// unwind slot counts down 1, 0, -1, and its middle store is a byte because the
// high three are already clear.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();						// retail 0x00887940

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class NamedReveal
{
public:
	~NamedReveal();

private:
	AsciiString m_bfmeFirst;				// +0x00
	AsciiString m_bfmeSecond;				// +0x04
	unsigned char m_bfmePad08[0x04];			// +0x08
	AsciiString m_bfmeThird;				// +0x0C
};

// ??1NamedReveal@@QAE@XZ
NamedReveal::~NamedReveal()
{
}
