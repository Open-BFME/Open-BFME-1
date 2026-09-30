// ?d_004354f0@@YAXXZ
// partial score=0.9729 date=2026-09-30
// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#define _STLP_NO_EXCEPTIONS 1
#define _M_insert_overflow j_0001be87
#include <vector>
#undef _M_insert_overflow

typedef int Int;
typedef unsigned short WideChar;

class BfmeItemKA;
class GameFont;
class UnicodeString;
class DisplayString;

struct Gen_t_00435350_m4pod
{
	void *m_data;
};

struct Gen_t_004353c0_p8cd
{
	Int m_data[2];
	Gen_t_004353c0_p8cd();
	Gen_t_004353c0_p8cd(const Gen_t_004353c0_p8cd &other);
	~Gen_t_004353c0_p8cd();
	Gen_t_004353c0_p8cd &operator=(const Gen_t_004353c0_p8cd &other);
};

class BfmeItemKA
{
public:
	void bfmeDoKA();
};

class Rva0048EC80Manager
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual DisplayString *newDisplayString() = 0;
};

class DisplayString
{
public:
	virtual void slot00() = 0;
	virtual void setText(UnicodeString text) = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void setFont(GameFont *font) = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void getSize(Int *height, Int *width) = 0;
};

extern Rva0048EC80Manager *Rva0048EC80TheManager;
extern BfmeItemKA **g_bfmeBegKA;
extern const WideChar BFMEEmptyString[];

// The constructor passes the sample string by value through DisplayString.
template <typename T>
class StringBase
{
	friend class UnicodeString;

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);

protected:
	struct Header
	{
		Int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
	~UnicodeString() {}
};

class Rva00435A40Sink : public BfmeItemKA
{
public:
	Rva00435A40Sink(GameFont *font, float width, float height,
		Int scaledWidth, Int value60, Int value58, Int value64);
	~Rva00435A40Sink();
	void publish(const UnicodeString &text, unsigned int color);

private:
	DisplayString *m_00;
	GameFont *m_04;
	_STL::vector<Gen_t_004353c0_p8cd> m_08;
	Int m_14;
	Int m_18;
	Int m_1c;
	Int m_20;
	Int m_24;
	Int m_28;
	Int m_2c;
	Int m_30;
	DisplayString **m_34;
	Int *m_38;
	Int m_3c;
	Int m_40;
	Int m_44;
	float m_48;
	float m_4c;
	float m_50;
	float m_54;
	float m_58;
	float m_5c;
	float m_60;
	float m_64;
	float m_68;
};

Rva00435A40Sink::Rva00435A40Sink(GameFont *font, float width, float height,
	Int scaledWidth, Int value60, Int value58, Int value64) :
	m_00(0),
	m_04(font),
	m_08(),
	m_14(4),
	m_18(value58),
	m_1c(0),
	m_20(scaledWidth),
	m_24(value60),
	m_28(0),
	m_2c(value64),
	m_30(0),
	m_34(0),
	m_38(0),
	m_3c(0),
	m_40(0),
	m_44(0),
	m_48(0.0f),
	m_4c(0.0f),
	m_50(0.0f),
	m_54(0.0f),
	m_58(0.0f),
	m_5c(0.0f),
	m_60(0.0f),
	m_64(0.0f),
	m_68(0.0f)
{
	m_34 = new DisplayString *[m_24];
	m_38 = new Int[m_24];

	for (Int i = 0; i < m_24; ++i)
	{
		m_34[i] = Rva0048EC80TheManager->newDisplayString();
		m_34[i]->setFont(m_04);
	}

	m_34[0]->setText(UnicodeString(BFMEEmptyString));
	Int textWidth;
	Int textHeight;
	m_34[0]->getSize(&textHeight, &textWidth);

	m_4c = width;
	m_48 = (float)textWidth * 0.06666667f;
	Int rowWidth = (m_24 - 1) * textWidth;
	float rowBottom = height - (float)rowWidth;
	m_58 = height;
	m_50 = rowBottom;
	m_54 = (float)m_20 + width;
	m_30 = textWidth;
	Int halfTextWidth = textWidth >> 1;
	float widthWithHalf = width + (float)halfTextWidth;
	m_5c = widthWithHalf;
	m_60 = rowBottom + (float)halfTextWidth;
	Int earlierRowWidth = (m_24 - 2) * textWidth;
	m_64 = (float)m_20 - (float)textWidth + widthWithHalf;
	m_68 = (float)earlierRowWidth + m_60;

	Gen_t_00435350_m4pod entry;
	entry.m_data = this;
	((_STL::vector<Gen_t_00435350_m4pod> *)&g_bfmeBegKA)->push_back(entry);

	m_00 = Rva0048EC80TheManager->newDisplayString();
	m_00->setFont(font);
}
