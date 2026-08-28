// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?doNamedFlash@ScriptActions@@IAEXABVAsciiString@@HPBURGBColor@@@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// Lift the ScriptActions::doNamedFlash naked dump to clean C++.
//
// Zero Hour's ScriptActions.cpp body. The two named constants are the only
// thing retail changes, and it does not name them: the seconds are multiplied
// by 5 (a `lea ecx,[eax+eax*4]`) and the product divided by 15 (magic
// 0x88888889 with add-back and sar 3, which brute-forces to exactly one
// divisor). MSVC does not algebraically fold 5*t/15 into t/3, so the two steps
// stay separate exactly as the two constants in the source are.
//
// Only the two virtual slots are reconstructed -- getUnitNamed at vtable +0x68
// and getDrawable at +0x28 -- and the entries ahead of them are declared to
// place them and never defined or called.
//
// Retail pins the layout: the flash count is at drawable+0x160 and the flash
// colour at +0x164, and the colour comes from the object when the caller passes
// no RGBColor.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt Color;

class AsciiString;
class Drawable;

// The bytes prove the product and the divisor, not which named constant is
// which; ZH spells them LOGICFRAMES_PER_SECOND and DRAWABLE_FRAMES_PER_FLASH.
enum
{
	LOGICFRAMES_PER_SECOND = 5,
	DRAWABLE_FRAMES_PER_FLASH = 15
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct RGBColor
{
	Color getAsInt(void) const;							///< ILT thunk at 0x0002D989
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();

	virtual Drawable *getDrawable(void) const;			///< vtable +0x28

	Color getIndicatorColor(void) const;				///< ILT thunk at 0x00009CA0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();

	virtual Object *getUnitNamed(const AsciiString &name);	///< vtable +0x68
};

extern ScriptEngine *TheScriptEngine;					///< retail [0x012F076C]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void setFlashCount(Int count) { m_flashCount = count; }
	void setFlashColor(Color color) { m_flashColor = color; }

private:
	unsigned char m_unreconstructed_00[0x160];
	Int m_flashCount;									///< retail this+0x160
	Color m_flashColor;									///< retail this+0x164
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doNamedFlash(const AsciiString &unitName, Int timeInSeconds, const RGBColor *color);
};

// ?doNamedFlash@ScriptActions@@IAEXABVAsciiString@@HPBURGBColor@@@Z
void ScriptActions::doNamedFlash(const AsciiString &unitName, Int timeInSeconds, const RGBColor *color)
{
	//sanity
	Object *obj = TheScriptEngine->getUnitNamed( unitName );
	if ( !obj )
	{
		return;
	}
	Drawable *drawable = obj->getDrawable();
	if( !drawable )
	{
		return;
	}

	if( timeInSeconds > 0 )
	{
		Int frames = LOGICFRAMES_PER_SECOND * timeInSeconds;
		Int count = frames / DRAWABLE_FRAMES_PER_FLASH;
		Color flashy = (color == 0) ? obj->getIndicatorColor() : color->getAsInt();
		drawable->setFlashColor( flashy );
		drawable->setFlashCount( count );
		return;
	}
}
