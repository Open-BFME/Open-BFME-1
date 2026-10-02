// cl: /MD /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// 0x00788A30: matched enumerateGeometry caller establishes this owner/signature.
// Retail has 1004 executable bytes and 38 bytes of dispatch tables immediately
// following; all 1042 bytes reproduce in probe, with the table targets verified.
// The 0x28-byte Geometry00786B70 allocation calls 0x00786B70 through 0x000347A2:
// its 40-byte ctor installs 0x01126AE4 and zeroes the pointer vector +4 and
// six-word tail +0x10. It takes ECX with zero stack arguments and returns this in EAX.
// The vector payload class names below are the existing CALLEE symbols only.
// Keep payloads incomplete: the parser's six/four-float records are not asserted
// to be ProductionPrerequisite or W3DAnimationInfo. Retail appends 24/16 bytes.

#include <hash_map>
#include <vector>
#include <stdio.h>

#include "string_base.h"
#include "ascii_string.h"
typedef AsciiString BFMERetailAsciiString;

class File
{
public:
	virtual ~File();
	virtual void slot04();
	virtual void close();
	virtual int slot0c(void *buffer, int bytes);
	virtual int slot10(const void *buffer, int bytes);
	virtual int slot14(int bytes, int mode);
	virtual void nextLine(char *buffer, int bufferSize);
	virtual bool slot1c();
	virtual bool slot20(int &value);
	virtual bool slot24(float &value);
	virtual bool slot28(AsciiString &value);
	virtual bool slot2c(const char *format, ...);
	virtual int slot30();
	virtual int slot34();
	virtual char *slot38();
	virtual File *slot3c();

	bool eof();
};

class FileSystem
{
public:
	File *openFile(const char *name, int access);
};

extern FileSystem *TheFileSystem;

// This helper is static in Open2Conv007.cpp.  MSVC's private-register ABI is
// encoded by the declaration's internal linkage; the exact decorated name is
// already carried by that matched body, so this TU-local declaration can use
// it without inventing a second semantic owner.
static File *Open2OpenPastSeparators(const AsciiString &name) throw()
{
	const char *text = name.str();
	File *file = TheFileSystem->openFile(text, 1);
	while (file == 0)
	{
		text = ::strchr(text, '\\');
		if (text == 0)
			return 0;
		++text;
		file = TheFileSystem->openFile(text, 1);
	}
	return file;
}

