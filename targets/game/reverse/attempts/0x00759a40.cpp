// ?rva00759A40@Rva00759A40ObjectDraw@@UBE_NPAV?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@_N@Z
// partial score=0.09 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include
// Retail RVA 0x00759A40, W3DQuadrupedDraw secondary-interface slot 41.

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
	Type &operator[](unsigned int index) { return _M_start[index]; }

private:
	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};
}

struct Rva00759A40String
{
	char *m_data;
};

struct Rva00759A40ModuleData
{
	unsigned char m_pad[0x15C];
	Rva00759A40String m_names[4];
};

class Rva00759A40ModelDrawInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual int getPristine(const void *condition, const char *name,
		int start, Coord3D *positions, Matrix3D *transforms,
		int maxBones, int extra) const = 0;
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
	};

class Rva00759A40ObjectDraw : public Rva00759A40ModelDrawInterface
{
public:
	virtual bool rva00759A40(
		_STL::vector<Coord3D, _STL::allocator<Coord3D> > *positions,
		bool pristine) const;

private:
	Rva00759A40ModuleData *getModuleData() const
	{
		return *(Rva00759A40ModuleData **)(
			(unsigned char *)const_cast<Rva00759A40ObjectDraw *>(this) - 8);
	}

	char *getDrawable() const
	{
		return *(char **)(
			(unsigned char *)const_cast<Rva00759A40ObjectDraw *>(this) - 4);
	}
};

bool Rva00759A40ObjectDraw::rva00759A40(
	_STL::vector<Coord3D, _STL::allocator<Coord3D> > *positions,
	bool pristine) const
{
	int zero = 0;
	const Rva00759A40ModuleData *data = getModuleData();
	if (data == (const Rva00759A40ModuleData *)zero)
		return false;
	Rva00759A40String *names =
		(Rva00759A40String *)((char *)data + 0x15C);
	char *text = names[0].m_data;
	if (text == (char *)zero || *(unsigned short *)(text + 4) == (unsigned short)zero)
	{
		text = names[1].m_data;
		if (text == (char *)zero || *(unsigned short *)(text + 4) == (unsigned short)zero)
			return false;
	}
	text = names[2].m_data;
	if (text == (char *)zero || *(unsigned short *)(text + 4) == (unsigned short)zero)
		text = names[3].m_data;
	if (text == (char *)zero || *(unsigned short *)(text + 4) == (unsigned short)zero)
		return false;

	char *drawable = (char *)zero;
	Matrix3D *world = (Matrix3D *)zero;
	if (pristine)
	{
		drawable = getDrawable();
		if (drawable == (char *)zero)
			return false;
		char *matrixStorage = *(char **)(drawable + 0xFC);
		if (matrixStorage == (char *)zero)
			return false;
		world = (Matrix3D *)(matrixStorage + 8);
	}
	positions->resize(4);
	bool valid[4];
	Rva00759A40String *current = names;
	unsigned int offset = 0;
	for (int i = 0; i < 4; ++i, ++current, offset += 0x0C)
	{
		Matrix3D transform;
		const char *name = current->m_data + 8;
		if (pristine)
		{
			valid[i] = getPristine(drawable + 0x250, name, 0,
				0, &transform, 1, 0) != 0;
			if (valid[i])
				transform.preMul(*world);
		}
		else
			valid[i] = getCurrent(name, transform);
		if (valid[i])
		{
			Coord3D *position = (Coord3D *)(
				(char *)positions->begin() + offset);
			position->x = transform[0][3];
			position->y = transform[1][3];
			position->z = transform[2][3];
		}
	}

	if (!valid[0] && !valid[1])
		return false;
	if (!valid[0])
		(*positions)[0] = (*positions)[1];
	else if (!valid[1])
		(*positions)[1] = (*positions)[0];
	if (!valid[2] && !valid[3])
		return false;
	if (!valid[2])
		(*positions)[2] = (*positions)[3];
	else if (!valid[3])
		(*positions)[3] = (*positions)[2];
	return true;
}
