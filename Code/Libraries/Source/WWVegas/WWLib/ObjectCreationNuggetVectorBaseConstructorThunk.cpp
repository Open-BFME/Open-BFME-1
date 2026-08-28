// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectCreationList.h
class ObjectCreationNugget
{
};

namespace _STL
{
	template <class Type>
	class allocator
	{
	};

	template <class Type, class Allocator>
	class _Vector_base
	{
	public:
		_Vector_base(unsigned int, const Allocator &);
	};

	__declspec(naked) _Vector_base<ObjectCreationNugget *, allocator<ObjectCreationNugget *> >::_Vector_base(
		unsigned int, const allocator<ObjectCreationNugget *> &)
	{
		__asm {
			_emit 0E9h
			_emit 053h
			_emit 076h
			_emit 019h
			_emit 000h
		}
	}
}
