// cl: /DNDEBUG /MD /EHsc
// readable body of ?checkForSupplyCenter@AIPlayer@@IAEXPAVBuildListInfo@@PAVObject@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp

typedef bool Bool;
typedef int Int;

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum GameDifficulty { DIFFICULTY_EASY, DIFFICULTY_NORMAL, DIFFICULTY_HARD };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	Int compare(const AsciiString &other) const;
	Bool operator==(const AsciiString &other) const { return compare(other) == 0; }
private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	class OCLUpdate *findUpdateModule(NameKeyType key);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/SidesList.h
class BuildListInfo
{
public:
	void setSupplyBuilding(Bool value) { m_supplyBuilding = value; }
	void setDesiredGatherers(Int value) { m_desiredGatherers = value; }
	void setCurrentGatherers(Int value) { m_currentGatherers = value; }
private:
	unsigned char m_unreconstructed_000[0x7c];
	Bool m_supplyBuilding;
	unsigned char m_unreconstructed_07d[3];
	Int m_desiredGatherers;
	Int m_currentGatherers;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned char m_unreconstructed_000[0x28];
	AsciiString m_side;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AISideInfo
{
public:
	void *m_vtable;
	AsciiString m_side;
	Int m_easy;
	Int m_normal;
	Int m_hard;
	unsigned char m_unreconstructed_014[0x1bc - 0x14];
	AISideInfo *m_next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class TAiData
{
public:
	unsigned char m_unreconstructed_000[0xec];
	AISideInfo *m_sideInfo;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	TAiData *getAiData() const { return m_aiData; }
private:
	unsigned char m_unreconstructed_000[0x14];
	TAiData *m_aiData;
};

extern AI *TheAI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
protected:
	void checkForSupplyCenter(BuildListInfo *info, Object *bldg);
private:
	unsigned char m_unreconstructed_000[0x0c];
	Player *m_player;
	unsigned char m_unreconstructed_010[0x2c - 0x10];
	GameDifficulty m_difficulty;
};

void AIPlayer::checkForSupplyCenter(BuildListInfo *info, Object *bldg)
{
	if (info)
	{
		if (bldg)
		{
			static const NameKeyType key_centerUpdate =
				TheNameKeyGenerator->nameToKey("SupplyCenterDockUpdate");
			OCLUpdate *centerModule = bldg->findUpdateModule(key_centerUpdate);
			if (centerModule)
			{
				info->setSupplyBuilding(true);
				Int desiredGatherers = 0;
				const AISideInfo *resInfo = TheAI->getAiData()->m_sideInfo;
				if (resInfo)
				{
					// VC7 otherwise folds this into a shorter non-retail address calculation.
					void *playerStorage = *reinterpret_cast<void *volatile *>(
						reinterpret_cast<char *>(this) + 0x0c);
					const AsciiString *side = reinterpret_cast<const AsciiString *>(
						reinterpret_cast<char *>(playerStorage) + 0x28);
					do
					{
						if (resInfo->m_side == *side)
						{
							GameDifficulty difficulty = m_difficulty;
							if (difficulty == DIFFICULTY_EASY)
								desiredGatherers = resInfo->m_easy;
							if (difficulty == DIFFICULTY_NORMAL)
								desiredGatherers = resInfo->m_normal;
							if (difficulty == DIFFICULTY_HARD)
								desiredGatherers = resInfo->m_hard;
						}
						resInfo = resInfo->m_next;
					} while (resInfo);
				}

				info->setSupplyBuilding(true);
				info->setCurrentGatherers(-1);
				info->setDesiredGatherers(desiredGatherers + 1);
			}
		}
	}
}
