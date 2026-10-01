extern const char g_bfmeEmptyAE[];

struct BfmeStrAE
{
	char *m_bfmeDataAE;
};

class BfmeThingAE
{
public:
	unsigned char m_bfmeHeadAE[4];
	int m_bfmeKeyAE;
};

class BfmeEntryAE
{
public:
	virtual void bfmeE00AE();
	virtual void bfmeE01AE();
	virtual void bfmeE02AE();
	virtual void bfmeE03AE();
	virtual void bfmeE04AE();
	virtual void bfmeE05AE();
	virtual void bfmeE06AE();
	virtual void bfmeE07AE();
	virtual void bfmeE08AE();
	virtual void bfmeE09AE();
	virtual void bfmeE10AE();
	virtual void bfmeE11AE();
	virtual void bfmeE12AE();
	virtual void bfmeE13AE();
	virtual void bfmeShowAE(bool on);

	BfmeThingAE *m_bfmeThingAE;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
enum NameKeyType { };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *text);
};

extern NameKeyGenerator *TheBfmeGenAE;

class BfmeOwnerAE
{
public:
	char bfmeSetAE(BfmeStrAE *name, char on);

	unsigned char m_bfmeHeadAE[0x150];
	BfmeEntryAE **m_bfmeListAE;
};

char BfmeOwnerAE::bfmeSetAE(BfmeStrAE *name, char on)
{
	const char *text = name->m_bfmeDataAE != 0 ? name->m_bfmeDataAE + 8 : g_bfmeEmptyAE;
	int key = (int)TheBfmeGenAE->nameToKey(text);

	for (BfmeEntryAE **p = m_bfmeListAE; *p != 0; p++)
	{
		BfmeEntryAE *entry = *p;
		BfmeThingAE *thing = entry->m_bfmeThingAE;

		if (key == thing->m_bfmeKeyAE)
		{
			entry->bfmeShowAE(on == 0);
			return 1;
		}
	}

	return 0;
}
