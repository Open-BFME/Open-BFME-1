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
	BFME_VIRTUAL_EIGHT(8, 9, 10, 11, 12, 13, 14, 15)
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
	BFME_VIRTUAL_EIGHT(72, 73, 74, 75, 76, 77, 78, 79)
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

#undef BFME_VIRTUAL_EIGHT
