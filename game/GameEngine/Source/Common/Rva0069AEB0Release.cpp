// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Release helper: clear sticky flag, optional stop, then mark done.

class Rva0069AEB0Node
{
public:
	void stop(int which);
	void finish(void *cookie);
};

class Rva0069AEB0Arg
{
public:
	char m_pad0[4];
	Rva0069AEB0Node *m_node; // +4
	char m_pad1[0x9];
	unsigned char m_done; // +0x11
	unsigned char m_f12; // +0x12
	unsigned char m_f13; // +0x13
	unsigned char m_f14; // +0x14
};

class Rva0069AEB0Owner
{
public:
	void release(Rva0069AEB0Arg *arg);

	char m_pad0[0x44];
	void *m_cookie; // +0x44
	char m_pad1[0x637 - 0x48];
	unsigned char m_block; // +0x637
	int m_gate; // +0x638
};

void Rva0069AEB0Owner::release(Rva0069AEB0Arg *arg)
{
	if (arg->m_f14 && !m_block)
	{
		arg->m_f14 = 0;
		if (!m_gate)
		{
			Rva0069AEB0Node *node = arg->m_node;
			if (node)
				node->stop(1);
		}
	}

	Rva0069AEB0Node *node = arg->m_node;
	if (node)
	{
		if (!arg->m_f12 && !arg->m_f13 && !arg->m_f14)
		{
			node->finish(m_cookie);
			arg->m_done = 1;
		}
	}
}
