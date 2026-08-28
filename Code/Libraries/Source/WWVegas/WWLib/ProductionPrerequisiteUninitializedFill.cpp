// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h
class ProductionPrerequisite
{
private:
	char m_data[0x18];
};

namespace _STL
{
struct __false_type
{
};

template <class T1, class T2>
void _Construct(T1 *destination, const T2 &value);

template <class ForwardIterator, class Size, class T>
ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size count, const T &value, const __false_type &)
{
	ForwardIterator current = first;
	while (count > 0)
	{
		_Construct(current, value);
		++current;
		--count;
	}
	return current;
}

template ProductionPrerequisite *__uninitialized_fill_n(
	ProductionPrerequisite *, unsigned int, const ProductionPrerequisite &, const __false_type &);
}
