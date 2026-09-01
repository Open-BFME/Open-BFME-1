// ?d_0076caf0@@YAXXZ
// partial score=0.95 date=2026-08-31
// Clean reconstruction of the small stale-stamp dispatcher at 0x0076CAF0.

extern int g_Va012F8064;
void j_00024f5a(void);

class Rva0076CAF0ConditionalDispatch
{
public:
	void dispatchIfStale(void);

private:
	unsigned char reserved[0x9c];
	int stamp;
};

void Rva0076CAF0ConditionalDispatch::dispatchIfStale(void)
{
	if (g_Va012F8064 != stamp) {
		j_00024f5a();
	}
}
