// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
};

namespace _STL
{
	template<class First, class Second> struct pair { };
	template<class T> struct _Select1st { };
	template<class T> struct less { };
	template<class T> class allocator { };
	template<class T> struct _Nonconst_traits { };
	template<class T, class Traits> struct _Rb_tree_iterator { };

	template<class Key, class Value, class Select, class Compare, class Allocator>
	class _Rb_tree
	{
	public:
		typedef _Rb_tree_iterator<Value, _Nonconst_traits<Value> > iterator;
		pair<iterator, bool> insert_unique(Value const &);
	};

	template<class Key, class Value, class Select, class Compare, class Allocator>
	__declspec(naked) pair<typename _Rb_tree<Key, Value, Select, Compare, Allocator>::iterator, bool> _Rb_tree<Key, Value, Select, Compare, Allocator>::insert_unique(Value const &)
	{
		__asm {
			_emit 0E9h
			_emit 0ABh
			_emit 0EAh
			_emit 061h
			_emit 000h
		}
	}
}

typedef _STL::pair<const AsciiString, Coord3D> AsciiStringCoord3DPair;
typedef _STL::_Rb_tree<AsciiString, AsciiStringCoord3DPair, _STL::_Select1st<AsciiStringCoord3DPair>, _STL::less<AsciiString>, _STL::allocator<AsciiStringCoord3DPair> > AsciiStringCoord3DTree;
template __declspec(naked) _STL::pair<_STL::_Rb_tree_iterator<AsciiStringCoord3DPair, _STL::_Nonconst_traits<AsciiStringCoord3DPair> >, bool> AsciiStringCoord3DTree::insert_unique(AsciiStringCoord3DPair const &);
