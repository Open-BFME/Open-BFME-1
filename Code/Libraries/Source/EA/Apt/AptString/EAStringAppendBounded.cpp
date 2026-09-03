// ?bfmeAppendVKG@BfmeBufVKG@@QAEPAV1@PBDI@Z
// cl: /O2 /DNDEBUG /MD

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

struct BfmeStringDataVKG
{
	unsigned short m_refCount;
	unsigned short m_size;
	unsigned short m_maxSize;
	unsigned short m_hash;
};

class BfmeStrVKJ
{
	protected:
	BfmeStringDataVKG *m_data;

	public:
	void bfmeReserveVKJ(unsigned int reserve, int offset,
		unsigned int size, int pushZero, unsigned int internalSize);
};

class BfmeBufVKG : public BfmeStrVKJ
{
public:
	BfmeBufVKG *bfmeAppendVKG(const char *source, unsigned int limit);
};

BfmeBufVKG *BfmeBufVKG::bfmeAppendVKG(const char *source, unsigned int limit)
{
	unsigned int count = 0;
	const char *scan = source;
	if (limit > 0)
	{
		while (*scan++ != 0 && ++count < limit)
			;
	}
	if (count != 0)
	{
		unsigned int oldSize = m_data->m_size;
		unsigned int newSize = oldSize + count;
		bfmeReserveVKJ(newSize, 0, oldSize, 1, newSize);
		memcpy(reinterpret_cast<char *>(m_data) + 8 + oldSize,
			source, count);
	}
	return this;
}
