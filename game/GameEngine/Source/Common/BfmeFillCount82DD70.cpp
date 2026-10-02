// stlport
// A count-form fill forwarded to the range-form one, built without
// optimisation. The empty tag is constructed and dropped -- a dispatch witness,
// not a value -- and it has to be the bare temporary: give it a name and it
// takes a second frame byte, moving the zero store from ebp-1 to ebp-2.
//
// The unoptimised code is scoped with #pragma optimize rather than a `// cl:
// /Od` line on purpose. retail's fill at 0x0082ADB0 is the 48-byte unrolled
// loop an optimised _STL::fill<char> emits, and a whole-file /Od turns it into
// the 40-byte memset-forwarding body, which is then a COMDAT copy that is not
// retail's. #pragma optimize("", off) leaves the helper's own codegen at the
// command line's /O2 and de-optimises only the function below.

#include <algorithm>

struct BfmeTag82DD70
{
};

#pragma optimize("", off)
char *bfmeFillCount82DD70(char *first, unsigned count, const char &value)
{
	BfmeTag82DD70();

	_STL::fill(first, first + count, value);
	return first + count;
}
