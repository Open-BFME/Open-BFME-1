// ?rva002AD670@StealthUpdate@@QAE?AW4UpdateSleepTime@@XZ
// partial score=0.97 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x002AD670 (1885 B): the per-frame stealth step that the real
// StealthUpdate::update (0x002ADFB0, entered through the UpdateModule
// subobject at +0x10) calls through ILT 0x0002DA79 after its disguise-restore
// prologue. Name keeps the address. Cold rewrite 2026-09-28 (opus-5.5) on the
// matched filter/result models (AIFindAllyNear.cpp,
// BuildAssistant_moveObjectsForConstruction.cpp) and markAsDetected's
// StealthUpdate layout: probe shape 0.967, 1873/1885 B, 1289 differing bytes
// (the old stash re-probed at shape 0.523, 1424 B).
// Open: this/self registers swapped (retail ESI=this, EDI=self), which moves
// most bytes; retail keeps draw in EBP from the stealth-allowed branch on; the
// toggle-module body block spills the compare value, ours the body pointer;
// null-owner branch computes the position twice. Landing needs pins:
// Drawable::rva00416820 (0x00416820), a bool alias of
// Object::bfmeHasSignificantPreferredLocomotorHeight (retail tests AL only),
// ~BfmeWideResult at 0x000C5FC0, the kind-filter ctor at 0x000C3DD0, and
// Object::findModule must be declared protected (IBE).

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ObjectID { INVALID_ID = 0 };
enum ObjectStatusTypes { OBJECT_STATUS_STEALTHED = 15, OBJECT_STATUS_DETECTED = 17 };
enum StealthLookType { STEALTHLOOK_NONE = 0 };

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &that);
	~AudioEventRTS();
	void setObjectID(ObjectID id);

private:
	unsigned char m_data[0x70];
};

class AudioManager
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
	virtual void addAudioEvent(AudioEventRTS *event);
};
extern AudioManager *TheAudio;

// The sound table read through the drawable; 0x00416FA0 is matched under this
// ledger name.
class ThingTemplate
{
public:
	const AudioEventRTS *getSound(Int which) const;
};

class Drawable
{
public:
	const AudioEventRTS *getSound(Int which) const
	{
		return ((const ThingTemplate *)this)->getSound(which);
	}
	void rva00416820(StealthLookType look, Real minOpacity, Real maxOpacity, Real pulse);

	unsigned char m_unmodelled000[0xb0];
	Real m_effectiveOpacity;
};

template <size_t NUMBITS>
class BitFlags
{
public:
	Bool test(Int i) const { return m_bits.test(i); }

private:
	_STL::bitset<NUMBITS> m_bits;
};

class KindOfMask
{
public:
	KindOfMask(Int init, Int bit1, Int bit2);

private:
	UnsignedInt m_words[6];
};
extern const KindOfMask KINDOFMASK_NONE;

class Object;

class AIUpdateInterface
{
public:
	virtual void slot000();
	virtual void slot001();
	virtual void slot002();
	virtual void slot003();
	virtual void slot004();
	virtual void slot005();
	virtual void slot006();
	virtual void slot007();
	virtual void slot008();
	virtual void slot009();
	virtual void slot010();
	virtual void slot011();
	virtual void slot012();
	virtual void slot013();
	virtual void slot014();
	virtual void slot015();
	virtual void slot016();
	virtual void slot017();
	virtual void slot018();
	virtual void slot019();
	virtual void slot020();
	virtual void slot021();
	virtual void slot022();
	virtual void slot023();
	virtual void slot024();
	virtual void slot025();
	virtual void slot026();
	virtual void slot027();
	virtual void slot028();
	virtual void slot029();
	virtual void slot030();
	virtual void slot031();
	virtual void slot032();
	virtual void slot033();
	virtual void slot034();
	virtual void slot035();
	virtual void slot036();
	virtual void slot037();
	virtual void slot038();
	virtual void slot039();
	virtual void slot040();
	virtual void slot041();
	virtual void slot042();
	virtual void slot043();
	virtual void slot044();
	virtual void slot045();
	virtual void slot046();
	virtual void slot047();
	virtual void slot048();
	virtual void slot049();
	virtual void slot050();
	virtual void slot051();
	virtual void slot052();
	virtual void slot053();
	virtual void slot054();
	virtual void slot055();
	virtual void slot056();
	virtual void slot057();
	virtual void slot058();
	virtual void slot059();
	virtual void slot060();
	virtual void slot061();
	virtual void slot062();
	virtual void slot063();
	virtual void slot064();
	virtual void slot065();
	virtual void slot066();
	virtual void slot067();
	virtual void slot068();
	virtual void slot069();
	virtual void slot070();
	virtual void slot071();
	virtual void slot072();
	virtual void slot073();
	virtual void slot074();
	virtual void slot075();
	virtual void slot076();
	virtual void slot077();
	virtual void slot078();
	virtual void slot079();
	virtual void slot080();
	virtual void slot081();
	virtual void slot082();
	virtual void slot083();
	virtual void slot084();
	virtual void slot085();
	virtual void slot086();
	virtual void slot087();
	virtual void slot088();
	virtual void slot089();
	virtual void slot090();
	virtual void slot091();
	virtual void slot092();
	virtual void slot093();
	virtual void slot094();
	virtual void slot095();
	virtual void slot096();
	virtual Bool slot097();

