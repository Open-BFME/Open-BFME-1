// cl: /O2 /Ob0

class Rva007B3E60G
{
public:
	void bar(void *);
};

void j_000247fd();

Rva007B3E60G *g_rva007b3e60;

class Rva007B3E60
{
public:
	void run();
};

void Rva007B3E60::run()
{
	typedef void (Rva007B3E60G::*BarCall)(void *);
	union { void *address; BarCall member; } call;
	call.address = (void *)j_000247fd;
	(g_rva007b3e60->*call.member)(this);
}
