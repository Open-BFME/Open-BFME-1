// cl: /DNDEBUG /DWIN32 /MD /EHsc
// stlport

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

template <int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };
	BitFlags(_dummy_kInit, Int index)
	{
		m_bits.set(index);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	char m_head00[4];
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	char m_head08[0xc8 - 8];
	UnsignedInt m_kindFlags0;
	UnsignedInt m_kindFlags1;
	UnsignedInt m_kindFlags2;
};

enum KindOfType
{
	KINDOF_TARGET = 0x59
};

class Drawable
{
public:
	Bool isActive() const
	{
		return *(Bool *)((char *)this + 0x3ac) != 0;
	}
};
class BfmeHordeMemberInterface;
class BfmeMemberAIInterface;

class Thing
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	Bool isKindOf(KindOfType kind) const;

	ThingTemplate *m_template;
};

class Object : public Thing
{
public:
	virtual Drawable *getDrawable() const;
	Object *bfmeResolveMeleeTarget(Int mode);
	void setStatus(const ObjectStatusMaskType &status, Bool set);
	void notifyModelConditionChanged();

	char m_head08[0x90 - 8];
	ObjectStatusMaskType m_status;
	char m_head9c[0x12c - 0x9c];
	UnsignedInt m_bfmeModelConditionFlags;
	char m_head130[0x200 - 0x130];
	BfmeHordeMemberInterface *m_bfmeMemberInterface;
	BfmeMemberAIInterface *m_bfmeAI;
};

class BfmeHordeMemberInterface
{
#define MEMBER_SLOT(N) virtual Int slot##N() = 0
public:
	MEMBER_SLOT(00); MEMBER_SLOT(01); MEMBER_SLOT(02); MEMBER_SLOT(03);
	MEMBER_SLOT(04); MEMBER_SLOT(05); MEMBER_SLOT(06); MEMBER_SLOT(07);
	MEMBER_SLOT(08); MEMBER_SLOT(09); MEMBER_SLOT(10); MEMBER_SLOT(11);
	virtual void leaveFormationPose(Int pose) = 0;
	virtual void enterFormationPose(Int pose) = 0;
#undef MEMBER_SLOT
};

class BfmeMemberAIInterface
{
#define AI_SLOT(N) virtual void slot##N() = 0
public:
	AI_SLOT(000); AI_SLOT(001); AI_SLOT(002); AI_SLOT(003);
	AI_SLOT(004); AI_SLOT(005); AI_SLOT(006); AI_SLOT(007);
	AI_SLOT(008); AI_SLOT(009); AI_SLOT(010); AI_SLOT(011);
	AI_SLOT(012); AI_SLOT(013); AI_SLOT(014); AI_SLOT(015);
	AI_SLOT(016); AI_SLOT(017); AI_SLOT(018); AI_SLOT(019);
	AI_SLOT(020); AI_SLOT(021); AI_SLOT(022); AI_SLOT(023);
	AI_SLOT(024); AI_SLOT(025); AI_SLOT(026); AI_SLOT(027);
	AI_SLOT(028); AI_SLOT(029); AI_SLOT(030); AI_SLOT(031);
	AI_SLOT(032); AI_SLOT(033); AI_SLOT(034); AI_SLOT(035);
	AI_SLOT(036); AI_SLOT(037); AI_SLOT(038); AI_SLOT(039);
	AI_SLOT(040); AI_SLOT(041); AI_SLOT(042); AI_SLOT(043);
	AI_SLOT(044); AI_SLOT(045); AI_SLOT(046); AI_SLOT(047);
	AI_SLOT(048); AI_SLOT(049); AI_SLOT(050); AI_SLOT(051);
	AI_SLOT(052); AI_SLOT(053); AI_SLOT(054); AI_SLOT(055);
	AI_SLOT(056); AI_SLOT(057); AI_SLOT(058); AI_SLOT(059);
	AI_SLOT(060); AI_SLOT(061); AI_SLOT(062); AI_SLOT(063);
	AI_SLOT(064); AI_SLOT(065); AI_SLOT(066); AI_SLOT(067);
	AI_SLOT(068); AI_SLOT(069); AI_SLOT(070); AI_SLOT(071);
	AI_SLOT(072); AI_SLOT(073); AI_SLOT(074); AI_SLOT(075);
	AI_SLOT(076); AI_SLOT(077); AI_SLOT(078); AI_SLOT(079);
	AI_SLOT(080); AI_SLOT(081); AI_SLOT(082); AI_SLOT(083);
	AI_SLOT(084); AI_SLOT(085); AI_SLOT(086); AI_SLOT(087);
	AI_SLOT(088); AI_SLOT(089); AI_SLOT(090); AI_SLOT(091);
	AI_SLOT(092); AI_SLOT(093); AI_SLOT(094); AI_SLOT(095);
	AI_SLOT(096); AI_SLOT(097); AI_SLOT(098); AI_SLOT(099);
	AI_SLOT(100); AI_SLOT(101); AI_SLOT(102); AI_SLOT(103);
	AI_SLOT(104); AI_SLOT(105); AI_SLOT(106); AI_SLOT(107);
	AI_SLOT(108); AI_SLOT(109); AI_SLOT(110); AI_SLOT(111);
	AI_SLOT(112); AI_SLOT(113); AI_SLOT(114); AI_SLOT(115);
	AI_SLOT(116); AI_SLOT(117); AI_SLOT(118); AI_SLOT(119);
	AI_SLOT(120); AI_SLOT(121); AI_SLOT(122); AI_SLOT(123);
	AI_SLOT(124); AI_SLOT(125); AI_SLOT(126);
	virtual void reset(Int mode) = 0;
#undef AI_SLOT
};

