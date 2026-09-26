// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LargeGroupAudioKeyMap copy assignment, retail 0x003D4540,
// 45 bytes. It releases the current key references, copies the three-dword
// map storage, then retains every selected key in the copy.

class LGA_MemberObj;

void bfmeClearMembers(LGA_MemberObj *map);

class Rva0039C830Mid
{
public:
	Rva0039C830Mid &operator=(const Rva0039C830Mid &other);
};

class LargeGroupAudioKeyMap
{
public:
	LargeGroupAudioKeyMap &operator=(const LargeGroupAudioKeyMap &other);
};

void bfmeRetainMembers(LargeGroupAudioKeyMap *map);

// ??4LargeGroupAudioKeyMap@@QAEAAV0@ABV0@@Z
LargeGroupAudioKeyMap &LargeGroupAudioKeyMap::operator=(
	const LargeGroupAudioKeyMap &other)
{
	if (&other != this)
	{
		bfmeClearMembers((LGA_MemberObj *)this);
		*(Rva0039C830Mid *)this = *(const Rva0039C830Mid *)&other;
		bfmeRetainMembers(this);
	}

	return *this;
}
