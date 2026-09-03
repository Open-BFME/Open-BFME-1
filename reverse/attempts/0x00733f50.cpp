// ?handle@Rva00734730@@QAEXHH@Z
// partial score=0.85 date=2026-09-02
// BFME retail 0x00733F50: guarded indexed handle update.

typedef unsigned char Bool;

struct Rva00734730EntryView
{
	unsigned char m_pad0[0x1F0];
	int m_state;
	unsigned char m_pad1[0xA0];
	int m_handle;
};

class Rva00734730
{
public:
	void handle(int index, int useObjectHandle);
};

void Rva00734730::handle(int index, int useObjectHandle)
{
	unsigned char *self = (unsigned char *)this;

	if (*(Bool *)(self + 0x2A990D))
		return;
	if (index >= *(int *)(self + 0x2A7CB0))
		return;

	Rva00734730EntryView &entry = *(Rva00734730EntryView *)(self + index * 0xE8);
	state = entry.m_state;
	if (state < 0)
		return;

	Bool useHandle = (Bool)useObjectHandle;
	if (useHandle)
	{
		unsigned char *object = *(unsigned char **)(self + 0x2A7CDC + state * 0x5C);
		entry.m_handle = *(int *)(object + 0x5C);
		*(Bool *)(self + 0x2A990C) = 1;
		return;
	}

	entry.m_handle = 0xFF;
	*(Bool *)(self + 0x2A990C) = 1;
}
