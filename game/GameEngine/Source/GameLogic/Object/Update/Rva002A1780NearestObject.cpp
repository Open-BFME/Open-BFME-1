// cl: /O2 /DNDEBUG /MD /EHsc /Igame/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1

// Retail RVA 0x002A1780, 175 bytes.
//
// Identity: a niladic __thiscall on the update-module receiver that returns an
// Object*.  Its only caller is retail 0x002A32D0 (RespawnUpdate::update),
// which reaches it through ILT 0x0001DD7C bound as a member pointer on
// (this-16) and uses the Object* it returns as a replacement source.  The
// module's witnessed layout there is vtable+0, module data+4, Object+8 -- the
// same +4/+8 this body reads.  No vtable slot names this body, so the class and
// method keep address-derived names; only the *behaviour* the bytes prove
// (build a two-filter chain, ask the partition for the closest object to
// this+0x38, fall back to the receiver's own Object) is stated.
//
// Callee contract, resolved from the image rather than assumed:
//   +0x22, +0x45  ILT 0x00020824 -> Object::getControllingPlayer() const
//   +0x78         PartitionFilter::link(PartitionFilter *) at retail 0x009F2AE0
//   +0x93         PartitionManager::getClosestObject(const Coord3D *, Real,
//                  Int, PartitionFilter *) at retail 0x009F26A0, via the pinned
//                  global ThePartitionManager 0x012ED5B8.
//
// Retail unwind states invoke the trivial PartitionFilter base cleanup;
// its 7-byte bodies at 0016AA10/00201F10 restore VA 01083B5C and return.
// Native virtual destruction expresses this lifetime; no fake out-of-line
// cleanup body is used to make the caller match.
//
// The 1,000,000.0f radius and the two filters' order are pinned by the byte
// gate; the argument-evaluation order (second argument's call before the
// first argument's add) is what produces retail's call/add/call sequence.

#include "basetype.h"

class Object;
class Player;

class Object
{
  public:
	Player *getControllingPlayer() const;
};

// Retail vtable 0x01097144; the matched consumer at 0x0041E9E0 uses the same
// table with the player payload at +8.
class PartitionFilter
{
  public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual bool allow(Object *) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

// vtable 0x01097144: base vtable, m_next, Player* at +8.
class PlayerFilter002A1780 : public PartitionFilter
{
  public:
	PlayerFilter002A1780(Player *p) : m_08(p) {}
	virtual ~PlayerFilter002A1780() {}
	virtual bool allow(Object *);
	virtual Int getPlayerMask();

	Player *m_08;
};

// Retail vtable 0x010A5158 -- the table the matched 0x00265150 body installs;
// its slot 1 is BfmeThingRJ::bfmeCheckRJ, so the +8/+C/+10 payload shape below
// is that class's own, not an invented one.
class Rva00265150RJFilter : public PartitionFilter
{
  public:
	Rva00265150RJFilter(void *subobject, void *extra, Bool match)
		: m_subobject(subobject), m_extra(extra), m_match(match) {}
	virtual ~Rva00265150RJFilter() {}
	virtual bool allow(Object *);
	virtual Int getPlayerMask();

	void *m_subobject;
	void *m_extra;
	Bool m_match;
};

class PartitionManager
{
  public:
	Object *getClosestObject(const Coord3D *position, Real range,
		Int distanceCalculation, PartitionFilter *filters);
};

extern PartitionManager *ThePartitionManager;

// +4 module data (a record whose +8 is the filter's first operand), +8 Object.
class Rva002A1780Module
{
  public:
	Object *nearestObject002A1780();

  private:
	void *m_vftable;
	char *m_moduleData;
	Object *m_object;
};

Object *Rva002A1780Module::nearestObject002A1780()
{
	Object *object = m_object;
	char *moduleData = m_moduleData;
	Player *player = object->getControllingPlayer();
	PlayerFilter002A1780 playerFilter(player);
	Rva00265150RJFilter rjFilter((void *)(moduleData + 8),
		object->getControllingPlayer(), 1);
	playerFilter.link(&rjFilter);
	Object *found = ThePartitionManager->getClosestObject(
		(const Coord3D *)((char *)object + 0x38), 1000000.0f, 0, &playerFilter);
	return found ? found : object;
}
