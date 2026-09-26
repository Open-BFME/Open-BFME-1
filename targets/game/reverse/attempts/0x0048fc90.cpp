// ?d_0048fc90@@YAXXZ
// partial score=0.7 date=2026-09-20
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /FAsc /Fabuild/worker-evidence/target-unsigned-return.cod
// ?d_0048fc90@@YAXXZ
// partial score=0.68 date=2026-09-20
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
class BfmeDisplayStringFC;

template <typename Char>
struct BfmeStringDataFC
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	Char m_text[1];
};

template <typename Char>
class BfmeStringBaseFC
{
	friend class UnicodeString;

public:
	BfmeStringBaseFC() : m_data(0) {}
	BfmeStringBaseFC(const BfmeStringBaseFC &other);
	~BfmeStringBaseFC() { releaseBuffer(); }
	void concat(const Char *text, int length);

protected:
	BfmeStringDataFC<Char> *m_data;
	void releaseBuffer();
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
	void clear()
	{
		BfmeStringBaseFC<unsigned short>::releaseBuffer();
	}
};

namespace _STL
{
template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate(void *block, unsigned int bytes);
};
}

struct BfmeLocalVecFC
{
	int *m_start;
	int *m_finish;
	int *m_end;

	BfmeLocalVecFC() : m_start(0), m_finish(0), m_end(0) {}
	~BfmeLocalVecFC()
	{
		if (m_start != 0) {
			unsigned int bytes = (unsigned int)((char *)m_end -
				(char *)m_start);
			if (bytes > 0x80)
				::operator delete(m_start);
			else
				_STL::__node_alloc<true, 0>::_M_deallocate(m_start, bytes);
		}
	}
};

struct BfmeLineInfoFC
{
	int m_height;
	int m_width;
	BfmeLocalVecFC *m_position;
	BfmeDisplayStringFC *m_display;
	UnicodeString m_text;
	int m_unknown14;
};

extern "C" __declspec(dllimport) int __cdecl iswspace(unsigned short c);

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

class BfmeDisplayFC;
class BfmeClientFC;
class BfmeDisplayManagerFC;

class BfmeDisplayStringFC
{
public:
	virtual void slot0();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
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
	int m_extra0c;
	int m_extra10;
	int m_extra14;
};

struct BfmeLayoutRangeFC
{
	BfmeLayoutElementFC **m_first;
	BfmeLayoutElementFC **m_last;
};

#define TheDisplayStringManager (*(BfmeDisplayManagerFC **)0x012f12cc)
#define TheDisplay (*(BfmeDisplayFC **)0x012f1270)
#define TheGameClient (*(BfmeClientFC **)0x012f1464)
#define g_bfmeUint32Scale (*(float *)0x01075358)
#define g_bfmeDisplayScale (*(float *)0x010f9aa8)
extern void j_0001ad25();
extern void j_0000badc();
extern void j_0001d30e();

class Gen_0048FA30;
typedef void (Gen_0048FA30::*BfmeAddLineFC)(const BfmeLineInfoFC *line);
typedef void (Gen_0048FA30::*BfmeFlushLineFC)(BfmeLineInfoFC *position, int line,
	const UnicodeString *text);
typedef BfmeLayoutFC (__cdecl *BfmeLayoutCallFC)(BfmeLayoutElementFC **first,
	BfmeLayoutElementFC **last, BfmeLayoutFC layout);
union BfmeAddLineCastFC { void *asVoid; BfmeAddLineFC member; };
union BfmeFlushLineCastFC { void *asVoid; BfmeFlushLineFC member; };
union BfmeLayoutCastFC { void *asVoid; BfmeLayoutCallFC function; };

class Gen_0048FA30
{
public:
	void bfmeClear(void);
	void bfmeForward(const UnicodeString &text, int force);
	void bfmeAddLine(const BfmeLineInfoFC *line);
	void bfmeFlushLine(BfmeLineInfoFC *position, int line,
		const UnicodeString *text);

private:
	int m_bfmeHead[2];					// +0x00
	BfmeTargetL *m_bfmeTarget;				// +0x08
	BfmeVecL m_bfmeVector;					// +0x0C
	int m_bfmeCount;					// +0x18
	int m_bfmeIndex;					// +0x1C
	int m_bfmeState;					// +0x20
};

#pragma comment(linker, "/alternatename:?bfmeAddLine@Gen_0048FA30@@QAEXPBUBfmeLineInfoFC@@@Z=?j_0001ad25@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeFlushLine@Gen_0048FA30@@QAEXPAVBfmeLineInfoFC@@HPBVUnicodeString@@@Z=?j_0000badc@@YAXXZ")

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
	virtual void slot24(); virtual void slot28();
	virtual unsigned int getMetric();
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

	float width = (float)(((BfmeDisplayFC *)TheDisplay)->getMetric() / 2);
	float height = (float)((BfmeDisplayFC *)TheDisplay)->getMetric();
	int scaledHeight = (int)(height * g_bfmeDisplayScale);
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

	BfmeLocalVecFC position;
	BfmeLineInfoFC info;
	info.m_height = (int)width;
	info.m_width = scaledHeight;
	info.m_position = &position;
	info.m_display = display;
	info.m_unknown14 = 0;
	UnicodeString line;
	int lineNumber = 0;
	const unsigned short *chars = text.text();
	int index = 0;
	bool atWhitespace = true;
	unsigned short ch = chars ? chars[0] : 0;
	while (index < text.length()) {
		if (atWhitespace) {
			if (iswspace(ch)) {
				if (ch == 0x20) {
					++lineNumber;
				} else if (ch == 0x0a) {
					this->bfmeAddLine(&info);
					lineNumber = 0;
				}
				++index;
				ch = chars ? chars[index] : 0;
				continue;
			}
			atWhitespace = false;
		}
		if (iswspace(ch)) {
		this->bfmeFlushLine(&info, lineNumber, &line);
		line.clear();
		lineNumber = 0;
		atWhitespace = true;
			continue;
		}
		line.concat(&ch, 1);
		++index;
		ch = chars ? chars[index] : 0;
	}
	if (!atWhitespace) {
		this->bfmeFlushLine(&info, lineNumber, &line);
	}
	this->bfmeAddLine(&info);

	BfmeLayoutCastFC layout;
	layout.asVoid = (void *)j_0001d30e;
	int x = 100;
	int childWidth = *(int *)((char *)(*(int *)(m_bfmeTarget->m_bfmeHead + 1)) + 0x10);
	float xStep = (float)childWidth * *(float *)0x109b46c;
	for (int *it = m_bfmeVector.m_bfmeStart;
		it != m_bfmeVector.m_bfmeFinish; ++it) {
		BfmeLayoutRangeFC *range = *(BfmeLayoutRangeFC **)it;
		BfmeLayoutElementFC **first = range->m_first;
		BfmeLayoutElementFC **last = range->m_last;
		x = (int)((float)x + xStep);
		int offset = 0x14;
		for (BfmeLayoutElementFC **item = first; item != last; ++item) {
			BfmeLayoutElementFC *element = *item;
			element->m_extra10 = offset;
			offset += element->m_extra0c;
			element->m_extra14 = x;
		}
		BfmeLayoutFC result = layout.function(first, last,
			BfmeLayoutFC(x));
		(void)result;
		x += 0x1e;
	}
	TheDisplayStringManager->freeDisplayString(display);
}
