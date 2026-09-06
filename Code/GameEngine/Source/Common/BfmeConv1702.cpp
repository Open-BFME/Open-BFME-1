extern "C" int __cdecl TableLookup(void *table, void *key);

struct BfmeCtxFT
{
	unsigned char m_bfmeHeadFT[0x134];
	void *m_bfmeTableFT;
};

typedef void (__cdecl *BfmeFnFT)(void *first, void *key, BfmeCtxFT *ctx, void *extra);

struct BfmeEntryFT
{
	void *m_bfmeFirstFT;
	void *m_bfmeKeyFT;
	BfmeFnFT m_bfmeFnFT;
	void *m_bfmeExtraFT;
};

void __cdecl bfmeDispatchFT(BfmeCtxFT *ctx, BfmeEntryFT *entry)
{
	if (TableLookup(ctx->m_bfmeTableFT, entry->m_bfmeKeyFT) != 0)
		entry->m_bfmeFnFT(entry->m_bfmeFirstFT, entry->m_bfmeKeyFT, ctx,
			entry->m_bfmeExtraFT);
}
