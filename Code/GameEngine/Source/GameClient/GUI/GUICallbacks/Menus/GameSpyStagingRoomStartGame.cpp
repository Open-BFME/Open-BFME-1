// cl: /DNDEBUG /MD /EHsc
// GameSpyStagingRoom::startGame, RVA 0x0063A3B0, 662 bytes.
// Identity: matched default/copy constructors install vtable VA 0x01102FE0;
// slot 3 routes through ILT 0x0000788D to this body.
// BFME layout: GameInfo 0x58, slots 0x78, local IP/port pair +0x34/+0x38.
// Unlike the ZH scaffold, BFME resolves player-name keys, clears both quick-match
// authentication strings and uses the player record tree for profile metadata.
// Existing j-thunk routes retain uncertain tree/setter identities without new pins.
class UnicodeString;
template<class T> struct StringData {int refs; unsigned short length,capacity; T text[1];};
template<class T> class StringBase {
 friend class AsciiString;friend class UnicodeString;
protected:
 StringBase():m_data(0){}
 StringBase(const StringBase&);
 ~StringBase(){releaseBuffer();}
 StringData<T>*m_data;
private:
 StringBase(const T*);
 void releaseBuffer();
 void set(const StringBase&);
public:
 void set(const T*,int);
 void concat(const T*,int);
};
class AsciiString:private StringBase<char>{
public:
 AsciiString():StringBase<char>(){}
 AsciiString(const AsciiString&s):StringBase<char>(s){}
 AsciiString(const char*s):StringBase<char>(s){}
 void translate(const UnicodeString&);
 const char*str()const{return m_data?m_data->text:"";}
 ~AsciiString(){}
 AsciiString&operator=(const AsciiString&s){StringBase<char>::set(s);return *this;}
};
class UnicodeString:private StringBase<unsigned short>{
public:
 UnicodeString():StringBase<unsigned short>(){}
 UnicodeString(const UnicodeString&s):StringBase<unsigned short>(s){}
 ~UnicodeString(){}
 void translate(const AsciiString&);
};

struct NetAddress{unsigned int ip;unsigned short port;};
class GameSlot{public:virtual void v0();char fields[0x24];UnicodeString name;AsciiString serial;NetAddress address;char tail[0xc];bool isHuman()const;UnicodeString getName()const;};
// The retail locale setter is ILT 0x288DA -> 0x505D40. The existing named
// setLocale pin reaches 0x6380F0 instead; retain this verified address owner.
class Gen00505D40{public:void bfmeSet(AsciiString);};
class GameSpyGameSlot:public GameSlot{public:
 int profileID;AsciiString login;char extra[0x14];int rankPoints,favoriteSide;char pad[8];AsciiString authName,authToken;
 void setLoginName(AsciiString s){login=s;}
};
struct PlayerInfoNode{char prefix[0x1c];AsciiString locale;char gap[8];int profileID;char gap2[4];int rankPoints;char gap3[12];int favoriteSide;};
extern void j_00022930();
class PlayerInfoTree{public:PlayerInfoNode*head;
 PlayerInfoNode*find(const AsciiString&name){typedef PlayerInfoNode*(PlayerInfoTree::*F)(const AsciiString&);union{void(*entry)();F method;}c;c.entry=j_00022930;return(this->*c.method)(name);}
};
class GameSpyInfoInterface{public:
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual void v8();
 virtual void v9();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual PlayerInfoTree*getPlayerInfoMap();
 virtual AsciiString*findPlayerName(const char*);
 virtual void v20();
 virtual void v21();
 virtual void v22();
 virtual void v23();
 virtual void v24();
 virtual void v25();
 virtual void v26();
 virtual void v27();
 virtual int getLocalProfileID();
 virtual void v29();
 virtual void v30();
 virtual void v31();
 virtual void v32();
 virtual void v33();
 virtual void v34();
 virtual void v35();
 virtual void v36();
 virtual void v37();
 virtual void v38();
 virtual void v39();
 virtual void v40();
 virtual void v41();
 virtual void v42();
 virtual void v43();
 virtual void v44();
 virtual void v45();
 virtual void v46();
 virtual void v47();
 virtual void v48();
 virtual void v49();
 virtual void v50();
 virtual void v51();
 virtual void v52();
 virtual void v53();
 virtual void v54();
 virtual void v55();
 virtual void v56();
 virtual void v57();
 virtual void v58();
 virtual void v59();
 virtual void v60();
 virtual void v61();
 virtual void v62();
 virtual void v63();
 virtual void v64();
 virtual void v65();
 virtual void v66();
 virtual void v67();
 virtual void v68();
 virtual void v69();
 virtual void v70();
 virtual void v71();
 virtual void v72();
 virtual void v73();
 virtual void v74();
 virtual void v75();
 virtual void v76();
 virtual void v77();
 virtual void v78();
 virtual void v79();
 virtual void v80();
 virtual void v81();
 virtual void v82();
 virtual unsigned int getInternalIP();
 virtual unsigned short getInternalPort();
};
class GameInfo{public:
 virtual void v0();virtual void v1();virtual void v2();virtual void startGame(int);virtual void v4();virtual int getLocalSlotNum();
 char fields[0x10];GameSlot*slot[8];NetAddress localAddress;char tail[0x1c];
};
class GameSpyStagingRoom:public GameInfo{public:
 GameSpyGameSlot slots[8];char extra[0x24];bool isQM;
 virtual void startGame(int);void launchGame();
};
class NAT{public:virtual ~NAT();NAT();char fields[0xc4];void attachSlotList(GameSlot**,int,unsigned int);void establishConnectionPaths();};
extern NAT*TheNAT;
extern GameSpyInfoInterface*TheGameSpyInfo;
typedef char SlotCheck[sizeof(GameSpyGameSlot)==0x78?1:-1];
typedef char BaseCheck[sizeof(GameInfo)==0x58?1:-1];
void GameSpyStagingRoom::startGame(int gameID)
{
    NetAddress address;
    address.ip = TheGameSpyInfo->getInternalIP();
    address.port = TheGameSpyInfo->getInternalPort();
    localAddress = address;
    if (TheNAT) {
        delete TheNAT;
        TheNAT = 0;
    }

    int numHumans = 0;
    for (int i = 0; i < 8; ++i) {
        if (slots[i].isHuman()) {
            ++numHumans;
            AsciiString gsName;
            gsName.translate(slots[i].getName());
            slots[i].setLoginName(gsName);
            AsciiString *key = TheGameSpyInfo->findPlayerName(gsName.str());
            if (isQM) {
                if (getLocalSlotNum() == i)
                    slots[i].profileID = TheGameSpyInfo->getLocalProfileID();
                slots[i].authName = AsciiString("");
                slots[i].authToken = AsciiString("");
            } else {
                PlayerInfoTree *tree = TheGameSpyInfo->getPlayerInfoMap();
                PlayerInfoNode *node = tree->head;
                if (key)
                    node = tree->find(*key);
                if (node != tree->head) {
                    slots[i].profileID = node->profileID;
                    ((Gen00505D40 *)&slots[i])->bfmeSet(node->locale);
                    slots[i].rankPoints = node->rankPoints;
                    slots[i].favoriteSide = node->favoriteSide;
                }
            }
        }
    }

    if (numHumans < 2)
        launchGame();
    else {
        TheNAT = new NAT;
        TheNAT->attachSlotList(slot, getLocalSlotNum(), localAddress.ip);
        TheNAT->establishConnectionPaths();
    }
}
