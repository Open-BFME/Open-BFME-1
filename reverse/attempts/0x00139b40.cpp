// ?newTemplate@BfmeThingFactory@@QAEPAVThingTemplate@@ABVAsciiString@@@Z
// partial score=0.45 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// BFME factory allocation at RVA 0x00139B40.
template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
public:
 void set(const StringBase<T> &);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
 AsciiString &operator=(const AsciiString &s) { set(s); return *this; }
	const char *str( void ) const { return m_data ? m_data->m_text : ""; }
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString( const unsigned short *text ) : StringBase<unsigned short>( text ) {}
	UnicodeString( const UnicodeString &other ) : StringBase<unsigned short>( other ) {}
	~UnicodeString() {}
	const unsigned short *str( void ) const;
};


extern "C" __declspec(dllimport) int __cdecl strncmp(const char *,const char *,unsigned int);
class ThingTemplate {
 public:
 ThingTemplate();
 ThingTemplate &operator=(const ThingTemplate &);
 void setCopiedFromDefault();
 unsigned char prefix[0x20];
 AsciiString name;
 unsigned char middle[0x38c-0x24];
 ThingTemplate *next;
 unsigned char beforeID[0x478-0x390];
 unsigned short id;
 unsigned char tail[0x4d4-0x47a];
};
typedef char VerifyThingTemplateSize[sizeof(ThingTemplate)==0x4d4 ? 1 : -1];
struct Rva001366A0Node { void *next; AsciiString key; ThingTemplate *value; };
class Rva00137E80Map { public:
 Rva001366A0Node *find(const AsciiString &);
 ThingTemplate *&operator[](const AsciiString &);
};
extern unsigned char rva_00eed611_copyState;
class BfmeThingFactory { public:
 const ThingTemplate *findTemplate(const AsciiString &);
 ThingTemplate *newTemplate(const AsciiString &);
 bool exists(const AsciiString &name) { if(!strncmp(name.str(),"***TESTING",10)) return true; return map.find(name)!=0; }
 __forceinline void initializeDefault(ThingTemplate *t) {
 if(exists(AsciiString("DefaultThingTemplate"))) {
  const ThingTemplate *d=findTemplate(AsciiString("DefaultThingTemplate"));
  rva_00eed611_copyState=1;
  *t=*d;
  rva_00eed611_copyState=0;
  t->setCopiedFromDefault();
 }
 }
 unsigned char prefix[8]; ThingTemplate *head; unsigned short nextID; unsigned short pad; Rva00137E80Map map;
};
ThingTemplate *BfmeThingFactory::newTemplate(const AsciiString &name) {
 ThingTemplate *t=new ThingTemplate;
 initializeDefault(t);
 unsigned int identifier=nextID;
 nextID=(unsigned short)(identifier+1);
 t->id=(unsigned short)identifier;
 t->name=name;
 map.find(t->name);
 t->next=head;
 head=t;
 map[t->name]=t;
 return t;
}
