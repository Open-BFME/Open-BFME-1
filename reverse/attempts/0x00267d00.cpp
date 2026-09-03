// ?apply@Rva00267D00Owner@@QAEX_N@Z
// partial score=0.97 date=2026-09-03
// cl: /DNDEBUG /MD

typedef unsigned int UnsignedInt;
typedef bool Bool;

struct Coord3D
{
	float x, y, z;
};

class Matrix3D;

class Object
{
public:
	void notifyModelConditionChanged(void);

	char m_pad00[0x38];
	Coord3D m_pos;
	char m_pad44[0x130 - 0x44];
	UnsignedInt m_flags130;
};

class FXList
{
public:
	Bool isEmpty(void) const;
	void doFXPos(const Coord3D *pos, const Matrix3D *mtx, float speed, const Coord3D *extra) const;
};

class Rva00267D00ModuleData
{
public:
	char m_pad[0x264];
	FXList *m_fx;
};

class Rva00267D00Owner
{
public:
	void apply(Bool skipFx);
	void helper(int arg);

private:
	char m_pad00[4];
	Rva00267D00ModuleData *m_data;
	Object *m_object;
};

// ?apply@Rva00267D00Owner@@QAEX_N@Z
void Rva00267D00Owner::apply(Bool skipFx)
{
	Object *object = m_object;
	UnsignedInt value = object->m_flags130;
	UnsignedInt tmp = value;
	if ((value & 0x800) != 0)
	{
		tmp &= ~0x800u;
		object->m_flags130 = tmp;
		object->notifyModelConditionChanged();
		if (!skipFx)
		{
			helper(1);
			FXList *fx = m_data->m_fx;
			if (fx != 0)
			{
				if (!fx->isEmpty())
					fx->doFXPos(&object->m_pos, 0, 0, 0);
			}
		}
	}
}
