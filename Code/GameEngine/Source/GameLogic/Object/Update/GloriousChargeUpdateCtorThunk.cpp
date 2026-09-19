// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <list>

class Thing;
class ModuleData;

class GloriousChargeUpdateRootBase
{
public:
	virtual ~GloriousChargeUpdateRootBase();
private:
	unsigned char m_pad[8];
};

class GloriousChargeUpdateBaseInterface1
{
public:
	virtual void slot();
};

class GloriousChargeUpdateBaseInterface2
{
public:
	virtual void slot();
private:
	unsigned char m_pad[0xC];
};

class GloriousChargeUpdateObjectModule : public GloriousChargeUpdateRootBase {};

class GloriousChargeUpdateBehaviorModule : public GloriousChargeUpdateObjectModule,
	public GloriousChargeUpdateBaseInterface1
{
public:
	virtual ~GloriousChargeUpdateBehaviorModule() {}
};

class GloriousChargeUpdateUpdateModule : public GloriousChargeUpdateBehaviorModule,
	public GloriousChargeUpdateBaseInterface2
{
public:
	virtual ~GloriousChargeUpdateUpdateModule() {}
};

class GloriousChargeUpdateSpecialPowerUpdateInterface
{
public:
	virtual void slot();
};

class GloriousChargeSpecialAbilityUpdate : public GloriousChargeUpdateUpdateModule,
	public GloriousChargeUpdateSpecialPowerUpdateInterface
{
public:
	GloriousChargeSpecialAbilityUpdate(Thing *, const ModuleData *);
	virtual ~GloriousChargeSpecialAbilityUpdate();
private:
	unsigned char m_pad[0xC4];
};

class GloriousChargeUpdate : public GloriousChargeSpecialAbilityUpdate
{
public:
	GloriousChargeUpdate(Thing *, const ModuleData *);
	virtual ~GloriousChargeUpdate();
private:
	_STL::list<int> m_specialObjectIDList;
	unsigned int m_frame;
	bool m_active;
};

GloriousChargeUpdate::GloriousChargeUpdate(Thing *thing, const ModuleData *data) :
	GloriousChargeSpecialAbilityUpdate(thing, data),
	m_specialObjectIDList(),
	m_frame(0),
	m_active(false)
{
	m_specialObjectIDList.clear();
}
