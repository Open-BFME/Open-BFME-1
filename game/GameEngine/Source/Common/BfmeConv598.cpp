// cl: /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Iinputs/reference/shims/sweep
#include "../../../Libraries/Source/WWVegas/WW3D2/part_emt.h"

class BfmeThingCGE
{
public:
	virtual void bfmeSpareCGE0();
	virtual void bfmeSpareCGE1();
	virtual void bfmeSpareCGE2();
	virtual void bfmeSpareCGE3();
	virtual void bfmeSpareCGE4();
	virtual void bfmeSpareCGE5();
	virtual void bfmeSpareCGE6();
	virtual void bfmeSpareCGE7();
	virtual void bfmeSpareCGE8();
	virtual void bfmeSpareCGE9();
	virtual bool bfmeAskCGE();
	virtual void bfmeStepCGE();
	int bfmeGoCGE();
	unsigned char m_bfmeGap[0x10];
	ParticleEmitterDefClass *m_bfmeSub;
};

int BfmeThingCGE::bfmeGoCGE()
{
	if (!bfmeAskCGE())
		bfmeStepCGE();
	// Retail calls ParticleEmitterClass::Create_From_Definition (0x0097F5D0),
	// the static member taking the definition by const reference.
	ParticleEmitterDefClass *def = m_bfmeSub;
	if (def == 0)
		return 0;
	return (int)ParticleEmitterClass::Create_From_Definition(*def);
}