class HordeContainModuleData
{
public:
	char m_head00[0x2cc];
	Int m_moduleState;
};

class HordeContainView
{
#define HORDE_SLOT(N) virtual Int slot##N(Int value) = 0
public:
	HORDE_SLOT(00); HORDE_SLOT(01); HORDE_SLOT(02); HORDE_SLOT(03);
	HORDE_SLOT(04); HORDE_SLOT(05); HORDE_SLOT(06); HORDE_SLOT(07);
	HORDE_SLOT(08); HORDE_SLOT(09); HORDE_SLOT(10); HORDE_SLOT(11);
	HORDE_SLOT(12); HORDE_SLOT(13); HORDE_SLOT(14); HORDE_SLOT(15);
	HORDE_SLOT(16); HORDE_SLOT(17); HORDE_SLOT(18); HORDE_SLOT(19);
	HORDE_SLOT(20); HORDE_SLOT(21); HORDE_SLOT(22); HORDE_SLOT(23);
	HORDE_SLOT(24); HORDE_SLOT(25); HORDE_SLOT(26); HORDE_SLOT(27);
	HORDE_SLOT(28); HORDE_SLOT(29); HORDE_SLOT(30); HORDE_SLOT(31);
	HORDE_SLOT(32); HORDE_SLOT(33); HORDE_SLOT(34); HORDE_SLOT(35);
	HORDE_SLOT(36); HORDE_SLOT(37); HORDE_SLOT(38); HORDE_SLOT(39);
	HORDE_SLOT(40); HORDE_SLOT(41); HORDE_SLOT(42); HORDE_SLOT(43);
	HORDE_SLOT(44); HORDE_SLOT(45); HORDE_SLOT(46); HORDE_SLOT(47);
	HORDE_SLOT(48); HORDE_SLOT(49); HORDE_SLOT(50); HORDE_SLOT(51);
	HORDE_SLOT(52); HORDE_SLOT(53); HORDE_SLOT(54); HORDE_SLOT(55);
	HORDE_SLOT(56); HORDE_SLOT(57); HORDE_SLOT(58); HORDE_SLOT(59);
	HORDE_SLOT(60); HORDE_SLOT(61); HORDE_SLOT(62); HORDE_SLOT(63);
	HORDE_SLOT(64); HORDE_SLOT(65); HORDE_SLOT(66); HORDE_SLOT(67);
	HORDE_SLOT(68); HORDE_SLOT(69); HORDE_SLOT(70); HORDE_SLOT(71);
	HORDE_SLOT(72); HORDE_SLOT(73); HORDE_SLOT(74); HORDE_SLOT(75);
	HORDE_SLOT(76); HORDE_SLOT(77); HORDE_SLOT(78); HORDE_SLOT(79);
	HORDE_SLOT(80); HORDE_SLOT(81); HORDE_SLOT(82); HORDE_SLOT(83);
	virtual Int slot84(Int value) = 0;
#undef HORDE_SLOT
};

class Rva00413FF0GuardedVCall
{
public:
	void forward(Int value);
};

class Rva004141C0
{
public:
	void broadcast();
};

