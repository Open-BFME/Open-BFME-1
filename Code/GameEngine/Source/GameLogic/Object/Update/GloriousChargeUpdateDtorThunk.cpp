// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <list>

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

class GloriousChargeUpdateObjectModule : public GloriousChargeUpdateRootBase
{
};

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdate : public GloriousChargeUpdateUpdateModule,
	public GloriousChargeUpdateSpecialPowerUpdateInterface
{
public:
	virtual ~SpecialAbilityUpdate();

private:
	unsigned char m_pad[0xC4];
};

class GloriousChargeUpdate : public SpecialAbilityUpdate
{
public:
	virtual ~GloriousChargeUpdate();

private:
	_STL::list<int> m_specialObjectIDList;
};

// ??1GloriousChargeUpdate@@UAE@XZ
GloriousChargeUpdate::~GloriousChargeUpdate()
{
	m_specialObjectIDList.clear();
}
