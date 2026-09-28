// ?Rva00396D40DoSetRallyPoint@@YA_NPAVObject@@ABUCoord3D@@_N0@Z
// partial score=0.96 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x00396D40, the rally-point setter the game reaches through the ILT
// thunk 0x00001479.  The Zero Hour twin is the file-static
// GameLogicDispatch.cpp:doSetRallyPoint and every string this body quotes is
// that function's ("HumanLocomotor", "GUI:RallyPointNoPath",
// "UnableToSetRallyPoint", "GUI:RallyPointSet", "RallyPointSet"), so the
// identity is the twin's.  The four-argument shape and the Bool result are not
// the twin's, so the ledger name keeps the address token.
//
// Both retail callers fix the extra arguments.  GameLogic's message dispatcher
// (0x00397540 +0x05EB) pushes (object, &coord, 1, 0) and the resolve callback
// bfmeResolveReferenceIfEnabled (0x003972F0 +0x26) pushes (object, &coord, 0, 0),
// so the third argument is the per-object feedback switch - the global-rally-point
// pass in Rva00397350GlobalRallyPointFeedback.cpp runs with it clear and prints
// one aggregate message instead - and the fourth is an optional object whose
// position replaces the requested one.  Both callers pass zero for the fourth,
// so its class is unproven; only its +0x38 Coord3D is read.
//
// STATE 2026-09-27 (second pass): 37 non-relocation bytes differ from retail, all
// of them two residues, and the compiled size is retail's 880 exactly.  Both
// residues are codegen order, not identity: every value keeps retail's role, so
// the reconstruction is right and only MSVC's two choices are wrong.
//   1. An ESI/EDI mirror, at four sites (+0x1b, +0x54, +0x98, +0x1b9) and their
//      users.  Every value keeps retail's role: the object pointer is the
//      long-lived one, the NameKey result, the &Object::m_position and the
//      Drawable are the short-lived scratch, and isLocal is in EBX.  Retail
//      gives the long-lived web EDI and the scratch ESI, this build the other
//      way round.
//   2. The 12-byte copy at the top.  Retail emits store 1, then the NameKey
//      call's argument setup, then stores 2 and 3, with the two later
//      displacements already adjusted for the push - so this is codegen order,
//      not a scheduled move.  MSVC stores all three before the call setup here.
//
// MEASURED THIS PASS, all negative, all at 37 bytes / 880, object still in ESI:
//   * The choice is set by the PATHFINDER block, and by nothing later.  With
//     only the head (isLocal, the copy, nameToKey, the LocomotorSet) the object
//     gets NO callee-saved register at all - it is reloaded from the argument
//     slot on every use.  Adding the block that uses the object twice and takes
//     &object->m_position is what forces the allocation.  Deleting the whole
//     tail (final feedback block emptied: 503 B; first static removed: 743 B)
//     leaves head=esi, so the "something later in this function" lead is dead.
//   * Making Object::getPosition() an out-of-line CALL does NOT flip it (897 B,
//     head=esi).  The flip is caused by the object's USE COUNT, not by the
//     inline accessor's lea, so do not re-run the reduced-TU experiment.
//   * Hoisting the position to a local before the first statement does not flip
//     it either way: a `const Coord3D &` reference and a `const Coord3D *`
//     pointer both cost 7 bytes (873 B) and add a fourth save (EBP), because the
//     value is not live at the top so MSVC sinks its materialisation below the
//     isLocallyControlled call.  The shape_levers.md "a field address counts
//     before a field load" lever needs the address to fold into the addressing
//     mode, which it cannot here.
//   * &object->m_position instead of &object->getPosition(), a pointer-returning
//     getPositionPtr(), pointer->reference callee parameters, a top-level const
//     object parameter, block-scoping the NameKey key, declaring the
//     LocomotorSet before the key, a named local for findLocomotorTemplate's
//     result, a cached NameKeyGenerator* receiver, and declared-then-assigned
//     rallyPosition all leave 37 bytes / head=esi.
//   * shape_family_levers.py reports NO applicable source-level family lever for
//     this source, and shape_search over eh_levers.py's six mechanical choices
//     (throw() on three callees, /EHsc-, _STLP_NO_EXCEPTIONS, nothrow delete[])
//     scores the unchanged source best.  rotation_sweep.py finds 16 toggles, all
//     +0.  This matches the documented limit: that lever does not reach
//     callee-saved swaps, and docs/shape_levers.md records bodies where the
//     choice stays compiler-internal after every choice is exhausted.
// CORRECTION to the previous STATE note: landing does NOT need pins for
// 0x012F0C70 / 0x012F0BE8.  Those are the addresses RETAIL's linker gave the two
// function-local statics; in this object both the statics and their guard bytes
// are IMAGE_REL_I386_DIR32 relocations onto ?rallyNotSet@?M@... and
// ?rallyPointSet@?BM@... (offsets 259, 272, 304, 356, 374 for the first, 645,
// 663, 695, 746, 751, 767, 772, 785 for the second), so probe masks them and
// the link resolves them wherever they land.  What a landing still has to pass
// is build.sh's DIR32-addresses check, which is a separate gate.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned short WideChar;

