// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TeamInQueue::isBuildTimeExpired, retail 0x00160FC0.
//
// The Zero Hour body unchanged; all four differences from AIPlayer.cpp's copy
// are offsets, and every one of them is read straight off the retail bytes:
//
//   TeamInQueue::m_team           +0x1c   (AIPlayer.cpp lands it at +0x20)
//   TeamInQueue::m_frameStarted   +0x24   (+0x28)
//   Team::m_proto                 +0x04   (+0x08)
//   m_initialIdleFrames           +0x1a4  (+0xdc)
//
// The first three are the same four-byte narrowing seen elsewhere in BFME's
// class graph -- both TeamInQueue and Team carry one base member fewer than the
// ZH headers give them. The fourth is not a shift: BFME's team template info
// is 200 bytes further out, so that class genuinely grew.
//
// Kept out of AIPlayer.cpp because correcting the classes there would move all
// 32 of its matched rows for one 38-byte body.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamTemplateInfo
{
public:
	char m_unreconstructed_00[0x1a4];
	int m_initialIdleFrames;					///< retail reads it at prototype+0x1a4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	// Retail folds the prototype-to-template-info offset and the field offset
	// into a single [edx+0x1a4] load, so where one ends and the other begins is
	// not observable from this body. Spelled as if the info block starts at the
	// prototype, which keeps the one number that IS observable exact.
	const TeamTemplateInfo *getTemplateInfo() const
	{
		return (const TeamTemplateInfo *)this;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	TeamPrototype *getPrototype() const { return m_proto; }

private:
	char m_unreconstructed_00[4];
	TeamPrototype *m_proto;						///< retail this+0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }

private:
	char m_unreconstructed_00[0x3c];
	unsigned int m_frame;						///< retail this+0x3c
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class TeamInQueue
{
public:
	bool isBuildTimeExpired();

private:
	char m_unreconstructed_00[0x1c];
	Team *m_team;								///< retail this+0x1c
	char m_unreconstructed_20[4];
	unsigned int m_frameStarted;				///< retail this+0x24
};

// ?isBuildTimeExpired@TeamInQueue@@QAE_NXZ
bool TeamInQueue::isBuildTimeExpired()
{
	if (m_team->getPrototype()->getTemplateInfo()->m_initialIdleFrames<1) {
		return false; // Unlimited time.
	}
	if (TheGameLogic->getFrame() > m_frameStarted + m_team->getPrototype()->getTemplateInfo()->m_initialIdleFrames) {
		return true;
	}
	return false;
}
