// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ModelConditionInfo has a 0x128-byte BFME layout.  Its callers
// enter through ILT 0x0002306F at retail body RVA 0x0013C3F0; the historical
// ledger row began fourteen bytes late, after the compiler's SEH prologue.

struct AsciiString
{
	~AsciiString();
	void *m_data;
};

struct Gen00026AB2
{
	~Gen00026AB2();
	void *m_start;
	void *m_finish;
	void *m_end;
};

struct Gen_uwm_000134ad
{
	~Gen_uwm_000134ad();
	void *m_start;
	void *m_finish;
	void *m_end;
};

struct Gen00776240Field60
{
	~Gen00776240Field60();
	void *m_start;
	void *m_finish;
	void *m_end;
};

void Gen0082E5F0(void *node, unsigned int size);

struct BfmeTreeAt9C
{
	void clear();
	__forceinline ~BfmeTreeAt9C()
	{
		clear();
		if (m_header != 0) {
			Gen0082E5F0(m_header, 0x2C);
		}
	}
	void *m_header;
};

class ModelConditionInfo
{
public:
	~ModelConditionInfo();

private:
	char m_unknown00[0x28];
	Gen00026AB2 m_at28;
	AsciiString m_at34;
	int m_unknown38;
	AsciiString m_at3C;
	Gen00026AB2 m_at40;
	AsciiString m_names4C[4];
	AsciiString m_names5C[4];
	AsciiString m_names6C[4];
	AsciiString m_names7C[4];
	AsciiString m_names8C[4];
	BfmeTreeAt9C m_at9C;
	Gen_uwm_000134ad m_atA0;
	Gen00776240Field60 m_atAC;
	int m_unknownB8;
	AsciiString m_atBC;
	char m_unknownC0[0x68];
};

ModelConditionInfo::~ModelConditionInfo()
{
}
