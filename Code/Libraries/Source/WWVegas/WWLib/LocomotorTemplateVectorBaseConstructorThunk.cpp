// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class LocomotorTemplate
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

	__declspec(naked) _Vector_base<LocomotorTemplate const *, allocator<LocomotorTemplate const *> >::_Vector_base(
		unsigned int, const allocator<LocomotorTemplate const *> &)
	{
		__asm {
			_emit 0E9h
			_emit 062h
			_emit 0BCh
			_emit 01Bh
			_emit 000h
		}
	}
}
