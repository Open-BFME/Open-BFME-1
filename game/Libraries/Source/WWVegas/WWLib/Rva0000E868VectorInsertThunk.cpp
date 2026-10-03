// Retail RVA 0x0000E868 is a five-byte tail jump to the matched
// vector<W3DModelDraw::WeaponRecoilInfo>::_M_insert_overflow body at
// 0x002109B0
// (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/WeaponRecoilInfoVectorInsertOverflowBody.cpp).
// The element is 12 bytes -- a state enum and two Reals -- matching the old
// TransitionInfo stand-in word for word, so the forward keeps its shape.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DModelDraw
{
public:
	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
	struct WeaponRecoilInfo
	{
		int m_state;
		float m_shift;
		float m_recoilRate;
	};
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *, const Type &, const __false_type &,
		unsigned int, bool);
};
}

class Rva0000E868Vector
	: public _STL::vector<W3DModelDraw::WeaponRecoilInfo,
		_STL::allocator<W3DModelDraw::WeaponRecoilInfo> >
{
public:
	__declspec(noinline) void insert(
		void *position, const void *value, const _STL::__false_type &tag,
		unsigned int fillLength, bool atEnd);
};

__declspec(noinline) void Rva0000E868Vector::insert(
	void *position, const void *value, const _STL::__false_type &tag,
	unsigned int fillLength, bool atEnd)
{
	this->_M_insert_overflow((W3DModelDraw::WeaponRecoilInfo *)position,
		*(const W3DModelDraw::WeaponRecoilInfo *)value,
		tag, fillLength, atEnd);
}
