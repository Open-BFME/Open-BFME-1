class BfmeCtxBS;

class BfmeInnerBS
{
public:
	BfmeCtxBS *bfmeGetBS(void);
};

class BfmeCtxBS
{
public:
	unsigned char m_bfmeHeadBS[4];
	BfmeInnerBS *m_bfmeInnerBS;
	unsigned char m_bfmeMidBS[0xc8];
	int m_bfmeFlagsBS;
};

class BfmeSrcBS
{
public:
	unsigned char m_bfmeHeadBS[4];
	BfmeCtxBS *m_bfmeCtxBS;
	unsigned char m_bfmeMidBS[0x70];
	int m_bfmeKeyBS;
};

class BfmeTgtBS
{
public:
	unsigned char m_bfmeHeadBS[0x74];
	int m_bfmeKeyBS;
};

class BfmeSlotBS
{
public:
	BfmeTgtBS *m_bfmeTgtBS;
	BfmeSrcBS *m_bfmeSrcBS;
};

int __cdecl bfmeBindBS(BfmeSrcBS *source, BfmeSlotBS *slot)
{
	if (source == 0)
		return 1;

	BfmeCtxBS *ctx = source->m_bfmeCtxBS;

	if (ctx && ctx->m_bfmeInnerBS)
		ctx = ctx->m_bfmeInnerBS->bfmeGetBS();

	if ((ctx->m_bfmeFlagsBS & 0x100) == 0)
		return 1;

	if (source->m_bfmeKeyBS == slot->m_bfmeTgtBS->m_bfmeKeyBS)
	{
		slot->m_bfmeSrcBS = source;

		return 0;
	}

	return 1;
}
