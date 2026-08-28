// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DynamicShroudClearingRangeUpdate::killGridDecals, retail 0x0028E3A0.
//
// The Zero Hour body unchanged. The two numbers retail bakes in both agree
// with the ZH header: the loop runs GRID_FX_DECAL_COUNT (30) times and steps
// 0x10 bytes -- sizeof(RadiusDecal), eight bytes more than RadiusDecalUpdate.cpp
// spells because that file never indexes an array of them -- and the array base
// is this+0x50.
//
// Spelled locally rather than ported whole: the ZH translation unit is not in
// the tree, and the only thing this body needs from it is where m_gridDecal
// starts.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecal
{
public:
	void clear();									///< shared with RadiusDecalUpdate; ILT 0x0004A8A9

private:
	const void *m_template;
	void *m_decal;
	// Retail steps the array by 0x10, so RadiusDecal is sixteen bytes.
	// RadiusDecalUpdate.cpp spells only the first eight -- it reaches a single
	// decal at a fixed offset and never indexes an array, so the size never
	// shows there.
	char m_unreconstructed_08[0x10 - 8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DynamicShroudClearingRangeUpdate.h
class DynamicShroudClearingRangeUpdate
{
public:
	void killGridDecals();

private:
	char m_unreconstructed_00[0x50];				///< retail reaches the array at this+0x50
	RadiusDecal m_gridDecal[30];					///< GRID_FX_DECAL_COUNT
};

//-------------------------------------------------------------------------------------------------
// ?killGridDecals@DynamicShroudClearingRangeUpdate@@QAEXXZ
void DynamicShroudClearingRangeUpdate::killGridDecals()
{
	for (int d = 0; d < 30; ++d)
	{
		m_gridDecal[d].clear();
	}

}