	Object *getCurrentVictim() const;
};

class BodyModuleInterface
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
	virtual Int slot15();
	virtual UnsignedInt slot16();
};

class ToggleModule
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
	virtual void slot21(Object *object);
	virtual void slot22(Object *object, Int value);
	virtual void slot23();
	virtual UnsignedInt slot24();
};

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Bool isGarrisonable();
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
	virtual void recalcApparentControllingPlayer();
};

class Module;
class Player;
class Gen001C9AC0 { public: void handle(Int value); };
class Rva001BEF20FieldAddress { public: char *get(); };
class RvaC4390First;
class RvaC4390Second { public: RvaC4390First *resolve(Int index); };

class Object
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
	virtual Drawable *getDrawable();

	void setStatusBit(Int bit, Bool set);
	void clearStatus(ObjectStatusTypes status);
	void notifyModelConditionChanged();
	Bool isLocallyControlled() const;
	Bool bfmeHasSignificantPreferredLocomotorHeight() const;
	Module *findModule(NameKeyType key) const;

	const BitFlags<86> &getStatusBits() const { return m_status; }
	ObjectID getID() const { return m_id; }
	Object *getContainedBy() const { return m_containedBy; }
	ContainModuleInterface *getContain() const { return m_contain; }

	unsigned char m_unmodelled004[0x34];
	Coord3D m_position;
	unsigned char m_unmodelled044[0x30];
	ObjectID m_id;
	unsigned char m_unmodelled078[0x18];
	BitFlags<86> m_status;
	unsigned char m_unmodelled09C[0x90];
	UnsignedInt m_modelFlags12C;
	unsigned char m_unmodelled130[0xcc];
	ContainModuleInterface *m_contain;
	BodyModuleInterface *m_body;
	AIUpdateInterface *m_ai;
	unsigned char m_unmodelled208[0x0c];
	Object *m_containedBy;
};

class PlayerList
{
public:
	unsigned char m_unmodelled00[0x0c];
	Player *m_localPlayer;
};
extern PlayerList *ThePlayerList;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_unmodelled00[0x3c];
	UnsignedInt m_frame;
};
extern GameLogic *TheGameLogic;

extern Real g_Rva012B22D4Scale;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *obj) = 0;
	virtual Int getPlayerMask();

	PartitionFilter *link(PartitionFilter *next);

	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(const KindOfMask &mustBeSet,
		const KindOfMask &mustBeClear)
		: m_mustBeSet(mustBeSet), m_mustBeClear(mustBeClear) {}
	virtual Bool allow(Object *obj);

	KindOfMask m_mustBeSet;
	KindOfMask m_mustBeClear;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	Rva0025ED50ObjectFilter(Object *object) : m_object(object) {}
	virtual Bool allow(Object *obj);

	Object *m_object;
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	PartitionFilterRelationship(Object *object, Int flags, Bool match)
		: m_object(object), m_flags(flags), m_match(match) {}
	virtual Bool allow(Object *obj);

	Object *m_object;
	Int m_flags;
	Bool m_match;
};

class Rva000FBDC0Filter : public PartitionFilter
{
public:
	Rva000FBDC0Filter() {}
	virtual Bool allow(Object *obj);
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *obj);
};

class Rva00260180SelfFilter : public PartitionFilter
{
public:
	Rva00260180SelfFilter(Object *object) : m_object(object) {}
	virtual Bool allow(Object *obj);

	Object *m_object;
};

struct SimpleObjectIteratorClump
{
	Object *m_object;
	Int m_distanceBits;
};

struct SimpleObjectIterator
{
	_STL::vector<SimpleObjectIteratorClump> m_entries;
	SimpleObjectIteratorClump *m_cursor;
	Int m_refCount;
};

struct BfmeWideResult
{
	SimpleObjectIterator *m_mpo;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &that);
	~BfmeWideResult();
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(Int a, Int b, Int c, Int d, Int e);
};
extern BfmeWideForwardC *ThePartitionManager;

