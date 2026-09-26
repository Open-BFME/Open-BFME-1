// cl: /Od
// A count-form fill forwarded to the range-form one, built without
// optimisation. The empty tag is constructed and dropped -- a dispatch witness,
// not a value -- and it has to be the bare temporary: give it a name and it
// takes a second frame byte, moving the zero store from ebp-1 to ebp-2.

struct BfmeTag82DD70
{
};

void rva0082ADB0Fill(char *first, char *last, const char &value);

char *bfmeFillCount82DD70(char *first, unsigned count, const char &value)
{
	BfmeTag82DD70();

	rva0082ADB0Fill(first, first + count, value);
	return first + count;
}
