// ?bfmeApplyIndicatorColor@Drawable@@QAEXI@Z
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: standalone conversion, TU-scoped Drawable field/vtable shim.
// Guarded by a per-instance flag at +0x31a; skips the KindOf gate entirely
// when TheGameLogic reports inactive, otherwise requires a bound Object
// that isAnyKindOf(bits 119, 179); on pass, loops the module list at +0x150
// pushing the colour through ObjectDrawInterface::replaceIndicatorColor,
// matching Zero Hour's Drawable::setIndicatorColor loop shape (vtable
// slots +0x9c getObjectDrawInterface / +0x74 replaceIndicatorColor).

struct Rva00367E30Logic;
extern Rva00367E30Logic *TheBfmeGameLogic;

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
	virtual void replaceIndicatorColor(unsigned int color); // vtable +0x74
};

class Drawable
{
public:
	void bfmeApplyIndicatorColor(unsigned int color);

	unsigned char m_pad_000[0xfc];
	Thing *m_object;
	unsigned char m_pad_100[0x150 - 0x100];
	BfmeDrawModuleD **m_modules;
	unsigned char m_pad_154[0x31a - 0x154];
	bool m_indicatorEnabled;
};

// ?bfmeApplyIndicatorColor@Drawable@@QAEXI@Z
void Drawable::bfmeApplyIndicatorColor(unsigned int color)
{
	if (!m_indicatorEnabled)
		return;

	Thing *thing = m_object;

	if (reinterpret_cast<BfmeObserverYU *>(TheBfmeGameLogic)->bfmeActiveYU())
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
			di->replaceIndicatorColor(color);
	}
}