// The pathfinder predicates are pinned with Vector3 spelled as their own first
// argument type; Coord3D derives from it so the conversions cost no code.
struct Vector3
{
	Real x;
	Real y;
	Real z;
};

struct Coord3D : public Vector3
{
};

#include "ascii_string.h"

// unicode_string.h declares the default constructor out of line; retail
// inlines it, and the two bodies below need the inlined shape.
class UnicodeString
{
public:
	UnicodeString() : m_data(0) {}
	UnicodeString(const UnicodeString &other)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&other);
	}
	~UnicodeString()
	{
		((StringBase<unsigned short> *)this)->releaseBuffer();
	}
	void __cdecl format(UnicodeString format, ...);

	// Retail hands the substitution operand the StringBase header pointer, not
	// the +0x08 text its own format() walks (0x00396D16 is a bare
	// `mov eax,[name]`), so this returns the header.
	void *getRawBuffer() const { return m_data; }

private:
	void *m_data;
};

class Drawable;
class ExitInterface;
class LocomotorSet;
class LocomotorTemplate;
class Object;
class Pathfinder;
class Player;

enum NameKeyType
{
	NAMEKEY_NONE = 0
};

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	Bool isLocallyControlled() const;
	ExitInterface *getObjectExitInterface() const;
	Player *getControllingPlayer() const;

	const Coord3D &getPosition() const { return m_position; }

#define OBJECT_SLOT(n) virtual void objectSlot##n();
	OBJECT_SLOT(00) OBJECT_SLOT(04) OBJECT_SLOT(08) OBJECT_SLOT(0C)
	OBJECT_SLOT(10) OBJECT_SLOT(14) OBJECT_SLOT(18) OBJECT_SLOT(1C)
	OBJECT_SLOT(20) OBJECT_SLOT(24)
	virtual Drawable *getDrawable();
#undef OBJECT_SLOT

	// +0x04 is the reference owner the display-name fallback walks; the chain
	// inside it is the one BfmeTryResolveReference.cpp proves at 0x003972F0.
	void *m_referenceOwner;
	unsigned char m_unmodelled[0x30];
	Coord3D m_position;
};

class ExitInterface
{
public:
#define EXIT_SLOT(n) virtual void exitSlot##n();
	EXIT_SLOT(00) EXIT_SLOT(04) EXIT_SLOT(08) EXIT_SLOT(0C)
	EXIT_SLOT(10) EXIT_SLOT(14) EXIT_SLOT(18)
	virtual void setRallyPoint(const Coord3D *pos);
#undef EXIT_SLOT
};

class Drawable
{
public:
	// 0x00416D20, reached through the ILT 0x00043A77; see
	// game/GameEngine/Source/GameClient/DrawableGetDisplayName.cpp.
	Bool getDisplayName(UnicodeString &name) const;

	Bool isSelected() const { return m_selected; }

private:
	unsigned char m_unmodelled[0x3AC];
	Bool m_selected;
};

class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

private:
	unsigned char m_unmodelled[0x24];
	Int m_playerIndex;
};

