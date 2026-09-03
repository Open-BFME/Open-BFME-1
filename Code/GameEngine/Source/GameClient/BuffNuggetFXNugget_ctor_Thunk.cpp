// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction of the BFME BuffNugget FX constructor.
// FieldParse at 0x010F2980 names BuffType, IsComplexBuff, six template
// strings, BuffLifeTime, Extrusion and Color.  The 12-byte tail at +0xE8
// is the same zero-then-range-assign shape as Made001E5AF0Member.

typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;

template <class T>
class StringBase
{
	friend class AsciiString;
	StringBase(const T *s);
	~StringBase();
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	// Inline forward so the this-pointer is computed before the literal is
	// pushed -- retail's six template strings are `lea ecx / push / call`.
	AsciiString(const char *s)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(s);
	}
	~AsciiString();

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXNugget
{
public:
	FXNugget();
	virtual ~FXNugget();

protected:
	int m_nuggetType;

private:
	unsigned char m_bfmeBaseData[0xAC];
};

class BuffNuggetFXNuggetMember
{
public:
	BuffNuggetFXNuggetMember()
	{
		m_start = 0;
		m_finish = 0;
		m_end = 0;
	}
	~BuffNuggetFXNuggetMember();
	void assign(void *first, void *last);

	void *volatile m_start;
	void *volatile m_finish;
	void *m_end;
};

class BuffNuggetFXNugget : public FXNugget
{
public:
	BuffNuggetFXNugget();
	virtual ~BuffNuggetFXNugget();

private:
	int m_buffType;
	Bool m_isComplexBuff;
	unsigned char m_padB9[3];
	UnsignedInt m_buffLifeTime;
	AsciiString m_buffThingTemplate;
	AsciiString m_buffOrcTemplate;
	AsciiString m_buffInfantryTemplate;
	AsciiString m_buffCavalryTemplate;
	AsciiString m_buffTrollTemplate;
	AsciiString m_buffMumakilTemplate;
	Real m_extrusion;
	RGBColor m_color;
	BuffNuggetFXNuggetMember m_member;
};

BuffNuggetFXNugget::BuffNuggetFXNugget() :
	m_buffType(0),
	m_isComplexBuff(false),
	m_buffLifeTime(0),
	m_buffThingTemplate("INVALID_THING"),
	m_buffOrcTemplate("INVALID_THING"),
	m_buffInfantryTemplate("INVALID_THING"),
	m_buffCavalryTemplate("INVALID_THING"),
	m_buffTrollTemplate("INVALID_THING"),
	m_buffMumakilTemplate("INVALID_THING"),
	m_extrusion(1.0f)
{
	m_color.red = 0.2f;
	m_color.green = 0.4f;
	m_color.blue = 1.0f;
	BuffNuggetFXNuggetMember *p = &m_member;
	void *last = p->m_finish;
	void *first = p->m_start;
	p->assign(first, last);
}
