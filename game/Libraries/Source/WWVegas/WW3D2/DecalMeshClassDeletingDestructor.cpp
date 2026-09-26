// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: DecalMeshClass scalar-deleting destructor at retail RVA
// 0x000FC6F0 (30 bytes). The exact constructor at 0x000FC2E0 installs vtable
// 0x010860C4, whose slot zero routes through ILT 0x0001762A to this wrapper.
// The WW3D class hierarchy corroborates identity; the complete destructor is
// called through ILT 0x00021D14.

class DecalMeshClass
{
public:
	virtual ~DecalMeshClass();
};

void forceDecalMeshClassDeletingDestructor()
{
	DecalMeshClass value;
}
