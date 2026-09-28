// ?update@StructureCollapseUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.90 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport
//
// BEST KNOWN SHAPE: probe shape 0.983, ours=945 vs retail=944 bytes, 286 non-reloc
// byte diffs, 5 structural differences (down from 0.685 / 809 bytes / 21 structural
// on the previous session's banked body).  The whole body matches modulo register
// renaming except the two items listed under STILL BLOCKING below.
//
// PROOF THAT THE FRAME AND BOTH OPERATOR SPELLINGS ARE RIGHT (all read off the
// retail image with tools/esp-tracking over dis_retail output):
//   frame 0x74 = 4 pushes (0x10) + locals.  Local slots, absolute from entry esp:
//     abs +0x00 .. +0x14  the WAITING/COLLAPSING Coord3D temporaries and the cached
//                         currentPosition pointer (retail +0x01c9 `lea edx,[esp+0x18]`
//                         resolves to abs +0x00, i.e. the setPosition argument)
//     abs +0x1c .. +0x4c  Matrix3D #1 (0x30 bytes) -- retail +0x0091 .. +0x00f1
//     abs -0x1c .. +0x54  Matrix3D #2, overlapping #1 (retail +0x02ec .. +0x0352)
//   So retail really does overlay the two matrices, exactly as the copy-then-zero
//   interleave at +0x032b..+0x0352 shows.
//
// STILL BLOCKING (2 items, both narrow):
//  (1) REGISTER ALLOCATION, blocker=register.  Retail allocates esi=this, edi=module
//      data, ebx=object, ebp=frame counter.  Ours allocates esi=this, ebx=module data,
//      edi=object.  MSVC 7.1 gives the FIRST callee-saved register in its preference
//      order to the first-defined long-lived pointer, and this source defines the
//      module-data pointer first (retail also reads it first, +0x000c) yet still
//      gives retail `edi`.  Tried and did NOT move it: dropping `const` from the
//      module-data pointer and from its accessor; swapping the now/building
//      definition order in both branches; hoisting the DONE-branch position pointer
//      into a local.  tools/shape_family_levers.py generates no register-family
//      choice for this body, so this is a compiler-internal allocation difference.
//  (2) FLAG-TEST SPELLING, blocker=constant-materialisation.  Retail emits
//      +0x02ac `mov eax,0x4000000` / +0x02b1 `test eax,ecx` / +0x02b5 `or ecx,eax`,
//      i.e. the POST_COLLAPSE bit lives in a REGISTER and the flag word in another.
//      Ours folds it to `test eax,0x4000000` / `or eax,0x4000000`.  Tried and did
//      NOT match: a bare literal; a named `const UnsignedInt`; the same name declared
//      BEFORE the clearModelConditionFlags call so it must be rematerialised; an
//      inline `setModelConditionFlag(UnsignedInt bit)` helper taking the bit as a
//      runtime argument (that one DID put the constant in a register, but then MSVC
//      emitted `mov ecx,eax; shr ecx,0x1a; test cl,1` -- a bit-test decomposition
//      instead of retail's plain TEST).  tools/shape_family_levers.py's `test` and
//      `constant` families produce one choice each here and neither is the retail
//      shape.
//
// LEVERS ALREADY TAKEN THIS SESSION (each measured, keep them):
//   * Object view m_modelConditionFlags at +0x114 and m_bodyModule at +0x200 (the pad
//     is 0xCC, not 0xC4) -- retail reads them at +0x02a6 and +0x02cf.
//   * setPosition/setOrientation declared directly on Object, not inherited from a
//     Thing base: retail passes ecx=ebx with NO +4 base adjust at +0x01d2/+0x02c8.
//   * the COLLAPSING shudder is added to the CACHED collapse origin this+0x28/2C/30
//     (retail +0x01c3/+0x01d8/+0x01e3), not to building->m_position.
//   * the new height is re-read from the member into a local after the two member
//     stores (retail +0x016e `mov edx,[esi+0x24]` / +0x017f spill / +0x01df reload);
//     keeping it in the FPU emits `fst` and loses the spill.
//   * the tail returns (UpdateSleepTime)1, not UPDATE_SLEEP_NONE -- retail +0x03a6
//     `mov eax,1`.
//   * the DONE epilogue asks for the drawable a SECOND time for the matrix but
//     hands the setter the drawable saved before doCollapseDoneStuff
//     (retail +0x02da vs +0x0284 `mov esi,eax`).
//   * `const Coord3D *volatile currentPosition` in the WAITING branch is LOAD-BEARING:
//     dropping volatile reshuffles the whole block (shape 0.983 -> 0.952, 14
//     structural diffs).  Do not "clean it up".
//
// CALLEE 0x002AE520 IS NOT A BLOCKER ANY MORE.  The previous verdict called it one
// because the ledger names it ?onDie@StructureToppleUpdate@@UAEXPBVDamageInfo@@@Z
// (one argument) while update() calls it with ZERO pushes.  This body calls it
// through the existing landed `doCollapseDoneStuff()` member, which the ledger already
// carries at 0x002A38A0 -- so the body compiles and links and the call site's operand
// matches retail (`mov ecx,edi` with edi = this-0x10, no stack argument).  The
// name/arity contradiction on 0x002AE520 is a SEPARATE conversion, not this body's
// dependency, and it no longer blocks landing this one.
//
// NOT LANDED: 945 of 944 bytes compiled (one byte over), 286 non-reloc diffs, so the
// byte gate fails.  The lift __emit copy in StructureCollapseUpdateUpdateThunk.cpp is
// left in place and the ledger row is untouched.

