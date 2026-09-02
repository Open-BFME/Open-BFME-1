// cl: /O2 /Ob0

struct Rva002EDF10View
{
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void pad35();
	virtual void pad36();
	virtual void pad37();
	virtual void pad38();
	virtual void pad39();
	virtual void pad40();
	virtual void pad41();
	virtual void pad42();
	virtual void pad43();
	virtual void pad44();
	virtual void pad45();
	virtual void pad46();
	virtual void pad47();
	virtual void pad48();
	virtual void pad49();
	virtual void meth(float a, int ms, int flag, float easeIn, float easeOut);
};

class View;
extern View *TheTacticalView;

void __stdcall rva002EDF10(float a, float sec, float easeIn, float easeOut)
{
	((Rva002EDF10View *)TheTacticalView)->meth(a, (int)(sec * 1000.0f), 0, easeIn * 1000.0f, easeOut * 1000.0f);
}

void __stdcall rva002EE000(float a, float sec, float easeIn, float easeOut)
{
	((Rva002EDF10View *)TheTacticalView)->meth(a, (int)(sec * 1000.0f), 1, easeIn * 1000.0f, easeOut * 1000.0f);
}
