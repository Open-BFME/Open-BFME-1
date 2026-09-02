// cl: /O2
// Open-BFME: 44-byte TheAI compare at retail 0x00203DB0. If the record at
// this+4 has a zero field at +0x28, return true; otherwise call a three-arg
// helper on TheAI with (this+8, record+0x24, 0x20) and return result >= field.

class Rva00203DB0AI
{
public:
	int compare(int left, int right, int mask);
};

extern Rva00203DB0AI *_TheAIParseDefinitionAI;

struct Rva00203DB0Record
{
	char m_pad[0x24];
	int m_right;
	int m_limit;
};

class Rva00203DB0Owner
{
public:
	unsigned char ready() const;

private:
	char m_pad[4];
	Rva00203DB0Record *m_record;
	int m_left;
};

unsigned char Rva00203DB0Owner::ready() const
{
	Rva00203DB0Record *record = m_record;
	if (record->m_limit == 0)
		return 1;
	int left = m_left;
	int right = record->m_right;
	return _TheAIParseDefinitionAI->compare(left, right, 0x20) >= record->m_limit;
}