#include <bitset>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

const char *const kRetailSourceFile =
	"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\StructureCollapseUpdate.cpp";

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 0,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

// retail's phase-name table (VA 0x12B232C) names five phases; BFME inserted
// ALMOST_FINAL between BURST and FINAL.
enum StructureCollapsePhaseType
{
	SCPHASE_INITIAL = 0,
	SCPHASE_DELAY = 1,
	SCPHASE_BURST = 2,
	SCPHASE_ALMOST_FINAL = 3,
	SCPHASE_FINAL = 4
};

enum StructureCollapseStateType
{
	COLLAPSESTATE_STANDING = 0,
	COLLAPSESTATE_WAITINGFORCOLLAPSESTART = 1,
	COLLAPSESTATE_COLLAPSING = 2,
	COLLAPSESTATE_DONE = 3
};

class Coord3D
{
public:
	Real x;
	Real y;
	Real z;
};

// WWMatrix3d: three rows of four reals, translation in the fourth column
// (m03 at +0x0C, m13 at +0x1C, m23 at +0x2C).  Upstream
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/matrix3d.h
// gives Matrix3D a user-declared copy constructor AND copy assignment operator,
// so `m = *p` copies field by field in declaration order (retail +0x0091..+0x00df,
// eleven dwords: m23's copy is dead because Set_Translation overwrites it) rather
// than collapsing into a rep movsd.
class Matrix3D
{
public:
	Matrix3D() {}
	__forceinline Matrix3D(const Matrix3D &m)
	{
		m00 = m.m00; m01 = m.m01; m02 = m.m02; m03 = m.m03;
		m10 = m.m10; m11 = m.m11; m12 = m.m12; m13 = m.m13;
		m20 = m.m20; m21 = m.m21; m22 = m.m22; m23 = m.m23;
	}
	__forceinline Matrix3D &operator=(const Matrix3D &m)
	{
		m00 = m.m00; m01 = m.m01; m02 = m.m02; m03 = m.m03;
		m10 = m.m10; m11 = m.m11; m12 = m.m12; m13 = m.m13;
		m20 = m.m20; m21 = m.m21; m22 = m.m22; m23 = m.m23;
		return *this;
	}

	// upstream spelling: Row[0][3] = t[0]; Row[1][3] = t[1]; Row[2][3] = t[2];
	void Set_Translation(const Coord3D &t) { m03 = t.x; m13 = t.y; m23 = t.z; }

	Real m00, m01, m02, m03;
	Real m10, m11, m12, m13;
	Real m20, m21, m22, m23;
};

Real GetGameClientRandomValueReal(Real lo, Real hi, char *file, Int line);
Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);
Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, Int line);

// The retail instance matrix is a Drawable member at +0x198; the caller reads it
// inline rather than through a call.
class Drawable
{
public:
	Matrix3D *getInstanceMatrix()
	{
		return reinterpret_cast<Matrix3D *>(reinterpret_cast<char *>(this) + 0x198);
	}
	void setInstanceMatrix(const Matrix3D *transform, Bool updatePartition);
};

