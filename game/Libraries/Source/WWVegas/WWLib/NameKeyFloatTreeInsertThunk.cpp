enum NameKeyType
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
		iterator insert_unique(iterator, Value const &);
	};

	template<class Key, class Value, class Select, class Compare, class Allocator>
	__declspec(naked) typename _Rb_tree<Key, Value, Select, Compare, Allocator>::iterator _Rb_tree<Key, Value, Select, Compare, Allocator>::insert_unique(iterator, Value const &)
	{
		__asm {
			_emit 0E9h
			_emit 099h
			_emit 01Eh
			_emit 011h
			_emit 000h
		}
	}
}

typedef _STL::pair<const NameKeyType, float> NameKeyFloatPair;
typedef _STL::_Rb_tree<NameKeyType, NameKeyFloatPair, _STL::_Select1st<NameKeyFloatPair>, _STL::less<NameKeyType>, _STL::allocator<NameKeyFloatPair> > NameKeyFloatTree;
template _STL::_Rb_tree_iterator<NameKeyFloatPair, _STL::_Nonconst_traits<NameKeyFloatPair> > NameKeyFloatTree::insert_unique(NameKeyFloatTree::iterator, NameKeyFloatPair const &);
