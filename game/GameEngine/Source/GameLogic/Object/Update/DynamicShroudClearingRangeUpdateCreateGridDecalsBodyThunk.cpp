// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

struct Coord3D;
class Player;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameEngine/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecal
{
public:
	void clear();
	void setPosition(const Coord3D &);

private:
	const void *m_template;
	void *m_decal;
	unsigned char m_empty;
	unsigned char m_padding[4];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecalTemplate
{
public:
	void createRadiusDecal(const Coord3D &, float, const Player *, RadiusDecal &) const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
protected:
	Object *getObject() const { return m_object; }

private:
	unsigned char m_header[8];
	Object *m_object;
	unsigned char m_state[0x14];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DynamicShroudClearingRangeUpdate.h
class DynamicShroudClearingRangeUpdate : public UpdateModule
{
public:
	void createGridDecals(const RadiusDecalTemplate &, float, const Coord3D &);

private:
	unsigned char m_stateData[0x30];
	RadiusDecal m_gridDecal[30];
};

// ?createGridDecals@DynamicShroudClearingRangeUpdate@@QAEXABVRadiusDecalTemplate@@MABUCoord3D@@@Z
void DynamicShroudClearingRangeUpdate::createGridDecals(
	const RadiusDecalTemplate &tmpl, float radius, const Coord3D &position)
{
	for (int decal = 0; decal < 30; ++decal)
	{
		m_gridDecal[decal].clear();
		tmpl.createRadiusDecal(position, radius,
			getObject()->getControllingPlayer(), m_gridDecal[decal]);
		m_gridDecal[decal].setPosition(position);
	}
}
