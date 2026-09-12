// ?notifyNested@Rva0024C420Owner@@QAEXPAX@Z
// partial score=0.98 date=2026-09-12
// ?notifyNested@Rva0024C420Owner@@QAEXPAX@Z
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
		Rva0024C420Result *result;
		Rva0024C420Contain *contain = (*it)->m_contain;
		if (contain == 0)
			continue;
		result = contain->getResult();
		if (result != 0)
			result->notify(*(void **)((char *)this - 0x18), arg);
	}
}
