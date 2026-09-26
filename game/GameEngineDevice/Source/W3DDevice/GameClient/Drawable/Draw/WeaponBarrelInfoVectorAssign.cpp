// cl: /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME7: STLport vector<WeaponBarrelInfo>::operator=, retail 0x0076ACD0,
// 300 bytes. Fuzzy twin of Rva00770830VectorAssign.cpp's
// vector<Gen00762250>::operator= (368 B, element width 0x38): same shape,
// element width 0x3C (60) instead of 0x38 (56).
//
// Identity: the head-copy/uninitialized_copy helper call (ILT 0x00036A89,
// gen_small/thunks_026.cpp) forwards to the already-matched
// ??$__copy@PBUWeaponBarrelInfo@ModelConditionInfo@@PAU12@H@_STL@@YAPAU...@Z
// at 0x0075EB00 (W3DModelDraw.cpp) -- the release-build WeaponBarrelInfo
// (ModelConditionInfo::WeaponBarrelInfo, GameClient/Module/W3DModelDraw.h) is
// 3 Ints + a Matrix3D with no _DEBUG/_INTERNAL AsciiString tail, i.e. exactly
// 0x3C (60) bytes, matching the imul-by-0x3C stride this body uses. The
// dealloc call (ILT 0x0000713A) and allocate-and-copy call (ILT 0x0004713B)
// and the shrink-destroy call (ILT 0x0004ABC4) are the width-60 instances of
// the same generic vector helpers the twin uses at width 56.

#include <vector>

struct Matrix3D
{
	float Row[3][4];
};

struct WeaponBarrelInfo
{
	int m_recoilBone;
	int m_fxBone;
	int m_muzzleFlashBone;
	Matrix3D m_projectileOffsetMtx;

	WeaponBarrelInfo();
	WeaponBarrelInfo( const WeaponBarrelInfo & );
	WeaponBarrelInfo &operator=( const WeaponBarrelInfo & );
};

template class _STL::vector<WeaponBarrelInfo>;
