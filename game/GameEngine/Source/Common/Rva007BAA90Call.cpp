// cl: /O2 /Ob0

class Rva007BAA90G
{
public:
	void bar(void *);
};

void j_00047f46();

class W3DVolumetricShadowManager;
extern W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;

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
	(((Rva007BAA90G *)TheW3DVolumetricShadowManager)->*call.member)(this);
}
