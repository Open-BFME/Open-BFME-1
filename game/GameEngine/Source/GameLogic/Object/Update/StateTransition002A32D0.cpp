// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x002A32D0 (463 bytes), an update-interface receiver at module+0x10.
// Negative offsets address the complete module's data (+4) and Object (+8).
// The complete owner/method identity is deliberately not guessed.
// Virtual slots are offsets witnessed in this body, not semantic names.
// Typed member-pointer unions bind existing ILT symbols without inventing
// callee identities: 1dd7c->2A1780 returns Object*; 2bdfa->1D27F0 takes a
// Coord3D pointer; 1a9dd->1B6EB0 takes a 40-byte mask; 3a279->383930 takes
// Object* and an integer. The last route's current ledger name omits args.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
struct Coord3D
{
	float x, y, z;
};
template <unsigned N> class BitFlags
{
	_STL::bitset<N> bits;
};
class Object;
class Player;
enum DisabledType
{
	Disabled4 = 4
};
enum ObjectStatusTypes
{
	Status3 = 3
};
class ExitInterface
{
  public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08(Object *, int);
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24(Coord3D *, bool);
};
class Object
{
  public:
	void clearModelConditionFlags(const BitFlags<304> &);
	void clearStatus(ObjectStatusTypes);
	bool clearDisabled(DisabledType);
	ExitInterface *getObjectExitInterface() const;
	void setDisabledUntil(DisabledType, unsigned);
	Player *getControllingPlayer() const;
};
class FXList
{
  public:
	bool bfmeIsBlocked();
	void doFXObj(const Object *, const Object *) const;
};
class GameLogic
{
  public:
	Object *findObjectByID(int);
	char m_pad00[0x3c];
	unsigned m_frame;
};
class PlayerList
{
  public:
	char m_pad00[12];
	Player *m_local;
};
class ControlBar
{
  public:
	char m_pad00[0x24];
	bool m_UIDirty;
};
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
extern ControlBar *TheControlBar;
struct StateData002A32D0
{
	char m_pad00[0x34];
	BitFlags<304> flags34, flags5c;
	FXList *fx84;
	FXList *fx88;
	char m_pad8c[8];
	unsigned m_f94;
};
class Body002A32D0
{
  public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4c();
	virtual void v50();
	virtual void v54(float, int);
};
class AI002A32D0
{
  public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4c();
	virtual void v50();
	virtual void v54();
	virtual void v58();
	virtual void v5c();
	virtual void v60();
	virtual void v64();
	virtual void v68();
	virtual void v6c();
	virtual void v70();
	virtual void v74();
	virtual void v78();
	virtual void v7c();
	virtual void v80();
	virtual void v84();
	virtual void v88();
	virtual void v8c();
	virtual void v90();
	virtual void v94();
	virtual void v98();
	virtual void v9c();
	virtual void va0();
	virtual void va4();
	virtual void va8();
	virtual void vac();
	virtual void vb0();
	virtual void vb4();
	virtual void vb8();
	virtual void vbc();
	virtual void vc0();
	virtual void vc4();
	virtual void vc8();
	virtual void vcc();
	virtual void vd0();
	virtual void vd4();
	virtual void vd8();
	virtual void vdc();
	virtual void ve0();
	virtual void ve4();
	virtual void ve8();
	virtual void vec();
	virtual void vf0();
	virtual void vf4();
	virtual void vf8();
	virtual void vfc();
	virtual void v100();
	virtual void v104();
	virtual void v108();
	virtual void v10c();
	virtual void v110();
	virtual void v114();
	virtual void v118();
	virtual void v11c();
	virtual void v120();
	virtual void v124();
	virtual void v128();
	virtual void v12c();
	virtual void v130();
	virtual void v134();
	virtual void v138();
	virtual void v13c();
	virtual void v140();
	virtual void v144();
	virtual void v148();
	virtual void v14c();
	virtual void v150();
	virtual void v154();
	virtual void v158();
	virtual void v15c();
	virtual void v160();
	virtual void v164();
	virtual void v168();
	virtual void v16c();
	virtual void v170();
	virtual void v174();
	virtual void v178();
	virtual void v17c();
	virtual bool v180();
};
struct ObjectFields002A32D0
{
	char m_pad00[0x38];
	Coord3D position;
	char m_pad44[0x78 - 0x44];
	int m_producerID;
	char m_pad7c[0x200 - 0x7c];
	Body002A32D0 *body;
	AI002A32D0 *ai;
	char m_pad208[0x370 - 0x208];
	int f370;
};
struct ModuleFields002A32D0
{
	void *vptr;
	StateData002A32D0 *data;
	Object *object;
	char m_pad0c[0x20 - 12];
	float m_f20;
	char m_pad24[8];
	int m_f2c;
	int m_f30, m_f34, m_f38;
};
extern void j_0001dd7c();
extern void j_0002bdfa();
extern void j_0003a279();
extern void j_0001a9dd();
class StateTransition002A32D0
{
  public:
	unsigned update();
	char m_pad00[16];
	float m_f20;
	char m_pad14[8];
	int m_f2c, m_f30, m_f34, m_f38;
};
unsigned StateTransition002A32D0::update()
{

	StateData002A32D0 *data = *(StateData002A32D0 **)((char *)this - 12);
	Object *object = *(Object **)((char *)this - 8);
	ObjectFields002A32D0 *fields = (ObjectFields002A32D0 *)object;
	switch (m_f2c)
	{
	case 2:
		return 0x3fffffff;
	case 3: {
		Object *source = TheGameLogic->findObjectByID(m_f30);
		if (!source)
		{
			ModuleFields002A32D0 *self = (ModuleFields002A32D0 *)((char *)this - 16);
			union {
				void (*f)();
				Object *(ModuleFields002A32D0::*m)();
			} c;
			c.f = j_0001dd7c;
			source = (self->*c.m)();
		}
		Coord3D position;
		position.x = fields->position.x;
		position.y = fields->position.y;
		position.z = fields->position.z;
		if (source)
		{
			position = ((ObjectFields002A32D0 *)source)->position;
			ExitInterface *exit = source->getObjectExitInterface();
			if (exit)
				exit->slot24(&position, true);
		}
		{
			union {
				void (*f)();
				void (Object::*m)(const Coord3D *);
			} c;
			c.f = j_0002bdfa;
			(object->*c.m)(&position);
		}
		{
			union {
				void (*f)();
				void (Object::*m)(const BitFlags<304> &);
			} c;
			c.f = j_0001a9dd;
			(object->*c.m)(data->flags34);
		}
		const FXList *fx = data->fx88;
		if (fx && !const_cast<FXList *>(fx)->bfmeIsBlocked())
			fx->doFXObj(object, 0);
		object->setDisabledUntil(Disabled4, TheGameLogic->m_frame + data->m_f94);
		m_f2c = 4;
		fields->body->v54(m_f20 * 100.0f, 0);
		m_f34 = -1;
		m_f38 = -1;
		Player *local = ThePlayerList->m_local;
		if (local == object->getControllingPlayer())
			TheControlBar->m_UIDirty = true;
		object->getControllingPlayer();
		return data->m_f94;
	}
	case 4: {
		object->clearModelConditionFlags(data->flags34);
		object->clearModelConditionFlags(data->flags5c);
		object->clearStatus(Status3);
		object->clearDisabled(Disabled4);
		m_f2c = 0;
		Object *source = TheGameLogic->findObjectByID(fields->m_producerID);
		AI002A32D0 *ai = ((ObjectFields002A32D0 *)(*(Object **)((char *)this - 8)))->ai;
		if (source && ai)
		{
			if (ai->v180())
			{
				ExitInterface *exit = source->getObjectExitInterface();
				if (exit)
				{
					int id = fields->f370;
					exit->slot08(object, 0);
					if (id != -1)
					{
						union {
							void (*f)();
							void (GameLogic::*m)(Object *, int);
						} c;
						c.f = j_0003a279;
						(TheGameLogic->*c.m)(object, id);
					}
				}
			}
		}
		break;
	}
	}
	return 0x3fffffff;
}
