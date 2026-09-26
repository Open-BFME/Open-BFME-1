// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: MixFileInfoBuffer::releaseInto, retail 0x003F6E10, 105 bytes. The
// body carried only a machine byte-dump row; the symbols.csv pin names it as
// the one-argument member FileInfoStruct's destructor calls on its first
// member.
//
// The buffer is on an intrusive list threaded through +0x2C, the next pointer,
// and +0x30, a pointer to whatever pointer refers to this one. That second
// field is what makes unlinking need no head: writing the next through it
// repairs the chain wherever the buffer sits.
//
// The unlink appears twice in the bytes, in full, which is what the two nested
// helpers give: the release unlinks, and the link it then performs unlinks
// again before threading the buffer onto the head it was handed. Afterwards one
// global count comes down.

class MixFileInfoBuffer
{
public:
	void releaseInto(void *head);

private:
	__forceinline void bfmeUnlink(void)
	{
		if (m_bfmePrevNext)
		{
			*m_bfmePrevNext = m_bfmeNext;

			if (m_bfmeNext)
				m_bfmeNext->m_bfmePrevNext = m_bfmePrevNext;

			m_bfmePrevNext = 0;
			m_bfmeNext = 0;
		}
	}

	__forceinline void bfmeLinkInto(MixFileInfoBuffer **head)
	{
		bfmeUnlink();

		m_bfmePrevNext = head;
		m_bfmeNext = *head;

		if (m_bfmeNext)
			m_bfmeNext->m_bfmePrevNext = &m_bfmeNext;

		*head = this;
	}

	char m_bfmeHead[0x2C];
	MixFileInfoBuffer *m_bfmeNext;				// +0x2C
	MixFileInfoBuffer **m_bfmePrevNext;			// +0x30
};

extern int TheBfmeMixFileInfoCount;				// 0x012F1098

// ?releaseInto@MixFileInfoBuffer@@QAEXPAX@Z
void MixFileInfoBuffer::releaseInto(void *head)
{
	bfmeUnlink();

	bfmeLinkInto((MixFileInfoBuffer **)head);

	--TheBfmeMixFileInfoCount;
}
