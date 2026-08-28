// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
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
			_emit 0C1h
			_emit 04Bh
			_emit 059h
			_emit 000h
		}
	}
}

typedef _STL::pair<ThingTemplate const * const, int> ThingTemplateIntPair;
typedef _STL::_Rb_tree<ThingTemplate const *, ThingTemplateIntPair, _STL::_Select1st<ThingTemplateIntPair>, _STL::less<ThingTemplate const *>, _STL::allocator<ThingTemplateIntPair> > ThingTemplateTree;
template __declspec(naked) _STL::_Rb_tree_iterator<ThingTemplateIntPair, _STL::_Nonconst_traits<ThingTemplateIntPair> > ThingTemplateTree::insert_unique(ThingTemplateTree::iterator, ThingTemplateIntPair const &);
