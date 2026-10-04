// Retail's deallocator here is the replaced global array operator delete[],
// matched at 0x00881EF0 as ??_V@YAXPAX@Z (game/Libraries/Source/WWVegas/
// WWLib/mem_ops.cpp). Naming the operator rather than a private wrapper is
// what makes this TU's reference resolve.
void __cdecl operator delete[](void *block) throw();

class BfmeMeshERF;
class MeshModelClass;

// The 0x00946FE0 constructor this stack local needs is retail's real
// Vertex_Split_Table constructor, matched in
// VertexSplitTableConstructorBFME.cpp; declare it, do not redefine it.
class Vertex_Split_Table
{
public:
	Vertex_Split_Table(MeshModelClass *mesh);

	// Same body as dx8renderer.cpp's inline copy (0x00944BC0): the flag word
	// sits at +0x10 and the array pointer at +0x0C.
	~Vertex_Split_Table(void)
	{
		if (m_bfmeOwnsERF)
			::operator delete[]((void *)m_bfmeDataERF);
	}

	unsigned char m_bfmeHeadERF[0xc];
	struct BfmeSlotERF
	{
		int m_bfmeAERF;
		int m_bfmeBERF;
	} *m_bfmeDataERF;
	char m_bfmeOwnsERF;
	char m_bfmePadERF[3];
};

// The 0x00948820 callee is DX8FVFCategoryContainer::Generate_Texture_Categories,
// matched in DX8FVFCategoryContainerGenerateTextureCategoriesBFME.cpp, which
// declares it in the protected section -- hence the IAE mangling. Declare it
// the same way, with this container befriended so the call below is a plain
// direct call, exactly as retail reaches it. Declared only, so this TU emits
// no vftable of its own.
class BfmeContainerERF;

class DX8FVFCategoryContainer
{
	friend class BfmeContainerERF;

protected:
	void Generate_Texture_Categories(Vertex_Split_Table &split_table,
		unsigned vertex_offset);
};

class BfmeContainerERF
{
public:
	virtual void bfmeAddMeshERF(BfmeMeshERF *mesh);
};

void BfmeContainerERF::bfmeAddMeshERF(BfmeMeshERF *mesh)
{
	Vertex_Split_Table list((MeshModelClass *)mesh);
	((DX8FVFCategoryContainer *)this)->Generate_Texture_Categories(list, 0);
}
