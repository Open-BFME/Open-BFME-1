// Retail VA 0x012F7094; the definition in SkirmishGameOptionsMenu.cpp
// is a SkirmishGameInfo pointer, not an integer flag.
class SkirmishGameInfo;
extern SkirmishGameInfo *TheSkirmishGameInfo;

// ILT 0x0002CB10 -> 0x0009FC90, the matched user-name serializer.
class Gen0009FC90Owner
{
public:
	void Rva0009FC90();
};

// ILT 0x00030495 -> UserPreferences::write at 0x000A9F60.
class UserPreferences
{
public:
	virtual bool write();
};

class BfmeThingBRA
{
public:
	bool bfmeGoBRA();
};

bool BfmeThingBRA::bfmeGoBRA()
{
	if (TheSkirmishGameInfo == 0)
		return false;
	reinterpret_cast<Gen0009FC90Owner *>(this)->Rva0009FC90();
	return reinterpret_cast<UserPreferences *>(this)->UserPreferences::write();
}
