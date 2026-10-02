// Open-BFME5: the layout-descriptor constructor at retail 0x00421B80, 129 bytes.
//
// The AsciiString member's default construction zeroes its pointer; set("Arial",
// 5) runs before the remaining stores. MSVC groups the plain initializers'
// shared constants itself (cl for the two true flags, eax for the three -1
// words).
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Gen_00421B80
{
public:
	Gen_00421B80(void);

	AsciiString m_bfmeName;					// +0x00
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
{
	static_cast<StringBase<char> &>(m_bfmeName).set("Arial", 5);
	m_bfmeSize = 10;
	m_bfmeBold = false;
	m_bfmeEnabled = true;
	m_bfmeFirst = -1;
	m_bfmeColor = 0xFF000000;
	m_bfmeSecond = -1;
	m_bfmeThird = -1;
	m_bfmeOffset = -0.05f;
	m_bfmeItalic = false;
	m_bfmeDepth = -10;
	m_bfmeVisible = true;
}
