// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/objectdlink
// Open-BFME5: clean C++ conversion of ScriptActions::doTeamFlash.
//
// The team walk uses the BFME Object DLINK pointer-to-member shape from
// ObjectDlinkPmf.h.  The retail body is the team analogue of doNamedFlash:
// seconds are scaled by five and divided by fifteen, then each drawable gets
// the selected colour and flash count.

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef UnsignedInt Color;

enum
{
	LOGICFRAMES_PER_SECOND = 5,
	DRAWABLE_FRAMES_PER_FLASH = 15
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct RGBColor
{
	Real red, green, blue;

	inline Int getAsInt(void) const
	{
		return
			((Int)(red * 255.0) << 16) |
			((Int)(green * 255.0) << 8) |
			((Int)(blue * 255.0) << 0);
	}
};

class AsciiString
{
	char *m_data;
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
	~BfmeStringArgBase();
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}
	~BfmeAsciiStringArg();

private:
	char *m_text;
};

class Drawable
{
public:
	void setFlashCount(Int count) { m_flashCount = count; }
	void setFlashColor(Color color) { m_flashColor = color; }

private:
	unsigned char m_unreconstructed_00[0x160];
	Int m_flashCount;
	Color m_flashColor;
};

class Object;

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[4];
};

class BfmeObjectVtbl
{
public:
	virtual void unused00(void);
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x64];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	virtual void unused01(void);
	virtual void unused02(void);
	virtual void unused03(void);
	virtual void unused04(void);
	virtual void unused05(void);
	virtual void unused06(void);
	virtual void unused07(void);
	virtual void unused08(void);
	virtual void unused09(void);
	virtual Drawable *getDrawable(void) const;

	Color getIndicatorColor(void) const;
};

#define callMemberFunction(object,ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS * (OBJCLASS::*GetNextFunc)(void) const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance(void)
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done(void) const { return m_cur == 0; }
	OBJCLASS *cur(void) const { return m_cur; }
};

class Team
{
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

public:
	Bool hasAnyObjects(Bool includeDead) const;

	DLINK_ITERATOR<Object> iterate_TeamMemberList(void) const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

class ScriptEngine
{
public:
	virtual void unused00(void);
	virtual void unused01(void);
	virtual void unused02(void);
	virtual void unused03(void);
	virtual void unused04(void);
	virtual void unused05(void);
	virtual void unused06(void);
	virtual void unused07(void);
	virtual void unused08(void);
	virtual void unused09(void);
	virtual void unused10(void);
	virtual void unused11(void);
	virtual void unused12(void);
	virtual void unused13(void);
	virtual void unused14(void);
	virtual void unused15(void);
	virtual void unused16(void);
	virtual Team *getTeamNamed(BfmeAsciiStringArg, Bool);
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamFlash(const AsciiString &, Int, const RGBColor *);
};

// ?doTeamFlash@ScriptActions@@IAEXABVAsciiString@@HPBURGBColor@@@Z
void ScriptActions::doTeamFlash(const AsciiString &teamName, Int timeInSeconds,
	const RGBColor *color)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (team == 0 || !team->hasAnyObjects(false))
		return;

	DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();

	while (!iter.done()) {
		Object *nextObj = iter.cur();
		Object *obj = nextObj;
		if (!obj) {
			break;
		}

		iter.advance();
		Drawable *draw = obj->getDrawable();
		if (!draw) {
			break;
		}

		Int frames = LOGICFRAMES_PER_SECOND * timeInSeconds;
		Int count = frames / DRAWABLE_FRAMES_PER_FLASH;
		Color flashy = (color == 0) ? obj->getIndicatorColor() : color->getAsInt();
		draw->setFlashColor(flashy);
		draw->setFlashCount(count);
	}
}
