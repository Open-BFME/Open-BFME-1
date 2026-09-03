// cl: /DNDEBUG /MD /EHsc
// readable body of ?getCurrentLaserRadius@LaserUpdate@@: Code/GameEngine/Source/GameLogic/Object/Update/LaserUpdate.cpp
//
// LaserUpdate::getCurrentLaserRadius — retail 0x00603A00 (63B).
// Zero Hour source: GeneralsMD/.../LaserUpdate.cpp
// Walk the drawable's DrawModule list for LaserDrawInterface and return
// getLaserTemplateWidth() * m_currentWidthScalar, else 0.0f.
// Const getDrawModules is the ILT at 0x00040A8E (ICF twin of the non-const
// getter at 0x00021472); both are `mov eax,[ecx+0x150]; ret`.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
class LaserDrawInterface
{
public:
	virtual float getLaserTemplateWidth() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DrawModule.h
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
	virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39();
	virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43();
	virtual LaserDrawInterface *getLaserDrawInterface() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void **getDrawModules() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LaserUpdate.h
class LaserUpdate
{
public:
	float getCurrentLaserRadius() const;

private:
	char m_pad00[8];
	Drawable *m_drawable;
	char m_pad0C[0x3C - 0x0C];
	float m_currentWidthScalar;
};

// ?getCurrentLaserRadius@LaserUpdate@@QBEMXZ
float LaserUpdate::getCurrentLaserRadius() const
{
	const Drawable *draw = m_drawable;
	for (DrawModule **d = (DrawModule **)draw->getDrawModules(); *d; ++d)
	{
		LaserDrawInterface *ldi = (*d)->getLaserDrawInterface();
		if (ldi)
			return ldi->getLaserTemplateWidth() * m_currentWidthScalar;
	}
	return 0.0f;
}
