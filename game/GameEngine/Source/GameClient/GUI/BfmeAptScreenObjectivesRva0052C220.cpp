// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail RVA 0x0052C220, 844 bytes. This is the Objectives/PlayerStatus
// screen table population method, not the MultiPlayerLoadScreen destructor
// named by the old lift. See identity_evidence/0x0052c220.md.
// AptScreenFactories.cpp independently witnesses the owning class and its
// +0x258 vector, +0x264 mode, +0x268 controls and +0x288 slot-index array.
// The exact original method name remains unknown.
//
// Keep native STLport push_back visible: an external-only declaration forces
// an extra color stack slot. Keeping the final slot-fill as a loop and copying
// the team number before format reproduces retail's register allocation.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <string.h>
#include "string_base.h"
typedef bool Bool;
class AsciiString
{
public:
	AsciiString() { m_data = 0; }
	AsciiString( const char *s )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( s );
	}
	AsciiString( const AsciiString &that )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that );
	}
	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

	// Inline: retail folds the literal's length into set(const char *, int).
	AsciiString &operator=( const char *s );

	void __cdecl format( AsciiString fmt, ... );

	const char *str() const
	{
		return m_data ? (const char *)(m_data + 8) : "";
	}
	// The header's length is the word four bytes in.
	Bool isEmpty() const
	{
		return !m_data || !*(const unsigned short *)(m_data + 4);
	}

private:
	char *m_data;
};

// Copies and releases through StringBase<unsigned short> directly, as the
// by-value arguments in retail do.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString() { m_data = 0; }
	UnicodeString( const wchar_t *s )
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase( s );
	}
	UnicodeString( const UnicodeString &that )
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&that );
	}
	~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

	void __cdecl format( UnicodeString fmt, ... );

private:
	unsigned short *m_data;
};

enum NameKeyType { NAMEKEY_INVALID = 0 };
class NameKeyGenerator { public: NameKeyType nameToKey(const char *); };
class Player { public: bool isPlayerObserver() const; };
class PlayerList { public: Player *findPlayerWithNameKey(NameKeyType); };
class GameSlot {
public:
 bool isOccupied() const;
 bool isHuman() const;
 bool isAI() const;
 UnicodeString getName() const;
 UnicodeString getApparentPlayerTemplateDisplayName() const;
 int getApparentColor() const;
 unsigned char m_unmodelled000[0x18];
 int m_teamNumber;
 unsigned char m_unmodelled01c[0x10];
 // +0x2c: copied then passed through nameToKey into findPlayerWithNameKey.
 AsciiString m_playerName;
};
class GameInfo { public: const GameSlot *getConstSlot(int) const; GameSlot *getSlot(int); };
class MultiplayerColorDefinition { public: unsigned char m_unmodelled000[0x10]; int m_color; };
class MultiplayerSettings { public: MultiplayerColorDefinition *getColor(int); };
class NetworkInterface { public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual bool isPlayerConnected(int);
};
class VictoryConditionsInterface { public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot10();
virtual bool hasBeenDefeated(Player *);
};
class GameTextInterface { public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual UnicodeString fetch(AsciiString, bool * = 0);
};
extern GameInfo *TheGameInfo;
extern NameKeyGenerator *TheNameKeyGenerator;
extern PlayerList *ThePlayerList;
extern NetworkInterface *TheNetwork;
extern VictoryConditionsInterface *TheVictoryConditions;
extern GameTextInterface *TheGameText;
extern MultiplayerSettings *TheMultiplayerSettings;

// Preserve the existing address-specific template identity at RVA 0x0052C1E0.
// Retail has separate copies: the plain vector<int> symbol resolves elsewhere.
// Each element carries one color integer; the size and vector layout are the
// same ones witnessed by the constructor and PlayerColor provider.
struct Gen_t_0052c1e0_p4pod { int a[1]; };
class BfmeAptScreenObjectives {
public:
 void rva0052C220();
 // ILT 0x0000C17B -> RVA 0x0052B540; ECX=this plus three stack slots.
 void rva0052B540(int row, int column, const UnicodeString &value);
private:
 unsigned char m_unmodelledPrefix[0x258];
 _STL::vector<Gen_t_0052c1e0_p4pod> m_players;
 int m_screenType;
 void *m_playerControls[8];
 signed char m_playerSlots[8];
};
void BfmeAptScreenObjectives::rva0052C220()
{
 if (m_screenType != 1) return;
 int row=0;
 for(int i=0;i<8;++i) {
  const GameSlot *slot=TheGameInfo->getConstSlot(i);
  if (!slot || !slot->isOccupied()) continue;
  AsciiString name=TheGameInfo->getSlot(i)->m_playerName;
  if (name.isEmpty()) continue;
  Player *player=ThePlayerList->findPlayerWithNameKey(TheNameKeyGenerator->nameToKey(name.str()));
  if (player) {
   bool connected=false;
   if ((TheNetwork && TheNetwork->isPlayerConnected(i)) || (!TheNetwork && slot->isHuman())) connected=true;
   if (slot->isAI()) connected=true;
   bool alive=!TheVictoryConditions->hasBeenDefeated(player);
   bool observer=player->isPlayerObserver();
   rva0052B540(row,0,slot->getName());
   rva0052B540(row,1,slot->getApparentPlayerTemplateDisplayName());
   AsciiString team;
   int teamNumber=slot->m_teamNumber+1;
   team.format(AsciiString("Team:%d"),teamNumber);
   if(slot->isAI() && slot->m_teamNumber==-1) team="Team:AI";
   rva0052B540(row,2,TheGameText->fetch(team));
   team="";
   if(connected) {
    if(alive) team="GUI:PlayerAlive";
    else if(observer) team="GUI:PlayerObserver";
    else team="GUI:PlayerDead";
   } else {
    if(observer) team="GUI:PlayerObserverGone";
    else team="GUI:PlayerGone";
   }
   rva0052B540(row,3,TheGameText->fetch(team));
   Gen_t_0052c1e0_p4pod color={{TheMultiplayerSettings->getColor(slot->getApparentColor())->m_color}};
   m_players.push_back(color);
   m_playerSlots[row]=(signed char)i;
   ++row;
  }
 }
 for(;row<8;++row) m_playerSlots[row]=-1;
}
