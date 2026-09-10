// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Clean C++ recovery of ScriptActions::doNamedEmoticon.
// Retail boundary: 0x002F04F0, 66 bytes.
// Identity: executeAction's NAMED_SET_EMOTICON arm dispatches this exact
// signature.  Retail calls ScriptEngine::getUnitNamed at +0x68, Object's
// getDrawable at +0x28, and the named Drawable::setEmoticon ILT.

typedef float Real;
typedef int Int;

class AsciiString
{
};

class Drawable
{
public:
	void setEmoticon(const AsciiString &, Int);
};

class Object
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual Drawable *getDrawable() = 0;
};

class ScriptEngine
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &) = 0;
};

// These are the retail VAs corresponding to the proven symbols
// TheScriptEngine (RVA 0x00EF076C) and g_bfmeK1266C (RVA 0x00C75344).
#define TheScriptEngine (*(ScriptEngine **)0x012F076C)
#define g_bfmeK1266C (*(float *)0x01075344)

class ScriptActions
{
protected:
	void doNamedEmoticon(const AsciiString &, const AsciiString &, Real);
};

void ScriptActions::doNamedEmoticon(const AsciiString &unitName,
	const AsciiString &emoticonName, Real duration)
{
	Object *obj = TheScriptEngine->getUnitNamed(unitName);
	if (obj)
	{
		Drawable *draw = obj->getDrawable();
		if (draw)
		{
			Int frames = (Int)(duration * g_bfmeK1266C);
			draw->setEmoticon(emoticonName, frames);
		}
	}
}
