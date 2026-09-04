// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: BfmeThingAVB destructor at retail 0x003B5170 (111B).
// Sibling of blocked ctor 0x003B5100. Dual inheritance: SubsystemInterface-sized
// primary base (dtor 0x009A1A40) plus Snapshot-like secondary at +0x08 (inline
// empty dtor restoring 0x01073744), then vector members at +0x10 (0x003B47F0 via
// ILT 0x00046939) and +0x20 (0x00363750 via ILT 0x00035D8C).

struct Gen_uwm_00046939
{
	~Gen_uwm_00046939();

private:
	char m_bytes[12];
};

struct Gen_uwm_00035d8c
{
	~Gen_uwm_00035d8c();

private:
	char m_bytes[12];
};

struct S4Base009A1A40
{
	virtual ~S4Base009A1A40();

private:
	int m_name04;
};

struct BfmeThingAVBSecondary
{
	virtual ~BfmeThingAVBSecondary() {}

private:
	int m_field04;
};

class BfmeThingAVB : public S4Base009A1A40, public BfmeThingAVBSecondary
{
public:
	virtual ~BfmeThingAVB();

private:
	Gen_uwm_00046939 m_vec10;
	char m_flag1C;
	char m_flag1D;
	char m_pad1E;
	char m_pad1F;
	Gen_uwm_00035d8c m_vec20;
};

// ??1BfmeThingAVB@@UAE@XZ
BfmeThingAVB::~BfmeThingAVB()
{
}
