// ??0Display@@QAE@XZ
// partial score=0.78 date=2026-09-17
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	void *m_name;
};

class BfmeUnicodeMember
{
public:
	BfmeUnicodeMember() : m_data(0) {}
	~BfmeUnicodeMember();
	void releaseBuffer();

private:
	void *m_data;
};

class BfmeAsciiMember
{
public:
	BfmeAsciiMember() : m_data(0) {}
	~BfmeAsciiMember();
	void releaseBuffer();

private:
	void *m_data;
};

class BfmeDisplayFieldString
{
public:
	void *m_data;
	void releaseBuffer();
};

extern "C" __declspec(dllimport) unsigned long __stdcall GetCurrentThreadId(void);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(void *frequency);

class Display : public SubsystemInterface
{
public:
	Display();
	virtual void bfmeStopMovie();

private:
	char m_data[0x138];
};

Display::Display()
{
	char *raw = (char *)this;
	UnsignedInt *words = (UnsignedInt *)raw;
	UnsignedByte *bytes = (UnsignedByte *)raw;

	words[2] = 0;
	words[3] = 0;
	words[4] = 0;
	bytes[0x14] = 0;
	words[6] = 0;
	words[7] = 0;
	words[8] = 0;
	words[9] = 0;
	words[14] = 0;
	words[15] = 0;
	words[16] = 0;
	bytes[0x44] = 0;
	words[10] = 0;
	words[11] = 0;
	words[12] = 0;
	words[13] = 0;
	words[18] = 0;
	words[19] = GetCurrentThreadId();
	bytes[0x59] = 0;
	words[20] = 0;
	words[21] = 0;
	bytes[0x58] = 0;
	words[23] = 0;
	bytes[0x60] = 0;

	UnsignedInt *movie = (UnsignedInt *)(raw + 0x64);
	movie += 6;
	movie[-6] = 0;
	movie[-5] = 0;
	movie[-4] = 0;
	movie[-3] = 0;
	movie[-2] = 0;
	movie[-1] = 0;
	movie[0] = 0;
	movie[1] = 0;
	movie[2] = 0;
	movie[3] = 0;
	movie[4] = 0;
	movie[5] = 0;
	movie[6] = 0;
	movie[7] = 0;
	movie[8] = 0;
	movie[9] = 0;
	movie[10] = 0;
	movie[11] = 0;

	words[43] = 0;
	BfmeDisplayFieldString *field = (BfmeDisplayFieldString *)(raw + 0xCC);
	words[44] = 0;
	words[45] = 0;
	words[46] = 0;
	words[47] = 0;
	words[48] = 0;
	words[49] = 0;
	words[50] = 0;
	field->m_data = 0;
	words[52] = 0;
	words[53] = 0;
	words[54] = 0;
	words[55] = 0;
	words[56] = 0;
	words[57] = 0;
	words[58] = 0;
	words[59] = 0;
	words[60] = 0;
	words[61] = 0;
	words[62] = 0;
	words[63] = 0;
	words[64] = 0;
	words[65] = 0;
	bytes[0x108] = 0;
	words[67] = 0;
	bytes[0x110] = 0;
	bytes[0x111] = 0;
	words[70] = 0;
	words[71] = 0x3F800000;
	words[72] = 0;
	words[73] = 0;
	words[74] = 0;
	words[75] = 0;
	words[76] = 0;
	words[77] = 0;
	words[78] = 0;
	words[79] = 0;

	field->releaseBuffer();
	QueryPerformanceFrequency((void *)0x012F1278);
	bfmeStopMovie();

	words[72] = 0;
	words[73] = 0;
	words[74] = 0;
	words[75] = 0;
	words[76] = 0;
}
