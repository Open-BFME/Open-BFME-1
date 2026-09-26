// cl: /DNDEBUG /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
/*
**	Command & Conquer Generals(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// The gap-filler hash tables of WW3D2/meshmdl.cpp: TriangleSide, SideIndexInfo
// and the two HashTemplateClass instantiations built on them, verbatim from the
// Zero Hour reference (Libraries/Source/WWVegas/WW3D2/meshmdl.cpp lines 369-440).
// Carried in their own TU because the rest of meshmdl.cpp reaches DX8 and the
// PlatformSDK, which the fleet toolchains do not have; only these file-local
// types and the templates they instantiate are needed to emit these bodies.

#include "hashtemplate.h"
#include "vector3.h"

struct TriangleSide
{
	Vector3 loc1;
	Vector3 loc2;
	TriangleSide(const Vector3& l1,const Vector3& l2);
	TriangleSide() {}

	bool operator== (const TriangleSide& s);
};

TriangleSide::TriangleSide(const Vector3& l1,const Vector3& l2)
{
	int i1=*(int*)&l1[0];
	i1=37*i1+*(int*)&l1[1];
	i1=37*i1+*(int*)&l1[2];
	int i2=*(int*)&l2[0];
	i2=37*i2+*(int*)&l2[1];
	i2=37*i2+*(int*)&l2[2];
	if (i1<i2) {
		loc1=l1;
		loc2=l2;
	}
	else {
		loc2=l1;
		loc1=l2;
	}
}

bool TriangleSide::operator== (const TriangleSide& s)
{
	unsigned i=*(unsigned*)&loc1[0]^*(unsigned*)&s.loc1[0];
	i|=*(unsigned*)&loc1[1]^*(unsigned*)&s.loc1[1];
	i|=*(unsigned*)&loc1[2]^*(unsigned*)&s.loc1[2];
	i|=*(unsigned*)&loc2[0]^*(unsigned*)&s.loc2[0];
	i|=*(unsigned*)&loc2[1]^*(unsigned*)&s.loc2[1];
	i|=*(unsigned*)&loc2[2]^*(unsigned*)&s.loc2[2];
	return !i;
}

// Get_Hash_Value specialization for Vector3.

template <> inline unsigned int HashTemplateKeyClass<Vector3>::Get_Hash_Value(const Vector3& location)
{
	const unsigned char* buffer=(const unsigned char*)&location;
	unsigned int hval=0;
	for (unsigned int a=0;a<sizeof(Vector3);++a) {
		hval+=37*hval+buffer[a];
	}
	return hval;
}

// Get_Hash_Value specialization for TriangleSide.

template <> inline unsigned int HashTemplateKeyClass<TriangleSide>::Get_Hash_Value(const TriangleSide& side)
{
	const unsigned char* buffer=(const unsigned char*)&side;
	unsigned int hval=0;
	for (unsigned int a=0;a<sizeof(TriangleSide);++a) {
		hval+=37*hval+buffer[a];
	}
	return hval;
}

struct SideIndexInfo
{
	unsigned short vidx1;
	unsigned short vidx2;
	unsigned polygon_index;
	SideIndexInfo() : vidx1(0), vidx2(0), polygon_index(0) {}
	SideIndexInfo(int i) { WWASSERT(0); }
};

HashTemplateClass<Vector3, unsigned> LocationHash;
HashTemplateClass<TriangleSide,SideIndexInfo> SideHash;

// Member-wise rather than whole-class: HashTemplateClass::Remove and the
// two-argument Exists compare ValueTypes, and SideIndexInfo has no operator==,
// so instantiating the whole class does not compile (nor did it in Zero Hour).
template void HashTemplateClass<Vector3,unsigned>::Insert(const Vector3&, const unsigned&);
template bool HashTemplateClass<Vector3,unsigned>::Exists(const Vector3&) const;
template void HashTemplateClass<Vector3,unsigned>::Remove_All(void);
template void HashTemplateClass<TriangleSide,SideIndexInfo>::Insert(const TriangleSide&, const SideIndexInfo&);
template bool HashTemplateClass<TriangleSide,SideIndexInfo>::Exists(const TriangleSide&) const;
template void HashTemplateClass<TriangleSide,SideIndexInfo>::Remove_All(void);
template SideIndexInfo HashTemplateClass<TriangleSide,SideIndexInfo>::Get(const TriangleSide&) const;

unsigned int (*const Vector3_Hash_Address)(const Vector3&) = &HashTemplateKeyClass<Vector3>::Get_Hash_Value;
