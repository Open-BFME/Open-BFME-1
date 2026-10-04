// cl: /O2 /MD
//
// Retail RVA 0x00008837 is a five-byte incremental-link tail jump to the
// independently matched vector<W3DAnimationInfo>::_M_clear body at 0x003B0E90.
// The tail jump keeps the member receiver and any caller state untouched, which
// is what the address-qualified thunk identity records. Calling _M_clear
// through a function-pointer union under its real name keeps the mangling
// MSVC gives a protected member (IAEXXZ, as retail recorded) without hiding a
// misspelled symbol behind a linker alternate.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DAnimationInfo
{
private:
	char m_body[16];
};

void j_00008837(void);

namespace _STL
{
// The body at 0x003B0E90 is matched in
// game/GameEngineDevice/.../W3DAnimationInfoVectorClearBody.cpp; only the
// reference belongs here, so this class carries no behaviour.
template <class Type>
class allocator {};

template <class Type, class Allocator>
class vector
{
protected:
	// STLport keeps _M_clear protected, which is what retail's mangled name
	// (IAEXXZ) records; a public one would ask for QAEXXZ.
	void _M_clear();

	Type *_M_start;

	friend void ::j_00008837(void);
};
}

typedef _STL::vector<W3DAnimationInfo, _STL::allocator<W3DAnimationInfo> > AnimationInfoVector;

void j_00008837(void)
{
	typedef void (AnimationInfoVector::*Fn)();
	union { void (*fn)(); Fn call; } u;
	u.call = &AnimationInfoVector::_M_clear;
	u.fn();
}