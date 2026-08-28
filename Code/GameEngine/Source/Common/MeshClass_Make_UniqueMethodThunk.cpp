// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail-layout C++ conversion of MeshClass::Make_Unique.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/meshmdl.h
class MeshModelClass
{
public:
	MeshModelClass(const MeshModelClass &);
	virtual void Delete_This();

	int RefCount;
	char Data[0xC0];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/mesh.h
class MeshClass
{
public:
	void Make_Unique(bool force_meshmdl_clone);

private:
	char Base[0xC8];
	MeshModelClass *Model;
};

void MeshClass::Make_Unique(bool force_meshmdl_clone)
{
	int refs = Model->RefCount;
	if (refs == 1 && !force_meshmdl_clone) {
		return;
	}

	MeshModelClass *newmesh = new MeshModelClass(*Model);
	if (newmesh != 0) {
		++newmesh->RefCount;
	}

	MeshModelClass *oldmesh = Model;
	if (oldmesh != 0) {
		if (--oldmesh->RefCount == 0) {
			oldmesh->Delete_This();
		}
	}
	Model = newmesh;

	if (newmesh != 0) {
		if (--newmesh->RefCount == 0) {
			newmesh->Delete_This();
		}
	}
}
