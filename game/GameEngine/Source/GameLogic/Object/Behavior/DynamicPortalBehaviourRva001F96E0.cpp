// ?createWaypoints@DynamicPortalBehaviour@@QAEXXZ
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source/GameLogic/Object
// stlport

#define _STLP_NO_EXCEPTIONS 1

#define _Vector_base Rva001F9330VectorBase
#include <vector>
#undef _Vector_base
#include "ascii_string.h"
#include "coord3d.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

#define TRUE true
#define FALSE false

#define BFMEAsciiEmptyString AsciiString::TheEmptyString

class Matrix3D;

#define OBJECT_TU_MEMBERS \
    Int getMultiLogicalBonePosition(const char *boneNamePrefix, Int maxBones, Coord3D *positions, Matrix3D *transforms, Bool convertToWorld, Int extra) const; \
    UnsignedInt rva074() const { return m_id; }
#include "object.h"
#undef OBJECT_TU_MEMBERS

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

// Trivial coordinate copy passed by pointer to the Waypoint constructor.
struct Rva001AB600Arg
{
	Real x, y, z;
};

// Six-dword records copied wholesale from the module data into the node.
struct Rva001F96E0Six
{
	UnsignedInt w[6];
};

// Field view of the Waypoint built through constructor 0x001AB600.
class Rva001A2D50Node
{
public:
	Rva001A2D50Node(Int id, AsciiString name, const Coord3D *location,
		AsciiString s1, AsciiString s2, AsciiString s3, Bool flag, Int kind,
		AsciiString s4);

	void setRva88_001F96E0(const Rva001F96E0Six &mask)
	{
		m_rva84 = TRUE;
		m_rva88 = mask;
	}
	void setRvaA0_001F96E0(Bool value) { m_rvaA0 = value; }

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
	void createWaypoints();

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

// ?createWaypoints@DynamicPortalBehaviour@@QAEXXZ
// Object::getMultiLogicalBonePosition (0x001BFAC0) is defined struct-keyed; the call
// names it through a member pointer.
extern "C" void __identifier("?getMultiLogicalBonePosition@Object@@QBEHPBDHPAUCoord3D@@PAVMatrix3D@@_NH@Z")(void);

void DynamicPortalBehaviour::createWaypoints()
{
	Coord3D positions[16];
	const Rva001F96E0ModuleData *data = getModuleData();
	Bool built = m_built;
	Object *obj = getObject();

	if (!built)
	{
		union { void (*raw)(void); Int (Object::*member)(const char *, Int, Coord3D *, Matrix3D *, Bool, Int) const; } boneCall;
		boneCall.raw = __identifier("?getMultiLogicalBonePosition@Object@@QBEHPBDHPAUCoord3D@@PAVMatrix3D@@_NH@Z");
		(obj->*boneCall.member)(data->m_bonePrefix.str(),
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
				AsciiString("#dynamicportal_wp"), (const Coord3D *)&location,
				BFMEAsciiEmptyString, BFMEAsciiEmptyString, BFMEAsciiEmptyString,
				FALSE, it->second, BFMEAsciiEmptyString);
			node->m_rvaA8 = objectValue;
			node->m_rva68 = TRUE;
			node->m_rva6c = data->m_rva74;
			node->setRva88_001F96E0(data->m_rva8c);
			node->setRvaA0_001F96E0(data->m_rvaC5);
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
		Int last = path[path.size() - 1];
		Int count = path.size();
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
				Rva001A2D50Node *nextNode = m_nodes[next];
				nextNode->m_rva48 = FALSE;
				Rva001A2D50Node *nextNodeAgain = m_nodes[next];
				m_nodes[prev]->m_rva44 = nextNodeAgain;
			}
		}
	}
}
