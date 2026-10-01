// cl: /O2

class Matrix3D
{
public:
	float Get_Z_Rotation(void) const;
};

class VDispatch4
{
public:
	virtual void v0(int, int, float, int);
	virtual void v1(int, int, float, int);
	virtual void v2(int, int, float, int);
	virtual void v3(int, int, float, int);
	virtual void v4(int, int, float, int);
	virtual void v5(int, int, float, int);
	virtual void v6(int, int, float, int);
	virtual void v7(int, int, float, int);
	virtual void v8(int, int, float, int);
	virtual void v9(int, int, float, int);
	virtual void v10(int, int, float, int);
	virtual void v11(int, int, float, int);
	virtual void v12(int, int, float, int);
	virtual void v13(int, int, float, int);
	virtual void v14(int, int, float, int);
	virtual void v15(int, int, float, int);
	virtual void v16(int, int, float, int);
	virtual void v17(int, int, float, int);
	virtual void v18(int, int, float, int);
	virtual void v19(int, int, float, int);
	virtual void v20(int, int, float, int);
	virtual void v21(int, int, float, int);
	virtual void v22(int, int, float, int);
	virtual void v23(int, int, float, int);
	virtual void v24(int, int, float, int);
	virtual void v25(int, int, float, int);
	virtual void v26(int, int, float, int);
	virtual void v27(int, int, float, int);
	virtual void v28(int, int, float, int);
	virtual void v29(int, int, float, int);
	virtual void v30(int, int, float, int);
	virtual void v31(int, int, float, int);
	virtual void v32(int, int, float, int);
};

// Retail global at 0x012F7014 is GameClient/Terrain/TerrainVisual.cpp's
// TerrainVisual *TheTerrainVisual. This TU keeps its own view of the object
// and casts at the single use, so the mangled name is the canonical one.
class TerrainVisual;

extern TerrainVisual *TheTerrainVisual;

void __stdcall rva001A34C0(int a, int b, Matrix3D *matrix, int extra)
{
	((VDispatch4 *)TheTerrainVisual)->v32(a, b, matrix->Get_Z_Rotation(), extra);
}
