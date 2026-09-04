// ?Rva0069AE40_check@@YG_NPAURva0069AE40Arg@@@Z
// partial score=0.85 date=2026-09-04
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Free stdcall predicate on audio-event-like object.

struct Rva0069AE40Inner
{
	char m_pad[0x54];
	float m_value;
};

struct Rva0069AE40Node
{
	char m_pad[0x41];
	unsigned char m_flag41;
	unsigned char m_flag42;
};

struct Rva0069AE40Arg
{
	char m_pad0[4];
	Rva0069AE40Inner *m_inner;
	char m_pad1[4];
	Rva0069AE40Node *m_node;
	char m_pad2[2];
	unsigned char m_flag12;
	unsigned char m_flag13;
	unsigned char m_flag14;
};

#define Rva0069AE40Threshold (*(const float *)0x0111BB98)

bool __stdcall Rva0069AE40_check(Rva0069AE40Arg *arg)
{
	if (!arg->m_flag12 && !arg->m_flag13 && !arg->m_flag14)
	{
		Rva0069AE40Inner *inner = arg->m_inner;
		if (inner)
		{
			float v = inner->m_value;
			float t = Rva0069AE40Threshold;
			if (v >= t)
				return false;
		}
		Rva0069AE40Node *node = arg->m_node;
		if (!node)
			return true;
		if (node != 0 && node->m_flag41)
			return true;
		node = arg->m_node;
		if (!node)
			return true;
		if (node->m_flag42)
			return true;
		return false;
	}
	return false;
}
