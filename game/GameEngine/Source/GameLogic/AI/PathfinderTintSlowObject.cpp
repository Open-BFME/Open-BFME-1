// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME-specific file-static helper at retail RVA 0x003DAB50 (159 bytes).
// The slow-request timing arm of Pathfinder::processPathfindQueue calls it;
// its only other call is the recursive visit below.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef unsigned int UnsignedInt;
typedef float Real;

struct RGBColor
{
	Real red;
	Real green;
	Real blue;
};

class Drawable
{
public:
	void applyTint(RGBColor color, UnsignedInt preColorTime,
		UnsignedInt postColorTime, UnsignedInt sustainedColorTime,
		Real frequency, Real amplitude);

	unsigned char m_unmodelled[0x114];
	UnsignedInt m_status;
};

class Object;
typedef _STL::list<Object *> ContainedItemsList;

#define BFME_CONTAIN_SLOT(n) virtual void containSlot##n();
class ContainModuleInterface
{
public:
	BFME_CONTAIN_SLOT(0) BFME_CONTAIN_SLOT(1) BFME_CONTAIN_SLOT(2)
	BFME_CONTAIN_SLOT(3) BFME_CONTAIN_SLOT(4) BFME_CONTAIN_SLOT(5)
	BFME_CONTAIN_SLOT(6) BFME_CONTAIN_SLOT(7) BFME_CONTAIN_SLOT(8)
	BFME_CONTAIN_SLOT(9) BFME_CONTAIN_SLOT(10) BFME_CONTAIN_SLOT(11)
	BFME_CONTAIN_SLOT(12) BFME_CONTAIN_SLOT(13) BFME_CONTAIN_SLOT(14)
	BFME_CONTAIN_SLOT(15) BFME_CONTAIN_SLOT(16) BFME_CONTAIN_SLOT(17)
	BFME_CONTAIN_SLOT(18) BFME_CONTAIN_SLOT(19) BFME_CONTAIN_SLOT(20)
	BFME_CONTAIN_SLOT(21) BFME_CONTAIN_SLOT(22) BFME_CONTAIN_SLOT(23)
	BFME_CONTAIN_SLOT(24) BFME_CONTAIN_SLOT(25) BFME_CONTAIN_SLOT(26)
	BFME_CONTAIN_SLOT(27) BFME_CONTAIN_SLOT(28) BFME_CONTAIN_SLOT(29)
	BFME_CONTAIN_SLOT(30) BFME_CONTAIN_SLOT(31) BFME_CONTAIN_SLOT(32)
	BFME_CONTAIN_SLOT(33) BFME_CONTAIN_SLOT(34) BFME_CONTAIN_SLOT(35)
	BFME_CONTAIN_SLOT(36) BFME_CONTAIN_SLOT(37) BFME_CONTAIN_SLOT(38)
	BFME_CONTAIN_SLOT(39) BFME_CONTAIN_SLOT(40) BFME_CONTAIN_SLOT(41)
	BFME_CONTAIN_SLOT(42) BFME_CONTAIN_SLOT(43) BFME_CONTAIN_SLOT(44)
	BFME_CONTAIN_SLOT(45) BFME_CONTAIN_SLOT(46) BFME_CONTAIN_SLOT(47)
	BFME_CONTAIN_SLOT(48) BFME_CONTAIN_SLOT(49) BFME_CONTAIN_SLOT(50)
	BFME_CONTAIN_SLOT(51) BFME_CONTAIN_SLOT(52) BFME_CONTAIN_SLOT(53)
	BFME_CONTAIN_SLOT(54) BFME_CONTAIN_SLOT(55) BFME_CONTAIN_SLOT(56)
	BFME_CONTAIN_SLOT(57) BFME_CONTAIN_SLOT(58) BFME_CONTAIN_SLOT(59)
	BFME_CONTAIN_SLOT(60) BFME_CONTAIN_SLOT(61) BFME_CONTAIN_SLOT(62)
	BFME_CONTAIN_SLOT(63) BFME_CONTAIN_SLOT(64)
	virtual const ContainedItemsList *getContainedItemsList() const;
};
#undef BFME_CONTAIN_SLOT

#define BFME_OBJECT_SLOT(n) virtual void objectSlot##n();
class Object
{
public:
	BFME_OBJECT_SLOT(0) BFME_OBJECT_SLOT(1) BFME_OBJECT_SLOT(2)
	BFME_OBJECT_SLOT(3) BFME_OBJECT_SLOT(4) BFME_OBJECT_SLOT(5)
	BFME_OBJECT_SLOT(6) BFME_OBJECT_SLOT(7) BFME_OBJECT_SLOT(8)
	BFME_OBJECT_SLOT(9)
	virtual Drawable *getDrawable() const;

	ContainModuleInterface *getContain() const { return m_contain; }

private:
	unsigned char m_unmodelled_04[0x1fc - 4];
	ContainModuleInterface *m_contain;
};
#undef BFME_OBJECT_SLOT

void bfmeTintSlowPathfindObject(Object *object)
{
	Drawable *drawable = object->getDrawable();
	if (drawable)
	{
		drawable->m_status |= 0x20;
		RGBColor white = { 1.0f, 1.0f, 1.0f };
		drawable->applyTint(white, 0, 0, 100, 0.0f, 0.0f);
	}

	ContainModuleInterface *contain = object->getContain();
	if (contain)
	{
		const ContainedItemsList *items = contain->getContainedItemsList();
		if (items)
		{
			for (ContainedItemsList::const_iterator it = items->begin();
				it != items->end(); ++it)
			{
				bfmeTintSlowPathfindObject(*it);
			}
		}
	}
}
