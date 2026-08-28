// cl: /DNDEBUG /MD /EHsc

// Slot 0 of the vtable at 0x0113DE30, the base of DefaultStaticSortListClass.
//
// The same misreading as LocalFileSystem, reached the same way and corrected by
// the same evidence. ??1DefaultStaticSortListClass stores 0x0113DE30, which made
// the table look like its own, but that store sits at +0x43 rather than at the
// top -- it is the inlined base destructor running after the derived one, not
// the derived class installing its vptr.
//
// DefaultStaticSortListClass's own table is 0x0113DE3C, installed twice from its
// own code, and its deleting stub at 0x009581E0 is slot 0 of that. So the table
// twelve bytes below belongs to the class it derives from, which static_sort_list.h
// names StaticSortListClass.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/static_sort_list.h
class StaticSortListClass
{
public:
	virtual ~StaticSortListClass(void);
};

// ??_GStaticSortListClass@@UAEPAXI@Z
StaticSortListClass::~StaticSortListClass(void)
{
}
