// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// Address-qualified clean-C++ carrier for the retail ILT entry at 0x0003236C,
// which tail-jumps to Campaign::getNextMission (see
// Campaign_getNextMission.cpp). It lives in its own unit so that
// Campaign_getNextMission.obj no longer carries the lowest retail RVA of its
// rows (5 bytes at 0x0003236C): that sorted the object ahead of retail's
// StringBase providers (0x0005D790+) in link order and its inline
// AsciiString copies were the ones kept.

class Mission;

class Campaign
{
public:
	Mission *getNextMission(Mission *current);
};

class Rva0003236CGetNextMissionThunk : public Campaign
{
public:
	Mission *forward(Mission *current);
};

Mission *Rva0003236CGetNextMissionThunk::forward(Mission *current)
{
	return getNextMission(current);
}
