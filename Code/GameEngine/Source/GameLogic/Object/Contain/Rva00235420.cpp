// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "Lib/BaseType.h"
#include "WWMath/matrix3d.h"

// The original owner is not proved, so retain the address in the name. The
// matched 0x00235380 body independently shows the circular list at this-0xAC,
// three-pointer nodes, and the same virtual slots 7 and 16.
struct Rva00235420Node
{
	Rva00235420Node *next;
	Rva00235420Node *previous;
	void *item;
};

class Rva00235420Owner
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual Coord3D *slot7(Coord3D *scratch, void *item, Real *angle);
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	void rva00235420(const Matrix3D &source);
};

class BfmeThing941F
{
public:
	void bfmeTwo941F(void *value);
};

void Rva00235420Owner::rva00235420(const Matrix3D &source)
{
	slot16();
	Real angle;
	Matrix3D matrix(source);
	Rva00235420Node *volatile *list =
		(Rva00235420Node *volatile *)((char *)this - 0xac);
	Rva00235420Node *head = *list;
	Rva00235420Node *node = head->next;
	if (node != head)
	{
		do
		{
			void *item = node->item;
			Coord3D scratch;
			Coord3D position = *slot7(&scratch, item, &angle);
			matrix[0][3] = position.x;
			matrix[1][3] = position.y;
			matrix[2][3] = position.z;
			((BfmeThing941F *)item)->bfmeTwo941F(&matrix);
			node = node->next;
		} while (node != *list);
	}
}
