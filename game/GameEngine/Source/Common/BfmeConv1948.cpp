class HAnimClass;

HAnimClass *Get_HAnim(const char *name);

extern char g_bfmeEmptyERC[];

struct BfmeStrDataERC
{
	int m_bfmeRefERC;
	unsigned short m_bfmeLenERC;
	unsigned short m_bfmePadERC;
	char m_bfmeTextERC[1];
};

class BfmeStrERC
{
public:
	BfmeStrERC(const BfmeStrERC &other);

	~BfmeStrERC() { releaseBuffer(); }

	void bfmeConcatERC(const char *text, int length);

	const char *bfmeTextERC() const
	{
		return m_bfmeDataERC ? m_bfmeDataERC->m_bfmeTextERC : g_bfmeEmptyERC;
	}

	int bfmeLenERC() const
	{
		return m_bfmeDataERC ? m_bfmeDataERC->m_bfmeLenERC : 0;
	}

	BfmeStrDataERC *m_bfmeDataERC;

private:
	void releaseBuffer();
};

void __stdcall bfmeAnimERC(BfmeStrERC *name, void *owner, HAnimClass **out)
{
	if (owner == 0)
		return;

	BfmeStrERC full = *name;

	full.bfmeConcatERC(".", 1);
	full.bfmeConcatERC(name->bfmeTextERC(), name->bfmeLenERC());

	*out = Get_HAnim(full.bfmeTextERC());
}
