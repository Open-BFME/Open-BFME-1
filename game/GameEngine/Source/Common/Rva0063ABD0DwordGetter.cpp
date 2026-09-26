// The carved body reads the first dword from its receiver.

struct Rva0063ABD0DwordGetter
{
	unsigned int value;

	unsigned int get();
};

unsigned int Rva0063ABD0DwordGetter::get()
{
	return value;
}