template <size_t NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags(BogusInitType, Int idx1, Int idx2, Int idx3, Int idx4);

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<304> ModelConditionFlags;

// The body module is refreshed through its own vtable slot 0x28.
class BodyModuleInterface
{
public:
	virtual void *slot00() { return 0; }
	virtual void *slot01() { return 0; }
	virtual void *slot02() { return 0; }
	virtual void *slot03() { return 0; }
	virtual void *slot04() { return 0; }
	virtual void *slot05() { return 0; }
	virtual void *slot06() { return 0; }
	virtual void *slot07() { return 0; }
	virtual void *slot08() { return 0; }
	virtual void *slot09() { return 0; }
	virtual void updateBodyParticleSystems();
};

class Object
{
public:
	// Retail passes the object pointer itself as `this` to setPosition (+0x01d2
	// `mov ecx,ebx`) and to setOrientation (+0x02c8), so both live at object+0x00
	// and must not sit behind a this-adjusting secondary base.
	void setPosition(const Coord3D *position);
	void setOrientation(Real angle);

	// the vptr takes the first four bytes, so the pad runs to object+0x38
	unsigned char m_unreconstructed00[0x34];
	Coord3D m_position;
	Real m_orientation;
	// retail reads the flag word at object+0x114 and the body module at
	// object+0x200 (retail +0x02a6 and +0x02cf), so the pad runs to 0x114.
	unsigned char m_unreconstructed48[0xCC];
	UnsignedInt m_modelConditionFlags;
	unsigned char m_unreconstructed114[0xE8];
	BodyModuleInterface *m_bodyModule;

	// Object's vtable slot 0x28 is the Drawable getter in BFME.
	virtual void *slot00() { return 0; }
	virtual void *slot01() { return 0; }
	virtual void *slot02() { return 0; }
	virtual void *slot03() { return 0; }
	virtual void *slot04() { return 0; }
	virtual void *slot05() { return 0; }
	virtual void *slot06() { return 0; }
	virtual void *slot07() { return 0; }
	virtual void *slot08() { return 0; }
	virtual void *slot09() { return 0; }
	virtual Drawable *getDrawable()
	{
		return reinterpret_cast<Drawable *>(reinterpret_cast<char *>(this) + 0x100);
	}

	void clearModelConditionFlags(const ModelConditionFlags &clear);
	void notifyModelConditionChanged();

	// Retail tests the flag word against a value held in a REGISTER
	// (+0x02a6 `mov ecx,[ebx+0x114]`, +0x02ac `mov eax,0x4000000`,
	// +0x02b1 `test eax,ecx`) and commits with `or ecx,eax`, so the bit must
	// arrive as a runtime argument rather than fold into the TEST immediate.
	// Spelling it as a masked write keeps the mask in a register across the
	// test, which is the order retail emits.
	__forceinline void setModelConditionFlag(UnsignedInt bit)
	{
		UnsignedInt flags = m_modelConditionFlags;
		if ((bit & flags) == 0)
		{
			m_modelConditionFlags = flags | bit;
			notifyModelConditionChanged();
		}
	}
};

class GameLogic
{
public:
	// retail reads the frame counter as a field at +0x3C, not through a call.
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_unreconstructed00[0x3C];
	UnsignedInt m_frame;
};

class GlobalData
{
public:
	unsigned char m_unreconstructed00[0x1AC];
	Real m_gravity;
};

extern GameLogic *TheBfmeGameLogic;
extern GlobalData *TheWritableGlobalData;

// getCollapseHeight() is a non-virtual member of the module at object+0x00, so it
// shares retail's this-0x10 here.
class StructureCollapseRetailLayout
{
public:
	Real getCollapseHeight();
};

class StructureCollapseUpdateModuleDataView
{
public:
	char m_unreconstructed00[0x34];
	Int m_minCollapseDelay;
	Int m_maxCollapseDelay;
	Int m_minBurstDelay;
	Int m_maxBurstDelay;
	Int m_bigBurstFrequency;
	Real m_collapseDamping;
	Real m_maxShudder;
};

