class BfmeMeshERF;

void __cdecl bfmeDelArrVGP(void *block) throw();

struct BfmeSlotERF
{
	int m_bfmeAERF;
	int m_bfmeBERF;
};

class BfmeMeshVecERF
{
public:
	BfmeMeshVecERF(BfmeMeshERF *mesh);
	~BfmeMeshVecERF(void)
	{
		if (m_bfmeOwnsERF)
			bfmeDelArrVGP(m_bfmeDataERF);
	}

	unsigned char m_bfmeHeadERF[0xc];
	BfmeSlotERF *m_bfmeDataERF;
	char m_bfmeOwnsERF;
	char m_bfmePadERF[3];
};

class BfmeContainerERF
{
public:
	virtual void bfmeAddMeshERF(BfmeMeshERF *mesh);
	void bfmeInsertERF(BfmeMeshVecERF *list, int flags);
};

void BfmeContainerERF::bfmeAddMeshERF(BfmeMeshERF *mesh)
{
	BfmeMeshVecERF list(mesh);
	bfmeInsertERF(&list, 0);
}
