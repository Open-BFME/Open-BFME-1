// cl: /O2

class AsciiString
{
public:
	int m_data;
};

class AsciiStringField
{
public:
	void set(AsciiString *value);
};

class Dict
{
public:
	AsciiString *setAsciiString(AsciiString value);
};

extern Dict g_dictA;
extern Dict g_dictB;

class Rva0019BC00Owner
{
public:
	void apply(int index, AsciiString a, AsciiString b);
	void prepare(int index);
	void finish(int index);

private:
	char m_head[0xC];
	char *m_data;
};

void Rva0019BC00Owner::apply(int index, AsciiString a, AsciiString b)
{
	prepare(index);
	AsciiStringField *field = (AsciiStringField *)(m_data + (index << 4) + 0xC);
	field->set(g_dictA.setAsciiString(a));
	field->set(g_dictB.setAsciiString(b));
	finish(index);
}
