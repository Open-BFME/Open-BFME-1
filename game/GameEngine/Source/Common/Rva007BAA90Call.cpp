// cl: /O2 /Ob0

class Rva007BAA90G
{
public:
	void bar(void *);
};

void j_00047f46();

Rva007BAA90G *g_rva007baa90;

class Rva007BAA90
{
public:
	void run();
};

void Rva007BAA90::run()
{
	typedef void (Rva007BAA90G::*BarCall)(void *);
	union { void *address; BarCall member; } call;
	call.address = (void *)j_00047f46;
	(g_rva007baa90->*call.member)(this);
}
