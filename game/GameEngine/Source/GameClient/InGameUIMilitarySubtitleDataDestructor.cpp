// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// InGameUI::MilitarySubtitleData complete destructor at retail 0x0043EBF0
// (5 bytes). ??_GMilitarySubtitleData@InGameUI (0x00442010) calls it through
// ILT 0x00018CE1; ilt_oracle CONFIRMS this decorated name at 0x0043EBF0. Its
// only destructible member is the UnicodeString at +0x00, whose inline
// StringBase<wchar_t> destructor leaves one tail jump to
// StringBase<wchar_t>::releaseBuffer (retail VA 0x00C881D0).

#include "unicode_string.h"

class DisplayString;

// layout: InGameUI.cpp InGameUI::removeMilitarySubtitle (retail field reads)
class InGameUI
{
public:
	struct MilitarySubtitleData
	{
		~MilitarySubtitleData();

		UnicodeString subtitle;
		unsigned int index;
		DisplayString *displayStrings[8];
		DisplayString *blockString;
		unsigned int currentDisplayString;
	};
};

InGameUI::MilitarySubtitleData::~MilitarySubtitleData()
{
}