struct Rva006C9270GlobalData
{
	char m_head00[0xa76];
	Bool m_flagA76;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

class OpenContain
{
public:
	virtual void onRemoving(Object *object);
};

class HordeContain
{
#define CONTAIN_SLOT(N) virtual void slot##N() = 0
public:
	CONTAIN_SLOT(00); CONTAIN_SLOT(01); CONTAIN_SLOT(02); CONTAIN_SLOT(03);
	CONTAIN_SLOT(04); CONTAIN_SLOT(05); CONTAIN_SLOT(06); CONTAIN_SLOT(07);
	CONTAIN_SLOT(08); CONTAIN_SLOT(09); CONTAIN_SLOT(10); CONTAIN_SLOT(11);
	CONTAIN_SLOT(12); CONTAIN_SLOT(13); CONTAIN_SLOT(14); CONTAIN_SLOT(15);
	CONTAIN_SLOT(16); CONTAIN_SLOT(17);
	virtual void onRemoving(Object *object);
#undef CONTAIN_SLOT
};

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?isKindOf@Thing@@QBE_NW4KindOfType@@@Z=?j_0003251f@@YAXXZ")
#pragma comment(linker, "/alternatename:?setStatus@Object@@QAEXABV?$BitFlags@$0FG@@@_N@Z=?j_000307e7@@YAXXZ")
#pragma comment(linker, "/alternatename:?notifyModelConditionChanged@Object@@QAEXXZ=?j_0002191d@@YAXXZ")
#pragma comment(linker, "/alternatename:?onRemoving@OpenContain@@UAEXPAVObject@@@Z=?j_00032e61@@YAXXZ")
#pragma comment(linker, "/alternatename:?forward@Rva00413FF0GuardedVCall@@QAEXH@Z=?j_00013435@@YAXXZ")
#pragma comment(linker, "/alternatename:?broadcast@Rva004141C0@@QAEXXZ=?d_000376cd@@YAXXZ")

void HordeContain::onRemoving(Object *member)
{
	((OpenContain *)this)->OpenContain::onRemoving(member);

	ThingTemplate *memberTemplate = member->m_template;
	if (memberTemplate != 0 && memberTemplate->m_nextOverride != 0)
		memberTemplate = (ThingTemplate *)memberTemplate->m_nextOverride->getFinalOverride();
	if ((memberTemplate->m_kindFlags0 & 0x00000800) != 0)
		goto formation;
	memberTemplate = member->m_template;
	if (memberTemplate != 0 && memberTemplate->m_nextOverride != 0)
		memberTemplate = (ThingTemplate *)memberTemplate->m_nextOverride->getFinalOverride();
	if ((memberTemplate->m_kindFlags2 & 0x10000000) != 0)
		goto formation;
	if (!member->isKindOf(KINDOF_TARGET))
		goto clearFormationFlags;

formation:
	member->setStatus(
		ObjectStatusMaskType(ObjectStatusMaskType::kInit, 37), false);

clearFormationFlags:
	UnsignedInt flags = member->m_bfmeModelConditionFlags;
	if ((flags & 0x00080000) != 0)
	{
		member->m_bfmeModelConditionFlags = flags & ~0x00080000;
		member->notifyModelConditionChanged();
	}
	flags = member->m_bfmeModelConditionFlags;
	if ((flags & 0x00100000) != 0)
	{
		member->m_bfmeModelConditionFlags = flags & ~0x00100000;
		member->notifyModelConditionChanged();
	}
	member->m_bfmeMemberInterface->enterFormationPose(5);

afterFormation:

	HordeContainModuleData *data = *(HordeContainModuleData **)((char *)this - 0x1c);
	if (data != 0 && data->m_moduleState != -1 && member->m_bfmeAI != 0)
		member->m_bfmeAI->reset(0);

	Object *owner = *(Object **)((char *)this - 0x18);
	if (owner == 0)
		return;
	Drawable *drawable = owner->getDrawable();
	if (drawable == 0)
		return;
	if (*(Bool *)((char *)drawable + 0x3ac) == 0)
		return;

	if (TheWritableGlobalData->m_flagA76)
	{
		Int value = ((HordeContainView *)((char *)this + 0xc4))->slot84(0);
		((Rva00413FF0GuardedVCall *)drawable)->forward(value);
		return;
	}

	drawable = member->getDrawable();
	Bool memberDrawableActive = true;
	if (drawable != 0)
		memberDrawableActive = drawable->isActive();
	if (memberDrawableActive)
		return;

	Object *resolved = member->bfmeResolveMeleeTarget(0);
	if (resolved != 0)
	{
		Object *resolvedObject = resolved;
		if (resolvedObject->getDrawable() != 0)
		{
			Drawable *resolvedDrawable = resolvedObject->getDrawable();
			if (*(Bool *)((char *)resolvedDrawable + 0x3ac))
				return;
		}
	}
	((Rva004141C0 *)drawable)->broadcast();
}
