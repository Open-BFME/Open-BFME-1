// cl: /Od
// stlport
// A byte handed to the worker below and the record handed back, built without
// optimisation. The frame holds something this body never names.

#include <string>

// Retail's call at 0x00830C40 rides the class's ILT thunk at 0x0003BC23, a bare
// `jmp` onto this STLport member (0x0053AE60, game/gen_small/tgrid_004.cpp).
// Naming the member directly reproduces the runtime image exactly -- the thunk
// adds no code -- and the specialisation declaration keeps this /Od TU from
// emitting its own (differing) inline copy of the body.
template <>
void _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >::
	push_back(char);

class BfmeThingOU
{
public:
	BfmeThingOU *bfmeSetOU(unsigned char one);
};

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > bfmeStringOU;

BfmeThingOU *BfmeThingOU::bfmeSetOU(unsigned char one)
{
	unsigned char spare[0x14];

	((bfmeStringOU *)this)->push_back((char)one);

	return this;
}
