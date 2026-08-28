// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
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

	__declspec(naked) _Vector_base<Object *, allocator<Object *> >::_Vector_base(
		unsigned int, const allocator<Object *> &)
	{
		__asm {
			_emit 0E9h
			_emit 0D4h
			_emit 033h
			_emit 013h
			_emit 000h
		}
	}
}
