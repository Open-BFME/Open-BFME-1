// cl: /DNDEBUG /MD /EHsc
// 0x0084AAD0 (8 bytes): an unreferenced __thiscall body alone in an
// int3-padded .text gap no ledger row covered,
//
//     add ecx,0x24 / jmp _STL::_Filebuf_base::_M_write (0x0084A7B0)
//
// forwarding its two stack arguments to the _Filebuf_base held at +0x24 of its
// receiver. No call, ILT stub, table slot or dir32 name reaches it.
// IDENTITY IS NOT RECOVERED: the owner is address-derived; only the member's
// offset is read from the bytes. Only the callee's declaration is given, so no
// STLport header is included.

namespace _STL
{
class _Filebuf_base
{
public:
	bool _M_write(char *buf, int n);
};
}

class Rva0084AAD0Owner
{
public:
	bool write(char *buf, int n);

private:
	char m_pad[0x24];
	_STL::_Filebuf_base m_base;
};

bool Rva0084AAD0Owner::write(char *buf, int n)
{
	return m_base._M_write(buf, n);
}
