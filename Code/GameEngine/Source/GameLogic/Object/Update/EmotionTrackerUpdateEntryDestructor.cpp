// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: EmotionTrackerUpdateEntry's destructor, retail 0x0037B130, 92
// bytes. The body carried only a machine byte-dump row; the symbols.csv pin
// names it.
//
// Three AsciiStrings and nothing else: +0xF4, +0x3C and +0x00, destroyed in
// that order, which is reverse declaration order. There is no vptr store at the
// top and no base call, so the class has neither.
//
// The unwind slot counts them down 1, 0, -1, and the middle store is a byte
// rather than a word because the compiler knows the three high bytes are
// already clear.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();						// retail 0x00887940

private:
	char *m_data;
};

class EmotionTrackerUpdateEntry
{
public:
	~EmotionTrackerUpdateEntry();

private:
	AsciiString m_bfmeFirst;				// +0x00
	unsigned char m_bfmePad04[0x3C - 0x04];
	AsciiString m_bfmeSecond;				// +0x3C
	unsigned char m_bfmePad40[0xF4 - 0x40];
	AsciiString m_bfmeThird;				// +0xF4
};

// ??1EmotionTrackerUpdateEntry@@QAE@XZ
EmotionTrackerUpdateEntry::~EmotionTrackerUpdateEntry()
{
}
