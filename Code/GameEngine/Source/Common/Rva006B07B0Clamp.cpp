// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clean reconstruction of the 0x006B07B0 bounded multiplier helper.

#define Rva006B07B0Zero (*(const float *)0x01075350)
#define Rva006B07B0One (*(const float *)0x01075334)

struct Rva006B07B0Data
{
	char m_pad00[0x14];
	void *m_slot14;
	char m_pad18[0x10];
	float m_value;
};

struct Rva006B07B0Argument
{
	Rva006B07B0Data *m_data;
};

struct Rva006B07B0Value
{
	char m_pad00[0x3c];
	int m_value;
};

extern void j_0002918b();

class Rva006B07B0Owner
{
public:
	float compute(Rva006B07B0Argument *argument, void *second, int mode);

private:
	char m_pad00[0x0c];
	Rva006B07B0Value *m_value;
};

float Rva006B07B0Owner::compute(
	Rva006B07B0Argument *argument, void *second, int mode)
{
	void *slot = argument->m_data->m_slot14;
	typedef float (Rva006B07B0Owner::*Callback)(void *, void *);
	union
	{
		void (*freeCallback)();
		Callback memberCallback;
	} callback;
	callback.freeCallback = ::j_0002918b;
	float result = (this->*callback.memberCallback)(slot, second);
	if (mode != 1)
		return result;

	float multiplier = Rva006B07B0One -
		argument->m_data->m_value / (float)m_value->m_value;
	if (multiplier < Rva006B07B0Zero)
	{
		multiplier = Rva006B07B0Zero;
	}
	else
	{
		if (multiplier > Rva006B07B0One)
			multiplier = Rva006B07B0One;
	}
	return result * multiplier;
}
