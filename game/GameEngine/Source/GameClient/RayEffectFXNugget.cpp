// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail construction and dispatch establish the 0xB4 base and four-argument positional ABI.

typedef float Real;

#include "ascii_string.h"

struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}

	Real x;
	Real y;
	Real z;
};

class Matrix3D;
class Object;
class ThingTemplate;

// reference interface: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

// reference interface: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void createRayEffectByTemplate(
		const Coord3D *source, const Coord3D *target, const ThingTemplate *thingTemplate);
};

extern ThingFactory *TheThingFactory;
extern GameClient *TheGameClient;

class FXNugget
{
public:
	FXNugget();
	virtual ~FXNugget();
	virtual void doFXPos(const Coord3D *, const Matrix3D *, Real, const Coord3D *) const;
	virtual void doFXObj(const Object *, const Object *) const;

protected:
	int m_nuggetType;

private:
	unsigned char m_bfmeBaseData[0xAC];
};

class RayEffectFXNugget : public FXNugget
{
public:
	RayEffectFXNugget();
	virtual ~RayEffectFXNugget();
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx,
		Real primarySpeed, const Coord3D *secondary) const;

private:
	AsciiString m_templateName;
	Coord3D m_primaryOffset;
	Coord3D m_secondaryOffset;
};

RayEffectFXNugget::RayEffectFXNugget()
{
	m_templateName.clear();
	m_primaryOffset.x = m_primaryOffset.y = m_primaryOffset.z = 0;
	m_secondaryOffset.x = m_secondaryOffset.y = m_secondaryOffset.z = 0;
	m_nuggetType = 2;
}

void RayEffectFXNugget::doFXPos(const Coord3D *primary, const Matrix3D *,
	Real, const Coord3D *secondary) const
{
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(m_templateName);
	if (primary && secondary && thingTemplate)
	{
		Coord3D sourcePosition = *primary;
		sourcePosition.x += m_primaryOffset.x;
		sourcePosition.y += m_primaryOffset.y;
		sourcePosition.z += m_primaryOffset.z;

		Coord3D targetPosition = *secondary;
		targetPosition.x += m_secondaryOffset.x;
		targetPosition.y += m_secondaryOffset.y;
		targetPosition.z += m_secondaryOffset.z;

		TheGameClient->createRayEffectByTemplate(
			&sourcePosition, &targetPosition, thingTemplate);
	}
}
