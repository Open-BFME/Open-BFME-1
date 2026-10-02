// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Source/GameLogic/Object
// stlport
// Retail 0x002A30D0 (399 bytes). The method identity remains opaque.
// Level-record layout is shared with the landed 0x002A23B0 lookup; the
// 0x002A2750/0x002A2B20 parser literals independently identify record fields.
// ObjectStatusBits.h lacks the other Object methods this body calls, so
// this TU retains its native BitFlags representation with a minimal Object.
// Use native bitset initialization: an explicit zero loop changes allocation.

#include <set>
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
// ObjectStatusBits.h defines a narrower Object without the methods below.
// Its BitFlags representation and kInit constructor are retained here.
template <int N> class BitFlags
{
	_STL::bitset<N> bits;

  public:
	enum Init
	{
		kInit
	};
	BitFlags()
	{
	}
	BitFlags(Init, int bit)
	{
		bits.set(bit);
	}
};
class Player;
class BfmeConditionFlags;
enum DisabledType
{
	Disabled4 = 4
};
class Object
{
  public:
	void clearAndSetModelConditionFlags(const BfmeConditionFlags &, const BfmeConditionFlags &);
	void setStatus(const BitFlags<86> &, bool);
	void setDisabled(DisabledType);
	void setEffectivelyDead(bool);
	Player *getControllingPlayer() const;
};
#define MAKE_OBJECT_STATUS_MASK(k) BitFlags<86>(BitFlags<86>::kInit, k)
struct Rva002A23B0Record
{
	unsigned level;
	int m_cost, m_time;
	float m_health;
	bool m_autoSpawn;
	Rva002A23B0Record(unsigned v)
		: level(v), m_cost(0), m_time(0), m_health(1.0f), m_autoSpawn(false)
	{
	}
	bool operator<(const Rva002A23B0Record &v) const
	{
		return level < v.level;
	}
};
typedef _STL::set<Rva002A23B0Record> Records;
class BfmeConditionFlags
{
	_STL::bitset<304> bits;

  public:
	BfmeConditionFlags()
	{
	}
};
class FXList
{
  public:
	bool bfmeIsBlocked();
	void doFXObj(const Object *, const Object *) const;
};
struct Rva002A30D0Data
{
	char m_pad00[12];
	BfmeConditionFlags flags;
	char m_pad34[0x84 - 0x34];
	FXList *fx;
	char m_pad88[0xa0 - 0x88];
	Records levels;
};

class Rva000FB2E0Owner
{
  public:
	int Gen000FB2E0Method(Object *, bool);
};
enum UpdateSleepTime
{
	Forever = 0x3fffffff
};
class UpdateModule
{
  protected:
	void setWakeFrame(Object *, UpdateSleepTime);
};
struct Rva002A30D0State
{
	char m_pad00[0x28];
	unsigned level;
};
struct Rva002A30D0Object
{
	char m_pad00[0x210];
	Rva002A30D0State *state;
};
class LevelState002A30D0 : public UpdateModule
{
  public:
	void apply();
	void *vptr;
	Rva002A30D0Data *data;
	Object *object;
	char m_pad0c[0x20 - 12];
	float m_f20;
	char m_pad24[8];
	int m_f2c;
	char m_pad30[8];
	int m_f38, m_f3c;
	bool m_f40;
};
void LevelState002A30D0::apply()
{
	Rva002A30D0Data *d = data;
	Object *obj = object;
	if (m_f2c == 0 || m_f2c == 4)
	{
		unsigned level = ((Rva002A30D0Object *)obj)->state->level;
		Records::iterator it = d->levels.find(Rva002A23B0Record(level));
		Records::iterator end = d->levels.end();
		if (it == end)
		{
			it = d->levels.find(Rva002A23B0Record(1));
			if (it == end)
			{
				setWakeFrame(obj, Forever);
				return;
			}
		}
		obj->clearAndSetModelConditionFlags(BfmeConditionFlags(), d->flags);
		const FXList *fx = d->fx;
		if (fx && !const_cast<FXList *>(fx)->bfmeIsBlocked())
			fx->doFXObj(obj, 0);
		obj->setDisabled(Disabled4);
		obj->setEffectivelyDead(true);
		obj->setStatus(MAKE_OBJECT_STATUS_MASK(3), true);
		m_f40 = !it->m_autoSpawn;
		m_f38 = it->m_time;
		m_f3c = it->m_cost;
		m_f20 = it->m_health;
		Player *player = obj->getControllingPlayer();
		if (player)
			((Rva000FB2E0Owner *)((char *)player + 0x684))->Gen000FB2E0Method(obj, !m_f40);
	}
}
