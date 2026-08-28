enum NameKeyType
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class LocomotorTemplate
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
			_emit 065h
			_emit 0C1h
			_emit 064h
			_emit 000h
		}
	}
}

typedef _STL::pair<const NameKeyType, LocomotorTemplate *> NameKeyLocomotorPair;
typedef _STL::_Rb_tree<NameKeyType, NameKeyLocomotorPair, _STL::_Select1st<NameKeyLocomotorPair>, _STL::less<NameKeyType>, _STL::allocator<NameKeyLocomotorPair> > NameKeyLocomotorTree;
template __declspec(naked) _STL::_Rb_tree_iterator<NameKeyLocomotorPair, _STL::_Nonconst_traits<NameKeyLocomotorPair> > NameKeyLocomotorTree::insert_unique(NameKeyLocomotorTree::iterator, NameKeyLocomotorPair const &);
