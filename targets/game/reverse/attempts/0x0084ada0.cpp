// ?rva0084ADA0OpenLog@Rva0084ADA0Owner@@QAEXPBDH@Z
// partial score=0.9 date=2026-09-06
// ?rva0084ADA0OpenLog@Rva0084ADA0Owner@@QAEXPBDH@Z
// Address-derived: opens a sub-filebuf at this+0xc+0x54 via the already-named
// STL internal _Filebuf_base::_M_open(name, mode, 0x80); on failure, reads a
// vbtable-style displacement at [[this]+4], uses it to locate a base
// sub-object, ORs flag bits into its +8 field (using its +0x58 field to pick
// which bit) and calls the already-named process() if a bit-test at +0x14
// against the new flags is non-zero.
namespace _STL
{
	class _Filebuf_base
	{
	public:
		bool _M_open(const char *name, int mode, long protection);
	};
}

void process();

class Rva0084ADA0Owner
{
public:
	unsigned char m_pad0[0xc];
	unsigned char m_filebuf[0x54 + 4];

	void rva0084ADA0OpenLog(const char *name, int mode);
};

void Rva0084ADA0Owner::rva0084ADA0OpenLog(const char *name, int mode)
{
	_STL::_Filebuf_base *fbBase = (_STL::_Filebuf_base *)(m_filebuf);
	_STL::_Filebuf_base *fb = (_STL::_Filebuf_base *)((char *)fbBase + 0x54);
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
