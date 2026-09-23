// ?select@Rva003C1EE0Owner@@QAEHPAX0PAURva003C1EE0Pair@@@Z
// partial score=0.2 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

struct Rva003C1EE0Pair
{
	float m_x;
	float m_y;
};

struct Rva003C1EE0OpaqueValue
{
	unsigned int m_opaque;
	void releaseBuffer();
};

struct Rva003C1EE0TempList
{
	Rva003C1EE0OpaqueValue *m_begin;
	Rva003C1EE0OpaqueValue *m_end;
	Rva003C1EE0OpaqueValue *m_capacity;

	Rva003C1EE0TempList()
		: m_begin(0), m_end(0), m_capacity(0)
	{
	}

	~Rva003C1EE0TempList();
};

class Gen003BD8D0Built;

class Rva003CA710Owner
{
public:
	void refresh(bool includeDisabled, bool requireSecond);
};

class Gen003BF540Owner
{
public:
	bool consume(void *built, Gen003BD8D0Built *input,
		void *list, void *unused);
};

struct Rva003C1EE0NestedView
{
	unsigned char m_pad00[0x18];
	bool m_flag18;
};

struct Rva003C1EE0InputView
{
	unsigned char m_pad00[0xC4];
	int m_resultC4;
	int m_resultC8;
	int m_resultCC;
	bool m_flagD0;
	bool m_flagD1;
	unsigned char m_padD2[0x1A];
	Rva003C1EE0NestedView *m_nestedEC;
};

class Rva003C1EE0Owner
{
public:
	void measurePair(Rva003C1EE0TempList *list, Rva003C1EE0Pair *out);
	int select(void *input, void *candidate, Rva003C1EE0Pair *out);

private:
	unsigned char m_pad00[0x28];
	void *m_manager;
};

#pragma comment(linker, "/alternatename:?measurePair@Rva003C1EE0Owner@@QAEXPAURva003C1EE0TempList@@PAURva003C1EE0Pair@@@Z=?j_000231d7@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva003C1EE0TempList@@QAE@XZ=?j_00026ab2@@YAXXZ")
#pragma comment(linker, "/alternatename:?releaseBuffer@Rva003C1EE0OpaqueValue@@QAEXXZ=?releaseBuffer@BFMERetailAsciiString@@AAEXXZ")

int Rva003C1EE0Owner::select(void *input, void *candidate,
	Rva003C1EE0Pair *out)
{
	Rva003C1EE0InputView *view = (Rva003C1EE0InputView *)input;
	if (candidate == 0)
	{
		out->m_y = 0.0f;
		out->m_x = 1.0f;
		return view->m_resultCC;
	}
	if (input == candidate)
		return view->m_resultC4;

	int selectedIndex;
	{
		Rva003C1EE0TempList list;
		((Rva003CA710Owner *)m_manager)->refresh(
			view->m_flagD0, view->m_flagD1);
		if (view->m_flagD1)
			view->m_nestedEC->m_flag18 = true;

		bool consumed = ((Gen003BF540Owner *)m_manager)->consume(
			candidate, (Gen003BD8D0Built *)input, &list, 0);
		((Rva003CA710Owner *)m_manager)->refresh(true, true);
		if (!consumed)
			return -1;

		selectedIndex = (int)(list.m_end - list.m_begin) - 1;
		measurePair(&list, out);

		int index = 0;
		while (index < list.m_end - list.m_begin)
		{
			list.m_begin[index].releaseBuffer();
			++index;
		}
	}

	if (selectedIndex > 1)
	{
		if (selectedIndex == 2)
			return view->m_resultC8;
		return view->m_resultCC;
	}
	return view->m_resultC4;
}
