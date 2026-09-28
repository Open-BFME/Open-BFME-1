// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// RVA 0x001628F0 +740. Identity: AIPlayer::update caller, AIPlayer vtable,
// and the SkillSet debug text shared with the GeneralsMD reference method.
// BFME witnesses: player +0xc and selector +0x30; Player name key +0x20,
// side string +0x28 and science points +0x264. AISideInfo has five 0x54-byte
// skill sets at +0x14/+0x68/+0xbc/+0x110/+0x164 and next at +0x1bc.
// The last 16 bytes of the retail extent are its four-entry switch table.
// Use a BFME-layout TU rather than the incompatible reference AIPlayer header.
// j_00022057 is the actual AsciiString::concat(const char*) ILT; the public
// ascii_string.h convenience wrapper targets StringBase directly instead.
#include "string_base.h"
template<class T> inline void StringBase<T>::concat(T c) { concat(&c,1); }
#include "ascii_string.h"
typedef int Int;
typedef bool Bool;
enum ScienceType {};
enum NameKeyType {};
class Player {
 char pad00[0x20]; NameKeyType m_playerNameKey; char pad24[4]; AsciiString m_side;
 char pad2c[0x264-0x2c]; int m_sciencePurchasePoints;
public:
 NameKeyType getPlayerNameKey() const {return m_playerNameKey;}
 const AsciiString &getSide() const {return m_side;}
 int getSciencePurchasePoints() const {return m_sciencePurchasePoints;}
 bool isCapableOfPurchasingScience(ScienceType) const;
 bool attemptToPurchaseScience(ScienceType);
};
struct TSkillSet { int m_numSkills; ScienceType m_skills[20]; };
class AISideInfo {
 void *vtable;
public:
 AsciiString m_side; int m_easy,m_normal,m_hard;
 TSkillSet m_skillSet1,m_skillSet2,m_skillSet3,m_skillSet4,m_skillSet5;
 AsciiString m_baseDefenseStructure1;
 AISideInfo *m_next;
};
class TAiData { char pad00[0xec]; public: AISideInfo *m_sideInfo; };
class AI { char pad00[0x14]; TAiData *m_aiData; public: const TAiData *getAiData() const {return m_aiData;} };
extern AI *TheAI;
class GameLogic { char pad00[0x3c]; unsigned m_frame; public: unsigned getFrame() const {return m_frame;} };
extern GameLogic *TheGameLogic;
class NameKeyGenerator { public: AsciiString keyToName(NameKeyType); };
extern NameKeyGenerator *TheNameKeyGenerator;
class ScienceStore { public: AsciiString getInternalNameForScience(ScienceType) const; };
extern ScienceStore *TheScienceStore;
class ScriptEngine { public: void AppendDebugMessage(const AsciiString&,bool); };
extern ScriptEngine *TheScriptEngine;
int GetGameLogicRandomValue(int,int,char*,int);
void j_00022057();
inline void concatText(AsciiString &s,const char *p) {
 union { void(*f)(); void(AsciiString::*m)(const char*); } u;u.f=j_00022057;
 (s.*u.m)(p);
}
class AIPlayer {
public:
 enum { INVALID_SKILLSET_SELECTION=-1 };
#define SLOT(n) virtual void slot##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10)
#undef SLOT
 virtual bool isSkirmishAI();
protected:
 virtual void doUpgradesAndSkills();
 char pad04[8]; Player *m_player; char pad10[0x20]; int m_skillsetSelector;
};
void AIPlayer::doUpgradesAndSkills(void)
{
	if (TheGameLogic->getFrame() < 2) {
		return;
	}

	Bool checkScience = m_player->getSciencePurchasePoints()>0;
	if (!checkScience) {
		return;
	}
	const AISideInfo *sideInfo = TheAI->getAiData()->m_sideInfo;
	while (sideInfo) {
		if (sideInfo->m_side.compare(m_player->getSide()) == 0) {
			break;
		}
		sideInfo = sideInfo->m_next;
	}
	if (sideInfo == 0) return;

	if (m_skillsetSelector == INVALID_SKILLSET_SELECTION) {
		Int limit = 0;
		if (sideInfo->m_skillSet2.m_numSkills>0) {
			limit = 1;
			if (sideInfo->m_skillSet3.m_numSkills>0) {
				limit = 2;
				if (sideInfo->m_skillSet4.m_numSkills>0) {
					limit = 3;
					if (sideInfo->m_skillSet5.m_numSkills>0) {
						limit = 4;
					}
				}
			}
		}
		if (isSkirmishAI()) {
			m_skillsetSelector = GetGameLogicRandomValue(0, limit, "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIPlayer.cpp", 0xb19);
		} else {
			m_skillsetSelector = 0;
		}
	}

	if (m_player->getSciencePurchasePoints()>0) {
		const TSkillSet *skillset;
		switch(m_skillsetSelector) {
			default:
			case 0: skillset = &sideInfo->m_skillSet1; break;
			case 1: skillset = &sideInfo->m_skillSet2; break;
			case 2: skillset = &sideInfo->m_skillSet3; break;
			case 3: skillset = &sideInfo->m_skillSet4; break;
			case 4: skillset = &sideInfo->m_skillSet5; break;
		}
		Int i;
		for (i=0; i<skillset->m_numSkills; i++) {
			ScienceType science = skillset->m_skills[i];
			if (m_player->isCapableOfPurchasingScience(science)) {
				if (m_player->attemptToPurchaseScience(science)) {
					AsciiString msg = TheNameKeyGenerator->keyToName(m_player->getPlayerNameKey());
					concatText(msg," purchases from SkillSet");
					msg.concat('1'+m_skillsetSelector);
					msg.concat(' ');
					msg.concat(TheScienceStore->getInternalNameForScience(science));
					concatText(msg,".");
					TheScriptEngine->AppendDebugMessage(msg, false);
				}
			}
		}
	}
}

