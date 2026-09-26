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
	virtual void bfmeV2(void);
	virtual void Clear(void);

	BfmeRefObj **m_vector;					// +0x04
	int m_max;						// +0x08
	int m_pad;						// +0x0C
	int m_count;						// +0x10
	int m_growth;						// +0x14
};

class Gen_0092F4B0
{
public:
	void bfmeReset(void);

private:
	BfmeVecCX m_shaders;					// +0x00
	BfmeVecCX m_vmats;					// +0x18
	BfmeVecCX m_textures;					// +0x30
};

// ?bfmeReset@Gen_0092F4B0@@QAEXXZ
void Gen_0092F4B0::bfmeReset(void)
{
	int i = 0;

	if (m_vmats.m_count > 0)
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

	m_textures.Clear();
	m_vmats.Clear();
	m_shaders.Clear();
}
