// ?method@Rva00418200Owner@@QAEXI@Z
// cl: /DNDEBUG /MD /EHsc
// Native126B address-derived provider. Argument is forwarded as one word;
// SubObjectsUpgrade passes its ExcludeSubobjects vector address, not color.
// Identity evidence: targets/game/reverse/identity_evidence/00418200-exclusion-argument.md

// Retail global at 0x012F0898 is GameLogic *TheGameLogic (defined once in
// game_logic.cpp); this TU only reads a member through a local view type, so
// cast at the use and keep the canonical spelling for the linker.
class GameLogic;
extern GameLogic *TheGameLogic;

class BfmeObserverYU
{
public:
	bool bfmeActiveYU();
};

struct KindOfMask
{
	unsigned int words[6];

	KindOfMask(int, int idx1, int idx2)
	{
		for (int i = 0; i < 6; ++i)
			words[i] = 0;
		words[idx1 >> 5] |= (1u << (idx1 & 31));
		words[idx2 >> 5] |= (1u << (idx2 & 31));
	}
};

class Thing
{
public:
	bool isAnyKindOf(const KindOfMask &mask) const;
};

class BfmeDrawModuleD
{
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
public:
	virtual void *getObjectDrawInterface(); // vtable +0x9c
};

class BfmeObjectDrawInterfaceD
{
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28();
public:
	virtual void slot29(unsigned int argument); // vtable +0x74
};

class Rva00418200Owner
{
public:
	void method(unsigned int argument);

	unsigned char m_pad_000[0xfc];
	Thing *m_object;
	unsigned char m_pad_100[0x150 - 0x100];
	BfmeDrawModuleD **m_modules;
	unsigned char m_pad_154[0x31a - 0x154];
	bool field031a;
};

// ?method@Rva00418200Owner@@QAEXI@Z
void Rva00418200Owner::method(unsigned int argument)
{
	if (!field031a)
		return;

	Thing *thing = m_object;

	if (reinterpret_cast<BfmeObserverYU *>(TheGameLogic)->bfmeActiveYU())
	{
		if (!thing)
			return;

		if (!thing->isAnyKindOf(KindOfMask(0, 119, 179)))
			return;
	}

	for (BfmeDrawModuleD **dm = m_modules; *dm; ++dm)
	{
		BfmeObjectDrawInterfaceD *di =
			reinterpret_cast<BfmeObjectDrawInterfaceD *>((*dm)->getObjectDrawInterface());
		if (di)
			di->slot29(argument);
	}
}
