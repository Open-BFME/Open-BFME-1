// Open-BFME5: retail RVA 0x00609360, 277 bytes.
//
// The constructor at 0x0060A000 installs vtable 0x01115AD0, and the matched
// destructor at 0x00609E30 clears the same g_bfmeStateDF singleton.  The
// adjacent matched 0x006092D0 method reads the mode at +0x04, so this body
// keeps the same state owner and uses address-derived virtual slot names.
// The incoming value remains opaque because retail only forwards it to slot
// +0x20.

// cl: /DNDEBUG /MD /EHsc

struct Coord2D
{
	float x;
	float y;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Rva003C9470Key
{
};

struct Rva003C9470Output
{
	float x;
	float y;
};

class Rva003C9470Owner
{
public:
	bool fallback(Rva003C9470Key *key, Rva003C9470Output *output);

	char m_padding00[8];
	void *m_value08;
};

class Gen003BDF20Element
{
};

class Rva003BDF20
{
public:
	Gen003BDF20Element *find(int id);
};

struct Rva000643F0Triple
{
	int value00;
	int value04;
	int value08;
};

class Rva000643F0Value
{
public:
	void copyTo(Rva000643F0Triple *destination) const;
};

typedef Rva000643F0Triple *(Rva000643F0Value::*CopyWithReturn)(
	Rva000643F0Triple *) const;

extern void j_00025531();

class BfmeW1105
{
public:
	int *bfmeGo1105C(int n);
};

class BfmeHostDA
{
public:
	void bfmeStopDA();
};

class BfmeLivingWorldManager
{
public:
	void rva00615900(const Coord2D &point);
};

class BfmeGameCW
{
};

class Mouse
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30(int, int);
	virtual void slot34();
	virtual void slot38(int);
};

class Rva006092D0State
{
public:
	void rva00609360(void *source);

	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20(void *source, Coord3D *point);
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30(int, int);
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64(Coord3D *point);
	virtual void slot68(int);

	int m_mode;
	bool m_enabled;
};

class Glo012F1028Type
{
public:
	char m_padding00[0x28];
	Rva003C9470Owner *m_at28;
};

extern Glo012F1028Type *Glo012F1028;
extern BfmeGameCW *g_bfmeGameCW;
extern Mouse *TheMouse;

// ?rva00609360@Rva006092D0State@@QAEXPAX@Z
void Rva006092D0State::rva00609360(void *source)
{
	Coord3D point;

	if (!m_enabled)
		return;

	switch (m_mode)
	{
	case 1:
	{
		Rva003C9470Owner *owner = Glo012F1028->m_at28;
		void *value = owner->m_value08;
		if (value == 0)
			return;

		if (!owner->fallback((Rva003C9470Key *)((char *)value + 4),
			(Rva003C9470Output *)((char *)this + 0x0C)))
			return;

		slot68(1);
		TheMouse->slot38(0);
		slot30(2, 0);
		if (g_bfmeGameCW != 0)
			((BfmeHostDA *)g_bfmeGameCW)->bfmeStopDA();
		return;
	}

	case 0:
	{
		Rva000643F0Triple copyPoint;

			slot20(source, &point);
			Gen003BDF20Element *value = ((Rva003BDF20 *)Glo012F1028)->find(8);
			if (value != 0)
			{
				int *result = ((BfmeW1105 *)((char *)value + 0x0C))->bfmeGo1105C(0);
				if (result != 0)
				{
					Rva000643F0Value *copy = (Rva000643F0Value *)result;
				union
				{
					void (*raw)();
					CopyWithReturn member;
				} copyCall;
				copyCall.raw = j_00025531;
				Rva000643F0Triple *copied =
					(copy->*copyCall.member)(&copyPoint);
				point.x = *(float *)&copied->value00;
				point.y = *(float *)&copied->value04;
				point.z = *(float *)&copied->value08;
				}
			}

			slot64(&point);
			slot30(1, 0);
			if (g_bfmeGameCW != 0)
			{
				Coord2D position;
				position.x = point.x;
				position.y = point.y;
				((BfmeLivingWorldManager *)g_bfmeGameCW)->rva00615900(position);
			}
			return;
		}
	}
}
