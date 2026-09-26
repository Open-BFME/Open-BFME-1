// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: InGameUI::MilitarySubtitleData scalar-deleting destructor at
// retail RVA 0x00442010 (30 bytes). The exact constructor, recovered
// InGameUI allocation/removal flow, and authoritative nested record layout
// establish identity. The wrapper calls its destructor through ILT 0x00018CE1
// before conditionally invoking operator delete.

class InGameUI
{
public:
	struct MilitarySubtitleData
	{
		~MilitarySubtitleData();
	};
};

void forceMilitarySubtitleDataDelete(InGameUI::MilitarySubtitleData *subtitle)
{
	delete subtitle;
}
