// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include
// Open-BFME5: fills four bone positions, W3DQuadrupedDraw W3DModelDrawInterface slot 41 (0x00759A40).
// Slots 3 and 5 are W3DModelDraw::getPristineBonePositionsForConditionState and ::getCurrentWorldspaceClientBonePositions.

#include "matrix3d.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

namespace _STL
{
template <class Type>
class allocator {};

template <class Type, class Allocator>
class vector
{
public:
	void resize(unsigned int newSize);
	Type *begin() { return _M_start; }
	Type &operator[](unsigned int index) { return *(begin() + index); }

private:
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};
}

struct Rva00759A40String
{
	struct Data
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		char m_text[1];
	};

	bool isEmpty() const { return m_data == 0 || m_data->m_length == 0; }
	const char *str() const
	{
		static const char TheNullChr = 0;
		return m_data ? m_data->m_text : &TheNullChr;
	}

	Data *m_data;
};

struct Rva00759A40ModuleData
{
	unsigned char m_pad[0x15C];
	Rva00759A40String m_names[4];
};

struct Rva00759A40Thing
{
	unsigned char m_pad0[0x8];
	Matrix3D m_transform;

	const Matrix3D *getTransformMatrix() const { return &m_transform; }
};

struct Rva00759A40Drawable
{
	unsigned char m_pad0[0xFC];
	Rva00759A40Thing *m_object;
	unsigned char m_pad100[0x150];
	unsigned int m_conditionState;

	const Rva00759A40Thing *getObject() const { return m_object; }
	const void *getModelConditionFlags() const { return &m_conditionState; }
};

class Rva00759A40ModelDrawInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual int getPristine(const void *condition, const char *name,
		int start, Coord3D *positions, Matrix3D *transforms,
		int maxBones, int *extra) const = 0;
	virtual int slot04(const char *name, int start, Coord3D *positions,
		Matrix3D *transforms, int maxBones) const = 0;
	virtual bool getCurrent(const char *name, Matrix3D &transform) const = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual bool rva00759A40(
		_STL::vector<Coord3D, _STL::allocator<Coord3D> > *positions,
		bool pristine) const = 0;
};

class Rva00759A40DrawModuleBase
{
public:
	virtual void moduleSlot00() = 0;

protected:
	Rva00759A40ModuleData *m_moduleData;
	Rva00759A40Drawable *m_drawable;
};

class Rva00759A40ObjectDraw : public Rva00759A40DrawModuleBase, public Rva00759A40ModelDrawInterface
{
public:
	virtual bool rva00759A40(
		_STL::vector<Coord3D, _STL::allocator<Coord3D> > *positions,
		bool pristine) const;

private:
	const Rva00759A40ModuleData *getModuleData() const { return m_moduleData; }
	const Rva00759A40Drawable *getDrawable() const { return m_drawable; }
};

bool Rva00759A40ObjectDraw::rva00759A40(
	_STL::vector<Coord3D, _STL::allocator<Coord3D> > *positions,
	bool pristine) const
{
	const Rva00759A40ModuleData *data = getModuleData();
	if (data == 0)
		return false;
	if (data->m_names[0].isEmpty() && data->m_names[1].isEmpty())
		return false;
	if (data->m_names[2].isEmpty() && data->m_names[3].isEmpty())
		return false;

	const Rva00759A40Drawable *drawable = 0;
	const Matrix3D *world = 0;
	if (pristine)
	{
		drawable = getDrawable();
		if (drawable == 0)
			return false;
		const Rva00759A40Thing *object = drawable->getObject();
		if (object == 0)
			return false;
		world = object->getTransformMatrix();
		if (world == 0)
			return false;
	}
	positions->resize(4);
	bool valid[4];
	for (int i = 0; i < 4; ++i)
	{
		if (data->m_names[i].isEmpty())
		{
			valid[i] = false;
			continue;
		}
		Matrix3D transform;
		if (pristine)
		{
			valid[i] = getPristine(drawable->getModelConditionFlags(), data->m_names[i].str(), 0, 0, &transform, 1, 0) != 0;
			transform.preMul(*world);
		}
		else
			valid[i] = getCurrent(data->m_names[i].str(), transform);
		if (valid[i])
		{
			(*positions)[i].x = transform.Get_X_Translation();
			(*positions)[i].y = transform.Get_Y_Translation();
			(*positions)[i].z = transform.Get_Z_Translation();
		}
	}

	if (!valid[0])
	{
		if (!valid[1])
			return false;
		(*positions)[0] = (*positions)[1];
	}
	else if (!valid[1])
		(*positions)[1] = (*positions)[0];
	if (!valid[2])
	{
		if (!valid[3])
			return false;
		(*positions)[2] = (*positions)[3];
	}
	else if (!valid[3])
		(*positions)[3] = (*positions)[2];
	return true;
}
