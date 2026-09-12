// ?processNestedRiders@Rva0024C940Owner@@QAEXXZ
// Retail RVA 0x0024C940, reached as the second containment-maintenance call
// from HordeTransportContain::update.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <list>

class BfmeXCQE { public: char bfmeKindCQE(void); };
class Rva0024C940Contain;

class Object
{
public:
#define S(n) virtual void slot##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
#undef S
	virtual BfmeXCQE *getState(void);
	char m_pad[0x1fc - 4];
	Rva0024C940Contain *m_contain;
};

class Rva0024C940Result
{
public:
#define S(n) virtual void slot##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
	S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
	S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29)
	S(30) S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39)
	S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47) S(48) S(49)
	S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57) S(58)
#undef S
	virtual _STL::list<Object *> *getNested(void);
};

class Rva0024C940Contain
{
public:
#define S(n) virtual void slot##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
	S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
	S(20) S(21) S(22) S(23) S(24) S(25)
#undef S
	virtual Rva0024C940Result *getResult(void);
};

class Rva0024C940Owner
{
public:
#define S(n) virtual void slot##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12)
#undef S
	virtual void handleNested(Rva0024C940Result *result, Object *object);
	void processNestedRiders(void);

private:
	char m_pad[0x34];
	_STL::list<Object *> m_objects;
};

void Rva0024C940Owner::processNestedRiders(void)
{
	_STL::list<Object *> nested;
	_STL::list<Object *> objects(m_objects);
	for (_STL::list<Object *>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		Object *outer = *it;
		if (outer == 0)
			continue;
		Rva0024C940Contain *contain = outer->m_contain;
		if (contain == 0)
			continue;
		Rva0024C940Result *result = contain->getResult();
		if (result == 0)
			continue;
		nested = *result->getNested();
		if (nested.empty())
			continue;
		Object *object = *nested.begin();
		BfmeXCQE *state = object->getState();
		if (state != 0 && !state->bfmeKindCQE())
			handleNested(result, object);
	}
}