class StructureCollapseUpdate
{
public:
	virtual UpdateSleepTime update();

protected:
	void doPhaseStuff(StructureCollapsePhaseType scphase, const Coord3D *target);
	void doCollapseDoneStuff();

private:
	const StructureCollapseUpdateModuleDataView *getRetailModuleData() const
	{
		return *reinterpret_cast<const StructureCollapseUpdateModuleDataView *const *>(
			reinterpret_cast<const char *>(this) - 0x0C);
	}

	Object *getRetailObject() const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const char *>(this) - 0x08);
	}

	// doPhaseStuff(), getCollapseHeight() and doCollapseDoneStuff() are members of
	// the module at object+0x00, so they run on object+0x00 in retail.
	StructureCollapseUpdate *getRetailModule() const
	{
		return const_cast<StructureCollapseUpdate *>(
			reinterpret_cast<const StructureCollapseUpdate *>(
				reinterpret_cast<const char *>(this) - 0x10));
	}

	// The vptr takes the first four bytes: retail's compiled `this` sits at
	// object+0x10 with the UpdateModuleInterface vtable there, so +0x14 is the
	// first member update() touches.
	char m_unreconstructed00[0x10];
	UnsignedInt m_collapseFrame;
	UnsignedInt m_burstFrame;
	Int m_collapseState;
	Real m_collapseVelocity;
	Real m_currentHeight;
	Coord3D m_collapseOrigin;
};

