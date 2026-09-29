// cl: /DNDEBUG /MD /EHs-c-
//
// readable body of ?addShadow@W3DShadowManager@@QAEPAVShadow@@PAVRenderObjClass@@PAUShadowTypeInfo@2@PAVDrawable@@@Z
// retail 0x007B76C0, 147 bytes, converted out of game/gen_asm/d_007b14a0.asm.
//
// BFME asks THREE shadow managers, not the two the Zero Hour source asks for.
// The three receivers are address-proven by the routed targets retail tail-jumps to:
//
//   0x01306F18 -> ILT 0x0001ADA7 -> 0x007BF240 ?addShadow@BfmeVolumetricShadowManager
//   0x01306DF0 -> ILT 0x000172FB -> 0x007B4340 ?addShadow@W3DProjectedShadowManager
//   0x01307178 -> ILT 0x00044882 -> 0x007C3260 ?createShadow@BfmeShadowBufferManager007C3260
//
// Retail lowers this one switch into a 64-entry byte map at 0x00BB7764 and a
// four-entry jump table at 0x00BB7754, both readable in the retail image, so
// every arm below is read out of the table rather than guessed:
//
//   value  1        -> table[0] = 0x00BB773B -> receiver 0x01306DF0 (projected)
//   value  2        -> table[1] = 0x00BB771A -> receiver 0x01306F18 (volumetric)
//   value  3        -> map index 3 = 0x00BB774E, the shared `xor eax,eax; ret 12` arm
//   value  4        -> table[2] = 0x00BB76F0 -> receiver 0x01307178 (buffer)
//   value  0x20     -> table[0] -> 0x01306DF0
//   value  0x40     -> table[0] -> 0x01306DF0
//   value  0x80     -> compared 0x00BB771A -> 0x01306F18
//   value  0x100    -> compared 0x00BB771A -> 0x01306F18
//   value  0x200    -> compared 0x00BB771A -> 0x01306F18
//   value  0x400    -> compared 0x00BB773B -> 0x01306DF0
//   value  0x800    -> compared 0x00BB773B -> 0x01306DF0
//   value  0x1000   -> compared 0x00BB773B -> 0x01306DF0
//
// Every other value in 1..0x40 carries map index 3 = 0x00BB774E, the shared
// `xor eax,eax; ret 12` arm, and 0x41..0x7F fail the range check into the same
// place, so the switch has no label for them -- 3 included.  The names below
// are the ones the shadow managers' roles support; only the VALUES are
// witnessed, by the table.

#define NULL 0

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shadow.h
// BFME widens m_ShadowName to 128 bytes, so m_type sits at +0x80.
class Shadow
{
public:
	struct ShadowTypeInfo
	{
		unsigned char m_shadowNames[0x80];
		int m_type;
	};
};

// The three receivers are the managers of W3DVolumetricShadowManagerAdd.cpp,
// W3DProjectedShadow.cpp and BfmeShadowBufferManagerCreate.cpp; retail
// tail-jumps to their ILT thunks, which is why each name is pinned at the
// thunk in symbols.csv with a route to the body.
//
// The other TUs do not spell the Shadow bases their returns need, and retail
// puts the buffer arm's BfmeShadowResource in the render-object argument slot,
// so both hierarchies are declared here as plain bases: nothing but the
// unconverted pointers moves and no layout is claimed.
class BfmeShadowResource
{
};

class RenderObjClass : public BfmeShadowResource
{
};

class Drawable
{
};

class W3DVolumetricShadow : public Shadow
{
};

class W3DProjectedShadow : public Shadow
{
};

class BfmeVolumetricShadowBufferOwner : public Shadow
{
};

enum ShadowType
{
	SHADOW_NONE = 0,
	SHADOW_DECAL = 0x01,
	SHADOW_VOLUME = 0x02,
	SHADOW_VOLUME_NEW = 0x04,
	SHADOW_ALPHA_DECAL = 0x20,
	SHADOW_ADDITIVE_DECAL = 0x40,
	SHADOW_VOLUME_NON_SELF_1 = 0x80,
	SHADOW_VOLUME_NON_SELF_2 = 0x100,
	SHADOW_VOLUME_NON_SELF_3 = 0x200,
	SHADOW_ALPHA_DECAL_DYNAMIC = 0x400,
	SHADOW_ADDITIVE_DECAL_DYNAMIC = 0x800,
	SHADOW_MERGE_DECAL = 0x1000
};

class BfmeVolumetricShadowManager
{
public:
	W3DVolumetricShadow *addShadow(RenderObjClass *robj,
		Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw);
};

class W3DProjectedShadowManager
{
public:
	W3DProjectedShadow *addShadow(RenderObjClass *robj,
		Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw);
};

class BfmeShadowBufferManager007C3260
{
public:
	BfmeVolumetricShadowBufferOwner *createShadow(BfmeShadowResource *resource,
		Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw);
};

extern BfmeVolumetricShadowManager *g_01306F18;
extern W3DProjectedShadowManager *g_01306DF0;
extern BfmeShadowBufferManager007C3260 *g_01307178;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShadow.h
class W3DShadowManager
{
public:
	Shadow *addShadow(RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw);
};

Shadow *W3DShadowManager::addShadow(
	RenderObjClass *robj, Shadow::ShadowTypeInfo *shadowInfo, Drawable *draw)
{
	ShadowType type = SHADOW_VOLUME;

	if (shadowInfo)
		type = (ShadowType)shadowInfo->m_type;

	switch (type)
	{
		case SHADOW_DECAL:
		case SHADOW_ALPHA_DECAL:
		case SHADOW_ADDITIVE_DECAL:
		case SHADOW_ALPHA_DECAL_DYNAMIC:
		case SHADOW_ADDITIVE_DECAL_DYNAMIC:
		case SHADOW_MERGE_DECAL:
			if (g_01306DF0)
				return g_01306DF0->addShadow(robj, shadowInfo, draw);
			break;

		case SHADOW_VOLUME:
		case SHADOW_VOLUME_NON_SELF_1:
		case SHADOW_VOLUME_NON_SELF_2:
		case SHADOW_VOLUME_NON_SELF_3:
			if (g_01306F18)
				return g_01306F18->addShadow(robj, shadowInfo, draw);
			break;

		case SHADOW_VOLUME_NEW:
			if (g_01307178)
				return g_01307178->createShadow(robj, shadowInfo, draw);
			break;

		default:
			return NULL;
	}

	return NULL;
}
