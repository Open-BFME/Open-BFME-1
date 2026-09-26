// Retail 0x0024C420 (210 B). Copies the contained-object list, runs the
// owner's virtual prepare(), then hands every contained object's nested
// result (contain slot 26) the owner word at this-0x18 and the argument.
//
// The owner word is copied into a local before the notify call. Passing it
// directly compiles to the same mov/push, but the argument load then comes
// out in EDX where retail has EAX: MSVC 7.1 hands out scratch registers
// round-robin, and only the copied form takes a step for the pushed owner
// (docs/shape_levers.md, "Scratch registers rotate").
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <list>

class Rva0024C420Result
{
public:
#define S(n) virtual void slot##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
	S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
	S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(30) S(31)
#undef S
	virtual void notify(void *owner, void *arg);
};

class Rva0024C420Contain
{
public:
#define S(n) virtual void slot##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
	S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
	S(20) S(21) S(22) S(23) S(24) S(25)
#undef S
	virtual Rva0024C420Result *getResult(void);
};

struct Rva0024C420ContainVtable
{
	void *slots[26];
	Rva0024C420Result *(__fastcall *getResult)(Rva0024C420Contain *self);
};

class Object
{
public:
	char m_pad[0x1fc];
	Rva0024C420Contain *m_contain;
};

class Rva0024C420Owner
{
public:
#define S(n) virtual void slot##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
	S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
	S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29)
	S(30) S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39)
	S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47) S(48) S(49)
	S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57) S(58) S(59)
	S(60) S(61) S(62) S(63) S(64)
#undef S
	virtual void prepare(void);
	void notifyNested(void *arg);

private:
	char m_pad[0x14];
	_STL::list<Object *> m_objects;
};

void Rva0024C420Owner::notifyNested(void *arg)
{
	_STL::list<Object *> objects(m_objects);
	prepare();
	for (_STL::list<Object *>::iterator it = objects.begin();
		 it != objects.end(); ++it)
	{
		Rva0024C420Contain *contain = (*it)->m_contain;
		if (contain == 0)
			continue;
		Rva0024C420Result *result;
		Rva0024C420ContainVtable *table = *(Rva0024C420ContainVtable **)contain;
		result = table->getResult(contain);
		if (result != 0)
		{
			void *owner = *(void **)((char *)this - 0x18);
			result->notify(owner, arg);
		}
	}
}
