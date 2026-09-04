// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

// Open-BFME5: W3DModelDraw-family const accessor returning the first element
// of the inline AsciiString range at +0x28/+0x2c, retail 0x007622C0, 148
// bytes. The nested range wrapper preserves the retail field-load shape.

#include "StringInline.h"

class Gen_007622C0_AsciiStringVector
{
public:
	int size() const { return m_end - m_begin; }
	AsciiString &operator[](unsigned int index) const { return m_begin[index]; }

	AsciiString *m_begin; // +0x28
	AsciiString *m_end;   // +0x2c
};

class Gen_007622C0
{
public:
	AsciiString method() const;

private:
	unsigned char m_unreconstructed_00[0x28];
	Gen_007622C0_AsciiStringVector m_items; // +0x28
};

AsciiString Gen_007622C0::method() const
{
	int count = m_items.size();
	if (count == 0)
	{
		AsciiString temp("");
		return temp;
	}
	return m_items[0];
}
