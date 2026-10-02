// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern unsigned int g_rva0075b2e0_value;

class Rva0076CAF0ConditionalDispatch
{
public:
	void dispatchIfStale(void);
	void target(void);

private:
	unsigned char reserved[0x9c];
	int stamp;
};

// ?dispatchIfStale@Rva0076CAF0ConditionalDispatch@@QAEXXZ
void Rva0076CAF0ConditionalDispatch::dispatchIfStale(void)
{
	if (g_rva0075b2e0_value != (unsigned int)stamp) {
		target();
	}
}
