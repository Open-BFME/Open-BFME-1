// cl: /DNDEBUG /MD /EHsc
// Open-BFME: LocomotorStore::newLocomotor, retail 0x001B6920, 98 bytes.
//
// One line: allocate a Locomotor and construct it from the template. The
// allocation is the plain global operator new rather than a pool -- the size
// goes on the stack and the returned pointer is null-checked before the
// constructor runs, which is exactly what MSVC emits for `new T(arg)` -- and
// the unwind funclet around it is the matching operator delete.
//
// sizeof(Locomotor) is 0xA8, the size pushed, and that is all this file can
// say about the class: the constructor is a call, so nothing of the layout is
// visible here. `this` is never touched, which is why the store's own model is
// empty; the frame's `push ecx` is allocation, not an argument.

typedef int Int;
typedef bool Bool;

class LocomotorTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class Locomotor
{
public:
	Locomotor(const LocomotorTemplate *tmpl);	// ILT 0x00040AA7

private:
	char m_bfme_body[0xA8];				// sizeof(Locomotor), the pushed size
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h
class LocomotorStore
{
public:
	Locomotor *newLocomotor(const LocomotorTemplate *tmpl) const;
};

Locomotor *LocomotorStore::newLocomotor(const LocomotorTemplate *tmpl) const
{
	return new Locomotor(tmpl);
}
