// ??1DX8MeshRendererClass@@QAE@XZ
// partial score=0.9 date=2026-09-04
// Structural recovery of the MeshRenderer destructor at 0x00949D00.
// The two embedded list members are the BFME build's distinct list bases.

extern char g_bfmeSimpleVectorVtable1292;
extern char g_bfmeVectorBaseVtable1292;

class BfmeSimpleVector1292
{
public:
	__declspec(nothrow) __forceinline ~BfmeSimpleVector1292()
	{
		register void **zero = 0;
		m_vtable = &g_bfmeSimpleVectorVtable1292;
		if (m_vector != zero)
			delete[] m_vector;
		m_vector = zero;
		m_vtable = &g_bfmeVectorBaseVtable1292;
		void **remaining = *reinterpret_cast<void **volatile *>(&m_vector);
		if (remaining != zero)
			delete[] remaining;
		m_vector = zero;
		m_count = 0;
	}

	private:
	void *m_vtable;
	void **m_vector;
	int m_count;
	int m_capacity;
};

class BfmeTextureCategoryList1292
{
public:
	virtual ~BfmeTextureCategoryList1292();

private:
	char m_padding04[0x14];
};

class BfmeFvfCategoryList1292
{
public:
	virtual ~BfmeFvfCategoryList1292();

private:
	char m_padding04[0x14];
};

class DX8MeshRendererClass
{
public:
	~DX8MeshRendererClass();
	void Invalidate(bool shutdown = false);
	void Clear_Pending_Delete_Lists();

private:
	bool m_enableLighting00;
	char m_padding01[3];
	void *m_camera04;
	BfmeSimpleVector1292 m_rigid08;
	BfmeFvfCategoryList1292 *m_skin18;
	BfmeTextureCategoryList1292 m_textureDelete1c;
	BfmeFvfCategoryList1292 m_fvfDelete34;
};

DX8MeshRendererClass::~DX8MeshRendererClass()
{
	Invalidate(true);
	Clear_Pending_Delete_Lists();
	if (m_skin18 != 0)
		delete m_skin18;
}
