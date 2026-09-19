// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: HordeSiegeEngineContain constructor.  The named factory and
// destructor fix the HordeTransport base and three STLport members.

#include <list>
#include <map>

class Thing;
class ModuleData;

class Object
{
public:
	void notifyModelConditionChanged();
private:
	unsigned char m_pad[0x128];
public:
	union
	{
		unsigned int m_status;
		unsigned char m_statusByte;
	};
};

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();
protected:
	unsigned int m_04;
	Object *m_object;
};

template <int Number> class __declspec(novtable) HordeTransportIface
{ public: virtual void slot() = 0; };

class __declspec(novtable) HordeTransportWideIface
{
public:
	virtual void slot() = 0;
private:
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class __declspec(novtable) HordeTransportPaddedIface
{
public:
	virtual void slot() = 0;
private:
	unsigned char m_pad[0x9c];
};

class HordeTransportContainBase : public BehaviorModule
{
public:
	HordeTransportContainBase(Thing *, const ModuleData *);
};

class HordeTransportContain : public HordeTransportContainBase,
	public HordeTransportIface<1>, public HordeTransportWideIface,
	public HordeTransportIface<2>, public HordeTransportIface<3>,
	public HordeTransportIface<4>, public HordeTransportIface<5>,
	public HordeTransportIface<6>, public HordeTransportPaddedIface,
	public HordeTransportIface<7>
{
public:
	HordeTransportContain(Thing *, const ModuleData *);
	virtual ~HordeTransportContain();
protected:
	unsigned char m_unreconstructed_d8[0x0c];
	int m_e4;
	bool m_e8;
};

struct Gen_t_00223550_p4pod { int a[1]; };
bool operator==(const Gen_t_00223550_p4pod&, const Gen_t_00223550_p4pod&);
bool operator<(const Gen_t_00223550_p4pod&, const Gen_t_00223550_p4pod&);

class HordeSiegeEngineContain : public HordeTransportContain
{
public:
	HordeSiegeEngineContain(Thing *, const ModuleData *);
	virtual ~HordeSiegeEngineContain();
private:
	_STL::list<int> m_listA;
	int m_f0;
	bool m_f4;
	unsigned char m_padf5[3];
	_STL::map<int, Gen_t_00223550_p4pod> m_map;
	_STL::list<int> m_listB;
};

// ??0HordeSiegeEngineContain@@QAE@PAVThing@@PBVModuleData@@@Z
HordeSiegeEngineContain::HordeSiegeEngineContain(Thing *thing, const ModuleData *data)
	: HordeTransportContain(thing, data)
{
	Object *object = m_object;
	m_f0 = 0;
	m_f4 = false;
	unsigned int statusBit = 0x40;
	if ((object->m_statusByte & statusBit) == 0)
	{
		object->m_status |= statusBit;
		object->notifyModelConditionChanged();
	}
}
