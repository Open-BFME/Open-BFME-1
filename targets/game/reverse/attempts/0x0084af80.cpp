// ?rva0084AF80OpenLog@Rva0084AF80Owner@@QAEXPBDH@Z
// partial score=0.9 date=2026-09-06
// ?rva0084AF80OpenLog@Rva0084AF80Owner@@QAEXPBDH@Z
// Address-derived: byte-identical sibling of 0x0084ADA0 (opens a different
// sub-filebuf, at this+0xc+0x24 instead of +0x54); see that TU's history for
// the register-colour wall in the vbtable-disp flag-update block.
namespace _STL
{
	class _Filebuf_base
	{
	public:
		bool _M_open(const char *name, int mode, long protection);
	};
}

void process();

class Rva0084AF80Owner
{
public:
	unsigned char m_pad0[0xc];
	unsigned char m_filebuf[0x24 + 4];

	void rva0084AF80OpenLog(const char *name, int mode);
};

void Rva0084AF80Owner::rva0084AF80OpenLog(const char *name, int mode)
{
	_STL::_Filebuf_base *fbBase = (_STL::_Filebuf_base *)(m_filebuf);
	_STL::_Filebuf_base *fb = (_STL::_Filebuf_base *)((char *)fbBase + 0x24);
	bool opened = fb->_M_open(name, mode, 0x80);
	void *result = opened ? (void *)fbBase : 0;
	if (!result)
	{
		void *vbtable = *(void **)this;
		char *base = (char *)this + *(int *)((char *)vbtable + 4);
		int flags = *(int *)(base + 8);
		int other = *(int *)(base + 0x58);
		flags |= 4;
		if (other == 0)
			flags |= 1;
		bool doProcess = (*(int *)(base + 0x14) & flags) != 0;
		*(int *)(base + 8) = flags;
		if (doProcess)
			process();
	}
}
