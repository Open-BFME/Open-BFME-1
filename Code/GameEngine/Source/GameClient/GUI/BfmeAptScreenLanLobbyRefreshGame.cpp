// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00519CB0, full585 bytes. LANAPI::OnGameCreate at689910 calls
// the matched screen transition51A5D0, which calls this body with the same
// receiver. The recovered constructor/destructor establish state+25C and
// preferences+390. The descriptive method spelling is not an original symbol.
// Only the guest branch sends RequestHasMap before applying the game state.
// AmIHost's actual body returns32 bits; this caller consumes its low byte.

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

public:
	void set( const StringBase<T> &other );
	void trim();
	void toLower();

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
struct UnicodeStringData
{
	unsigned int m_refCount;
	unsigned short m_length;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString() : m_data( 0 ) {}
	UnicodeString( const unsigned short *text );
	UnicodeString( const UnicodeString &other )
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&other );
	}
	~UnicodeString();
	void format( UnicodeString format, ... );
	void format( const unsigned short *format, ... );
	void concat( const unsigned short *text, int length );
	void set( const UnicodeString &other )
	{
		((StringBase<unsigned short> *)this)->set(
			*(const StringBase<unsigned short> *)&other );
	}
	void trim()
	{
		((StringBase<unsigned short> *)this)->trim();
	}
	bool isEmpty() const { return !m_data || m_data->m_length == 0; }

private:
	UnicodeStringData *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void format( AsciiString format, ... );
	void toLower() { ((StringBase<char>*)this)->toLower(); }
	const char *str() const
	{
		return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
	}
};


class GameWindow;
void GadgetListBoxReset(GameWindow *);
void GadgetTextEntrySetText(GameWindow *,UnicodeString);
class GameSlot {public:void setMapAvailability(bool);};
// The already matched bounds-checked LAN slot accessor has stride0x68.
// This view covers the color/start/faction fields and its state at+0x38.
struct Rva0068D3E0Slot
{
 char m_base[0xC]; int m_color,m_start,m_faction; char m_middle[0x20];int m_type;
};
class Rva0068D3E0Arr {public:Rva0068D3E0Slot *at(int);};
class GameInfo
{
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void adjustSlotsForMap();
 void setMapForwarder(AsciiString);
 void setMapCRC(unsigned int);
 void setMapSize(unsigned int);
 GameSlot *getSlot(int);
 unsigned int getMapCRC()const{return m_crc;}
 unsigned int getMapSize()const{return m_size;}
 char m_beforeCRC[0x3C];unsigned int m_crc,m_size;
};
class LANAPI
{
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void RequestHasMap();
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
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual int AmIHost();
 virtual void slot47();
 virtual GameInfo *GetMyGame();
};
extern LANAPI *TheLAN;
extern void j_0003029c();
class __single_inheritance SkirmishScreenState
{
public:
 bool apply(void *,int);
 bool ready()
 {
  typedef bool(SkirmishScreenState::*Method)();union Bits {Method member;void(*code)();} b;
  b.code=j_0003029c;return (this->*b.member)();
 }
 char m_extent[0x134];
};
extern void j_00043d24();
extern void j_00027d3b();
class __single_inheritance LANPreferences
{
public:
 AsciiString getPreferredMap();
 int preferredColor()
 {
  typedef int(LANPreferences::*Method)();union Bits {Method member;void(*code)();}b;
  b.code=j_00043d24;return (this->*b.member)();
 }
 int preferredFaction()
 {
  typedef int(LANPreferences::*Method)();union Bits {Method member;void(*code)();}b;
  b.code=j_00027d3b;return (this->*b.member)();
 }
 char m_extent[0x14];
};
// The existing tree finder at773E0 returns a node or the cache sentinel.
// Node+3C/+40 correspond to the stored metadata size/CRC fields.
struct MapNode {char m_header[0x3C];unsigned int m_size,m_crc;};
extern void j_000263d7();
class __single_inheritance MapCache
{
public:
 void updateCache();
 MapNode *find(const AsciiString &name)
 {
  typedef MapNode *(MapCache::*Method)(const AsciiString &);union Bits{Method member;void(*code)();}b;
  b.code=j_000263d7;return (this->*b.member)(name);
 }
 MapNode *m_head;
};
extern MapCache *TheMapCache;
class BfmeAptScreenLanLobby
{
public:
 bool refreshLanGameRva00519CB0();
 void restorePreferencesRva005195B0();
 char m_before[0x25C];SkirmishScreenState m_state;LANPreferences m_preferences;
 char m_3A4[0xC];GameWindow *m_list;char m_3B4[8];GameWindow *m_chat;
};
bool BfmeAptScreenLanLobby::refreshLanGameRva00519CB0()
{
 if(m_state.ready() && TheLAN && TheLAN->GetMyGame())
 {
  GadgetListBoxReset(m_list);
  GadgetTextEntrySetText(m_chat,UnicodeString::TheEmptyString);
  TheMapCache->updateCache();
  if((unsigned char)TheLAN->AmIHost())
  {
   GameInfo *game=TheLAN->GetMyGame();
   Rva0068D3E0Slot *slot=((Rva0068D3E0Arr*)game)->at(0);
   restorePreferencesRva005195B0();
   slot->m_color=m_preferences.preferredColor();
   slot->m_faction=m_preferences.preferredFaction();
   if(slot->m_faction<=-2)slot->m_start=-1;
   slot->m_type=1;
   game->setMapForwarder(m_preferences.getPreferredMap());
   AsciiString mapName=m_preferences.getPreferredMap();
   mapName.toLower();
   MapCache *cache=TheMapCache;
   MapNode *node=cache->find(mapName);
   if(node!=cache->m_head)
   {
    TheLAN->GetMyGame()->getSlot(0)->setMapAvailability(true);
    TheLAN->GetMyGame()->setMapCRC(node->m_crc);
    TheLAN->GetMyGame()->setMapSize(node->m_size);
    TheLAN->GetMyGame()->adjustSlotsForMap();
   }
  }
  else
  {
   TheLAN->GetMyGame()->setMapCRC(TheLAN->GetMyGame()->getMapCRC());
   TheLAN->GetMyGame()->setMapSize(TheLAN->GetMyGame()->getMapSize());
   TheLAN->RequestHasMap();
  }
  return m_state.apply(TheLAN->GetMyGame(),0);
 }
 return false;
}

typedef char LanRefreshStateSize[(sizeof(SkirmishScreenState)==0x134)?1:-1];
typedef char LanRefreshPrefsSize[(sizeof(LANPreferences)==0x14)?1:-1];
