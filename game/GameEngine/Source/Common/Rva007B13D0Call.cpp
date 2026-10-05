// cl: /O2 /Ob0

struct Rva007AFB50Shadow;

class W3DProjectedShadowManager
{
public:
	void rva007AFB50(Rva007AFB50Shadow *);
};

extern W3DProjectedShadowManager *TheW3DProjectedShadowManager;

class Rva007B13D0
{
public:
	void run();
};

void Rva007B13D0::run()
{
	TheW3DProjectedShadowManager->rva007AFB50(reinterpret_cast<Rva007AFB50Shadow *>(this));
}
