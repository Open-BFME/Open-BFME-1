// ?b_0000e868@@YAXXZ at retail RVA 0x0000E868.
// Retail jumps to the matched 12-byte STLport vector overflow body.

namespace State
{
struct TransitionInfo
{
	int word00;
	int word04;
	int word08;
};
}

namespace _STL
{
struct __false_type
{
};

class StateTransitionInfoInsertOverflowShim
{
public:
	void insert_overflow(State::TransitionInfo *position,
		const State::TransitionInfo &value, const __false_type &tag,
		unsigned int fillLength, bool atEnd);
};
}

class Rva0000E868Vector
{
public:
	typedef _STL::StateTransitionInfoInsertOverflowShim TargetVector;

	__declspec(noinline) void insert(
		void *position, const void *value, const _STL::__false_type &tag,
		unsigned int fillLength, bool atEnd);
};

__declspec(noinline) void Rva0000E868Vector::insert(
	void *position, const void *value, const _STL::__false_type &tag,
	unsigned int fillLength, bool atEnd)
{
	reinterpret_cast<TargetVector *>(this)->insert_overflow(
		(State::TransitionInfo *)position,
		*(const State::TransitionInfo *)value,
		tag, fillLength, atEnd);
}