UpdateSleepTime StructureCollapseUpdate::update(void)
{
	// Retail reads the module data into edi before the STANDING test resolves, so
	// the load and the edi save sit in the fallthrough.
	const StructureCollapseUpdateModuleDataView *d = getRetailModuleData();

	if (m_collapseState == COLLAPSESTATE_STANDING)
		return UPDATE_SLEEP_FOREVER;

	// We are in the dramatic pause between when the building has lost all its hit
	// points and when it starts toppling over.
	if (m_collapseState == COLLAPSESTATE_WAITINGFORCOLLAPSESTART)
	{
		Object *building = getRetailObject();
		UnsignedInt now = TheBfmeGameLogic->getFrame();

		// volatile: the pointer must survive in a frame slot across the RNG calls
		// (retail +0x004c stores it and +0x010d reloads it).  Without volatile MSVC
		// re-derives it and the whole block reshuffles.
		const Coord3D *volatile currentPosition = &building->m_position;
		// Retail evaluates the Y random first and the X random second (the first
		// result lands in the frame slot Set_Translation reads as t[1]), so the two
		// assignments are spelled in that order.
		Coord3D shudder;
		shudder.y = GetGameClientRandomValueReal(
			-d->m_maxShudder, d->m_maxShudder, const_cast<char *>(kRetailSourceFile), 192);
		shudder.x = GetGameClientRandomValueReal(
			-d->m_maxShudder, d->m_maxShudder, const_cast<char *>(kRetailSourceFile), 192);
		shudder.z = 0.0f;

		const Matrix3D *instMatrix = building->getDrawable()->getInstanceMatrix();
		Matrix3D newInstMatrix;
		newInstMatrix = *instMatrix;
		newInstMatrix.Set_Translation(shudder);
		building->getDrawable()->setInstanceMatrix(&newInstMatrix, true);

		if (now >= m_collapseFrame)
		{
			m_collapseState = COLLAPSESTATE_COLLAPSING;
			getRetailModule()->doPhaseStuff(SCPHASE_BURST, currentPosition);
			// This has to use a game logic random value since the bursts can spawn
			// debris, and debris is sync'd.
			m_burstFrame = now + GetGameLogicRandomValue(
				d->m_minBurstDelay, d->m_maxBurstDelay,
				const_cast<char *>(kRetailSourceFile), 206);
		}
	}

	// The building is in the process of falling over.
	if (m_collapseState == COLLAPSESTATE_COLLAPSING)
	{
		UnsignedInt now = TheBfmeGameLogic->getFrame();
		Object *building = getRetailObject();

		// Retail stores the new height (+0x0162 `fstp [esi+0x24]`) and then READS
		// the member back into edx (+0x016e) to spill it into a frame slot (+0x017f)
		// that survives the two RNG calls and is reloaded for the shudder's z term
		// (+0x01df `fld [esp+0x14]`).  Keeping the value in the FPU instead emits
		// `fst` and loses the spill, so re-read the member here.
		m_currentHeight -= m_collapseVelocity;
		m_collapseVelocity -= TheWritableGlobalData->m_gravity * (1.0 - d->m_collapseDamping);
		const Real height = m_currentHeight;

		// The shudder is applied against the collapse origin beginStructureCollapse
		// cached at object+0x38 (retail +0x01c3/+0x01d8/+0x01e3 read this+0x28/2C/30),
		// not against the building's live position.
		Coord3D shudder;
		shudder.y = GetGameLogicRandomValueReal(
			-d->m_maxShudder, d->m_maxShudder, const_cast<char *>(kRetailSourceFile), 228);
		shudder.x = GetGameLogicRandomValueReal(
			-d->m_maxShudder, d->m_maxShudder, const_cast<char *>(kRetailSourceFile), 228)
			+ m_collapseOrigin.x;
		shudder.y += m_collapseOrigin.y;
		shudder.z = height + m_collapseOrigin.z;
		building->setPosition(&shudder);

		if (now >= m_burstFrame)
		{
			// Retail computes the position pointer once into ebp (+0x0204) and
			// reuses it as doPhaseStuff's second argument in both arms.
			const Coord3D *currentPosition = &building->m_position;
			if (GetGameLogicRandomValue(1, d->m_bigBurstFrequency,
				const_cast<char *>(kRetailSourceFile), 237) == 1)
			{
				getRetailModule()->doPhaseStuff(SCPHASE_BURST, currentPosition);
			}
			else
			{
				getRetailModule()->doPhaseStuff(SCPHASE_DELAY, currentPosition);
			}
			// This has to use a game logic random value since the bursts can spawn
			// debris, and debris is sync'd.
			m_burstFrame += GetGameLogicRandomValue(
				d->m_minBurstDelay, d->m_maxBurstDelay,
				const_cast<char *>(kRetailSourceFile), 246);
		}

		const Real collapseHeight =
			reinterpret_cast<StructureCollapseRetailLayout *>(getRetailModule())
				->getCollapseHeight();

		if ((collapseHeight + m_currentHeight) <= 0.0f)
		{
			m_collapseState = COLLAPSESTATE_DONE;
			getRetailModule()->doPhaseStuff(SCPHASE_FINAL, &building->m_position);
			Drawable *drawable = building->getDrawable();

			getRetailModule()->doCollapseDoneStuff();

			// Retail reads the flag word into ecx, materialises the POST_COLLAPSE bit
			// into eax (+0x02ac) and commits with `or ecx,eax` (+0x02b5).  MSVC only
			// rematerialises an immediate into a register -- rather than folding it
			// into the TEST -- when the value must survive the intervening
			// clearModelConditionFlags call, i.e. when it is a named local declared
			// BEFORE that call and used after it.
			const UnsignedInt POST_COLLAPSE = 0x4000000u;
			building->clearModelConditionFlags(
				ModelConditionFlags(ModelConditionFlags::kInit, 0x42, 0x43, 0x44, 5));
			building->setModelConditionFlag(POST_COLLAPSE);
			building->setOrientation(building->m_orientation);

			// Need to update body particle systems, now
			building->m_bodyModule->updateBodyParticleSystems();

			// Retail asks the object for the drawable a SECOND time here
			// (+0x02da) to read the matrix, but hands the setter the drawable it
			// saved before the done epilogue (+0x0284 `mov esi,eax`).
			const Matrix3D *instMatrix = building->getDrawable()->getInstanceMatrix();
			Matrix3D newInstMatrix;
			newInstMatrix = *instMatrix;
			Coord3D zero;
			zero.x = 0.0f;
			zero.y = 0.0f;
			zero.z = 0.0f;
			newInstMatrix.Set_Translation(zero);
			drawable->setInstanceMatrix(&newInstMatrix, true);

			return UPDATE_SLEEP_FOREVER;
		}

		if ((0.7f * collapseHeight + m_currentHeight) <= 0.0f)
		{
			getRetailModule()->doPhaseStuff(SCPHASE_ALMOST_FINAL, &building->m_position);
			building->m_bodyModule->updateBodyParticleSystems();
		}
	}

	// Retail returns 1 out of the 0.7f tail (+0x03a6 `mov eax,1`) and 1 from the
	// fallthrough, so the tail is not the enum constant zero.
	return (UpdateSleepTime)1;
}
