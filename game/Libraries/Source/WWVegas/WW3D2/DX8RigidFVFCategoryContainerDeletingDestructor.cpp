// cl: /DNDEBUG /MD /EHsc

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8renderer.h
class DX8RigidFVFCategoryContainer
{
	friend void forceDX8RigidFVFCategoryContainerDeletingDestructorCopy(const DX8RigidFVFCategoryContainer &that);
public:
	virtual ~DX8RigidFVFCategoryContainer();
};


void Force_DX8RigidFVFCategoryContainer_Deleting_Destructor(DX8RigidFVFCategoryContainer *container)
{
	delete container;
}

// ~DX8RigidFVFCategoryContainer is matched out of line (dx8renderer.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceDX8RigidFVFCategoryContainerDeletingDestructorCopy(const DX8RigidFVFCategoryContainer &that)
{
	DX8RigidFVFCategoryContainer value(that);
}