const char *parsePathNumber007861E0(const AsciiString&,int*,bool);
enum Relationship { BfmeLookupValue0=0 };
class ProductionPrerequisite;
class W3DAnimationInfo;
namespace _STL {
template<> class vector<ProductionPrerequisite> {
public: void *begin,*end,*capacity;
 vector():begin(0),end(0),capacity(0) {}
 void push_back(const ProductionPrerequisite&);
};
template<> class vector<W3DAnimationInfo> {
public: void *begin,*end,*capacity;
 vector():begin(0),end(0),capacity(0) {}
 void push_back(const W3DAnimationInfo&);
};
}
struct Gen_t_00786f50_m4pod { int a[1]; };
namespace _STL {
template<> struct __type_traits<Gen_t_00786f50_m4pod> {
 typedef __true_type has_trivial_default_constructor;
 typedef __true_type has_trivial_copy_constructor;
 typedef __true_type has_trivial_assignment_operator;
 typedef __true_type has_trivial_destructor;
 typedef __true_type is_POD_type;
};
}
class Geometry00786B70 {
public:
 Geometry00786B70() throw();
 void *m_at00;
 _STL::vector<Gen_t_00786f50_m4pod> m_records;
 float m_at10[6];
};
extern int R2Data01126AFC, R2Data01126B2C;
class Rva00787380 {
public:
 void *m_at00;
 int m_at04;
 _STL::vector<ProductionPrerequisite> m_at08;
 Rva00787380():m_at00(&R2Data01126AFC),m_at04(0) {}
};
class Rva007876D0 {
public:
 void *m_at00;
 float m_at04;
 int m_at08;
 _STL::vector<W3DAnimationInfo> m_at0C;
 Rva007876D0():m_at00(&R2Data01126B2C) {}
};
class BfmeA1159 {
public:
 BfmeA1159() throw();
 void *m_bfme00;
 unsigned m_bfme04;
 char m_bfme08[12];
 bool m_bfme14,m_bfme15;
 unsigned m_bfme18;
 float m_bfme1c[6];
};
struct Rva007882F0Value;
class Rva007882F0PointerMap { public: Rva007882F0Value *lookup(unsigned int); };
class GeometryRecord00788A30 {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
 virtual unsigned slot10();
};
class Rva00789010Owner {
public:
 void rva00788A30(const AsciiString& filename);
 AsciiString m_name;
 unsigned m_at04;
 _STL::hash_map<int,Relationship> m_at08;
};
void Rva00789010Owner::rva00788A30(const AsciiString& filename)
{
 int number=0;
 const char *path=parsePathNumber007861E0(filename,&number,true);
 if (!path) return;
 File *file=Open2OpenPastSeparators(AsciiString(path));
 if (!file) return;
 char line[1024]; line[1023]=0;
 file->nextLine(line,1023);
 if(line[0]!='c') { file->close();return; }
 GeometryRecord00788A30 *current=0;
 _STL::vector<ProductionPrerequisite> *triangles=0;
 Geometry00786B70 *geometry=new Geometry00786B70;
 *(Geometry00786B70**)&m_at08[number]=geometry;
 while(!file->eof()) {
  file->nextLine(line,1023);
  switch(line[0]) {
  case 'c': current=0;triangles=0;break;
  case 's': {
   unsigned red,green,blue,alpha;
   switch(line[2]) {
   case 't': {
    char wrap=0;
    BfmeA1159 *record=new BfmeA1159;
    current=(GeometryRecord00788A30*)record;
    unsigned texture;
    sscanf(line,"s t%c:%d:%d:%d:%d:%d:%f:%f:%f:%f:%f:%f",&wrap,&red,&green,&blue,&alpha,&texture,
     &record->m_bfme1c[0],&record->m_bfme1c[1],&record->m_bfme1c[2],&record->m_bfme1c[3],&record->m_bfme1c[4],&record->m_bfme1c[5]);
    record->m_bfme04=(((alpha<<8)|red)<<8|green)<<8|blue;
    record->m_bfme14=wrap=='w';
    record->m_bfme18=(unsigned)((Rva007882F0PointerMap*)this)->lookup(texture);
    triangles=(_STL::vector<ProductionPrerequisite>*)&record->m_bfme08;
    break;
   }
   case 's': {
    Rva00787380 *record=new Rva00787380;
    current=(GeometryRecord00788A30*)record;
    sscanf(line,"s s:%d:%d:%d:%d",&red,&green,&blue,&alpha);
    record->m_at04=(((alpha<<8)|red)<<8|green)<<8|blue;
    triangles=&record->m_at08;
    break;
   }
   case 'l': {
    Rva007876D0 *record=new Rva007876D0;
    current=(GeometryRecord00788A30*)record;
    sscanf(line,"s l:%f:%d:%d:%d:%d",&record->m_at04,&red,&green,&blue,&alpha);
    record->m_at08=(((alpha<<8)|red)<<8|green)<<8|blue;
    break;
   }
   default: file->close(); return;
   }
   geometry->m_records.push_back(*(Gen_t_00786f50_m4pod*)&current);
   break;
  }
  case 't': {
   if(!current || !triangles) { file->close(); return; }
   float triangle[6];
   sscanf(line,"t %f:%f:%f:%f:%f:%f",&triangle[0],&triangle[1],&triangle[2],&triangle[3],&triangle[4],&triangle[5]);
   triangles->push_back(*(ProductionPrerequisite*)triangle);
   break;
  }
  case 'l': {
   if(!current || !current->slot10()) { file->close();return; }
   float segment[4];
   sscanf(line,"l %f:%f:%f:%f",&segment[0],&segment[1],&segment[2],&segment[3]);
   ((_STL::vector<W3DAnimationInfo>*)((char*)current+12))->push_back(*(W3DAnimationInfo*)segment);
   break;
  }
  default: file->close(); return;
  }
 }
 file->close();
}
