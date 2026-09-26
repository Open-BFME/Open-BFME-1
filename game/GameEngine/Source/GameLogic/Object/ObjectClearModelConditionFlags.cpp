// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFME's 304-condition mask differs from Zero Hour's 320-condition header.
// Object::clearModelConditionFlags, retail 0x001B6E60: forward a zeroed
// set-mask alongside the caller's clear-mask to clearAndSetModelConditionFlags.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

template <size_t NUMBITS>
class BitFlags
{
public:
	BitFlags() {}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<304> ModelConditionFlags;

class Object
{
public:
	void clearAndSetModelConditionFlags(const ModelConditionFlags &clear,
		const ModelConditionFlags &set);
	void clearModelConditionFlags(const ModelConditionFlags &clear);
};

extern void j_000095ed();
typedef void (Object::*ClearAndSetModelConditionFlagsCall)(
	const ModelConditionFlags &, const ModelConditionFlags &);

void Object::clearModelConditionFlags(const ModelConditionFlags &clear)
{
	ModelConditionFlags empty;
	union
	{
		void (*freeFunction)();
		ClearAndSetModelConditionFlagsCall memberFunction;
	} clearAndSet;
	clearAndSet.freeFunction = j_000095ed;
	(this->*clearAndSet.memberFunction)(clear, empty);
}