class LocomotorStore
{
public:
	const LocomotorTemplate *findLocomotorTemplate(NameKeyType key);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class LocomotorSet
{
public:
	LocomotorSet();
	virtual ~LocomotorSet();
	void addLocomotor(const LocomotorTemplate *lt);

	// 0x001B7450 zero-fills through +0x20 behind the vtable pointer.
	char m_unmodelled[0x20];
};

class Pathfinder
{
public:
	Bool clientSafeQuickDoesPathExist(Object *object, const Coord3D *from,
		const Coord3D *to, const LocomotorSet *set);
	Bool bfmePickBridge(const Vector3 &from, const Vector3 &to, Vector3 *pos);
};

class AI
{
public:
	Pathfinder *pathfinder() const { return m_pathfinder; }

private:
	unsigned char m_unmodelled[0x0C];
	Pathfinder *m_pathfinder;
};

// The override walk the display-name fallback shares with
// BfmeTryResolveReference.cpp.  The +0x0C member it then reads is not named by
// any evidence, so the field keeps the offset in its name.
class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();

	unsigned char m_pad00[4];
	BfmeOverridable *m_next;
	unsigned char m_pad08[4];
	void *m_field0C;
};

class GameTextInterface
{
public:
#define TEXT_SLOT(n) virtual void textSlot##n();
	TEXT_SLOT(00) TEXT_SLOT(04) TEXT_SLOT(08) TEXT_SLOT(0C)
	TEXT_SLOT(10) TEXT_SLOT(14) TEXT_SLOT(18) TEXT_SLOT(1C)
	TEXT_SLOT(20) TEXT_SLOT(24)
#undef TEXT_SLOT
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);
};

// The Unicode overload sits at slot 13; see
// game/GameEngine/Source/Common/System/SaveGame/GameStateSaveGame.cpp.
class InGameUI
{
public:
#define UI_SLOT(n) virtual void uiSlot##n();
	UI_SLOT(00) UI_SLOT(04) UI_SLOT(08) UI_SLOT(0C)
	UI_SLOT(10) UI_SLOT(14) UI_SLOT(18) UI_SLOT(1C)
	UI_SLOT(20) UI_SLOT(24) UI_SLOT(28) UI_SLOT(2C) UI_SLOT(30)
	virtual void message(UnicodeString message, ...);
#undef UI_SLOT
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, ObjectID ownerID = INVALID_ID);
	virtual ~AudioEventRTS();
	void setPosition(const Coord3D *position);
	void setPlayerIndex(Int playerIndex);
};

class AudioClient
{
public:
#define AUDIO_SLOT(n) virtual void audioSlot##n();
	AUDIO_SLOT(00) AUDIO_SLOT(04) AUDIO_SLOT(08) AUDIO_SLOT(0C)
	AUDIO_SLOT(10) AUDIO_SLOT(14) AUDIO_SLOT(18) AUDIO_SLOT(1C)
	AUDIO_SLOT(20) AUDIO_SLOT(24) AUDIO_SLOT(28) AUDIO_SLOT(2C)
	AUDIO_SLOT(30) AUDIO_SLOT(34) AUDIO_SLOT(38) AUDIO_SLOT(3C) AUDIO_SLOT(40)
	virtual void addAudioEvent(AudioEventRTS *event);
#undef AUDIO_SLOT
};

class ControlBar
{
public:
	void markUIDirty() { m_uiDirty = true; }

private:
	unsigned char m_unmodelled[0x24];
	Bool m_uiDirty;
};

#define TheNameKeyGenerator (*(NameKeyGenerator **)0x012ED600)
#define TheAI (*(AI **)0x012EF214)
#define TheLocomotorStore (*(LocomotorStore **)0x012EF504)
#define TheAudioClientUpdate (*(AudioClient **)0x012ED668)
#define TheGameText (*(GameTextInterface **)0x012F147C)
#define TheInGameUI (*(InGameUI **)0x012F148C)
#define TheControlBar (*(ControlBar **)0x012F33F8)

// Retail materialises the fallback as the symbol's own address in a
// `mov eax, imm32`, so it is an array here and not a pointer variable.
extern const WideChar g_bfmeEmptyUnicode[];

