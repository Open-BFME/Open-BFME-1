// Open-BFME5: the layout-descriptor constructor at retail 0x00421B80, 129 bytes.
//
// The name member is built by a two-argument constructor that zeroes the
// pointer and calls set, so the call precedes every other store; the rest are
// plain initializers and MSVC groups their shared constants itself (cl for the
// two true flags, eax for the three -1 words).

class BfmeStrWD
{
public:
	__forceinline BfmeStrWD(const char *text, int length)
	{
		set(text, length);
	}

	~BfmeStrWD(void);

	void set(const char *text, int length);

	char *m_bfmeData;					// +0x00
};

// An empty base with a destructor: no bytes of layout, but it gives the body
// the unwind frame and state 0 retail carries.
// The empty base sits at +0x00, so zeroing the name pointer from its
// constructor anchors that store ahead of set's argument setup; written inside
// the string's own constructor the same store sinks past the pushes.
class BfmeGuardWD
{
public:
	__forceinline BfmeGuardWD(void)
	{
		*(char **)this = 0;
	}

	~BfmeGuardWD(void);
};

class Gen_00421B80 : public BfmeGuardWD
{
public:
	Gen_00421B80(void);

	BfmeStrWD m_bfmeName;					// +0x00
	int m_bfmeSize;						// +0x04
	bool m_bfmeBold;					// +0x08
	bool m_bfmeEnabled;					// +0x09
	int m_bfmeFirst;					// +0x0C
	unsigned int m_bfmeColor;				// +0x10
	int m_bfmeSecond;					// +0x14
	int m_bfmeThird;					// +0x18
	float m_bfmeOffset;					// +0x1C
	bool m_bfmeItalic;					// +0x20
	int m_bfmeDepth;					// +0x24
	bool m_bfmeVisible;					// +0x28
};

// ??0Gen_00421B80@@QAE@XZ
Gen_00421B80::Gen_00421B80(void)
	: m_bfmeName("Arial", 5),
	  m_bfmeSize(10),
	  m_bfmeBold(false),
	  m_bfmeEnabled(true),
	  m_bfmeFirst(-1),
	  m_bfmeColor(0xFF000000),
	  m_bfmeSecond(-1),
	  m_bfmeThird(-1),
	  m_bfmeOffset(-0.05f),
	  m_bfmeItalic(false),
	  m_bfmeDepth(-10),
	  m_bfmeVisible(true)
{
}
