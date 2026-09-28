// cl: /O2 /MD
class Rva008C5FD0Zero
{
public:
	Rva008C5FD0Zero();

private:
	unsigned int m_words[22];
};

extern "C" int __cdecl atexit(void (__cdecl *callback)());
void bfmeForward_00C70F80(void);

struct Rva008AE770Stack : Rva008C5FD0Zero
{
	__forceinline Rva008AE770Stack()
	{
		atexit(bfmeForward_00C70F80);
	}
};

Rva008AE770Stack Rva008AE770TheStack;
