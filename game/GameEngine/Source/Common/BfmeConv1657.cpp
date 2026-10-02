// Open-BFME5 conversions.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"

// Keep the by-value entry type while calling the real StringBase cleanup
// bodies at RVAs 0x00887940 (narrow) and 0x008881D0 (wide).
class BfmeStrNVUY
{
public:
	BfmeStrNVUY(const BfmeStrNVUY &other);
	~BfmeStrNVUY() { ((StringBase<char> *)this)->clear(); }
	char *m_bfme00;
};

class BfmeStrWVUY
{
public:
	BfmeStrWVUY() { m_bfme00 = 0; }
	~BfmeStrWVUY() { ((StringBase<unsigned short> *)this)->clear(); }
	unsigned short *m_bfme00;
};

class BfmeOwnVUY
{
public:
	char bfmeApplyVUY(BfmeStrNVUY text);
	virtual void bfmeSlot0VUY();
	virtual void bfmeSlot1VUY();
	virtual void bfmeSlot2VUY();
	virtual void bfmeSlot3VUY();
	virtual char bfmeSlot4VUY(BfmeStrWVUY *text);
};

char BfmeOwnVUY::bfmeApplyVUY(BfmeStrNVUY text)
{
	BfmeStrWVUY wide;

	((UnicodeString *)&wide)->translate(*(const AsciiString *)&text);

	return bfmeSlot4VUY(&wide);
}
