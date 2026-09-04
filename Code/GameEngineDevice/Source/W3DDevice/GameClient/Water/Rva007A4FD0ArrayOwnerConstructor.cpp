// cl: /DNDEBUG /MD /EHsc
// Retail 0x007A4FD0: constructor for the 0x80-byte water polygon record.
// The vtable/dtor at 0x007A1230 and the two six-element EH arrays identify
// the record; its polygon-trigger initializer is the adjacent 0x007A4D40
// body.

class Rva007A4FD0AsciiString
{
public:
	Rva007A4FD0AsciiString(void);
	~Rva007A4FD0AsciiString(void);

private:
	void *m_data;
};

class Rva007A4FD0Cell
{
public:
	Rva007A4FD0Cell(void);
	~Rva007A4FD0Cell(void);

private:
	void *m_data;
};

class Rva007A4FD0ArrayOwner
{
public:
	Rva007A4FD0ArrayOwner(void *source);
	virtual ~Rva007A4FD0ArrayOwner(void);
	void initialize(void *source);

private:
	unsigned char m_firstFlag;
	unsigned char m_firstPadding[3];
	void *m_firstValue;
	Rva007A4FD0AsciiString m_names[6];
	Rva007A4FD0Cell m_cells[6];
	unsigned char m_secondFlag;
	unsigned char m_secondPadding[0x0f];
	unsigned int m_value4c;
	unsigned int m_value50;
	unsigned int m_value54;
	unsigned int m_value58;
	unsigned int m_value5c;
	unsigned int m_value60;
	unsigned char m_cached;
};

// The initializer is still a generic dump row.  Keep its call target named by
// that existing row until the adjacent body is converted; the cast supplies
// the recovered thiscall/one-argument ABI without inventing a second address.
extern void d_007a4d40(void);

// VC7.1 reserves __thiscall in a free-function-pointer typedef.  A fastcall
// cast with the source duplicated gives the same ECX object and stack argument
// while leaving the otherwise-unused EDX copy harmless at the target.
typedef void (__fastcall *Rva007A4FD0InitializeCall)(
	Rva007A4FD0ArrayOwner *, void *, void *);

Rva007A4FD0ArrayOwner::Rva007A4FD0ArrayOwner(void *source)
	: m_firstFlag(0), m_firstValue(0)
{
	m_secondFlag = 0;
	m_value4c = 0;
	m_value50 = 0;
	m_value54 = 0;
	m_value58 = 0;
	m_value5c = 0;
	m_value60 = 0;
	m_cached = 0;
	((Rva007A4FD0InitializeCall)d_007a4d40)(this, source, source);
}
