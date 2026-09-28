// Retail 0x0060B900 is a 147-byte method body. The matched wrapper in
// Rva003A3DC0.cpp calls it through the five-byte thunk at 0x0003D893.
// The method keeps its RVA in its name because no caller proves a semantic name.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

extern void j_00028c0e(void);

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

struct Rva0060B900Pair
{
	void *first;
	void *second;

	Rva0060B900Pair(const Rva0060B900Pair &other)
		: first(other.first), second(other.second) {}
	~Rva0060B900Pair() {}
};

struct Gen_t_0060b500_m4pod
{
	int value[1];
};

class Rva0060ACB0
{
public:
	int *rva0060ACB0(void *context, Rva0060B900Pair pair, void *item,
		UnsignedInt index, UnsignedByte flag);
};

class Rva0060B900
{
public:
	UnsignedByte padding[0x0C];
	std::vector<void *> items;

	void rva0060B900(void *context, const Rva0060B900Pair *pair,
		std::vector<Gen_t_0060b500_m4pod> *output, UnsignedByte flag);
};

void Rva0060B900::rva0060B900(void *context,
	const Rva0060B900Pair *pair,
	std::vector<Gen_t_0060b500_m4pod> *output, UnsignedByte flag)
{
	typedef int *(Rva0060ACB0::*Resolve)(void *, Rva0060B900Pair,
		void *, UnsignedInt, UnsignedByte);
	union Route
	{
		void (*function)();
		Resolve member;
	} route;
	route.function = j_00028c0e;
	int *value;
	for (UnsignedInt i = 0; i < items.size(); ++i)
	{
		value = (((Rva0060ACB0 *)this)->*route.member)(
			context, *pair, items.begin()[i], i, flag);
		if (value)
		{
			output->push_back(
				*reinterpret_cast<Gen_t_0060b500_m4pod *>(&value));
		}
	}
}
