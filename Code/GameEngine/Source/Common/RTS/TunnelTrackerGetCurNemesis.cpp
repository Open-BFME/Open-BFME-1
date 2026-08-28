// cl: /DNDEBUG /MD /EHsc
// readable body of ?getCurNemesis@TunnelTracker@@: Code/GameEngine/Source/Common/RTS/TunnelTracker.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	bool isEffectivelyDead() const { return (m_privateStatus & 1) != 0; }

private:
	unsigned char m_pad_000[0x344];
	unsigned char m_privateStatus;
};

// Retail's helper name is unavailable, so this TU-specific ABI name preserves
// the proven Object-pointer call shape without claiming its canonical identity.
class BFMEObjectStealthQuery
{
public:
	bool isStealthedAndUndetected(const Object *viewer) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
	Object *findObjectByID(int id);

private:
	unsigned char m_pad_000[0x3c];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/TunnelTracker.h
class TunnelTracker
{
public:
	Object *getCurNemesis();

private:
	unsigned char m_pad_000[0x18];
	int m_curNemesisID;
	unsigned int m_nemesisTimestamp;
};

Object *TunnelTracker::getCurNemesis()
{
	if (m_curNemesisID == 0)
		return 0;

	if (m_nemesisTimestamp + 20 < TheGameLogic->getFrame()) {
		m_curNemesisID = 0;
		return 0;
	}

	Object *target = TheGameLogic->findObjectByID(m_curNemesisID);
	if (target != 0 &&
		(((BFMEObjectStealthQuery *)target)->isStealthedAndUndetected(0) ||
		 target->isEffectivelyDead()))
		target = 0;

	if (target == 0)
		m_curNemesisID = 0;

	return target;
}
