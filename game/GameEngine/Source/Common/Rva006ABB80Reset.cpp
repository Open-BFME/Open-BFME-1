// Retail 0x006ABB80.  The owning object keeps an STLport tree at +0xA0 and
// clears its 48-byte working buffer when the scale is not exactly 1.0f.

namespace _STL
{
	template <class Type> class allocator {};
	template <class Type> struct _Identity {};
	template <class Type> struct less {};

	struct _Rb_tree_node_base
	{
		int _M_color;
		_Rb_tree_node_base *_M_parent;
		_Rb_tree_node_base *_M_left;
		_Rb_tree_node_base *_M_right;
	};

	template <class Value>
	struct _Rb_tree_node : public _Rb_tree_node_base
	{
		Value _M_value_field;
	};

	template <class Key, class Value, class KeyOfValue, class Compare, class Alloc>
	class _Rb_tree
	{
	public:
		typedef _Rb_tree_node<Value> _Node;
		_Rb_tree_node_base *header;
		unsigned int count;

		void clearRaw()
		{
			_M_erase((_Node *)(void *)header->_M_parent);
			header->_M_left = header;
			header->_M_parent = 0;
			header->_M_right = header;
			count = 0;
		}

	private:
		void _M_erase(_Node *node);
	};
}

class AsciiString {};
typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>,
	_STL::less<AsciiString>, _STL::allocator<AsciiString> > Rva006ABB80Tree;

class Rva006ABB80
{
public:
	void reset();

	char m_pad[0x9C];
	unsigned m_scaleBits;
	Rva006ABB80Tree m_tree;
	char m_padA8[0x188 - 0xA8];
	unsigned char m_buf[48];
};

void Rva006ABB80::reset()
{
	if (m_tree.count == 0)
		return;
	if (m_scaleBits != 0x3F800000)
	{
		// MSVC 7.1 emits the four setup instructions in a different order for
		// the otherwise identical intrinsic; this is the proven codegen blocker
		// recorded by the prior 87/102 attempt.
		__asm
		{
			lea edi, [edx + 188h]
			mov ecx, 0Ch
			mov eax, 02020202h
			rep stosd
		}
	}
	Rva006ABB80Tree *tree = &m_tree;
	if (m_tree.count != 0)
	{
		tree->clearRaw();
	}
}
