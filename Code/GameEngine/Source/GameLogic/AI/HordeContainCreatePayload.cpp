// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME: HordeContain initial payload cleanup, retail 0x0023C000.

#define _STLP_USE_NEWALLOC 1

typedef bool Bool;
typedef unsigned int UnsignedInt;

#include <list>

class Object;
class ContainModuleInterface;

class HordeContainInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04(Bool enabled);
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void destroyMember(Object *member);
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void slot92();
	virtual void slot93();
	virtual void slot94();
	virtual void slot95();
	virtual void slot96();
	virtual void slot97();
	virtual void slot98();
	virtual void slot99();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
	virtual void slot104();
	virtual void slot105();
	virtual void slot106();
	virtual void slot107();
	virtual void slot108();
	virtual void slot109();
	virtual void slot110();
	virtual void finish();
};

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual HordeContainInterface *getHordeContainInterface();
};

class Object
{
public:
	UnsignedInt getProducerID() const { return m_producerID; }

	char m_pad00[0x78];
	UnsignedInt m_producerID;
	char m_pad7c[0x1fc - 0x7c];
	ContainModuleInterface *m_contain;
	void *m_body;
	void *getBodyModule() const { return m_body; }
};

class GameLogic
{
public:
	void destroyObject(Object *object);
};

extern GameLogic *TheGameLogic;

class OpenContainPrimaryBase
{
public:
	virtual void behaviorModuleAnchor();

	Object *getObject() const { return m_object; }

protected:
	unsigned int m_04;
	Object *m_object;
};

class OpenContainBehaviorInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual ContainModuleInterface *getContain();
};

class TransportContainIface2
{
public:
	virtual void slot00();
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class TransportContainIface3 { public: virtual void slot00(); };
class TransportContainIface4 { public: virtual void slot00(); };
class TransportContainIface5 { public: virtual void slot00(); };
class TransportContainIface6 { public: virtual void slot00(); };
class TransportContainIface7 { public: virtual void slot00(); };
class TransportContainIface8 { public: virtual void slot00(); };

class __declspec(novtable) OpenContain : public OpenContainPrimaryBase,
	public OpenContainBehaviorInterface,
	public TransportContainIface2,
	public TransportContainIface3,
	public TransportContainIface4,
	public TransportContainIface5,
	public TransportContainIface6,
	public TransportContainIface7,
	public TransportContainIface8
{
	public:
	const _STL::list<Object *> &getContainList() const { return m_members; }

protected:
	_STL::list<Object *> m_members;
	char m_pad3c[0xd4 - 0x3c];
};

class TransportContainIface9 { public: virtual void slot00(); };

class TransportContainFields
{
	unsigned int m_d8;
	unsigned int m_dc;
	bool m_e0;
};

class __declspec(novtable) SiegeEngineContainBase : public OpenContain,
	public TransportContainIface9,
	public TransportContainFields
{
	public:
	virtual ~SiegeEngineContainBase();
};

class HordeContainEleventhBase
	: public HordeContainInterface
{
};

extern void j_0003a355();

class __declspec(novtable) HordeContain : public SiegeEngineContainBase, public HordeContainEleventhBase
{
	protected:
	virtual void createPayload();

private:
	char m_padE8[0x200 - 0xe8];
	int m_damagePercent;
};

void HordeContain::createPayload()
{
	if (!getObject()->getProducerID())
	{
		j_0003a355();

		HordeContainInterface *horde = (HordeContainInterface *)((char *)this + 0xe4);
		horde->slot04(false);

		ContainModuleInterface *contain = getContain();
		if (contain && getContain()->getHordeContainInterface())
		{
			_STL::list<Object *> members = getContainList();
			UnsignedInt count = members.size();

			int toDestroy = (int)(((double)(100 - m_damagePercent) * 0.01) * count);
			if (toDestroy < members.size() && toDestroy > 0)
			{
				Object *member;
				_STL::list<Object *>::iterator it = members.begin();
				while (it != members.end())
				{
					member = *it;
					if (member->getBodyModule() && toDestroy)
					{
						horde->destroyMember(member);
						TheGameLogic->destroyObject(member);
						--toDestroy;
					}
					++it;
				}
			}
		}

		horde->finish();
	}
}
