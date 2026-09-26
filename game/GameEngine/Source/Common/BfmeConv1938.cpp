class UnicodeString;

struct BfmeBufDF
{
	unsigned char m_bfmeHeadDF[4];
	unsigned short m_bfmeLenDF;
};

class UnicodeString
{
public:
	void set(const UnicodeString &other);

	~UnicodeString() { releaseBufferDF(); }

	void releaseBufferDF();

	BfmeBufDF *m_data;
};

class View
{
public:
	virtual void bfmeSlot000DF();
	virtual void bfmeSlot001DF();
	virtual void bfmeSlot002DF();
	virtual void bfmeSlot003DF();
	virtual void bfmeSlot004DF();
	virtual void bfmeSlot005DF();
	virtual void bfmeSlot006DF();
	virtual void bfmeSlot007DF();
	virtual void bfmeSlot008DF();
	virtual void bfmeSlot009DF();
	virtual void bfmeSlot010DF();
	virtual void bfmeSlot011DF();
	virtual void bfmeSlot012DF();
	virtual void bfmeSlot013DF();
	virtual void bfmeSlot014DF();
	virtual void bfmeSlot015DF();
	virtual void bfmeSlot016DF();
	virtual void bfmeSlot017DF();
	virtual void bfmeSlot018DF();
	virtual void bfmeSlot019DF();
	virtual void bfmeSlot020DF();
	virtual void bfmeSlot021DF();
	virtual void bfmeSlot022DF();
	virtual void bfmeSlot023DF();
	virtual void bfmeSlot024DF();
	virtual void bfmeSlot025DF();
	virtual void bfmeSlot026DF();
	virtual void bfmeSlot027DF();
	virtual void bfmeSlot028DF();
	virtual void bfmeSlot029DF();
	virtual void bfmeSlot030DF();
	virtual void bfmeSlot031DF();
	virtual void bfmeSlot032DF();
	virtual void bfmeSlot033DF();
	virtual void bfmeSlot034DF();
	virtual void bfmeSlot035DF();
	virtual void bfmeSlot036DF();
	virtual void bfmeSlot037DF();
	virtual void bfmeSlot038DF();
	virtual void bfmeSlot039DF();
	virtual void bfmeSlot040DF();
	virtual void bfmeSlot041DF();
	virtual void bfmeSlot042DF();
	virtual void bfmeSlot043DF();
	virtual void bfmeSlot044DF();
	virtual void bfmeSlot045DF();
	virtual void bfmeSlot046DF();
	virtual void bfmeSlot047DF();
	virtual void bfmeSlot048DF();
	virtual void bfmeSlot049DF();
	virtual void bfmeSlot050DF();
	virtual void bfmeSlot051DF();
	virtual void bfmeSlot052DF();
	virtual void bfmeSlot053DF();
	virtual void bfmeSlot054DF();
	virtual void bfmeSlot055DF();
	virtual void bfmeSlot056DF();
	virtual void bfmeSlot057DF();
	virtual void bfmeSlot058DF();
	virtual void bfmeSlot059DF();
	virtual void bfmeSlot060DF();
	virtual void bfmeSlot061DF();
	virtual void bfmeSlot062DF();
	virtual void bfmeSlot063DF();
	virtual void bfmeSlot064DF();
	virtual void bfmeSlot065DF();
	virtual void bfmeSlot066DF();
	virtual void bfmeSlot067DF();
	virtual void bfmeSlot068DF();
	virtual void bfmeSlot069DF();
	virtual void bfmeSlot070DF();
	virtual void bfmeSlot071DF();
	virtual void bfmeSlot072DF();
	virtual void bfmeSlot073DF();
	virtual void bfmeSlot074DF();
	virtual void bfmeSlot075DF();
	virtual void bfmeSlot076DF();
	virtual void bfmeSlot077DF();
	virtual void bfmeSlot078DF();
	virtual void bfmeSlot079DF();
	virtual void bfmeSlot080DF();
	virtual void bfmeSlot081DF();
	virtual void bfmeSlot082DF();
	virtual void bfmeSlot083DF();
	virtual void bfmeSlot084DF();
	virtual void bfmeSlot085DF();
	virtual void bfmeSlot086DF();
	virtual void bfmeSlot087DF();
	virtual void bfmeSlot088DF();
	virtual void bfmeSlot089DF();
	virtual void bfmeSlot090DF();
	virtual void bfmeSlot091DF();
	virtual void bfmeSlot092DF();
	virtual void bfmeSlot093DF();
	virtual void bfmeSlot094DF();
	virtual void bfmeSlot095DF();
	virtual void bfmeSlot096DF();
	virtual void bfmeSlot097DF();
	virtual void bfmeSlot098DF();
	virtual void bfmeSlot099DF();
	virtual void bfmeSlot100DF();
	virtual void bfmeSlot101DF();
	virtual void bfmeSlot102DF();
	virtual void bfmeSlot103DF();
	virtual void bfmeSlot104DF();
	virtual void bfmeSlot105DF();
	virtual void bfmeSlot106DF();
	virtual void bfmeSlot107DF();
	virtual void bfmeSlot108DF();
	virtual void bfmeSlot109DF();
	virtual void bfmeSlot110DF();
	virtual void bfmeSlot111DF();
	virtual void bfmeSlot112DF();
	virtual void bfmeSlot113DF();
	virtual void bfmeSlot114DF();
	virtual void bfmeSlot115DF();
	virtual void bfmeSlot116DF();
	virtual void bfmeSlot117DF();
	virtual void bfmeSlot118DF();
	virtual void bfmeSlot119DF();
	virtual void bfmeSlot120DF();
	virtual void bfmeSlot121DF();
	virtual void bfmeSlot122DF();
	virtual void bfmeSlot123DF();
	virtual void bfmeSlot124DF();
	virtual void bfmeSlot125DF();
	virtual void bfmeSlot126DF();
	virtual void bfmeSlot127DF();
	virtual void bfmeSlot128DF();
	virtual void bfmeSlot129DF();
	virtual void bfmeSlot130DF();
	virtual void bfmeSlot131DF();
	virtual void bfmeSlot132DF();
	virtual void bfmeSlot133DF();
	virtual void bfmeSlot134DF();
	virtual void bfmeSlot135DF();
	virtual void bfmeShowDF(UnicodeString *text);
	virtual void bfmeHideDF();
};

extern View *TheTacticalView;

class BfmeHostDF
{
public:
	void bfmeSetLabelDF(UnicodeString text);

	unsigned char m_bfmeHeadDF[0xb8];
	UnicodeString m_bfmeLabelDF;
};

void BfmeHostDF::bfmeSetLabelDF(UnicodeString text)
{
	UnicodeString *dst = &m_bfmeLabelDF;

	dst->set(text);

	if (dst->m_data != 0 && dst->m_data->m_bfmeLenDF != 0)
		TheTacticalView->bfmeShowDF(dst);
	else
		TheTacticalView->bfmeHideDF();
}