struct StealthUpdateModuleData
{
	unsigned char m_unmodelled000[0x08];
	UnsignedInt m_stealthDelay;
	unsigned char m_unmodelled00C[0x14];
	Real m_opacityMin20;
	Real m_opacityMax24;
	UnsignedInt m_pulseFrames28;
	unsigned char m_unmodelled02C[4];
	Real m_revealDistanceFromTarget;
	unsigned char m_unmodelled034[0x1e];
	Bool m_flag52;
	unsigned char m_unmodelled053[1];
	UnsignedInt m_disguiseTransitionFrames;
	UnsignedInt m_disguiseRevealTransitionFrames;
	Real m_range5C;
	UnsignedInt m_mask60;
	unsigned char m_unmodelled064[0x2bc];
	UnsignedInt m_delay320;
};

class StealthUpdate
{
public:
	virtual void slot00();

	UpdateSleepTime rva002AD670();

	void markAsDetected(UnsignedInt frames, Bool propagate);
	UpdateSleepTime calcSleepTime() const
	{
		return m_enabled ? UPDATE_SLEEP_NONE : UPDATE_SLEEP_FOREVER;
	}

protected:
	StealthLookType calcStealthedStatusForPlayer(const Object *obj, const Player *player);
	void changeVisualDisguise();
	void hintDetectableWhileUnstealthed();

public:
	Bool allowedToStealthAt002ACD90(const Coord3D *a, const Coord3D *b) const;

	const StealthUpdateModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled00C[0x14];
	UnsignedInt m_stealthAllowedFrame;
	UnsignedInt m_detectionExpiresFrame;
	UnsignedInt m_nextFrame28;
	Bool m_enabled;
	Bool m_restoring2D;
	unsigned char m_unmodelled02E[0x0e];
	UnsignedInt m_disguiseTransitionFrames;
	Bool m_disguiseHalfpointReached;
	Bool m_transitioningToDisguise;
};

