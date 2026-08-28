// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: BFME_ModuleInfoNuggetCopyLayout's copy constructor, retail
// 0x00770D60, 87 bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// Three members and nothing else: an AsciiString at +0x00 and a twelve-byte
// vector at +0x04, both copy-constructed from the source, and a word at +0x10
// copied straight. The source pointer is used as itself for the first and
// biased by four for the second.
//
// The unwind slot is written once, between the two constructors: the string is
// standing by then and has to come down if the vector's constructor throws.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);			// retail 0x00887B60
	~AsciiString();

private:
	char *m_bfmeData;
};

struct BfmeLegendStringVec
{
	BfmeLegendStringVec(const BfmeLegendStringVec &other);	// ILT 0x00015474
	~BfmeLegendStringVec();

	char *m_bfmeStart;
	char *m_bfmeFinish;
	char *m_bfmeEndOfStorage;
};

struct BFME_ModuleInfoNuggetCopyLayout
{
	BFME_ModuleInfoNuggetCopyLayout(
			const BFME_ModuleInfoNuggetCopyLayout &other);

	AsciiString m_bfmeName;					// +0x00
	BfmeLegendStringVec m_bfmeStrings;			// +0x04
	Int m_bfme10;						// +0x10
};

// ??0BFME_ModuleInfoNuggetCopyLayout@@QAE@ABU0@@Z
BFME_ModuleInfoNuggetCopyLayout::BFME_ModuleInfoNuggetCopyLayout(
		const BFME_ModuleInfoNuggetCopyLayout &other) :
	m_bfmeName(other.m_bfmeName),
	m_bfmeStrings(other.m_bfmeStrings)
{
	m_bfme10 = other.m_bfme10;
}
