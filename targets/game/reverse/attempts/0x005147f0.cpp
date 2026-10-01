// ?rva005147F0@BfmeAptScreenInGameChat@@QAEXXZ
// partial score=0.2558 date=2026-10-01
#include "game/GameEngine/Include/GameClient/BfmeAptScreenBaseLayout.h"
// cl: /DNDEBUG /MD /EHsc /I.
// stlport
//
// BfmeAptScreenInGameChat::rva00513BF0, retail 0x00513BF0, 511 bytes: collects the profile ids of the
// selected friends-list rows, filtered by internet player status and by the buddy-lookup result mask.
// The friend-button callers at 0x00514DA0 and 0x005151F0 reach it through the pinned ILT 0x00017373.

#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned short WideChar;

class GameWindow;

template <typename T>
class StringBase
{
	friend class UnicodeString;

	public:
	StringBase() : m_data( 0 ) {}
	~StringBase() { releaseBuffer(); }

	private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[ 1 ];
	};

	Header *m_data;
	void releaseBuffer();
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString( const UnicodeString &other )
		: StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
};

Int GadgetListBoxGetNumEntries( GameWindow *listbox );
void GadgetListBoxGetSelected( GameWindow *listbox, Int *selectList );
UnicodeString GadgetListBoxGetText( GameWindow *listbox, Int row, Int column );
void *GadgetListBoxGetItemData( GameWindow *listbox, Int row, Int column );

class Player
{
public:
	UnicodeString getPlayerDisplayName();
};

struct Rva002EE330PlayerList
{
	unsigned char m_unmodelled000[ 0xc ];
	Player *m_local;
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class BfmeAptScreenBase
{
public:
	virtual ~BfmeAptScreenBase();
	virtual int aptSlot1(unsigned int, unsigned int, unsigned int);
	virtual int aptSlot2(unsigned int, unsigned int, unsigned int);
	virtual int aptSlot3(unsigned int);
	virtual int aptSlot4(unsigned int, unsigned int);
	virtual int aptSlot5();
	virtual int aptSlot6();
	virtual void *aptSlot7();
	virtual int aptSlot8();
	virtual int aptSlot9();
	virtual bool aptSlot10();
	virtual bool aptSlot11();
	virtual void aptSlot12();
	virtual void aptSlot13();
private:
	BfmeAptScreenBaseLayout<> m_primaryStorage;
};

class S4Owner
{
public:
	virtual ~S4Owner();
private:
	unsigned char m_unmodelled[0x30];
};

class _bfme_AptGameWindow : public BfmeAptScreenBase, public S4Owner
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
	unsigned int movie() const { return ((const unsigned int *)m_tail)[1]; }
private:
	unsigned char m_tail[0xc];
};

class __multiple_inheritance BfmeAptScreenInGameChat
	: public _bfme_AptGameWindow
{
public:
	Int rva00513BF0( GameWindow *list, void *selected, Int buddyMask, Bool skipStatusFilter );
	void rva005147F0();
	void _bfme_enableChat(bool enabled);
	Int _bfme_getInternetPlayerStatus( const UnicodeString &name );
	Int rva00512890( Int profileID, UnicodeString &result );

private:
	int m_field258;
	unsigned char m_padding25c[ 4 ];
	int m_field260;
	GameWindow *m_friendsList;
	int m_field268;
	unsigned char m_padding26c[ 4 ];
	unsigned char m_tail[ 0x292 - 0x270 ];
	bool addDirty, addEnabled, removeDirty, removeEnabled;
};


#include "game/GameEngine/Source/Common/SmallGaps/Rva00511260SetAddButton.cpp"

template<class T> struct Rva005147F0Allocator : std::allocator<T> {
 template<class U> struct rebind { typedef Rva005147F0Allocator<U> other; };
 T *allocate(size_t count, const void * = 0) const {
  return count ? (T *)_STL::__node_alloc<true, 0>::allocate(count * sizeof(T)) : 0;
 }
 void deallocate(T *ptr, size_t count) const {
  if(ptr) _STL::__node_alloc<true, 0>::deallocate(ptr,count*sizeof(T));
 }
};
typedef std::vector<int, Rva005147F0Allocator<int> > Rva005147F0Vector;
void BfmeAptScreenInGameChat::rva005147F0()
{
 Rva005147F0Vector values;
 bool allReady=false;
 bool chatReady=false;
 if (rva00513BF0(m_friendsList,&values,7,false)>0) {
  Rva005147F0Vector::iterator end=values.end();
  Rva005147F0Vector::iterator it=values.begin();
  allReady=true;
  while(it!=end) {
   {
    UnicodeString result;
    if(rva00512890(*it,result)!=4) allReady=false;
    if(rva00512890(*it,result)==1) chatReady=true;
   }
   ++it;
   if(!allReady) break;
  }
 }
 int *selected=0;
 GadgetListBoxGetSelected(m_friendsList,(int *)&selected);
 bool removeReady=selected && *selected>=0;
 if(addDirty || allReady!=addEnabled) {
  addDirty=false;addEnabled=allReady;
  Rva00579160TheManager->fire((void*)movie(),allReady?"EnableAddButton":"DisableAddButton",0,0,0,0,0,0);
 }
 if(removeDirty || removeReady!=removeEnabled) {
  removeEnabled=removeReady;removeDirty=false;
  Rva00579160TheManager->fire((void*)movie(),removeReady?"EnableRemoveButton":"DisableRemoveButton",0,0,0,0,0,0);
 }
 _bfme_enableChat(chatReady);
}
