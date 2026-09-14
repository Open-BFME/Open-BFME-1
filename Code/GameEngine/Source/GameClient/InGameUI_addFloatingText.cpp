// ?addFloatingText@InGameUI@@UAEXABVUnicodeString@@PBUCoord3D@@H@Z
// BFME's InGameUI moved the floating-text list to +0x1298 and stores its
// timeout as a Real at +0x129c.  Keep this retail view local to the body.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef int Color;

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	void set(const StringBase<T> &other);

private:
	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}

	UnicodeString &operator=(const UnicodeString &other)
	{
		set(other);
		return *this;
	}
};

class DisplayString
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text);
};

class FloatingTextData
{
public:
	FloatingTextData();
	virtual ~FloatingTextData();

	Color m_color;
	UnicodeString m_text;
	DisplayString *m_dString;
	Real m_x;
	Real m_y;
	Real m_z;
	Int m_frameTimeOut;
	Int m_frameCount;
};

struct Rva004435A0FloatingTextNode
{
	Rva004435A0FloatingTextNode *m_next;
	Rva004435A0FloatingTextNode *m_previous;
	FloatingTextData *m_value;
};

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate(UnsignedInt size);
};
}

inline void *operator new(UnsignedInt, void *where)
{
	return where;
}

class Rva004435A0FloatingTextList
{
public:
	void push_front(FloatingTextData *value)
	{
		Rva004435A0FloatingTextNode *position = m_node->m_next;
		Rva004435A0FloatingTextNode *node =
			(Rva004435A0FloatingTextNode *)_STL::__new_alloc::allocate(0xc);
		new (&node->m_value) FloatingTextData *(value);
		Rva004435A0FloatingTextNode *previous = position->m_previous;
		node->m_next = position;
		node->m_previous = previous;
		previous->m_next = node;
		position->m_previous = node;
	}

private:
	Rva004435A0FloatingTextNode *m_node;
};

class Rva004435A0ClientRoot4120
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual UnsignedInt getFrame();
};

class Rva004435A0BfmeGameLogic
{
public:
	UnsignedByte getDrawIconUI() const { return m_drawIconUI; }

	private:
	UnsignedByte m_beforeDrawIconUI[0x92];

	public:
	UnsignedByte m_drawIconUI;
};

#define TheBfmeGameLogic (*(Rva004435A0BfmeGameLogic **)0x012F0898)
#define TheGameClient (*(Rva004435A0ClientRoot4120 **)0x012F1464)
#define BfmeFloatingTextScale (*(const Real *)0x010F48DC)

extern Real BfmeZeroRange;
extern Real g_bfmeUint32Scale;

struct Rva004435A0Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Rva004435A0InGameUI
{
public:
	virtual void addFloatingText(const UnicodeString &text,
		const Rva004435A0Coord3D *pos, Color color);

private:
	UnsignedByte m_beforeFloatingTextList[0x1294];
	Rva004435A0FloatingTextList m_floatingTextList;
	Real m_floatingTextTimeOut;
};

// ?addFloatingText@InGameUI@@UAEXABVUnicodeString@@PBUCoord3D@@H@Z
void Rva004435A0InGameUI::addFloatingText(const UnicodeString &text,
	const Rva004435A0Coord3D *pos, Color color)
{
	if (TheBfmeGameLogic->getDrawIconUI())
	{
		FloatingTextData *newFTD = new FloatingTextData;
		newFTD->m_frameCount = 0;
		newFTD->m_color = color;
		newFTD->m_x = pos->x;
		newFTD->m_z = pos->z;
		newFTD->m_y = pos->y;
		newFTD->m_text = text;
		newFTD->m_dString->setText(text);

		if (m_floatingTextTimeOut <= 0.0f)
			newFTD->m_frameTimeOut = TheGameClient->getFrame() + 10;
		else
			newFTD->m_frameTimeOut = (Int)(TheGameClient->getFrame()
				+ m_floatingTextTimeOut * BfmeFloatingTextScale);

		m_floatingTextList.push_front(newFTD);
	}
}
