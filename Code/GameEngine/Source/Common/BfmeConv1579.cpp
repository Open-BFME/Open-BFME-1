// Open-BFME5 conversions.

class BfmeStrVSH
{
public:
	void bfmeSetVSH(const char *text, int length);
	void bfmeAssignVSH(const BfmeStrVSH &other);
	char *m_bfme00;
};

template <typename T>
class StringBaseVSH
{
	friend class UnicodeString;

private:
	StringBaseVSH(const StringBaseVSH<T> &source);
	~StringBaseVSH();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBaseVSH<unsigned short>
{
public:
	UnicodeString(const UnicodeString &source)
		: StringBaseVSH<unsigned short>(source) {}
	~UnicodeString() {}
};

class GameWindow;

class BfmeSrcVSH
{
public:
	char m_bfmePad00[0x50];
	BfmeStrVSH m_bfme50;
};

class BfmeCfgVSH
{
public:
	void bfmeApplyVSH(BfmeSrcVSH *src);
	void bfmeStep1VSH(BfmeSrcVSH *src);
	void bfmeStep2VSH(BfmeSrcVSH *src);
	void bfmeStep3VSH(BfmeSrcVSH *src);
	void bfmeStep4VSH(BfmeSrcVSH *src);
	void bfmeStep5VSH(BfmeSrcVSH *src);
	BfmeStrVSH m_bfme00;
	char m_bfmePad04[0x0c];
	GameWindow *m_bfme10;
};

void GadgetListBoxReset(GameWindow *listBox);
int GadgetListBoxAddEntryText(GameWindow *listBox, UnicodeString text,
	int color, int row, int column, bool overwrite);

extern void j_000036bb(void);
typedef UnicodeString (__cdecl *BfmeMapTitleGetter)(void);


void BfmeCfgVSH::bfmeApplyVSH(BfmeSrcVSH *src)
{
	if (src != 0)
		m_bfme00.bfmeAssignVSH(src->m_bfme50);
	else
		m_bfme00.bfmeSetVSH("", 0);

	bfmeStep1VSH(src);
	bfmeStep2VSH(src);
	bfmeStep3VSH(src);
	bfmeStep4VSH(src);
	bfmeStep5VSH(src);
}

void BfmeCfgVSH::bfmeStep4VSH(BfmeSrcVSH *src)
{
	if (m_bfme10 != 0)
	{
		GadgetListBoxReset(m_bfme10);
		if (src != 0)
			GadgetListBoxAddEntryText(m_bfme10,
				((BfmeMapTitleGetter)j_000036bb)(), -1, -1, -1, true);
	}
}
