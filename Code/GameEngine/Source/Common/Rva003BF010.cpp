// cl: /DNDEBUG /MD /EHsc
//
// Rva003BF540::run, retail 0x003BF010, 303 bytes.
//
// d_003b8450: disabled/anyReady early-out; +0x4C hold path decrements +0x48
// from 15 then notifyTarget on Glo012F4B98; else isOpen+allowed then hold
// the arg at +0xC4 until count 0x2D and a non-empty name at arg+0x34.

template <typename T>
class StringBase
{
	friend class AsciiString;
	StringBase(const StringBase<T> &other);
	~StringBase();
public:
	bool isEmpty() const;
private:
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other)
		: StringBase<char>(other)
	{
	}
	~AsciiString() {}
	bool isEmpty() const { return StringBase<char>::isEmpty(); }
};

class Gen_00609320
{
public:
	unsigned char bfmeDisabled() const;
};

extern Gen_00609320 *g_bfmeStateDF;

class Glo012F4B98Type
{
public:
	void notifyTarget();
	void show00592D60(AsciiString *name, void (__cdecl *callback)(bool));
};

extern Glo012F4B98Type *Glo012F4B98;

class Glo012F706CType
{
public:
	bool isOpen() const;
};

extern Glo012F706CType *g_bfmeGameCW;

class Rva003BF010Arg
{
public:
	char m_pad[0x34];
	AsciiString m_name;
};

class Rva003BF540
{
public:
	void run(Rva003BF010Arg *arg);
	bool anyReady() const;
	bool allowed();

private:
	char m_pad00[0x48];
	int m_at48;
	unsigned char m_at4C;
	unsigned char m_at4D;
	char m_pad4E[0xC4 - 0x4E];
	Rva003BF010Arg *m_atC4;
};

void Rva003BF540::run(Rva003BF010Arg *arg)
{
	if (g_bfmeStateDF->bfmeDisabled())
		return;
	if (anyReady())
		return;

	if (m_at4C)
	{
		if (arg == m_atC4)
		{
			m_at4D = 0;
			return;
		}
		if (!m_at4D)
		{
			m_at48 = 15;
			m_at4D = 1;
		}
		if (--m_at48 > 0)
			return;
	}
	else if (g_bfmeGameCW->isOpen() && allowed())
	{
		if (!arg)
			return;
		if (m_atC4 != arg)
		{
			m_at48 = 0;
			m_at4C = 0;
			m_at4D = 0;
			m_atC4 = arg;
		}
		if (++m_at48 <= 0x2D)
			return;
		{
			AsciiString copy(arg->m_name);
			if (!copy.isEmpty())
				Glo012F4B98->show00592D60(&arg->m_name, 0);
			m_at4C = 1;
		}
		return;
	}
	else
		goto zero_fields;

	Glo012F4B98->notifyTarget();
zero_fields:
	m_atC4 = 0;
	m_at48 = 0;
	m_at4C = 0;
	m_at4D = 0;
}
