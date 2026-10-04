#include <bitset>
namespace _STL { using namespace std; }

// ?rva002CDF00@Rva002CDF00Host@@QAEXPAVRva002CDF00Thing@@@Z
// The retail body reads a secondary owner at this-0x18, calls virtual slot 10
// on that owner and on its argument, then forwards a null argument to the
// returned result. The address-derived names preserve that evidence without
// assigning an unsupported semantic class name.

extern void j_00041998(void);
extern void j_0002191d(void);

class Rva002CDF00Result
{
public:
	void apply(void *arg);
};

class Rva002CDF00ConditionBits
{
public:
	bool test(int bit) const { return bits.test(bit); }
	void set(int bit) { bits.set(bit); }

private:
	_STL::bitset<32> bits;
};

class Rva002CDF00Thing
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Rva002CDF00Result *getResult();

	unsigned char m_head[0x12c];
	Rva002CDF00ConditionBits m_flags;
};

class Rva002CDF00Host
{
public:
	void rva002CDF00(Rva002CDF00Thing *a);
};

void Rva002CDF00Host::rva002CDF00(Rva002CDF00Thing *a)
{
	if (!a->m_flags.test(16))
	{
		a->m_flags.set(16);
		typedef void (Rva002CDF00Thing::*Notify)();
		union { void (*fn)(); Notify call; } notify = { j_0002191d };
		(a->*notify.call)();
	}

	Rva002CDF00Result *first = (*(Rva002CDF00Thing **)((char *)this - 0x18))->getResult();
	Rva002CDF00Result *second = a->getResult();

	if (second != 0 && first != 0)
	{
		typedef void (Rva002CDF00Result::*Apply)(void *);
		union { void (*fn)(); Apply call; } apply = { j_00041998 };
		(second->*apply.call)(0);
	}
}
