// Open-BFME5 conversion.

struct R4Word
{
	const char *m_name;
	int m_value;
};

const R4Word *Rva008D48F0(const char *text, unsigned int length);

class Rva008AD000
{
public:
	unsigned char has(int value);
};

class Rva008ACFC0RegisteredObject
{
public:
	virtual void onRegistered(void) = 0;
};

class Rva008ACFC0PointerRegistry
{
public:
	void add(Rva008ACFC0RegisteredObject *value);
};

class Rva008AD350Holder
{
private:
	char m_padding00[0xA28];
public:
	Rva008AD000 m_members;
};

extern Rva008AD350Holder *g_bfmeHolderBU;
extern unsigned int g_bfmeHashMasks008AD350[];

struct BfmeHeader008AD350
{
	unsigned short m_refs;
	unsigned short m_length;
	char m_padding04[4];
	char m_text[1];
};

struct BfmeString008AD350
{
	BfmeHeader008AD350 *m_header;
};

class BfmeObject008AD350
{
public:
	void setMember(BfmeString008AD350 *key, void *value, int enabled);

private:
	char m_padding00[0x1C];
	int m_bits : 24;
	int m_tail : 8;
};

void BfmeObject008AD350::setMember(BfmeString008AD350 *key, void *value, int enabled)
{
	const BfmeHeader008AD350 *header = key->m_header;
	const R4Word *word = Rva008D48F0(header->m_text, header->m_length);

	if (word != 0 && word->m_value >= 0xC8)
	{
		unsigned mask = g_bfmeHashMasks008AD350[word->m_value];
		if (enabled != 0)
			m_bits &= ~mask;
		else
			m_bits |= mask;

		if (enabled == 0)
		{
			Rva008AD000 *members = (Rva008AD000 *)((char *)g_bfmeHolderBU + 0xA28);
			if (members->has((int)value) == 0)
				((Rva008ACFC0PointerRegistry *)members)->add((Rva008ACFC0RegisteredObject *)value);
		}
	}
}
