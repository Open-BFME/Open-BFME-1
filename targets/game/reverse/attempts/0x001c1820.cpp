// ?getSingleLogicalBonePositionOnTurret@Object@@QBE_NW4WhichTurretType@@PBDPAUCoord3D@@PAVMatrix3D@@@Z
// partial score=0.99 date=2026-09-27
// STASH for ?getSingleLogicalBonePositionOnTurret@Object@@QBE_NW4WhichTurretType@@PBDPAUCoord3D@@PAVMatrix3D@@@Z @ 0x001C1820 (1008B).
// Placement: game/GameEngine/Source/GameLogic/Object/Object.cpp, replacing the
// present-unmatched ZH-literal body that precedes Object::getMultiLogicalBonePosition.
// Requires TU context above the insertion point: BFME_OBJ_AI macro (m_ai@0x204) and
// BFMEDrawableBoneQuery (6-arg getPristineBonePositions, ret 0x18). Probe 2026-09-27:
// size 1008=1008, 8 non-reloc bytes differ, all FPU-stack scheduling at +01a7/+01a9/+01ab/+01af
// (second turnAdjustment.Translate row 0: retail evaluates R02*(-z) first via fld st(2),
// MSVC evaluates R01*(-y) first via reload of [esp+0x3c]). Tried: assignment-in-condition
// (worse: prologue order), TU-local __forceinline Translate view with ZH/left, reversed,
// and right associations (same 8B core, or worse). Suspect BFME WWMath header micro-difference.

// Retail reaches the drawable through Object vtable slot +0x28 (the slot
// BfmeDefectObjectVtableView below witnesses for getDrawable) and reads BFME
// m_ai at +0x204 directly (BFME_OBJ_AI above); the ZH-layout header this TU
// compiles against keeps both members inline at other offsets, so the body
// spells both explicitly. BFME Drawable::getPristineBonePositions takes 6
// stack args (ret 0x18), so the bone query uses the BFMEDrawableBoneQuery
// view above, like Object::getSingleLogicalBonePosition does.
// ?getSingleLogicalBonePositionOnTurret@Object@@QBE_NW4WhichTurretType@@PBDPAUCoord3D@@PAVMatrix3D@@@Z
class BfmeTurretDrawableView
{
public:
#define BFME_TURRET_SLOT(n) virtual void slot##n(void) = 0;
	BFME_TURRET_SLOT(00) BFME_TURRET_SLOT(01)
	BFME_TURRET_SLOT(02) BFME_TURRET_SLOT(03)
	BFME_TURRET_SLOT(04) BFME_TURRET_SLOT(05)
	BFME_TURRET_SLOT(06) BFME_TURRET_SLOT(07)
	BFME_TURRET_SLOT(08) BFME_TURRET_SLOT(09)
	virtual Drawable *getDrawable(void) = 0;
#undef BFME_TURRET_SLOT
};
Bool Object::getSingleLogicalBonePositionOnTurret( WhichTurretType whichTurret, const char* boneName, Coord3D* position, Matrix3D* transform ) const
{
	Coord3D turretPosition;
	Coord3D bonePosition;
	Drawable *drawable = reinterpret_cast<BfmeTurretDrawableView *>(const_cast<Object *>(this))->getDrawable();
	AIUpdateInterface *ai = BFME_OBJ_AI(this);
	if( drawable == NULL  || ai == NULL )
		return FALSE;

	// We need to find the TurretBone's pristine position.
	drawable->getProjectileLaunchOffset( PRIMARY_WEAPON, 1, NULL, whichTurret, &turretPosition, NULL );
	// And the required bone's pristine position
	if( reinterpret_cast<const BFMEDrawableBoneQuery *>(drawable)->getPristineBonePositions(boneName, 0, &bonePosition, NULL, 1, 0) != 1 )
		return FALSE;
	//Then we mojo the Logic position of the required bone like Missile firing does.  Using the logic twist of the turret
	Real turretRotation;
	ai->getTurretRotAndPitch( whichTurret, &turretRotation, NULL );

	Matrix3D boneOffset(TRUE);// This will be from the turret to the requested bone

//	Vector3 bonePositionVector(	bonePosition.x - turretPosition.x, 
//															bonePosition.y - turretPosition.y, 
//															bonePosition.z - turretPosition.z );
	Vector3 bonePositionVector(	bonePosition.x, 
															bonePosition.y, 
															bonePosition.z );
	boneOffset.Translate(bonePositionVector);

	Matrix3D turnAdjustment(TRUE);// this is the turret twist to be applied to the final answer

	turnAdjustment.Translate( turretPosition.x, turretPosition.y, turretPosition.z );
	turnAdjustment.In_Place_Pre_Rotate_Z(turretRotation);
	turnAdjustment.Translate( -turretPosition.x, -turretPosition.y, -turretPosition.z );

	Matrix3D boneLogicTransform;
	boneLogicTransform.mul( turnAdjustment, boneOffset );

	Matrix3D worldTransform;
	convertBonePosToWorldPos(NULL, &boneLogicTransform, NULL, &worldTransform);

	Vector3 tmp = worldTransform.Get_Translation();
	Coord3D worldPos;
	worldPos.x = tmp.X;
	worldPos.y = tmp.Y;
	worldPos.z = tmp.Z;

	if( position )
		*position = worldPos;
	if( transform )
		*transform = worldTransform;

	return TRUE;
}
