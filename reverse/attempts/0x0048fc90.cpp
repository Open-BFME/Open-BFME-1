// ?d_0048fc90@@YAXXZ
// partial score=0.55 date=2026-09-10
// A clear that destroys its range through an out-of-line helper before
// emptying the vector.
//
// The helper takes the two ends and an empty object by value: MSVC gives that
// object a stack slot, writes its one byte there and pushes the whole word,
// which is why the prologue reserves four bytes it otherwise never uses.

extern void * (__cdecl *bfmeMemCopy)(void *destination, const void *source, unsigned int bytes);

class BfmeAllocL
{
public:
	BfmeAllocL(void)
	{
		m_bfmeTag = 0;
	}

	char m_bfmeTag;
};

char __cdecl bfmeDestroyRange(int *first, int *last, BfmeAllocL allocator);	// retail thunk 0x0002376D -> 0x0042376D

inline int *bfmeCopyRange(int *destination, const int *first, const int *last)
{
	if (first == last)
		return destination;

	int bytes = (const char *)last - (const char *)first;

	return (int *)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

class BfmeVecL
{
public:
	void bfmeErase(int *first, int *last)
	{
		m_bfmeFinish = bfmeCopyRange(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	int *m_bfmeEnd;						// +0x08
};

class BfmeTargetL
{
public:
	int m_bfmeHead[6];					// +0x00
	int m_bfmeColour;					// +0x18
};

class UnicodeString;

template <typename Char>
struct BfmeStringDataFC
{
	int m_refCount;
	int m_length;
	Char m_text[1];
};

template <typename Char>
class BfmeStringBaseFC
{
	friend class UnicodeString;

public:
	BfmeStringBaseFC() : m_data(0) {}
	BfmeStringBaseFC(const BfmeStringBaseFC &other);
	~BfmeStringBaseFC();
	void concat(const Char *text, int length);

protected:
	BfmeStringDataFC<Char> *m_data;
};

class UnicodeString : private BfmeStringBaseFC<unsigned short>
{
public:
	UnicodeString() : BfmeStringBaseFC<unsigned short>() {}
	UnicodeString(const UnicodeString &other)
		: BfmeStringBaseFC<unsigned short>(other)
	{
	}
	~UnicodeString() {}

	int length() const { return m_data ? m_data->m_length : 0; }
	const unsigned short *text() const
	{
		return m_data ? m_data->m_text : 0;
	}
	void concat(const unsigned short *text, int length)
	{
		BfmeStringBaseFC<unsigned short>::concat(text, length);
	}
};

class BfmeThingDispatchFC
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void clear();
};

class BfmeTargetDispatchFC
{
public:
	virtual void slot0();
	virtual void prepare();
};

class BfmeDisplayStringFC
{
public:
	virtual void slot0();
	virtual void setFont(void *font);
};

class BfmeDisplayManagerFC
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual BfmeDisplayStringFC *newDisplayString();
	virtual void freeDisplayString(BfmeDisplayStringFC *string);
};

class BfmeLayoutFC
{
public:
	BfmeLayoutFC(int offset) : m_offset(offset) {}
	int m_offset;
};

struct BfmeLayoutElementFC
{
	void *m_measure;
	int m_unused;
	int m_offset;
};

extern BfmeDisplayManagerFC *TheDisplayStringManager;
extern void *TheDisplay;
extern void *TheGameClient;
extern float g_bfmeUint32Scale;
extern void j_0001ad25();
extern void j_0000badc();
extern void j_0001d30e();

class Gen_0048FA30;
typedef void (Gen_0048FA30::*BfmeAddLineFC)(const UnicodeString *line);
typedef void (Gen_0048FA30::*BfmeFlushLineFC)(int *position, int line,
	const UnicodeString *text);
typedef BfmeLayoutFC (__cdecl *BfmeLayoutCallFC)(BfmeLayoutElementFC **first,
	BfmeLayoutElementFC **last, BfmeLayoutFC layout);
union BfmeAddLineCastFC { void (*raw)(); BfmeAddLineFC member; };
union BfmeFlushLineCastFC { void (*raw)(); BfmeFlushLineFC member; };
union BfmeLayoutCastFC { void (*raw)(); BfmeLayoutCallFC function; };

class Gen_0048FA30
{
public:
	void bfmeClear(void);
	void bfmeForward(const UnicodeString &text, int force);
	void bfmeAddLine(const UnicodeString *line);
	void bfmeFlushLine(int *position, int line, const UnicodeString *text);

private:
	int m_bfmeHead[2];					// +0x00
	BfmeTargetL *m_bfmeTarget;				// +0x08
	BfmeVecL m_bfmeVector;					// +0x0C
	int m_bfmeCount;					// +0x18
	int m_bfmeIndex;					// +0x1C
	int m_bfmeState;					// +0x20
};

// ?bfmeClear@Gen_0048FA30@@QAEXXZ
void Gen_0048FA30::bfmeClear(void)
{
	m_bfmeCount = 0;
	m_bfmeIndex = 0;
	m_bfmeState = 0;

	bfmeDestroyRange(m_bfmeVector.m_bfmeStart, m_bfmeVector.m_bfmeFinish, BfmeAllocL());

	m_bfmeVector.bfmeClear();

	m_bfmeTarget->m_bfmeColour = 0xFF000000;
}

class BfmeDisplayFC
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual int getWidth(); virtual int getHeight();
};

