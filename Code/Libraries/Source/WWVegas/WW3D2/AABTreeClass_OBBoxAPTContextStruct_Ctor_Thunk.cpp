// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the AAB-tree OBBox/APT build context constructor to clean C++.
//
// The vendored Zero Hour tree (aabtree.h) declares OBBoxAPTContextStruct::Box as a
// by-value OBBoxClass copied through the real 97-byte OBBoxClass copy constructor
// (matched at retail 0x00931420). This call site instead resolves to 0x00888400 --
// a second, ICF-folded compile of that same one-argument constructor -- and the very
// next store (context.APT) lands only 4 bytes after context.Box begins, room for one
// handle, not the full 15-float box. So the OBBoxClass this TU sees is a compact
// non-trivial handle whose copy constructor is defined elsewhere (pinned below),
// matching what retail actually built here.

typedef unsigned long uint32;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/obbox.h
class OBBoxClass
{
public:
	OBBoxClass(const OBBoxClass &);
private:
	void *m_unreconstructed_00;
};

template <class T> class SimpleDynVecClass
{
public:
	T &operator[](int index);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/aabtree.h
class AABTreeClass
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/aabtree.h
	struct OBBoxAPTContextStruct
	{
		OBBoxAPTContextStruct(const OBBoxClass &box, SimpleDynVecClass<uint32> &apt);

		OBBoxClass						Box;
		SimpleDynVecClass<uint32> &	APT;
	};
};

// ??0OBBoxAPTContextStruct@AABTreeClass@@QAE@ABVOBBoxClass@@AAV?$SimpleDynVecClass@K@@@Z
AABTreeClass::OBBoxAPTContextStruct::OBBoxAPTContextStruct(const OBBoxClass &box, SimpleDynVecClass<uint32> &apt) :
	Box(box), APT(apt)
{ }
