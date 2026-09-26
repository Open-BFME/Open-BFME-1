// d_00295760
// partial score=0.08 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5 WIP candidate for retail 0x00295760 (654 B), dump d_00280010.asm.
// BFME-only UpdateModule near HijackerUpdate/AutoAbilityBehavior in the
// address space -- no Zero Hour twin (grep of reference/CnC_Generals_Zero_Hour
// for the callee names below returned nothing). Adjustor-this pattern matches
// the sibling bodies: incoming ecx (esi) is UpdateModuleInterface-adjusted,
// [esi-0xc] recovers the ModuleData pointer, [esi-8] recovers the Object*.
//
// Shape from python tools/dis_retail.py 0x00295760:
//   - frame gate: nextFrame (self+0x20) vs TheBfmeGameLogic frame, same idiom
//     as the AutoAbilityBehavior body.
//   - a 0x14-byte Coord3D-shaped struct is copied from [object+0x214]'s
//     substructure (+0x38) into self+0x14..+0x27 when object+0x214 is null
//     (an early "no info yet" snapshot path) -- present as the ecx==0 branch
//     at retail +0x40..+0x5d.
//   - the main path (ecx != 0) reads TheTerrainLogic->getHighestLayerForDestination
//     (pinned, still a dump) and GeometryInfo::getMaxHeightAbovePosition
//     (matched) to clamp a height value, calls a BfmeThingPositionSetter
//     (pinned setPosition) and a BfmeDrop987 clear (pinned), sets flags at
//     self+0x10/+0x11, and on the first "landed" transition spawns a particle
//     system through TheParticleSystemManager.
//   - a BfmeWideResult local (built via bfmeForwardWideC, matched) armed with
//     vtable constant 0x1083B5C feeds an exception/log path gated by the
//     layer-height comparisons; not modeled here.
//
// NOT BYTE EXACT -- banked as a partial; only the frame gate and the ecx==0
// snapshot-copy arm are modeled below to establish a compiling structural
// candidate.

typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord3D { Real x, y, z, w, w2; };	// self+0x14..+0x27, 0x14 bytes incl. padding

class GameLogic
{
public:
	unsigned char m_pad000[0x3c];
	int m_frame;
};
extern GameLogic *g_TheBfmeGameLogic0898;

class Object
{
public:
	unsigned char m_pad000[0x214];
	void *m_info214;	// +0x214: null on the "no info yet" branch
};

class ModuleData
{
public:
	unsigned char m_pad000[0xc];
	int m_18;	// self-0xc -> [ecx+0x18], added to the retail frame to seed self+0x20
};

// upstream layout candidate: negative offsets recovered the same way as the
// AutoAbilityBehavior body (this arrives via the UpdateModuleInterface vtable
// slot, adjusted +0x?? from the concrete class start).
class Gen00295760Update
{
public:
	const ModuleData *m_moduleData;	// -0xc
	Object *m_object;					// -8
	unsigned char m_pad000[0x10];
	unsigned char m_flag10;				// +0x10
	unsigned char m_flag11;				// +0x11
	unsigned char m_pad012[0x20 - 0x12];
	int m_nextFrame;					// +0x20
	Coord3D m_snapshot;					// +0x14 (aliases m_flag10/11/pad, see retail +0x4f-0x5a copy)
};

// address-derived name; no Zero Hour twin.
void bfmeUpdate_00295760(Gen00295760Update *self)
{
	if (self->m_nextFrame == -1)
	{
		self->m_nextFrame = self->m_moduleData->m_18 + g_TheBfmeGameLogic0898->m_frame;
	}

	if ((UnsignedInt)self->m_nextFrame > (UnsignedInt)g_TheBfmeGameLogic0898->m_frame)
		return;

	Object *obj = self->m_object;
	if (obj->m_info214 == 0)
	{
		// retail copies a 0x14-byte struct from (info+0x38) into self+0x14;
		// no info pointer yet in this candidate, so nothing to copy.
		return;
	}

	// Remainder of retail body (terrain layer/height clamp, position setter,
	// particle spawn, BfmeWideResult log path) intentionally not yet
	// reproduced -- structural placeholder only.
}
