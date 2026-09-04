// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Constructor paired with the polymorphic member destructor at retail
// 0x004B1670. The last member is the inline BFME buffer constructor.

void *bfmeAllocNode(unsigned int bytes);             // retail 0x0082E540

class BfmeBase1134
{
public:
	BfmeBase1134(void);
	virtual ~BfmeBase1134(void);

private:
	int m_bfmeField;
};

struct BfmeTailT
{
	BfmeTailT(unsigned int bytes)
	{
		m_bfmeData = 0;
		m_bfmeData = (char *)bfmeAllocNode(bytes);
		m_bfmeLength = 0;
		m_bfmeData[0] = 0;
		*(int *)(m_bfmeData + 4) = 0;
		*(char **)(m_bfmeData + 8) = m_bfmeData;
		*(char **)(m_bfmeData + 12) = m_bfmeData;
	}
	~BfmeTailT(void);

	char *m_bfmeData;
	int m_bfmeLength;
};

class BfmeOpaqueZeroMember
{
public:
	BfmeOpaqueZeroMember(void)
	{
		m_bfmeValue = 0;
	}
	~BfmeOpaqueZeroMember(void);

	int m_bfmeValue;
};

class Gen_004B1670 : public BfmeBase1134
{
public:
	Gen_004B1670(void);
	virtual ~Gen_004B1670(void);

private:
	char m_bfme08;
	int m_bfmeVectorStart;
	int m_bfmeVectorFinish;
	BfmeOpaqueZeroMember m_bfmeVectorEnd;
	int m_bfme18;
	int m_bfme1c;
	int m_bfme20;
	int m_bfme24;
	int m_bfme28;
	int m_bfme2c;
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
	int m_bfme3c;
	int m_bfme40;
	BfmeTailT m_bfmeBuffer;
};

// ??0Gen_004B1670@@QAE@XZ
Gen_004B1670::Gen_004B1670(void) :
	BfmeBase1134(),
	m_bfme08(0),
	m_bfmeVectorStart(0),
	m_bfmeVectorFinish(0),
	m_bfmeVectorEnd(),
	m_bfme18(0),
	m_bfme1c(0),
	m_bfme30(0),
	m_bfme34(0),
	m_bfme38(0),
	m_bfme3c(0),
	m_bfme40(0),
	m_bfmeBuffer(0x18)
{
}
