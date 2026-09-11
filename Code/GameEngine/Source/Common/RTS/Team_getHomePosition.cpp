// cl: /DNDEBUG /MD /EHsc

typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// BFME keeps the TeamTemplateInfo inside TeamPrototype.  The retail offsets
// below are the fields shared with the authoritative Zero Hour layout:
// m_homeLocation followed by m_hasHomeLocation.
class TeamTemplateInfoView
{
public:
	unsigned char m_head[0x5c];
	Coord3D m_homeLocation;
	bool m_hasHomeLocation;
};

class TeamPrototypeView
{
public:
	unsigned char m_head[0x12c];
	TeamTemplateInfoView m_teamTemplate;
};

class Team
{
public:
	Coord3D *getHomePosition(Coord3D *out);
	Coord3D *getEstimateTeamPosition(Coord3D *out) const;

	void *m_vptr;
	TeamPrototypeView *m_prototype;
};

Coord3D *Team::getHomePosition(Coord3D *out)
{
	TeamTemplateInfoView *info = &m_prototype->m_teamTemplate;
	if (info != 0 && info->m_hasHomeLocation)
	{
		out->x = info->m_homeLocation.x;
		out->y = info->m_homeLocation.y;
		out->z = info->m_homeLocation.z;
		return out;
	}

	getEstimateTeamPosition(out);
	return out;
}