#pragma comment(linker, "/alternatename:??0LocomotorSet@@QAE@XZ=?Rva001B7450@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1LocomotorSet@@UAE@XZ=?Gen_001BA9E0@@UAE@XZ")
#pragma comment(linker, "/alternatename:?getDisplayName@Drawable@@QBE?AVUnicodeString@@@Z=?getDisplayName@Drawable@@QBEDAAVUnicodeString@@@Z")
#pragma comment(linker, "/alternatename:?clientSafeQuickDoesPathExist@Pathfinder@@QAE_NPAVObject@@PBVCoord3D@@1PAVLocomotorSet@@@Z=?clientSafeQuickDoesPathExist@Pathfinder@@QAE_NPAVObject@@PBVCoord3D@@1H@Z")

Bool Rva00396D40DoSetRallyPoint(Object *object, const Coord3D &position,
	Bool showFeedback, Object *positionSource)
{
	Bool isLocal = object->isLocallyControlled();
	Coord3D rallyPosition = position;

	// Retail calls nameToKey, then builds the LocomotorSet, then looks the
	// template up, so the key has to be a local of its own statement: a single
	// nested call would put the set's constructor first.
	NameKeyType key = TheNameKeyGenerator->nameToKey("HumanLocomotor");
	LocomotorSet locomotorSet;
	locomotorSet.addLocomotor(TheLocomotorStore->findLocomotorTemplate(key));

	// Retail tests the optional position source first and jumps PAST the path
	// test into the copy at 0x00396E22, so the source polarity runs the other
	// way round: the path test is the fall-through and the copy is the else.
	if (!positionSource)
	{
		if (!TheAI->pathfinder()->clientSafeQuickDoesPathExist(object,
					 &object->getPosition(), &rallyPosition, &locomotorSet) &&
			 !TheAI->pathfinder()->bfmePickBridge(object->getPosition(),
				rallyPosition, &rallyPosition))
		{
			if (isLocal && showFeedback)
			{
				TheInGameUI->message(TheGameText->fetch("GUI:RallyPointNoPath"));

				static AudioEventRTS rallyNotSet("UnableToSetRallyPoint");
				rallyNotSet.setPosition(&rallyPosition);
				TheAudioClientUpdate->addAudioEvent(&rallyNotSet);
			}
			return false;
		}
	}
	else
	{
		rallyPosition = positionSource->getPosition();
	}

	ExitInterface *exitInterface = object->getObjectExitInterface();
	if (!exitInterface)
		return false;
	exitInterface->setRallyPoint(&rallyPosition);

	if (isLocal && showFeedback)
	{
		UnicodeString message;
		UnicodeString name;
		Drawable *drawable = object->getDrawable();
		const void *text;
		if (drawable && drawable->getDisplayName(name))
		{
			text = name.getRawBuffer();
		}
		else
		{
			// 0x00396F1C walks the same override chain
			// BfmeTryResolveReference.cpp proves at 0x003972F0 and then reads
			// +0x0C of what the walk returned.  The join point is that read
			// itself: both null tests branch straight to it, so the chain's own
			// result is never tested and the owner doubles as the fallback.
			BfmeOverridable *value = (BfmeOverridable *)object->m_referenceOwner;
			if (value)
			{
				BfmeOverridable *reference = *(BfmeOverridable **)
					((char *)value + 4);
				if (reference)
					value = reference->friend_getFinalOverride();
			}
			text = value->m_field0C;
		}

		// Both arms reach the null test and the +0x08 skip: retail jumps from
		// the display-name arm straight into it, so the text pointer is a
		// StringBase header in either case and the characters start past it.
		const void *substitute = text ? (const char *)text + 8
			: (const void *)g_bfmeEmptyUnicode;

		message.format(TheGameText->fetch("GUI:RallyPointSet"), substitute);
		TheInGameUI->message(message);

		static AudioEventRTS rallyPointSet("RallyPointSet");
		rallyPointSet.setPosition(&rallyPosition);
		rallyPointSet.setPlayerIndex(
			object->getControllingPlayer()->getPlayerIndex());
		TheAudioClientUpdate->addAudioEvent(&rallyPointSet);

		if (drawable && drawable->isSelected())
			TheControlBar->markUIDirty();
	}

	return true;
}
