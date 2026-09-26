// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/shims
#include "rendobj.h"
// ?bindTrack@TerrainTracksRenderObjClassSystem@@QAEPAVTerrainTracksRenderObjClass@@PAVRenderObjClass@@MPBD11@Z
// Complete retail 0x0072FCA0..0x0072FD3B (155 bytes), RET20.
// BFME extends the ZH bindTrack algorithm with caller-supplied bone names.
// Free/used heads +14/+10 are independently witnessed by name_oracle and
// the matched system constructor; track links +12FC/+1300 and bound+12ED
// are checked against this full body and the matched init.
// Keep the REAL static helper in this TU. VC7.1 then chooses the witnessed
// private ESI/ECX/stack ABI automatically. Both this caller and the helper's
// complete 201 bytes at 0x0072FBA0 are independently byte-exact. The helper
// is already claimed by W3DTerrainTracks.cpp and adds no new byte credit.
// BFME retail 0x0072FCA0: bind a terrain track object from the free list.

typedef unsigned char Bool;

class TerrainTracksRenderObjClass
{
public:
	void init(float width, float length, const char *texture);
	unsigned char m_pad00[0x12ED];
	Bool m_bound;
	unsigned char m_pad12EE[0x0E];
	TerrainTracksRenderObjClass *m_nextSystem;
	TerrainTracksRenderObjClass *m_prevSystem;
};

class TerrainTracksRenderObjClassSystem
{
public:
	TerrainTracksRenderObjClass *bindTrack(RenderObjClass *owner, float length,
		const char *texture, const char *leftBone, const char *rightBone);

private:
	unsigned char m_pad00[0x10];
	TerrainTracksRenderObjClass *m_usedModules;
	TerrainTracksRenderObjClass *m_freeModules;
};

static float computeTrackSpacing(RenderObjClass *renderObj, const char *leftBone, const char *rightBone) {
    float trackSpacing = 14.0f;
    int leftTrack, rightTrack;
    rightTrack = renderObj->Get_Bone_Index(leftBone);
    leftTrack = renderObj->Get_Bone_Index(rightBone);
    if (rightTrack != 0 && leftTrack != 0) {
        Vector3 leftPos,rightPos;
        leftPos=renderObj->Get_Bone_Transform(rightTrack).Get_Translation();
        rightPos=renderObj->Get_Bone_Transform(leftTrack).Get_Translation();
        rightPos -= leftPos;
        trackSpacing = rightPos.Length()+4.0f;
    }
    return trackSpacing;
}

TerrainTracksRenderObjClass *TerrainTracksRenderObjClassSystem::bindTrack(
	RenderObjClass *renderObject, float length, const char *texture,
	const char *leftBone, const char *rightBone)
{
	TerrainTracksRenderObjClass *mod;

	mod = m_freeModules;
	if (mod)
	{
		if (mod->m_nextSystem)
			mod->m_nextSystem->m_prevSystem = mod->m_prevSystem;
		if (mod->m_prevSystem)
			mod->m_prevSystem->m_nextSystem = mod->m_nextSystem;
		else
			m_freeModules = mod->m_nextSystem;

		mod->m_prevSystem = 0;
		mod->m_nextSystem = m_usedModules;
		if (m_usedModules)
			m_usedModules->m_prevSystem = mod;
		m_usedModules = mod;
		mod->init(computeTrackSpacing(renderObject, leftBone, rightBone),
			length, texture);
		mod->m_bound = 1;
	}

	return mod;
}
