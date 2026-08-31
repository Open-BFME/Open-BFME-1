// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

struct Rva001A3410Input
{
	char m_padding[0x0C];
	int m_value;
};

class Rva001A3410TerrainVisual
{
public:
	virtual void v00() = 0; virtual void v01() = 0;
	virtual void v02() = 0; virtual void v03() = 0;
	virtual void v04() = 0; virtual void v05() = 0;
	virtual void v06() = 0; virtual void v07() = 0;
	virtual void v08() = 0; virtual void v09() = 0;
	virtual void v10() = 0; virtual void v11() = 0;
	virtual void v12() = 0; virtual void v13() = 0;
	virtual void v14() = 0; virtual void v15() = 0;
	virtual void v16() = 0; virtual void v17() = 0;
	virtual void v18() = 0; virtual void v19() = 0;
	virtual void v20() = 0; virtual void v21() = 0;
	virtual void v22() = 0; virtual void v23() = 0;
	virtual void v24() = 0; virtual void v25() = 0;
	virtual void v26() = 0; virtual void v27() = 0;
	virtual void v28() = 0; virtual void v29() = 0;
	virtual void v30() = 0; virtual void v31() = 0;
	virtual void v32() = 0; virtual void v33() = 0;
	virtual void v34() = 0; virtual void v35() = 0;
	virtual void v36() = 0; virtual void v37() = 0;
	virtual void v38() = 0; virtual void v39() = 0;
	virtual void v40() = 0;
	virtual void dispatch(int value, int ownerValue) = 0;
};

extern "C" Rva001A3410TerrainVisual *g_bfmeTerrainVisual;

class Rva001A3410Owner
{
public:
	void forward(Rva001A3410Input *input, int unused);

private:
	int m_value;
};

void Rva001A3410Owner::forward(Rva001A3410Input *input, int)
{
	g_bfmeTerrainVisual->dispatch(input->m_value, m_value);
}
