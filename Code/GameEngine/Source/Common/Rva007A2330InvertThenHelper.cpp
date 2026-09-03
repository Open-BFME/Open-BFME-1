// cl: /EHs-c-
//
// thiscall with one stack argument: two vtable+0x50 calls on *arg, then
// ShaderClass::Invert_Backface_Culling(true) and (false) (0x00910DF0), a
// byte store to 0x012D6DFC, and the claimed helper at 0x007AA820 via ILT
// 0x000243B6.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/shader.h
class ShaderClass
{
public:
	static void Invert_Backface_Culling(bool onoff);
};

class Rva007A2330Target
{
public:
	virtual void slot00(); virtual void slot04();
	virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24();
	virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C();
	virtual void slot50();
};

extern char g_rva007A2330Flag;

class Rva007A2330
{
public:
	void apply(Rva007A2330Target **target);
	void helper(Rva007A2330Target **target);
};

void Rva007A2330::apply(Rva007A2330Target **target)
{
	(*target)->slot50();
	(*target)->slot50();
	ShaderClass::Invert_Backface_Culling(true);
	ShaderClass::Invert_Backface_Culling(false);
	g_rva007A2330Flag = 1;
	helper(target);
}