class BfmeClientFC
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0c(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1c(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3c(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4c(); virtual void slot50();
	virtual void slot54(); virtual void slot58(); virtual void slot5c();
	virtual void slot60(); virtual void slot64(); virtual int getFrame();
};

void Gen_0048FA30::bfmeForward(const UnicodeString &source, int force)
{
	((BfmeThingDispatchFC *)this)->clear();
	UnicodeString text(source);
	((BfmeTargetDispatchFC *)m_bfmeTarget)->prepare();
	if (text.length() == 0)
		return;

	int width = ((BfmeDisplayFC *)TheDisplay)->getWidth() / 2;
	if (width < 0)
		width += (int)g_bfmeUint32Scale;
	int height = ((BfmeDisplayFC *)TheDisplay)->getHeight();
	if (height < 0)
		height += (int)g_bfmeUint32Scale;
	m_bfmeCount = ((BfmeClientFC *)TheGameClient)->getFrame();
	if (force) {
		m_bfmeIndex = m_bfmeCount + force * 0x1e;
		m_bfmeState = m_bfmeIndex - 0x1e;
	} else {
		m_bfmeIndex = 0;
		m_bfmeState = m_bfmeCount + 0x1c2;
	}

	m_bfmeTarget->m_bfmeColour = 0xFF000000;
	BfmeDisplayStringFC *display = TheDisplayStringManager->newDisplayString();
	if (!display)
		return;
	display->setFont(*(void **)((char *)m_bfmeTarget + 4));

	UnicodeString line;
	int position[4] = { 0, 0, 0, height };
	int lineNumber = 0;
	const unsigned short *chars = text.text();
	for (int i = 0; i < text.length(); ++i) {
		unsigned short ch = chars ? chars[i] : 0;
		if (ch == 0x20) {
			++lineNumber;
		} else if (ch == 0x0a) {
			BfmeAddLineCastFC add = { j_0001ad25 };
			(this->*add.member)(&line);
			lineNumber = 0;
		} else {
			line.concat(chars + i, 1);
		}
	}
	if (line.length() != 0) {
		BfmeFlushLineCastFC flush = { j_0000badc };
		(this->*flush.member)(position, lineNumber, &line);
	}

	BfmeLayoutElementFC **first = (BfmeLayoutElementFC **)m_bfmeVector.m_bfmeStart;
	BfmeLayoutElementFC **last = (BfmeLayoutElementFC **)m_bfmeVector.m_bfmeFinish;
	BfmeLayoutCastFC layout = { j_0001d30e };
	BfmeLayoutFC result = layout.function(first, last, BfmeLayoutFC(position[3]));
	(void)result;
	TheDisplayStringManager->freeDisplayString(display);
}
