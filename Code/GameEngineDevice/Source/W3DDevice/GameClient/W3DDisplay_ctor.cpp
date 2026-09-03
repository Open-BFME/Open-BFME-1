// cl: /DNDEBUG /MD /EHsc

// W3DDisplay::W3DDisplay, retail 0x006FA630. reloc_names.csv identity=real
// (call-sites=1 from W3DGameClient.cpp). Display base ctor, then both vftables
// (+0 and +8, so Display is MI with an 8-byte first base), then eh-vector
// construction of two 0xC-byte members at +0xC0, then the two POD stores.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	int m_name;
};

class DisplaySecond
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display : public SubsystemInterface, public DisplaySecond
{
public:
	Display();
	virtual ~Display();

private:
	unsigned char m_unmodelled[0x90 - 12];
};

class W3DDisplayElem
{
public:
	W3DDisplayElem();
	~W3DDisplayElem();

private:
	int m_a;
	int m_b;
	int m_c;
};

// Named W3DDisplayRetail because ??0W3DDisplay@@QAE@XZ is already the
// 5-byte ILT thunk at 0x00002432. reloc_names.csv still identifies this
// body as that constructor.
class W3DDisplayRetail : public Display
{
public:
	W3DDisplayRetail();
	virtual ~W3DDisplayRetail();

private:
	int m_90;
	unsigned char m_unmodelled_94[0x28];
	unsigned char m_bc;
	W3DDisplayElem m_arr[2];
};

// ??0W3DDisplayRetail@@QAE@XZ
W3DDisplayRetail::W3DDisplayRetail()
{
	m_bc = 0;
	m_90 = 0;
}

// ??1W3DDisplayRetail@@UAE@XZ
W3DDisplayRetail::~W3DDisplayRetail()
{
}
