// Address-derived reconstruction of retail 0x007F00B0 (98 bytes).
// The caller and the neighbouring FESL allocator bodies establish a three-
// pointer interface object: vptr, acquire callback, release callback.

struct Rva007F00B0Allocator
{
	void *m_vtable;
	void *m_allocate;
	void *m_release;
};

typedef void *(__cdecl *Rva007F00B0Allocate)(unsigned int, int);

Rva007F00B0Allocator *g_Rva0130A5B0;
extern void *g_0112A5C4[];

// The default callbacks this body installs are retail's pooled operator
// new/delete forwarders at VA 0x00BEFFE0 and 0x00BEFFF0 (RVA 0x007EFFE0 and
// 0x007EFFF0): one 14-byte `return malloc(s)` and one 12-byte `free(p)` body
// that ICF merged every pooled class onto -- see the ICF-alias rows in
// functions.csv.  Common/INI/ini.cpp is where that pool glue is declared (its
// MEMORY_POOL_GLUE_WITHOUT_GCMP macro expands to exactly these two members
// plus the magic enum, in that order); declaration only here, because this TU
// stores their addresses and nothing else.
class DynamicAudioEventRTS
{
public:
	enum DynamicAudioEventRTSMagicEnum { DYNAMIC_AUDIO_EVENT_RTS_GLUE_NOT_IMPLEMENTED = 0 };

public:
	void *operator new(unsigned int size, DynamicAudioEventRTSMagicEnum magic);
	void operator delete(void *p, DynamicAudioEventRTSMagicEnum magic);
};

void *operator new(unsigned int size);

void Rva007F00B0(void *allocate, void *release)
{
	Rva007F00B0Allocator *p;

	if (g_Rva0130A5B0)
		return;

	if (allocate)
	{
		p = (Rva007F00B0Allocator *)((Rva007F00B0Allocate)allocate)(12, 0);
		if (p)
			p->m_allocate = allocate;
		else
			goto clear;
	}
	else
	{
		p = (Rva007F00B0Allocator *)::operator new(12);
		if (p)
			p->m_allocate = (void *)&DynamicAudioEventRTS::operator new;
		else
			goto clear;
	}

	p->m_vtable = g_0112A5C4;
	if (!release)
		release = (void *)&DynamicAudioEventRTS::operator delete;
	p->m_release = release;
	g_Rva0130A5B0 = p;
	return;

clear:
	g_Rva0130A5B0 = 0;
}
