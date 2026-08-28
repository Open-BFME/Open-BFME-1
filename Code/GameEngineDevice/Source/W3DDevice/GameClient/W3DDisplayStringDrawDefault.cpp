// cl: /DNDEBUG /DWIN32 /MD /EHsc
// readable body of ?draw@W3DDisplayString@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayString.cpp

typedef int Int;
typedef int Color;

// BFME added the two-argument convenience overload at vtable slot +0x34;
// the four-argument draw it delegates to is the next slot at +0x38.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplayString.h
class W3DDisplayString
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
	virtual void draw(Int x, Int y, Color color, Color dropColor);
	virtual void draw(Int x, Int y);
};

void W3DDisplayString::draw(Int x, Int y)
{
	draw(x, y, 0, 0);
}
