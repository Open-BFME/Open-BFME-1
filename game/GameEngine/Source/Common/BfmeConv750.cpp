// ILT0001AB86 -> 00193760/81: thiscall copy constructor, one reference, RET4.
extern "C" void __identifier("??0?$pair@$$CBUGen_t_00193760_k4@@UGen_t_00193760_p12cd@@@_STL@@QAE@ABU01@@Z")();

class BfmeOtherDPC
{
public:
	unsigned char m_bfmeHead[8];
	int m_bfmeVal;
};

BfmeOtherDPC *bfmeGoDPC(BfmeOtherDPC *other, void *value, int *src)
{
	volatile int tmp = 0;
	union
	{
		void (*address)();
		void (BfmeOtherDPC::*member)(const BfmeOtherDPC &);
	} route = { __identifier("??0?$pair@$$CBUGen_t_00193760_k4@@UGen_t_00193760_p12cd@@@_STL@@QAE@ABU01@@Z") };
	(other->*route.member)(*(const BfmeOtherDPC *)value);
	other->m_bfmeVal = *src;
	return other;
}
