// cl: /DNDEBUG /MD /EHsc
// stlport
#include <vector>

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }
	void *m_buffer;
private:
	void releaseBuffer();
};

class Rva00387D90String : public BFMERetailAsciiString
{
public:
	Rva00387D90String(const char *text) : BFMERetailAsciiString(text) {}
};

class Rva00387D90Owner
{
public:
	Rva00387D90String *at(int index);
	unsigned char m_head[0x54];
	std::vector<Rva00387D90String> m_slots;
};

Rva00387D90String *Rva00387D90Owner::at(int index)
{
	if (index >= 0 && (unsigned int)index < (unsigned int)m_slots.size())
		return &m_slots[index];
	static Rva00387D90String invalid("Invalid Slot");
	return &invalid;
}
