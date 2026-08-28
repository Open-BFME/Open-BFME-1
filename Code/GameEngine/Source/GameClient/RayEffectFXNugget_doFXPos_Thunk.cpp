// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction of BFME's ray-effect position dispatch.

typedef float Real;

class AsciiString
{
private:
	void *m_data;
};

struct Coord3D
{
	Coord3D(const Coord3D &that) : x(that.x), y(that.y), z(that.z) {}

	Real x;
	Real y;
	Real z;
};

class Matrix3D;
class ThingTemplate;

class ThingFactory
{
public:
	ThingTemplate *findTemplate(const AsciiString &name);
};

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

class RayEffectFXNugget
{
public:
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx,
		Real primarySpeed, const Coord3D *secondary) const;

private:
	unsigned char m_pad[0xB0];
	AsciiString m_templateName;
	Coord3D m_primaryOffset;
	Coord3D m_secondaryOffset;
};

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
