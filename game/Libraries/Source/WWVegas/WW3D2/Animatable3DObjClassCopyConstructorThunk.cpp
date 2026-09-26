// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
#define Matrix4x4 Matrix4
#include "winbase_shim.h"

#include "animobj.h"
#include "htree.h"
#include "assetmgr.h"
#include "hanim.h"
#include "hcanim.h"
#include "ww3d.h"
#include "wwmemlog.h"
#include "animatedsoundmgr.h"

// ??0Animatable3DObjClass@@QAE@ABV0@@Z
Animatable3DObjClass::Animatable3DObjClass(const Animatable3DObjClass & src) :
	CompositeRenderObjClass(src),
	IsTreeValid(0),
	CurMotionMode(BASE_POSE),
	HTree(NULL),
	_bfme_a3o_v0(NULL)
{
   // Inline struct members can't be initialized in init list for some reason...
	ModeAnim.Motion=NULL;
	ModeAnim.Frame=0.0f;
	ModeAnim.PrevFrame=0.0f;
	ModeAnim.LastSyncTime=WW3D::Get_Sync_Time();
	ModeAnim.frameRateMultiplier=1.0;	// 020607 srj -- added
	ModeAnim.animDirection=1.0;	// 020607 srj -- added
	ModeInterp.Motion0=NULL;
	ModeInterp.Motion1=NULL;
	ModeInterp.Frame0=0.0f;
	ModeInterp.Frame1=0.0f;
	ModeInterp.Percentage=0.0f;
	ModeCombo.AnimCombo=NULL;

	*this = src;
}
