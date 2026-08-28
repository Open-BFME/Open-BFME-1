// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
};

namespace _STL
{
	template <class Type>
	class allocator
	{
	};

	template <class Type, class Allocator>
	class vector
	{
	public:
		vector(const Allocator &);
	};

	__declspec(naked) vector<AsciiString, allocator<AsciiString> >::vector(
		const allocator<AsciiString> &)
	{
		__asm {
			_emit 0E9h
			_emit 02Eh
			_emit 0B7h
			_emit 04Bh
			_emit 000h
		}
	}
}
