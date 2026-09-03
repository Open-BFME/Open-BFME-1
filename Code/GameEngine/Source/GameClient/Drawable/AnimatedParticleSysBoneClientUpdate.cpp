// cl: /DNDEBUG /MD /EHsc
//
// AnimatedParticleSysBoneClientUpdate::clientUpdate — retail 0x00603020 (61B).
// Zero Hour source: GeneralsMD/.../AnimatedParticleSysBoneClientUpdate.cpp
// ++m_life, then walk the drawable's DrawModule list for ObjectDrawInterface
// and stop on the first updateBonesForClientParticleSystems that returns true.
// BFME's interface takes a trailing int (retail push 0); ZH has none.

class ObjectDrawInterface
{
public:
	virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
	virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
	virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
	virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
	virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
	virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
	virtual void p24(); virtual void p25();
	virtual bool updateBonesForClientParticleSystems(int);
};

class DrawModule
{
public:
	virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
	virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
	virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
	virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
	virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
	virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
	virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27();
	virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31();
	virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35();
	virtual void p36(); virtual void p37(); virtual void p38();
	virtual ObjectDrawInterface *getObjectDrawInterface();
};

class Drawable
{
public:
	void **getDrawModules();
};

class AnimatedParticleSysBoneClientUpdate
{
public:
	virtual void clientUpdate();

private:
	void *m_moduleData;
	Drawable *m_drawable;
	unsigned m_life;
};

// ?clientUpdate@AnimatedParticleSysBoneClientUpdate@@UAEXXZ
void AnimatedParticleSysBoneClientUpdate::clientUpdate()
{
	++m_life;
	Drawable *draw = m_drawable;
	if (draw)
	{
		for (DrawModule **dm = (DrawModule **)draw->getDrawModules(); *dm; ++dm)
		{
			ObjectDrawInterface *di = (*dm)->getObjectDrawInterface();
			if (di)
			{
				if (di->updateBonesForClientParticleSystems(0))
					break;
			}
		}
	}
}
