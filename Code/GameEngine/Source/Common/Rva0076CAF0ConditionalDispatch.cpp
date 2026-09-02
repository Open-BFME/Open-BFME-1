// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern int g_Va012F8064;

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
	if (g_Va012F8064 != stamp) {
		target();
	}
}
