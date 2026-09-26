// Retail RVA 0x00955A00 (71 bytes). The owner is independently established;
// the exact retail method name is unknown, so the banked bfmeSetWG is retained.
// Invalidating cached bounds is unconditional, including an out-of-range index.
//
// Independent evidence:
// - W3DStreakDraw::streakBody0077D6B0 passes (index, Vector3, width) to this
//   body through the streak object.
// - BfmeStreakObject's matched constructor at 0x009566D0 and its matched
//   Cast_Ray/Get_Obj_Space_Bounding_Box bodies establish the RenderObjClass
//   base, point data at +0xC8 and width data at +0xD8.
// - RenderObjClass::Invalidate_Cached_Bounding_Volumes() is the canonical
//   source-level operation for retail's `and [this+0x10],0xfffdffff` tail.
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

#include "rendobj.h"
#include "simplevec.h"
#include "vector3.h"

class BfmeStreakObject : public RenderObjClass
{
public:
	void bfmeSetWG(unsigned int index, const Vector3 *value, float amount);

private:
	SimpleDynVecClass<Vector3> m_points;
	SimpleDynVecClass<float> m_widths;
};

// ?bfmeSetWG@BfmeStreakObject@@QAEXIPBVVector3@@M@Z
void BfmeStreakObject::bfmeSetWG(unsigned int index, const Vector3 *value, float amount)
{
	if (index < (unsigned int)m_points.Count())
	{
		m_points[index] = *value;
		m_widths[index] = amount;
	}
	Invalidate_Cached_Bounding_Volumes();
}
