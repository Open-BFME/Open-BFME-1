// Open-BFME5: address-derived body, retail 0x0028F4D0 size 56.
// Cache the indexed pointer from [this+0x80, this+0x84) into [this+0x8C],
// or store null when the signed index at +0xB4 is out of range.
// IDENTITY NOT RECOVERED: no caller, vtable, or source names this body.

class Rva0028F4D0
{
public:
	void pick();

private:
	char m_pad[0x80];
	union
	{
		void **m_begin;
		int m_beginAddress;
	};
	void **m_end;
	char m_pad2[4];
	void *m_current;
	char m_pad3[0x24];
	int m_index;
};

// ?pick@Rva0028F4D0@@QAEXXZ
void Rva0028F4D0::pick()
{
	int index = m_index;
	if (index >= 0)
	{
		int count = ((int)m_end - m_beginAddress) >> 2;
		if ((unsigned int)index < count)
		{
			void **begin = *(void ** volatile *)((char *)this + 0x80);
			m_current = begin[index];
			return;
		}
	}
	m_current = 0;
}