// ?rva002AD670@StealthUpdate@@QAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime StealthUpdate::rva002AD670()
{
	UnsignedInt now = TheGameLogic->getFrame();
	const StealthUpdateModuleData *data = m_moduleData;
	Object *self = m_object;

	if (!m_enabled && !m_restoring2D)
		return UPDATE_SLEEP_FOREVER;

	Drawable *draw = self->getDrawable();
	if (draw)
	{
		if (m_restoring2D)
		{
			if (m_stealthAllowedFrame < now)
				self->setStatusBit(OBJECT_STATUS_STEALTHED, true);
			if (m_detectionExpiresFrame && m_detectionExpiresFrame < now)
			{
				if (self->m_modelFlags12C & 0x40000)
				{
					self->m_modelFlags12C &= ~0x40000;
					self->notifyModelConditionChanged();
				}
				self->clearStatus(OBJECT_STATUS_STEALTHED);
				((Gen001C9AC0 *)self)->handle(0x1c);
				m_restoring2D = false;
				m_nextFrame28 = now + data->m_delay320;
			}
		}
		else if (m_disguiseTransitionFrames)
		{
			--m_disguiseTransitionFrames;
			Real factor;
			if (m_transitioningToDisguise)
				factor = 1.0f - (Real)m_disguiseTransitionFrames / (Real)data->m_disguiseTransitionFrames;
			else
				factor = 1.0f - (Real)m_disguiseTransitionFrames / (Real)data->m_disguiseRevealTransitionFrames;
			if (factor >= 0.5f && !m_disguiseHalfpointReached)
			{
				changeVisualDisguise();
				m_disguiseHalfpointReached = true;
			}
			draw->m_effectiveOpacity = (Real)fabs(1.0f - (factor + factor));
			if (!m_disguiseTransitionFrames && !m_transitioningToDisguise)
			{
				m_enabled = false;
				self->clearStatus(OBJECT_STATUS_STEALTHED);
				self->clearStatus(OBJECT_STATUS_DETECTED);
				return calcSleepTime();
			}
		}

		StealthLookType look = calcStealthedStatusForPlayer(self, ThePlayerList->m_localPlayer);
		draw->rva00416820(look, data->m_opacityMin20, data->m_opacityMax24,
			(Real)data->m_pulseFrames28 * g_Rva012B22D4Scale);
	}

	static NameKeyType key_Toggle = TheNameKeyGenerator->nameToKey("ToggleHiddenSpecialAbilityUpdate");
	ToggleModule *toggle = (ToggleModule *)self->findModule(key_Toggle);
	if (toggle && !m_restoring2D)
	{
		AIUpdateInterface *ai = self->m_ai;
		if (!self->bfmeHasSignificantPreferredLocomotorHeight())
		{
			if (ai && ai->slot097())
				markAsDetected(0, true);
		}
		toggle->slot21(self);
		BodyModuleInterface *body = self->m_body;
		if (body && body->slot16() > toggle->slot24())
			toggle->slot22(self, body->slot15());
	}

	Real revealDistance = m_moduleData->m_revealDistanceFromTarget;
	if (revealDistance > 0.0f && !m_restoring2D && self->m_ai)
	{
		Object *target = self->m_ai->getCurrentVictim();
		if (target)
		{
			Real dx = self->m_position.x - target->m_position.x;
			Real dy = self->m_position.y - target->m_position.y;
			Real distSqr = dx * dx + dy * dy;
			if (distSqr <= revealDistance * revealDistance)
			{
				markAsDetected(0, true);
				return calcSleepTime();
			}
		}
	}

	UnsignedInt mask = m_moduleData->m_mask60;
	if (mask && !m_restoring2D)
	{
		UnsignedInt bits = *(UnsignedInt *)((Rva001BEF20FieldAddress *)m_object)->get() & mask;
		if (bits)
		{
			markAsDetected(0, true);
			return calcSleepTime();
		}
	}
	if (0)
	{
		markAsDetected(0, true);
		return calcSleepTime();
	}

	if (m_moduleData->m_range5C > 0.0f && !m_restoring2D)
	{
		Int relationship = data->m_flag52 ? 4 : 1;
		const BfmeWideResult &iter = ThePartitionManager->bfmeForwardWideC(
			(Int)&self->m_position, *(const Int *)&m_moduleData->m_range5C, 2,
			(Int)Rva00260180SelfFilter(self).link(&Rva0025ED50RootFilter())
				->link(&Rva000FBDC0Filter())
				->link(&PartitionFilterRelationship(self, relationship, true))
				->link(&Rva0025ED50ObjectFilter(self))
				->link(&PartitionFilterAcceptByKindOf(KINDOFMASK_NONE, KindOfMask(0, 25, 157))),
			1);
		if (iter.m_mpo->m_entries.size() > 0)
		{
			markAsDetected(0, true);
			return calcSleepTime();
		}
	}

	Object *owner = (Object *)((RvaC4390Second *)m_object)->resolve(0);
	Bool allowed;
	if (!owner)
		allowed = allowedToStealthAt002ACD90(&m_object->m_position, &m_object->m_position);
	else
		allowed = allowedToStealthAt002ACD90(&m_object->m_position, &owner->m_position);
	if (allowed)
	{
		if (m_stealthAllowedFrame > now)
			return calcSleepTime();
		if (!self->getStatusBits().test(OBJECT_STATUS_STEALTHED) && draw)
		{
			AudioEventRTS soundEvent = *draw->getSound(0x60);
			soundEvent.setObjectID(self->getID());
			TheAudio->addAudioEvent(&soundEvent);
		}
		self->setStatusBit(OBJECT_STATUS_STEALTHED, true);
	}
	else
	{
		if (!m_restoring2D)
			m_stealthAllowedFrame = now + m_moduleData->m_stealthDelay;
		if (self->getStatusBits().test(OBJECT_STATUS_STEALTHED))
		{
			if (draw)
			{
				AudioEventRTS soundEvent = *draw->getSound(0x60);
				soundEvent.setObjectID(self->getID());
				TheAudio->addAudioEvent(&soundEvent);
			}
			self->clearStatus(OBJECT_STATUS_STEALTHED);
			hintDetectableWhileUnstealthed();
			markAsDetected(0, true);
		}
	}

	Bool detectedStatusChangedThisFrame = false;
	if (now <= m_detectionExpiresFrame)
	{
		if (self->getStatusBits().test(OBJECT_STATUS_DETECTED))
			return calcSleepTime();
		detectedStatusChangedThisFrame = true;
		if (draw)
		{
			AudioEventRTS soundEvent = *draw->getSound(0x61);
			soundEvent.setObjectID(self->getID());
			TheAudio->addAudioEvent(&soundEvent);
		}
	}
	else
	{
		if (self->getStatusBits().test(OBJECT_STATUS_DETECTED))
		{
			detectedStatusChangedThisFrame = true;
			if (self->isLocallyControlled() && draw)
			{
				AudioEventRTS soundEvent = *draw->getSound(0x60);
				soundEvent.setObjectID(self->getID());
				TheAudio->addAudioEvent(&soundEvent);
			}
		}
		self->clearStatus(OBJECT_STATUS_DETECTED);
	}

	if (detectedStatusChangedThisFrame)
	{
		Object *container = self->getContainedBy();
		if (container)
		{
			ContainModuleInterface *contain = container->getContain();
			if (contain && contain->isGarrisonable())
				contain->recalcApparentControllingPlayer();
		}
	}

	return calcSleepTime();
}
