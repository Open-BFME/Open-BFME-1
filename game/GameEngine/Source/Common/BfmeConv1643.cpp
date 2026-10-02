// Open-BFME5 conversions.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class BfmeStrNVUL
{
public:
	~BfmeStrNVUL() { reinterpret_cast<StringBase<char> *>(this)->clear(); }
	char *m_bfme00;
};

class BfmeStrWVUL
{
public:
	~BfmeStrWVUL() { reinterpret_cast<StringBase<unsigned short> *>(this)->clear(); }
	unsigned short *m_bfme00;
};

class BfmeOwnVUL
{
public:
	~BfmeOwnVUL();
	char m_bfmePad00[0x20];
	BfmeStrNVUL m_bfme20;
	char m_bfmePad24[4];
	BfmeStrNVUL m_bfme28;
	char m_bfmePad2c[4];
	BfmeStrWVUL m_bfme30;
	char m_bfmePad34[0x10];
	BfmeStrWVUL m_bfme44;
	BfmeStrWVUL m_bfme48;
};

BfmeOwnVUL::~BfmeOwnVUL()
{
}
