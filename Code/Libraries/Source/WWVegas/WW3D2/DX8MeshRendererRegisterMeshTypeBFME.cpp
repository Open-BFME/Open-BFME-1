// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ?Register_Mesh_Type@DX8MeshRendererClass@@QAEXPAVMeshModelClass@@@Z
// Matched MeshModelClass::Register_For_Rendering (0094F900) proves the owner
// and MeshModelClass* argument. Native renderer/list declarations are reused.
// BFME mesh sort level is +1c (the shared header still has +20); bone link +58.
// Matched constructor 00947170 proves the address-qualified container's
// 0x104-byte allocation, vtable VA0113D05C, four tail words and bool at +100.
// Vtable RVAs by slot: 948B40/94A320/948B60/944C20/945D20/947D00/9471D0.
// Slots 2 and 4 are Add_Mesh(MeshModelClass*) and Check_If_Mesh_Fits(...).
// Registered-list links +bc/+c0 and head VA0134B0E4 agree with the matched
// Unregister_Mesh_Type (00945F20) and Invalidate implementations.
#include "dx8renderer.h"
#include "meshmdl.h"
#include "ww3d.h"
#include "wwmemlog.h"

struct BfmeMeshRegistrationLinks
{
	MeshModelClass **prev;
	MeshModelClass *next;
};

class Rva00947170SkinContainer : public DX8FVFCategoryContainer
{
public:
	Rva00947170SkinContainer(bool sorting, bool skinned)
		: DX8FVFCategoryContainer(skinned ? 0x252 : 0x112, sorting),
		  m_f0(0), m_f4(0), m_f8(0), m_fc(0), m_skinned(skinned)
	{
	}

	virtual ~Rva00947170SkinContainer();
	virtual void Render(void);
	virtual void Add_Mesh(MeshModelClass *mmc);
	virtual void Log(bool only_visible);
	virtual bool Check_If_Mesh_Fits(MeshModelClass *mmc);
	virtual void Add_Delayed_Visible_Material_Pass(MaterialPassClass *pass, MeshClass *mesh);
	virtual void Render_Delayed_Procedural_Material_Passes(void);

	int m_f0;
	int m_f4;
	int m_f8;
	int m_fc;
	bool m_skinned;
};

static __forceinline MeshModelClass *& Bfme_Registered_Mesh_Head()
{
	return *reinterpret_cast<MeshModelClass **>(0x0134B0E4);
}

extern void Add_Rigid_Mesh_To_Container(
	FVFCategoryList *container_list, unsigned fvf, MeshModelClass *mmc);

// ?Register_Mesh_Type@DX8MeshRendererClass@@QAEXPAVMeshModelClass@@@Z
void DX8MeshRendererClass::Register_Mesh_Type(MeshModelClass *mmc)
{
	WWMEMLOG(MEM_GEOMETRY);

	bool skin = (mmc->Get_Flag(MeshModelClass::SKIN) != 0)
		&& (*reinterpret_cast<void * const *>(reinterpret_cast<const char *>(mmc) + 0x58) != 0);
	bool sorting = (!!mmc->Get_Flag(MeshModelClass::SORT)) && WW3D::Is_Sorting_Enabled()
		&& (*reinterpret_cast<const unsigned char *>(reinterpret_cast<const char *>(mmc) + 0x1c) == SORT_LEVEL_NONE);

	if (skin) {
		WWASSERT(texture_category_container_list_skin);

		FVFCategoryListIterator it(texture_category_container_list_skin);
		while (!it.Is_Done()) {
			DX8FVFCategoryContainer *container = it.Peek_Obj();
			if (sorting == container->Is_Sorting() && container->Check_If_Mesh_Fits(mmc)) {
				container->Add_Mesh(mmc);
				return;
			}
			it.Next();
		}

		DX8FVFCategoryContainer *new_container = new Rva00947170SkinContainer(sorting, false);
		texture_category_container_list_skin->Add_Tail(new_container);
		new_container->Add_Mesh(mmc);
		return;
	}

	BfmeMeshRegistrationLinks *links = reinterpret_cast<BfmeMeshRegistrationLinks *>(
		reinterpret_cast<char *>(mmc) + 0xbc);
	if (links->prev != 0) {
		return;
	}

	unsigned fvf = DX8FVFCategoryContainer::Define_FVF(mmc, enable_lighting);
	int i;
	for (i = 0; i < texture_category_container_lists_rigid.Count(); ++i) {
		FVFCategoryList *list = texture_category_container_lists_rigid[i];
		WWASSERT(list);
		DX8FVFCategoryContainer *container = list->Peek_Head();
		if (container != 0 && container->Get_FVF() != fvf) {
			continue;
		}

		Add_Rigid_Mesh_To_Container(list, fvf, mmc);
		break;
	}

	if (i == texture_category_container_lists_rigid.Count()) {
		FVFCategoryList *new_fvf_category = new FVFCategoryList();
		texture_category_container_lists_rigid.Add(new_fvf_category);
		Add_Rigid_Mesh_To_Container(new_fvf_category, fvf, mmc);
	}

	if (!mmc->PolygonRendererList.Is_Empty()) {
		if (links->prev == 0) {
			links->next = Bfme_Registered_Mesh_Head();
			links->prev = &Bfme_Registered_Mesh_Head();
			Bfme_Registered_Mesh_Head() = mmc;
			if (links->next != 0) {
				reinterpret_cast<BfmeMeshRegistrationLinks *>(
					reinterpret_cast<char *>(links->next) + 0xbc)->prev = &links->next;
			}
		}
	}
}
