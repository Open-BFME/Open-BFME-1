// ?d_0019ff20@@YAXXZ
// partial score=0.9668 date=2026-09-28
// cl: /O2 /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// 2026-09-28 opus-5.5: early returns (if(!TheAudio) return; if(name.isEmpty()) return;) give retail's or esi,-1 CSE and 693 B;
// residue = 23 low-frame displacement bytes: retail packs exists with push_back tag at B+3 and keeps the loop spill tv at B+0x20.

typedef bool Bool;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

namespace _STL
{

class __new_alloc
{
public:
	static void *allocate( unsigned int bytes );
};

}

#include "ascii_string.h"
template<> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }
template<> inline bool StringBase<char>::isNotEmpty() const { return m_data != 0 && m_data->length != 0; }

class Dict
{
public:
	AsciiString getAsciiString( NameKeyType key, Bool *exists ) const;

	char m_body[0x14];
};

class GenKey
{
public:
	int fetch();
};

extern GenKey GenKey0012A7988;

struct Rva001A0320Record
{
	char m_prefix[4];
	Dict m_dict;
};

struct Rva0019A7D0Element
{
	int m_a;
	int m_b;
};

class Rva0019A7D0Vector
{
public:
	Rva0019A7D0Vector():m_begin(0),m_end(0),m_capacity(0) {}
	~Rva0019A7D0Vector();
	Rva0019A7D0Element *m_begin;
	Rva0019A7D0Element *m_end;
	Rva0019A7D0Element *m_capacity;
};

class Rva00197AE0Temporary
{
public:
	__forceinline Rva00197AE0Temporary()
		: m_header( 0 )
	{
		m_header = _STL::__new_alloc::allocate( 0x14 );
		m_count = 0;
		*(unsigned char *)m_header = 0;
		*(void **)((char *)m_header + 4) = 0;
		*(void **)((char *)m_header + 8) = m_header;
		*(void **)((char *)m_header + 12) = m_header;
	}
	~Rva00197AE0Temporary();

	void *m_header;
	int m_count;
	int m_compare;
};

class Rva0019A1D0Tree
{
public:
	~Rva0019A1D0Tree();

private:
	char m_body[0x0c];
};

class Rva0019A1D0Member
{
public:
	~Rva0019A1D0Member();

private:
	char m_body[0x0c];
};

class Rva0019A1D0Owner
{
public:
	Rva0019A1D0Owner();
 __forceinline ~Rva0019A1D0Owner() {}

	Rva0019A1D0Tree m_tree;
	Rva0019A1D0Member m_member;
	short m_a;
	short m_b;
};

class ScriptList
{
public:
	ScriptList();
	~ScriptList();

private:
	char m_body[0x4c];
};

struct Rva0019A7988Entry
{
	char m_prefix[4];
	void *m_data;
	char m_tail[8];
};

class PlayerAITypeSet
{
public:
	int find( AsciiString *name );

	char m_prefix[8];
	Rva0019A7988Entry *m_entries;
};

extern PlayerAITypeSet *ThePlayerAITypeSet;

class Rva001A0320Owner
{
public:
	void rva0019FF20();
	void fill( int index, Rva0019A7D0Vector *out );

private:
	char m_prefix[0x28];
	int m_count;
	Rva001A0320Record m_records[1];

	void fillHelper( int index, Rva0019A7D0Vector *out, void *entry,
		Rva00197AE0Temporary *temporary, ScriptList *scripts,
		Rva0019A1D0Owner *tree );
	void buildScriptData( Rva001A0320Record *record, ScriptList *scripts,
		Rva0019A1D0Owner *tree );
};

#pragma comment(linker, "/alternatename:?getAsciiString@Dict@@QBE?AVAsciiString@@W4NameKeyType@@PA_N@Z=?j_0002ff6d@@YAXXZ")
#pragma comment(linker, "/alternatename:?fetch@GenKey@@QAEHXZ=?j_00009304@@YAXXZ")
#pragma comment(linker, "/alternatename:?find@PlayerAITypeSet@@QAEHPAVAsciiString@@@Z=?j_0000336e@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00197AE0Temporary@@QAE@XZ=?j_000124db@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva0019A1D0Tree@@QAE@XZ=?j_0001a910@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva0019A1D0Member@@QAE@XZ=?j_0002d6a5@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva0019A1D0Owner@@QAE@XZ=?j_00008792@@YAXXZ")
#pragma comment(linker, "/alternatename:??0ScriptList@@QAE@XZ=?j_0002fe7d@@YAXXZ")
#pragma comment(linker, "/alternatename:??1ScriptList@@QAE@XZ=?j_0003b7ff@@YAXXZ")
#pragma comment(linker, "/alternatename:?fillHelper@Rva001A0320Owner@@AAEXHPAVRva0019A7D0Vector@@PAXPAVRva00197AE0Temporary@@PAVScriptList@@PAVRva0019A1D0Owner@@@Z=?j_00008634@@YAXXZ")
#pragma comment(linker, "/alternatename:?buildScriptData@Rva001A0320Owner@@AAEXPAURva001A0320Record@@PAVScriptList@@PAVRva0019A1D0Owner@@@Z=?j_0003dc0d@@YAXXZ")


#pragma comment(linker, "/alternatename:??1Rva0019A7D0Vector@@QAE@XZ=?j_000089a4@@YAXXZ")
extern GenKey GenKey0012A7918;
void *operator new(unsigned int,void *p) {return p;}
void operator delete(void*,void*) {}
namespace _STL {
struct __false_type { __false_type() {} };
template<class T> class allocator {};
template<class T,class U> __forceinline void _Construct(T *p,const U &v) { new(p) T(v); }
template<class T,class A=allocator<T> > class vector {
public:
 T *m_begin,*m_end,*m_capacity;
 vector():m_begin(0),m_end(0),m_capacity(0) {}
 ~vector();
 __forceinline void push_back(const T &value) {
  if(m_end!=m_capacity) {_Construct(m_end,value); ++m_end;}
  else _M_insert_overflow(m_end,value,__false_type(),1,true);
 }
protected:
 void _M_insert_overflow(T*,const T&,const __false_type&,unsigned int,bool);
};
}
#pragma comment(linker, "/alternatename:??1?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QAE@XZ=?j_00026ab2@@YAXXZ")
struct Rva0019FF20AudioData {char prefix[0x74]; AsciiString field74;};
class AudioManager {public:
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
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual Rva0019FF20AudioData *slot72();
};
extern AudioManager *TheAudio;
void Rva001A0320Owner::rva0019FF20() {
 int count=m_count;
 for(int index=0;index<count;++index) {
  Rva001A0320Record *record;
  if(index<0 || index>=m_count) record=0;
  else record=&m_records[index];
  Dict *dict=&record->m_dict;
  bool exists;
  if(dict && dict->getAsciiString((NameKeyType)GenKey0012A7918.fetch(),&exists).isEmpty()) {
   if(index==-1)return;
   AsciiString name;
   if(!TheAudio) return;
   name=TheAudio->slot72()->field74;
   if(name.isEmpty()) return;
     Rva0019A7D0Vector out;
     Rva00197AE0Temporary temporary;
     _STL::vector<AsciiString> names;
     ScriptList scripts;
     Rva0019A1D0Owner tree;
     names.push_back(name);
     fillHelper(index,&out,&names,&temporary,&scripts,&tree);
     buildScriptData(record,&scripts,&tree);
   return;
  }
 }
}
