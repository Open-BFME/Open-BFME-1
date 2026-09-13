// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x006B0C50. Same +0x9C scale / +0xA0 tree / +0x188 48-byte buffer
// as Rva006ABB80::reset. erase() the key; if anything was removed and the
// scale is not 1.0f, fill the buffer with 0x02. The stosd setup order is
// the proven codegen blocker recorded on the sibling at 0x006ABB80.

class AsciiString
{
};

namespace _STL
{
	template <class Type> class allocator {};
	template <class Type> struct _Identity {};
	template <class Type> struct less {};

	template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	class _Rb_tree
	{
	public:
		unsigned int erase(const Key &key);
	};
}

typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>,
	_STL::less<AsciiString>, _STL::allocator<AsciiString> > Rva006B0C50Tree;

class Rva006B0C50
{
public:
	void eraseFill(const AsciiString &key);

	char m_pad[0x9C];
	unsigned m_scaleBits;
	Rva006B0C50Tree m_tree;
	char m_padA8[0x188 - 0xA8];
	unsigned char m_buf[48];
};

void Rva006B0C50::eraseFill(const AsciiString &key)
{
	if (m_tree.erase(key) <= 0)
		return;
	if (m_scaleBits == 0x3F800000)
		return;
	__asm
	{
		lea edi, [esi + 188h]
		mov ecx, 0Ch
		mov eax, 02020202h
		rep stosd
	}
}
