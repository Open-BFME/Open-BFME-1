// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern unsigned int g_rva0075b2e0_value;

// Tail target: ILT 0x00024F5F -> 0x0076C080, matched as
// ?advanceAnimation@Rva0076C080@@QAEXXZ on the same object.
class Rva0076C080
{
public:
	void advanceAnimation();
};

class Rva0076CAF0ConditionalDispatch
{
public:
	void dispatchIfStale(void);

private:
	unsigned char reserved[0x9c];
	int stamp;
};

// ?dispatchIfStale@Rva0076CAF0ConditionalDispatch@@QAEXXZ
void Rva0076CAF0ConditionalDispatch::dispatchIfStale(void)
{
	if (g_rva0075b2e0_value != (unsigned int)stamp) {
		((Rva0076C080 *)this)->advanceAnimation();
	}
}
