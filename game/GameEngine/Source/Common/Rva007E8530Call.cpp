// cl: /O2 /Ob0

void __stdcall rva007e8530_bar(void *self, void *g);

void *g_rva007e8530;

class Rva007E8530
{
public:
	void run();
};

void Rva007E8530::run()
{
	rva007e8530_bar(this, g_rva007e8530);
}
