enum NameKeyType
{
};

namespace ModuleFactory
{
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ModuleFactory.h
	class ModuleTemplate
	{
	};
}

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
		template<class SearchKey>
		_Rb_tree_iterator<Value, _Nonconst_traits<Value> > find(SearchKey const &);
	};

	template<class Key, class Value, class Select, class Compare, class Allocator>
	template<class SearchKey>
	__declspec(naked) _Rb_tree_iterator<Value, _Nonconst_traits<Value> > _Rb_tree<Key, Value, Select, Compare, Allocator>::find(SearchKey const &)
	{
		__asm {
			_emit 0E9h
			_emit 077h
			_emit 0A5h
			_emit 011h
			_emit 000h
		}
	}
}

typedef _STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> ModuleTemplatePair;
typedef _STL::_Rb_tree<NameKeyType, ModuleTemplatePair, _STL::_Select1st<ModuleTemplatePair>, _STL::less<NameKeyType>, _STL::allocator<ModuleTemplatePair> > ModuleTemplateTree;
template __declspec(naked) _STL::_Rb_tree_iterator<ModuleTemplatePair, _STL::_Nonconst_traits<ModuleTemplatePair> > ModuleTemplateTree::find<NameKeyType>(NameKeyType const &);
