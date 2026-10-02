// Open-BFME5 conversions.

// Retail body at 0x0089CC10; declared in
// Rva0089CC10ConditionalOffset.cpp, spelled here by its defining name so the
// call resolves to ?get@Rva0089CC10Object@@QBEHXZ.
class Rva0089CC10Object
{
public:
	int get() const;
	int m_bfme00;
};

class BfmeA1223
{
public:
	int bfmeSize1223();
	char m_bfmePad00[8];
	Rva0089CC10Object m_bfme08;
	char m_bfmePad0c[0x1c - 0x0c];
	int m_bfme1c;
};

int BfmeA1223::bfmeSize1223()
{
	return m_bfme08.get() + (m_bfme1c & 0xff) + 3;
}
