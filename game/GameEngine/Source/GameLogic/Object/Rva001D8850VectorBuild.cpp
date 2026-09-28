// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
//
// Neutral reconstruction of the 0x001D8850 wrapper.  Retail takes three
// stack arguments in addition to ECX and returns with ret 0x0c.  The helper
// at 0x001D88C0 is a separate body and consumes six stack arguments with
// ret 0x18; this TU calls its existing ILT through a typed member pointer.

extern void j_00019ff1();
extern void j_0001b57c();
extern void j_00007edc();

struct Rva001D8850VectorInt
{
	int *m_begin;
	int *m_end;
	int *m_capacity;
};

struct Rva001D8850Subject
{
	char m_pad00[0x44];
	void *m_field44;
};

class Rva001D8850Owner
{
public:
	void buildVector(
		Rva001D8850Subject *subject, void *unused, int value);

private:
	char m_pad00[0x11b];
	unsigned char m_flag11b;
};

void Rva001D8850Owner::buildVector(
	Rva001D8850Subject *subject, void *unused, int value)
{
	(void)unused;
	if (subject == 0)
		return;

	if (m_flag11b != 0)
	{
		typedef bool (Rva001D8850Subject::*AboveTerrain)(void) const;
		union
		{
			void (__cdecl *freeAboveTerrain)();
			AboveTerrain memberAboveTerrain;
		} aboveTerrain;
		aboveTerrain.freeAboveTerrain = ::j_00019ff1;
		if ((subject->*aboveTerrain.memberAboveTerrain)())
			return;
	}

	Rva001D8850VectorInt result;
	typedef void (Rva001D8850Owner::*Populate)(
		Rva001D8850VectorInt *, void *, void *, void *, void *, int);
	union
	{
		void (__cdecl *freePopulate)();
		Populate memberPopulate;
	} populate;
	populate.freePopulate = ::j_0001b57c;
	(this->*populate.memberPopulate)(
		&result,
		(char *)subject + 0x38,
		(char *)subject + 8,
		subject->m_field44,
		subject,
		value);

	typedef void (Rva001D8850VectorInt::*Destroy)(void);
	union
	{
		void (__cdecl *freeDestroy)();
		Destroy memberDestroy;
	} destroy;
	destroy.freeDestroy = ::j_00007edc;
	(result.*destroy.memberDestroy)();
}
