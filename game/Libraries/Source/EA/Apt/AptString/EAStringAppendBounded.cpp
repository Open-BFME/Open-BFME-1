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

// The reserve call retail makes here is EAStringC::ChangeBuffer at 0x0089E570
// (matched in EAStringCMid.cpp); only the layout matters to this TU.
class EAStringC
{
	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	void ChangeBuffer(unsigned int reserve, unsigned int offset,
		unsigned int copy, CBPushZero pushZero, unsigned int internalSize);

protected:
	BfmeStringDataVKG *m_data;

	friend class BfmeBufVKG;
};

class BfmeBufVKG : public EAStringC
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
		ChangeBuffer(newSize, 0, oldSize, EAStringC::CB_PUSH_ZERO, newSize);
		memcpy(reinterpret_cast<char *>(m_data) + 8 + oldSize,
			source, count);
	}
	return this;
}
