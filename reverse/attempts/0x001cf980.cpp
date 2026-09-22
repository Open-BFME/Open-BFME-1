// ?queryAt001CF980@Object@@QAEPAVRva001CF980Result@@XZ
// partial score=0.95 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Ireference/shims/bfmeobject /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// Retail RVA 0x001CF980..0x001CF9D2 (82 bytes): Object::queryAt001CF980.
// Name and signature come from the matched caller at 0x0025AEE0
// (DominateEnemySpecialPower_slot15.cpp) and its reverse/symbols.csv pin.
// Selects this when template flag 0x1000 is set, else Object+0x214 when it is
// KINDOF 0x6C, then tail-calls slot 0x68 of the selected m_contain.
// The two inline helpers are what move the selected object into EAX and the
// contain pointer into ECX; a single flat body keeps the object in ESI.

enum KindOfType
{
	KINDOF_0x6C = 0x6C
};

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;
	void *m_head;
	Overridable *m_nextOverride;
};

class Rva001CF980Thing : public Overridable
{
public:
	char m_gap[0xD4 - 8];
	unsigned m_flags_d4;
};

class Rva001CF980Result;

class Rva001CF980Iface
{
public:
	virtual void *slot00();
	virtual void *slot01();
	virtual void *slot02();
	virtual void *slot03();
	virtual void *slot04();
	virtual void *slot05();
	virtual void *slot06();
	virtual void *slot07();
	virtual void *slot08();
	virtual void *slot09();
	virtual void *slot10();
	virtual void *slot11();
	virtual void *slot12();
	virtual void *slot13();
	virtual void *slot14();
	virtual void *slot15();
	virtual void *slot16();
	virtual void *slot17();
	virtual void *slot18();
	virtual void *slot19();
	virtual void *slot20();
	virtual void *slot21();
	virtual void *slot22();
	virtual void *slot23();
	virtual void *slot24();
	virtual void *slot25();
	virtual Rva001CF980Result *slot26();
};

class Thing
{
public:
	bool isKindOf(KindOfType t) const;

private:
	virtual ~Thing();
	Rva001CF980Thing *m_template;
	friend class Object;
};

class Object : public Thing
{
public:
	Rva001CF980Result *queryAt001CF980();

private:
	Object *selectedObjectAt001CF980();
	Rva001CF980Result *containSlot68At001CF980();

	char m_gap_1fc[0x1FC - 8];
	Rva001CF980Iface *m_contain;
	char m_gap_214[0x214 - 0x200];
	Object *m_other;
};

inline Object *Object::selectedObjectAt001CF980()
{
	Rva001CF980Thing *thing = m_template;
	if (thing)
	{
		if (thing->m_nextOverride)
			thing = (Rva001CF980Thing *)thing->m_nextOverride->getFinalOverride();
	}
	if (thing->m_flags_d4 & 0x1000)
		return this;
	Object *obj = m_other;
	if (obj && obj->isKindOf(KINDOF_0x6C))
		return obj;
	return 0;
}

inline Rva001CF980Result *Object::containSlot68At001CF980()
{
	Rva001CF980Iface *contain = m_contain;
	if (contain)
		return contain->slot26();
	return 0;
}

Rva001CF980Result *Object::queryAt001CF980()
{
	Object *obj = selectedObjectAt001CF980();
	if (obj)
		return obj->containSlot68At001CF980();
	return 0;
}
