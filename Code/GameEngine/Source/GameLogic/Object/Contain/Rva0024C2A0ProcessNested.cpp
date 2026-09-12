// ?processNested@Rva0024C2A0Owner@@QAEXPAVObject@@PAX@Z
// Retail RVA 0x0024C2A0. The full 294-byte boundary comes from Ghidra and the
// contained-object/result layout is shared with the adjacent exact passes.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <list>

class Rva0024C2A0Contain;
class Object
{
public:
	char m_pad[0x1fc];
	Rva0024C2A0Contain *m_contain;
	char m_pad200[0x368 - 0x200];
	unsigned char m_skip;
};

class Rva0024C2A0Result
{
public:
#define S(n) virtual void slot##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
	S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
	S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29)
	S(30) S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39)
#undef S
	virtual void removeNested(Object *object);
#define S(n) virtual void slot##n();
	S(41) S(42) S(43) S(44) S(45) S(46) S(47) S(48) S(49)
	S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57) S(58)
#undef S
	virtual _STL::list<Object *> *getNested(void);
};

class Rva0024C2A0Contain
{
public:
#define S(n) virtual void slot##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
	S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
	S(20) S(21) S(22) S(23) S(24) S(25)
#undef S
	virtual Rva0024C2A0Result *getResult(void);
};

class Rva0024C2A0Owner
{
public:
	void processNested(Object *subject, void *arg);
	void handleNested(Object *object, void *arg);
};

void Rva0024C2A0Owner::processNested(Object *subject, void *arg)
{
	Rva0024C2A0Contain *contain = subject->m_contain;
	if (contain == 0)
		return;
	Rva0024C2A0Result *result = contain->getResult();
	if (result == 0)
		return;
	_STL::list<Object *> nested(*result->getNested());
	for (_STL::list<Object *>::iterator it = nested.begin(); it != nested.end(); ++it)
	{
		Object *object = *it;
		if (!object->m_skip)
		{
			result->removeNested(object);
			handleNested(object, arg);
		}
	}
	for (_STL::list<Object *>::iterator it = nested.begin(); it != nested.end(); ++it)
	{
		Object *object = *it;
		result->removeNested(object);
		handleNested(object, arg);
	}
	handleNested(subject, arg);
}
