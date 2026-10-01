// ?rva001f96e0@DynamicPortalBehaviour@@QAEXXZ
// partial score=0.8468 date=2026-10-01
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// Retail returns at +0x3D2, confirming a 979-byte body.
// Caller 0x001F9C20 reaches slot 1 of vtable 0x010A3950, which identifies the receiver as DynamicPortalBehaviour.
// The caller and vtable do not name the method, so the source uses an address-derived name.
// The draft reads each path through begin() and end() accessors.
// It emits 979 bytes with 150 bytes outside relocation operands and seven structural differences.
// The compiler still writes the module pointer at [esp+0x2C], while retail writes it at [esp+0x18].


#define _STLP_NO_EXCEPTIONS 1

#include <vector>
#include "ascii_string.h"
#include "coord3d.h"


typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

#define TRUE true
#define FALSE false

extern const AsciiString BFMEAsciiEmptyString;
#pragma comment(linker, "/alternatename:?BFMEAsciiEmptyString@@3VAsciiString@@B=?TheEmptyString@AsciiString@@2V1@B")

class Matrix3D;

class Object
{
public:
	Int getMultiLogicalBonePosition(const char *boneNamePrefix, Int maxBones,
		Coord3D *positions, Matrix3D *transforms, Bool convertToWorld, Int extra) const;

	UnsignedInt rva074() const { return m_rva074; }

private:
	char m_pad00[0x74];
	UnsignedInt m_rva074;
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	char m_pad00[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class Waypoint;

class Pathfinder
{
public:
	void rva003D84A0(Waypoint *waypoint);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

private:
	char m_pad00[0x0c];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

// Twelve-byte location argument of the node constructor (pinned spelling).
struct Rva001AB600Arg
{
	Real x, y, z;
};

// Six-dword records copied wholesale from the module data into the node.
struct Rva001F96E0Six
{
	UnsignedInt w[6];
};

// The 0xB0-byte node built here (constructor 0x001AB600 via ILT 0x0001ADB1).
class Rva001A2D50Node
{
public:
	Rva001A2D50Node(Int id, AsciiString name, const Rva001AB600Arg &location,
		AsciiString s1, AsciiString s2, AsciiString s3, Bool flag, Int kind,
		AsciiString s4);

	char m_pad00[0x20];
	Rva001A2D50Node *m_links[8];
	Rva001A2D50Node *m_rva40;
	Rva001A2D50Node *m_rva44;
	Bool m_rva48;
	char m_pad49[3];
	Int m_numLinks;
	char m_pad50[0x18];
	Bool m_rva68;
	char m_pad69[3];
	Rva001F96E0Six m_rva6c;
	Bool m_rva84;
	char m_pad85[3];
	Rva001F96E0Six m_rva88;
	Bool m_rvaA0;
	char m_padA1[7];
	UnsignedInt m_rvaA8;
	UnsignedInt m_rvaAC;
};

typedef _STL::vector<Int> Rva001F96E0Path;

struct Rva001F96E0Pair
{
	Int first;
	Int second;
};

class Rva001F96E0ModuleData
{
public:
	char m_pad00[0x70];
	Int m_numBones;
	Rva001F96E0Six m_rva74;
	Rva001F96E0Six m_rva8c;
	AsciiString m_bonePrefix;
	_STL::vector<Rva001F96E0Pair> m_pairs;
	_STL::vector<Rva001F96E0Path> m_paths;
	char m_padC0[5];
	Bool m_rvaC5;
	char m_padC6[0x16];
	Real m_rvaDC;
};

class DynamicPortalBehaviour
{
public:
	void rva001f96e0();

	const Rva001F96E0ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

private:
	void *m_vtable;
	const Rva001F96E0ModuleData *m_moduleData;
	Object *m_object;
	char m_pad0c[0x18];
	Rva001A2D50Node *m_nodes[6];
	Bool m_built;
};

void DynamicPortalBehaviour::rva001f96e0()
{
	Coord3D positions[16];
	const Rva001F96E0ModuleData *data = getModuleData();
	Bool built = m_built;
	Object *obj = getObject();

	if (!built)
	{
		obj->getMultiLogicalBonePosition(data->m_bonePrefix.str(),
			data->m_numBones, positions, NULL, TRUE, 0);

		UnsignedInt startFrame = 0;
		if (data->m_rvaDC > 0.0f)
			startFrame = TheGameLogic->getFrame() - (Int)(data->m_rvaDC * -5.0f);

		UnsignedInt objectValue = getObject()->rva074();
		Int i = 0;
		for (_STL::vector<Rva001F96E0Pair>::const_iterator it = data->m_pairs.begin();
			it != data->m_pairs.end(); ++it, ++i)
		{
			const Coord3D *src = &positions[it->first];
			Rva001AB600Arg location = *(const Rva001AB600Arg *)src;
			Rva001A2D50Node *node = new Rva001A2D50Node(0x7ffffffe,
				AsciiString("#dynamicportal_wp"), location,
				BFMEAsciiEmptyString, BFMEAsciiEmptyString, BFMEAsciiEmptyString,
				FALSE, it->second, BFMEAsciiEmptyString);
			node->m_rvaA8 = objectValue;
			node->m_rva68 = TRUE;
			node->m_rva6c = data->m_rva74;
			node->m_rva84 = TRUE;
			node->m_rvaA0 = data->m_rvaC5;
			node->m_rva88 = data->m_rva8c;
			if (startFrame > 0)
				node->m_rvaAC = startFrame;
			m_nodes[i] = node;
		}
		m_built = TRUE;
	}

	for (_STL::vector<Rva001F96E0Path>::const_iterator pathIt = data->m_paths.begin();
		pathIt != data->m_paths.end(); ++pathIt)
	{
		Rva001F96E0Path path = *pathIt;
		Int first = *path.begin();
		Int count = path.size();
		Int last = *(path.end() - 1);
		if (!built)
		{
			Rva001A2D50Node *end = m_nodes[last];
			Rva001A2D50Node *start = m_nodes[first];
			if (start->m_numLinks < 8)
			{
				start->m_links[start->m_numLinks] = end;
				++start->m_numLinks;
			}
			end->m_rva40 = start;
		}
		TheAI->pathfinder()->rva003D84A0((Waypoint *)m_nodes[first]);
		if (!built)
		{
			for (Int j = 0; j < count - 2; ++j)
			{
				Int next = *(path.begin() + j + 1);
				Int prev = *(path.begin() + j);
				m_nodes[next]->m_rva48 = FALSE;
				m_nodes[prev]->m_rva44 = m_nodes[next];
			}
		}
	}
}
