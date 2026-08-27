// cl: /DNDEBUG /MD /EHsc

// BFME RingRenderObjClass::Prepare_LOD, retail 0x00919900. The focused ABI
// slice is anchored by the real Ring vftable at 0x00D3AD28 and the unique
// RingRenderObjClass::Get_Cost entry at slot 75.

class CameraClass;

#define BFME_VIRTUAL_EIGHT(a, b, c, d, e, f, g, h) \
	virtual void Dummy##a(); virtual void Dummy##b(); \
	virtual void Dummy##c(); virtual void Dummy##d(); \
	virtual void Dummy##e(); virtual void Dummy##f(); \
	virtual void Dummy##g(); virtual void Dummy##h();

class RingRenderObjClass
{
public:
	BFME_VIRTUAL_EIGHT(0, 1, 2, 3, 4, 5, 6, 7)
	virtual void Dummy8();
	virtual void Dummy9();
	virtual int Get_Num_Polys(void) const;
	virtual void Dummy11();
	virtual void Dummy12();
	virtual void Dummy13();
	virtual void Dummy14();
	virtual void Dummy15();
	BFME_VIRTUAL_EIGHT(16, 17, 18, 19, 20, 21, 22, 23)
	BFME_VIRTUAL_EIGHT(24, 25, 26, 27, 28, 29, 30, 31)
	BFME_VIRTUAL_EIGHT(32, 33, 34, 35, 36, 37, 38, 39)
	BFME_VIRTUAL_EIGHT(40, 41, 42, 43, 44, 45, 46, 47)
	BFME_VIRTUAL_EIGHT(48, 49, 50, 51, 52, 53, 54, 55)
	BFME_VIRTUAL_EIGHT(56, 57, 58, 59, 60, 61, 62, 63)
	virtual void Dummy64();
	virtual void Dummy65();
	virtual void Dummy66();
	virtual void Dummy67();
	virtual void Dummy68();
	virtual void Dummy69();
	virtual void Dummy70();
	virtual void Prepare_LOD(CameraClass &camera);
	virtual void Dummy72();
	virtual void Dummy73();
	virtual void Dummy74();
	virtual float Get_Cost(void) const;
	virtual float Get_Value(void) const;
	virtual float Get_Post_Increment_Value(void) const;
	virtual void Dummy78();
	virtual void Dummy79();
	BFME_VIRTUAL_EIGHT(80, 81, 82, 83, 84, 85, 86, 87)
	virtual void Dummy88();
	virtual float Get_Screen_Size(CameraClass &camera);

private:
	unsigned char PaddingToLODCount[0xC4];
	unsigned int LODCount;					// +0x0C8
	unsigned char PaddingToScreenArea[4];
	float ScreenArea;					// +0x0D0
	unsigned char PaddingToCurrentLOD[0x50];
	unsigned int CurrentLOD;					// +0x124
};

// ?Prepare_LOD@RingRenderObjClass@@UAEXAAVCameraClass@@@Z
void RingRenderObjClass::Prepare_LOD(CameraClass &camera)
{
	ScreenArea = Get_Screen_Size(camera);
	CurrentLOD = CurrentLOD >= LODCount ? LODCount : CurrentLOD;
}

// ?Get_Value@RingRenderObjClass@@UBEMXZ
float RingRenderObjClass::Get_Value(void) const
{
	if (CurrentLOD == 0) {
		return 3.402823466e+38F;
	}

	float polygon_count = (float)Get_Num_Polys();
	float coverage =
		(1.0F - 0.5F / (polygon_count * polygon_count)) * ScreenArea;
	return coverage / Get_Cost();
}

#undef BFME_VIRTUAL_EIGHT
