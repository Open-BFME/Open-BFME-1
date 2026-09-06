// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD

typedef bool Bool;

class Rva00249310Object;

class Rva00249310Result
{
};

class Rva00249310Contain
{
public:
	virtual void unused00(void) = 0;
	virtual void unused01(void) = 0;
	virtual void unused02(void) = 0;
	virtual void unused03(void) = 0;
	virtual void unused04(void) = 0;
	virtual void unused05(void) = 0;
	virtual void unused06(void) = 0;
	virtual void unused07(void) = 0;
	virtual void unused08(void) = 0;
	virtual void unused09(void) = 0;
	virtual void unused10(void) = 0;
	virtual void unused11(void) = 0;
	virtual void unused12(void) = 0;
	virtual void unused13(void) = 0;
	virtual void unused14(void) = 0;
	virtual void unused15(void) = 0;
	virtual void unused16(void) = 0;
	virtual void unused17(void) = 0;
	virtual void unused18(void) = 0;
	virtual void unused19(void) = 0;
	virtual void unused20(void) = 0;
	virtual void unused21(void) = 0;
	virtual void unused22(void) = 0;
	virtual void unused23(void) = 0;
	virtual void unused24(void) = 0;
	virtual void unused25(void) = 0;
	virtual Rva00249310Result *getResult(void) = 0;
};

class Rva00249310Object
{
public:
	char m_head[0x94];
	unsigned char m_status;
	char m_pad95[0x1fc - 0x95];
	Rva00249310Contain *m_contain;
};

class Rva00249310Owner
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual Rva00249310Result *slot26(void) = 0;
	virtual int slot27(Rva00249310Object *object) = 0;
	virtual Bool slot28(Rva00249310Object *object) = 0;

	Bool preflight(Rva00249310Object *object, Bool mode);
};

#pragma comment(linker, "/alternatename:?preflight@Rva00249310Owner@@QAE_NPAVRva00249310Object@@_N@Z=?j_0002c836@@YAXXZ")

class Rva00249310Interface
{
public:
	Bool check(Rva00249310Object *object, Bool mode);
};

Bool Rva00249310Interface::check(Rva00249310Object *object, Bool mode)
{
	Rva00249310Owner *owner = (Rva00249310Owner *)((char *)this - 0x20);
	if (!owner->preflight(object, mode))
		return false;

	Rva00249310Contain *contain = object->m_contain;
	if (contain != 0)
	{
		Rva00249310Result *result = contain->getResult();
		if (result != 0)
		{
			if (mode != true)
				return true;
			return owner->slot28(object);
		}
	}

	if ((object->m_status & 0x20) != 0)
	{
		return owner->slot27(object) != 0;
	}

	return owner->slot28(object);
}
