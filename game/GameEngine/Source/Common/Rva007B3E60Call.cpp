// cl: /O2 /Ob0

class Rva007B3E60G
{
public:
	void bar(void *);
};

void j_000247fd();

class W3DProjectedShadowManager;
extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;

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
	(reinterpret_cast<Rva007B3E60G *>(TheW3DProjectedShadowManager)->*call.member)(this);
}
