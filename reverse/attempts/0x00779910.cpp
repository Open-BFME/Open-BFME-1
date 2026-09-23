// ?rva00779910@W3DModelDraw@@QAEXXZ
// partial score=0.95 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Source/WWVegas/WWSaveLoad /Ireference/shims
// stlport
// Retail 0x00779910, 770 bytes, thiscall, no arguments.
//
// Owner: the matched W3DModelDraw destructor at 0x0077B090 tears down the
// vectors at +0x130 (ILT 0x0000B073) and +0x13C (ILT 0x00006730/0x0000B109),
// and name_oracle witnesses +0x34 as W3DModelDraw::m_renderObject.  The sole
// caller, 0x00779F10 through ILT 0x0000CB80, passes its own receiver.  No
// surviving name proves the method spelling, so it stays address-derived.
//
// Each 0x20-byte entry holds a render object, the name of a bone on the
// drawable's model, three rotation angles fed to Rotate_X/Y/Z, and a
// countdown.  While the countdown is positive the object follows the rotated
// bone; once it runs out the bone name is handed to the vector at +0x13C, the
// object leaves the scene and the entry is erased.  The entry type keeps the
// ledger's name, which the out-of-line __copy (0x007748D0) and element
// destructor (0x00769D90) are pinned under.

#define __PLACEMENT_VEC_NEW_INLINE  // always.h defines array placement-new itself
#include "rendobj.h"
#include <string>
#include <vector>

// W3DDisplay::m_3DScene is the global at VA 0x012F8058; slot 3 removes a
// render object, as in W3DModelDrawNukeCurrentRender.cpp.
class RTS3DScene
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void Remove_Render_Object(RenderObjClass *obj);
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

struct Gen_t_00777e90_p32cd
{
	RenderObjClass *m_renderObject;  // +0x00
	std::string m_boneName;          // +0x04
	float m_rotateX;                 // +0x10
	float m_rotateY;                 // +0x14
	float m_rotateZ;                 // +0x18
	int m_countdown;                 // +0x1C
};

class W3DModelDraw
{
public:
	void rva00779910();

private:
	unsigned char m_unmodelled00[0x10];
	void *m_pointer10;                                      // +0x010
	unsigned char m_unmodelled14[0x34 - 0x14];
	RenderObjClass *m_renderObject;                         // +0x034
	unsigned char m_unmodelled38[0x130 - 0x38];
	std::vector<Gen_t_00777e90_p32cd> m_boneFollowers;      // +0x130
	std::vector<std::string> m_releasedBoneNames;           // +0x13C
};

// ?rva00779910@W3DModelDraw@@QAEXXZ
void W3DModelDraw::rva00779910()
{
	if (m_pointer10 == 0 || m_renderObject == 0)
		return;

	std::vector<Gen_t_00777e90_p32cd>::iterator it = m_boneFollowers.begin();
	while (it != m_boneFollowers.end())
	{
		if (it->m_countdown <= 0)
		{
			m_releasedBoneNames.push_back(it->m_boneName);
			W3DDisplay::m_3DScene->Remove_Render_Object(it->m_renderObject);
			it->m_renderObject->Release_Ref();
			it = m_boneFollowers.erase(it);
			continue;
		}

		Gen_t_00777e90_p32cd &follower = *it;
		if (!follower.m_boneName.empty())
		{
			Matrix3D transform = m_renderObject->Get_Bone_Transform(follower.m_boneName.c_str());
			transform.Rotate_X(follower.m_rotateX);
			transform.Rotate_Y(follower.m_rotateY);
			transform.Rotate_Z(follower.m_rotateZ);
			follower.m_renderObject->Set_Transform(transform);
		}
		--follower.m_countdown;
		++it;
	}
}
