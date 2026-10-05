// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Address-derived selector at retail 0x003C1EE0: refresh the +0x28 manager, consume into an AsciiString vector, pick +0xC4/+0xC8/+0xCC.

#include <vector>
#include "ascii_string.h"

struct Coord2D
{
	float m_x;
	float m_y;
};

typedef _STL::vector<AsciiString> Rva003C1EE0TempList;

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

	// ?getNested@Rva003C1EE0InputView@@QAEPAURva003C1EE0NestedView@@XZ absent-from-retail
	Rva003C1EE0NestedView *getNested() { return m_nestedEC; }
};

class LivingWorldLogic
{
public:
	void measurePair(Rva003C1EE0TempList *list, Coord2D *out);
	int select(void *input, void *candidate, Coord2D *out);
	// ?refreshManager@LivingWorldLogic@@QAEX_N0@Z absent-from-retail
	void refreshManager(bool includeDisabled, bool requireSecond)
	{
		((Rva003CA710Owner *)m_manager)->refresh(includeDisabled, requireSecond);
	}

private:
	unsigned char m_pad00[0x28];
	void *m_manager;
};

int LivingWorldLogic::select(void *input, void *candidate,
	Coord2D *out)
{
	Rva003C1EE0InputView *view = (Rva003C1EE0InputView *)input;
	if (candidate == 0)
	{
		out->m_y = 0.0f;
		out->m_x = 1.0f;
		return view->m_resultCC;
	}
	int selectedIndex;
	if (input == candidate)
		goto selectFirst;
	{
		Rva003C1EE0TempList list;
		refreshManager(view->m_flagD0, view->m_flagD1);
		if (view->m_flagD1)
			view->getNested()->m_flag18 = true;

		bool consumed = ((Gen003BF540Owner *)m_manager)->consume(
			candidate, (Gen003BD8D0Built *)input, &list, 0);
		refreshManager(true, true);
		if (consumed)
		{
			selectedIndex = list.size() - 1;
			measurePair(&list, out);

			for (unsigned int index = 0;
				index < list.size(); ++index)
			{
				list[index].clear();
			}
		}
		else
		{
			return -1;
		}
	}
	if (selectedIndex <= 1)
	{
selectFirst:
		return view->m_resultC4;
	}
	if (selectedIndex == 2)
		return view->m_resultC8;
	return view->m_resultCC;
}
