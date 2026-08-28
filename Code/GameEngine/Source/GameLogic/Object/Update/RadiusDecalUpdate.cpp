// cl: /DNDEBUG /MD /EHsc

struct Coord3D;
class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecal
{
public:
	void clear();

private:
	const void *m_template;
	void *m_decal;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecalTemplate
{
public:
	void createRadiusDecal(const Coord3D &, float, const Player *, RadiusDecal &) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
protected:
	Object *getObject() const { return m_object; }
	void setWakeFrame(Object *, unsigned int);

private:
	char m_header[8];
	Object *m_object;
	char m_updateState[0x14];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadiusDecalUpdate.h
class RadiusDecalUpdate : public UpdateModule
{
public:
	void createRadiusDecal(const RadiusDecalTemplate &, float, const Coord3D &);
	void killRadiusDecal();

private:
	RadiusDecal m_deliveryDecal;
	bool m_killWhenNoLongerAttacking;
};

void RadiusDecalUpdate::createRadiusDecal(const RadiusDecalTemplate &tmpl, float radius, const Coord3D &pos)
{
	m_deliveryDecal.clear();
	tmpl.createRadiusDecal(pos, radius, getObject()->getControllingPlayer(), m_deliveryDecal);
	setWakeFrame(getObject(), m_killWhenNoLongerAttacking ? 0x3FFFFFFF : 1);
}

// ?killRadiusDecal@RadiusDecalUpdate@@QAEXXZ
void RadiusDecalUpdate::killRadiusDecal()
{
	m_deliveryDecal.clear();
	setWakeFrame(getObject(), 0x3FFFFFFF);	// UPDATE_SLEEP_FOREVER
}
