#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

class BfmeStrXD
{
};

const BfmeStrXD &bfmeMedianXD(const BfmeStrXD &a, const BfmeStrXD &b, const BfmeStrXD &c)
{
	if (((const StringBase<char> &)a).compare((const StringBase<char> &)b) < 0)
		if (((const StringBase<char> &)b).compare((const StringBase<char> &)c) < 0)
			return b;
		else if (((const StringBase<char> &)a).compare((const StringBase<char> &)c) < 0)
			return c;
		else
			return a;
	else if (((const StringBase<char> &)a).compare((const StringBase<char> &)c) < 0)
		return a;
	else if (((const StringBase<char> &)b).compare((const StringBase<char> &)c) < 0)
		return c;
	else
		return b;
}
