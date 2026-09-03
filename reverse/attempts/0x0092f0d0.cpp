// ?bfmeFree@Gen_0092F0D0@@QAEXXZ
// partial score=0.91 date=2026-09-02
class BfmeRefObj
{
public:
	virtual void bfmeDelete(void);
	int m_refs;						// +0x04
};

class BfmeVecCX
{
public:
	virtual void bfmeV0(void);
	virtual void bfmeV1(void);
	virtual void Resize(int newsize, void *array);
	virtual void Clear(void);

	BfmeRefObj **m_vector;					// +0x04
	int m_max;						// +0x08
	int m_pad;						// +0x0C
	int m_count;						// +0x10
	int m_growth;						// +0x14
};

class Gen_0092F0D0
{
public:
	void bfmeFree(void);

private:
	void *m_vptr;						// +0x00
	int m_refs;						// +0x04
	BfmeVecCX m_vmats;					// +0x08
	BfmeVecCX m_textures;					// +0x20
};

// ?bfmeFree@Gen_0092F0D0@@QAEXXZ
void Gen_0092F0D0::bfmeFree(void)
{
	int count = m_vmats.m_count;
	int i = 0;

	if (count > 0)
	{
		while (i < m_vmats.m_count)
		{
			BfmeRefObj *obj = m_vmats.m_vector[i];

			if (obj)
			{
				if (--obj->m_refs == 0)
					obj->bfmeDelete();

				m_vmats.m_vector[i] = 0;
			}

			i++;
		}
	}

	int vmax = m_vmats.m_max;
	m_vmats.Clear();
	m_vmats.Resize(vmax, 0);

	int tmax = m_textures.m_max;
	m_textures.Clear();
	m_textures.Resize(tmax, 0);
}
