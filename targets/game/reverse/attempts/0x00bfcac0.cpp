// ?d_00bfcac0@@YAXXZ
// partial score=0.24 date=2026-10-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/asciistring_outofline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Igame/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// DataChunk.cpp
// Implementation of Data Chunk save/load system
// Author: Michael S. Booth, October 2000

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// ??0OutputChunk@@QAE@XZ present-unmatched
// ??0Mapping@@QAE@XZ present-unmatched

#include "stdlib.h"
#include "string.h"
#include "Compression.h"
// BFME's placement operator delete is one shared 12-byte body that calls the
// CRT free import at 0x009F6C3A directly; ZH's macro routes it through
// ::operator delete, which is a different (and here, wrong) callee.  Scoped to
// the one header that declares this TU's pooled classes.
#pragma push_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
extern "C" void free(void *);
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
friend class DataChunkInput; \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
		return MP_GLUE_ALLOCATE(ARGCLASS); \
	} \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		free(p); \
	} \
protected: \
	inline void *operator new(size_t s) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
		return ::operator new(s); \
	} \
	inline void operator delete(void *p) \
	{ \
		::operator delete(p); \
	} \
private: \
	virtual MemoryPool *getObjectMemoryPool() \
	{ \
		return ARGCLASS::getClassMemoryPool(); \
	} \
public:
#include "Common/DataChunk.h"
#pragma pop_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")
#include "Common/File.h"
#include "Common/FileSystem.h"
#include "Common/GameEngine.h"

// UnicodeString is StringBase<WideChar>, and retail inlined its one-line
// forwarders away: the call sites below encode the StringBase<WideChar> bodies
// directly, not the ZH UnicodeString spellings (which resolve to the NARROW
// StringBase<char> bodies).
#include "string_base.h"

// ??0?$StringBase@G@@AAE@ABV0@@Z at 0x00888400 -- private, which is what
// mangles it AAE.
inline UnicodeString::UnicodeString( const UnicodeString &stringSrc )
{
	((StringBase<WideChar> *)this)->StringBase<WideChar>::StringBase(
		*(const StringBase<WideChar> *)&stringSrc );
}

// If verbose, lots of debug logging.
#define not_VERBOSE

// BFME retail GameEngine vtable: serviceWindowsOS is slot 16 (+0x40).
// ZH GameEngine.h places it earlier; force the retail slot for DataChunk yield sites.
class BFME_GameEngineServiceWindowsOS {
public:
	virtual void _bfme_ge_slot00() = 0;
	virtual void _bfme_ge_slot01() = 0;
	virtual void _bfme_ge_slot02() = 0;
	virtual void _bfme_ge_slot03() = 0;
	virtual void _bfme_ge_slot04() = 0;
	virtual void _bfme_ge_slot05() = 0;
	virtual void _bfme_ge_slot06() = 0;
	virtual void _bfme_ge_slot07() = 0;
	virtual void _bfme_ge_slot08() = 0;
	virtual void _bfme_ge_slot09() = 0;
	virtual void _bfme_ge_slot10() = 0;
	virtual void _bfme_ge_slot11() = 0;
	virtual void _bfme_ge_slot12() = 0;
	virtual void _bfme_ge_slot13() = 0;
	virtual void _bfme_ge_slot14() = 0;
	virtual void _bfme_ge_slot15() = 0;
	virtual void serviceWindowsOS() = 0;
};

static inline void bfmeDataChunkYieldToOS(void)
{
	::Sleep(0);
	if (TheGameEngine)
		reinterpret_cast<BFME_GameEngineServiceWindowsOS *>(TheGameEngine)->serviceWindowsOS();
}

CachedFileInputStream::CachedFileInputStream(void):m_size(0),m_buffer(NULL),m_pos(0)
{
}

CachedFileInputStream::~CachedFileInputStream(void)
{
	if (m_buffer) {
		delete[] m_buffer;
		m_buffer=NULL;
	}
}

// BFME's AsciiString carries the eight-byte StringBase header where this TU
// compiles the four-byte one, so str() is spelled out at retail's offset.
#define BFME_STR8(s) (*(char *const *)&(s) ? *(char *const *)&(s) + 8 : (char *)"")

// File's virtuals sit one entry lower than the vendored header declares:
// close is +0x08, size is +0x2C and readEntireAndClose is +0x34, against
// +0x0C, +0x30 and +0x38.  FileSystem::openFile is a DIRECT call in both and
// needs no view.
class BfmeFileView
{
public:
	virtual void _bfme_file_v0( void ) = 0;
	virtual void _bfme_file_v1( void ) = 0;
	virtual void close( void ) = 0;							///< vtable +0x08
	virtual void _bfme_file_v3( void ) = 0;
	virtual void _bfme_file_v4( void ) = 0;
	virtual void _bfme_file_v5( void ) = 0;
	virtual void _bfme_file_v6( void ) = 0;
	virtual void _bfme_file_v7( void ) = 0;
	virtual void _bfme_file_v8( void ) = 0;
	virtual void _bfme_file_v9( void ) = 0;
	virtual void _bfme_file_v10( void ) = 0;
	virtual Int size( void ) = 0;							///< vtable +0x2C
	virtual void _bfme_file_v12( void ) = 0;
	virtual char *readEntireAndClose( void ) = 0;			///< vtable +0x34
};

Bool CachedFileInputStream::open(AsciiString path)
{
	File *file=TheFileSystem->openFile(BFME_STR8(path), File::READ | File::BINARY);
	m_size = 0;

	if (file) {
		m_size=((BfmeFileView *)file)->size();
		if (m_size) {
			m_buffer = ((BfmeFileView *)file)->readEntireAndClose();
			file = NULL;
		}
		m_pos=0;
	}

	if (CompressionManager::isDataCompressed(m_buffer, m_size) == 0)
	{
		//DEBUG_LOG(("CachedFileInputStream::open() - file %s is uncompressed at %d bytes!\n", path.str(), m_size));
	}
	else
	{
		Int uncompLen = CompressionManager::getUncompressedSize(m_buffer, m_size);
		//DEBUG_LOG(("CachedFileInputStream::open() - file %s is compressed!  It should go from %d to %d\n", path.str(),
		//	m_size, uncompLen));
		char *uncompBuffer = NEW char[uncompLen];
		Int actualLen = CompressionManager::decompressData(m_buffer, m_size, uncompBuffer, uncompLen);
		if (actualLen == uncompLen)
		{
			//DEBUG_LOG(("Using uncompressed data\n"));
			delete[] m_buffer;
			m_buffer = uncompBuffer;
			m_size = uncompLen;
		}
		else
		{
			//DEBUG_LOG(("Decompression failed - using compressed data\n"));
			// decompression failed.  Maybe we invalidly thought it was compressed?
			delete[] uncompBuffer;
		}
	}
	//if (m_size >= 4)
	//{
	//	DEBUG_LOG(("File starts as '%c%c%c%c'\n", m_buffer[0], m_buffer[1],
	//		m_buffer[2], m_buffer[3]));
	//}

	if (file)
	{
		((BfmeFileView *)file)->close();
	}
	return m_size != 0;
}

void CachedFileInputStream::close(void)
{
	if (m_buffer) {
		delete[] m_buffer;
		m_buffer=NULL;
	}
	m_pos=0;
	m_size=0;
}

Int CachedFileInputStream::read(void *pData, Int numBytes)
{
	if (m_buffer) {
		if ((numBytes+m_pos)>m_size) {
			numBytes=m_size-m_pos;
		}
		if (numBytes) {
			memcpy(pData,m_buffer+m_pos,numBytes);
			m_pos+=numBytes;
		}
		return(numBytes);
	}
	return 0;
}

UnsignedInt CachedFileInputStream::tell(void)
{
	return m_pos;
}

Bool CachedFileInputStream::absoluteSeek(UnsignedInt pos)
{
	if (pos<0) return false;
	if (pos>m_size) {
		pos=m_size;
	}
	m_pos=pos;
	return true;
}

Bool CachedFileInputStream::eof(void)
{
	return m_size==m_pos;
}

// ?rewind@CachedFileInputStream@@QAEXXZ
void CachedFileInputStream::rewind()
{
	m_pos=0;
}

// -----------------------------------------------------------

//
// FileInputStream - helper class.	Used to read in data using a FILE *
//
/*
// ??0FileInputStream@@ present-unmatched
FileInputStream::FileInputStream(void):m_file(NULL)
{
}

// ??1FileInputStream@@ present-unmatched
FileInputStream::~FileInputStream(void)
{
	if (m_file != NULL) {
		m_file->close();
		m_file = NULL;
	}
}

// ?open@FileInputStream@@ present-unmatched
Bool FileInputStream::open(AsciiString path)
{
	m_file = TheFileSystem->openFile(path.str(), File::READ | File::BINARY);
	return m_file==NULL?false:true;
}

// ?close@FileInputStream@@ present-unmatched
void FileInputStream::close(void)
{
	if (m_file != NULL) {
		m_file->close();
		m_file = NULL;
	}
}

// ?read@FileInputStream@@ present-unmatched
Int FileInputStream::read(void *pData, Int numBytes)
{
	int bytesRead = 0;
	if (m_file != NULL) {
		bytesRead = m_file->read(pData, numBytes);
	}
	return(bytesRead);
}

// ?tell@FileInputStream@@ present-unmatched
UnsignedInt FileInputStream::tell(void)
{
	UnsignedInt pos = 0;
	if (m_file != NULL) {
		pos = m_file->position();
	}
	return(pos);
}

// ?absoluteSeek@FileInputStream@@ present-unmatched
Bool FileInputStream::absoluteSeek(UnsignedInt pos)
{
	if (m_file != NULL) {
		return (m_file->seek(pos, File::START) != -1);
	}
	return(false);
}

// ?eof@FileInputStream@@ present-unmatched
Bool FileInputStream::eof(void)
{
	if (m_file != NULL) {
		return (m_file->size() == m_file->position());
	}	 
	return(true);
}

// byte-exact reconstruction: game/GameEngine/Source/Common/FileInputStreamRewindThunk.cpp
// ?rewind@FileInputStream@@ present-unmatched
void FileInputStream::rewind()
{
	if (m_file != NULL) {
		m_file->seek(0, File::START);
	}
}
*/

//----------------------------------------------------------------------
// DataChunkOutput
// Data will be stored to a temporary m_tmp_file until the DataChunkOutput
// object is destroyed.  At that time, the actual output m_tmp_file will
// be written, including a table of m_contents.
//----------------------------------------------------------------------

// DataChunkOutput's constructor, destructor and openDataChunk are supplied by
// DataChunkOutput.cpp and DataChunkOutputDestructor.cpp. Those native bodies
// preserve the retail temporary-file protocol and BFME object layout.

// ?closeDataChunk@DataChunkOutput@@QAEXXZ
// Body in DataChunk_closeDataChunk.asm (exact 118B retail).

void DataChunkOutput::writeReal( Real r ) 
{ 
	::fwrite( (const char *)&r, sizeof(float) , 1, m_tmp_file  ); 
}

void DataChunkOutput::writeInt( Int i ) 
{ 
	::fwrite( (const char *)&i, sizeof(Int) , 1, m_tmp_file ); 
}

void DataChunkOutput::writeByte( Byte b ) 
{ 
	::fwrite( (const char *)&b, sizeof(Byte) , 1, m_tmp_file ); 
}

void DataChunkOutput::writeArrayOfBytes(char *ptr, Int len) 
{ 
	::fwrite( (const char *)ptr, 1, len , m_tmp_file ); 
}

// String serialization uses the verified providers in DataChunkOutput.cpp.

// ?writeNameKey@DataChunkOutput@@QAEXW4NameKeyType@@@Z
// Body in DataChunk_writeNameKey.asm (exact 134B retail @ 0x00104300).
// Queue 0x00454F43 was misplaced (inside MapUtil Player_%d_Start fn @ 0x454EF0).


// ?writeDict@DataChunkOutput@@QAEXABVDict@@@Z
// Body in DataChunk_writeDict.asm (exact 572B retail @ 0x001043B0).
// Queue 0x001043FB was INSIDE (after first fwrite of pair-count).

// Force-emit Dict inline accessors matched as out-of-line COMDATs on this TU.
// Previously only pulled by the C++ writeDict body (now MASM).
static void bfme_force_dict_accessors(const Dict &d, Int n)
{
	(void)d.getPairCount();
	(void)d.getNthKey(n);
	(void)d.getNthType(n);
}
// Address-of prevents the static helper (and thus the accessor COMDATs) from being dropped.
void (*bfme_force_dict_accessors_anchor)(const Dict &, Int) = &bfme_force_dict_accessors;

//----------------------------------------------------------------------
// DataChunkTableOfContents
//----------------------------------------------------------------------

// Table construction uses the retail inline provider in DataChunkOutput.cpp.

// Table destruction uses the native inline providers in DataChunkInput.cpp
// and DataChunkOutputDestructor.cpp, whose retail parents delete list nodes
// through their virtual deleting destructor.

// convert name to integer identifier
UnsignedInt DataChunkTableOfContents::getID( const AsciiString& name )		
{
	Mapping *m = findMapping( name );

	if (m)
		return m->id;

	DEBUG_CRASH(("name not found in DataChunkTableOfContents::getName for name %s\n",name.str()));
	return 0;
}

// create new ID for given name or return existing mapping
UnsignedInt DataChunkTableOfContents::allocateID(const AsciiString& name )
{
	Mapping *m = findMapping( name );

	if (m)
		return m->id;
	else
	{
		// allocate new id mapping
		m = newInstance(Mapping);

		m->id = m_nextID++;
		m->name =  name ;

		// prepend to list
		m->next = m_list;
		m_list = m;

		m_listLength++;

		return m->id;
	}
}

// DataChunkTableOfContents findMapping/getName/read/write and DataChunkInput's
// constructor/destructor are provided by DataChunkTableOfContents.cpp,
// DataChunkInputCtorThunk.cpp, and DataChunkInput.cpp. Their retail-verified
// BFME layouts supersede the reference definitions formerly emitted here.

// Parser registration is supplied by DataChunkInput.cpp. Retail returns the
// inserted UserParser and maintains both intrusive list links in its BFME node.

// Keep the retail placement-delete body that the removed parser construction
// previously emitted for exception cleanup.
void (*bfme_user_parser_placement_delete)(void *, UserParser::UserParserMagicEnum) =
	&UserParser::operator delete;

// parse the chunk stream using registered parsers
// it is assumed that the file position is at the start of a data chunk
// (it can be inside a parent chunk) when parse is called.
// ?parse@DataChunkInput@@QAE_NPAX@Z
// Body in DataChunk_parse.asm (exact 1006B retail).

// clear the stack
// ?clearChunkStack@DataChunkInput@@IAEXXZ present-unmatched
void DataChunkInput::clearChunkStack( void )
{
	InputChunk *c, *next;

	for( c=m_chunkStack; c; c=next )
	{
		next = c->next;
		c->deleteInstance();
	}

	m_chunkStack = NULL;
}

// Checks if the file has our initial tag word.
// ?isValidFileType@DataChunkInput@@QAE_NXZ present-unmatched
Bool DataChunkInput::isValidFileType(void)
{
	return m_contents.isOpenedForRead();
}

// Open-BFME5: byte-exact clean C++ reconstruction at retail RVA 0x001032A0.
AsciiString DataChunkInput::openDataChunk(DataChunkVersionType *ver )
{
	// allocate a new chunk and place it on top of the chunk stack
	InputChunk *c = newInstance(InputChunk);
	c->id = 0;
	c->version = 0;
	c->dataSize = 0;
	//DEBUG_LOG(("Opening data chunk at offset %d (%x)\n", m_file->tell(), m_file->tell()));
	// read the chunk ID
	m_file->read( (char *)&c->id, sizeof(UnsignedInt) );
	decrementDataLeft( sizeof(UnsignedInt) );

	// read the chunk version number
	m_file->read( (char *)&c->version, sizeof(DataChunkVersionType) );
	decrementDataLeft( sizeof(DataChunkVersionType) );

	// read the chunk data size
	m_file->read( (char *)&c->dataSize, sizeof(Int) );
	decrementDataLeft( sizeof(Int) );

	// all of the data remains to be read
	c->dataLeft = c->dataSize;
	c->chunkStart = m_file->tell();

	*ver = c->version;

	c->next = m_chunkStack;
	m_chunkStack = c;
	if (this->atEndOfFile()) {
		return (AsciiString(""));
	}
	return m_contents.getName( c->id );
}

// close chunk and move to start of next chunk
void DataChunkInput::closeDataChunk( void )
{										
	if (m_chunkStack == NULL)
	{
		// TODO: Throw exception
		return;
	}

	if (m_chunkStack->dataLeft > 0)
	{
		// skip past the remainder of this chunk
		m_file->absoluteSeek( m_file->tell()+m_chunkStack->dataLeft );
		decrementDataLeft( m_chunkStack->dataLeft );

	}

	// pop the chunk off the stack
	InputChunk *c = m_chunkStack;
	m_chunkStack = m_chunkStack->next;
	// Retail001029D0 invokes InputChunk's deleting destructor directly
	// (vtable0108631C slot0 ->001026F0), without the ZH pool-release path.
	delete c;
}


// return label of current data chunk
// ?getChunkLabel@DataChunkInput@@QAE?AVAsciiString@@XZ present-unmatched
AsciiString DataChunkInput::getChunkLabel( void )
{
	if (m_chunkStack == NULL)
	{
		// TODO: Throw exception
		DEBUG_CRASH(("Bad."));
		return AsciiString("");
	}

	return m_contents.getName( m_chunkStack->id );
}

// return version of current data chunk
DataChunkVersionType DataChunkInput::getChunkVersion( void )
{
	if (m_chunkStack == NULL)
	{
		// TODO: Throw exception
		DEBUG_CRASH(("Bad."));
		return NULL;
	}

	return m_chunkStack->version;
}		

// getChunkDataSize uses the retail inline provider in DataChunkInput.cpp.

// return size of data left to read in this chunk
UnsignedInt DataChunkInput::getChunkDataSizeLeft( void )
{
	if (m_chunkStack == NULL)
	{
		// TODO: Throw exception
		DEBUG_CRASH(("Bad."));
		return NULL;
	}

	return m_chunkStack->dataLeft;
}

Bool DataChunkInput::atEndOfChunk( void )
{
	if (m_chunkStack)
	{
		if (m_chunkStack->dataLeft <= 0)
			return true;
		return false;
	}

	return true; 
}

// update data left in chunk(s)
// since data read from a chunk is also read from all parent chunks,
// traverse the chunk stack and decrement the data left for each
inline void DataChunkInput::decrementDataLeft( Int size )
{
	InputChunk *c;

	c = m_chunkStack;
	while (c) {
		c->dataLeft -= size;
		c = c->next;
	}
	// The sizes of the parent chunks on the stack are adjusted in closeDataChunk.
}

Real DataChunkInput::readReal(void) 
{ 
	Real r;
	DEBUG_ASSERTCRASH(m_chunkStack->dataLeft>=sizeof(Real), ("Read past end of chunk."));
	m_file->read( (char *)&r, sizeof(Real) ); 
	decrementDataLeft( sizeof(Real) );
	return r; 
}

Int DataChunkInput::readInt(void) 
{ 
	Int i;
	DEBUG_ASSERTCRASH(m_chunkStack->dataLeft>=sizeof(Int), ("Read past end of chunk."));
	m_file->read( (char *)&i, sizeof(Int) ); 
	decrementDataLeft( sizeof(Int) );
	return i; 
}

Byte DataChunkInput::readByte(void) 
{ 
	Byte b;
	DEBUG_ASSERTCRASH(m_chunkStack->dataLeft>=sizeof(Byte), ("Read past end of chunk."));
	m_file->read( (char *)&b, sizeof(Byte) ); 
	decrementDataLeft( sizeof(Byte) );
	return b; 
}

// readArrayOfBytes and readNameKey use the verified providers in DataChunkInput.cpp.

// Full584B at0x001039C0 includes561B code plus3 alignment and5 DWORD
// switch targets at0x00103BF4 through0x00103C08 exclusive; CC follows.
Dict DataChunkInput::readDict() 
{ 
	bfmeDataChunkYieldToOS();
	UnsignedShort len;	
	DEBUG_ASSERTCRASH(m_chunkStack->dataLeft>=sizeof(UnsignedShort), ("Read past end of chunk."));
	m_file->read( &len, sizeof(UnsignedShort) );
	decrementDataLeft( sizeof(UnsignedShort) );
	DEBUG_ASSERTCRASH(m_chunkStack->dataLeft>=len, ("Read past end of chunk."));

	Dict d(len);

	for (int i = 0; i < len; i++)
	{
		Int keyAndType = readInt();
		Dict::DataType t = (Dict::DataType)(keyAndType & 0xff);
		keyAndType >>= 8;

		AsciiString kname = m_contents.getName(keyAndType);
		NameKeyType k = TheNameKeyGenerator->nameToKey(BFME_STR8(kname));

		switch(t)
		{
			case Dict::DICT_BOOL:
				d.setBool(k, readByte() ? true : false);
				break;
			case Dict::DICT_INT:
				d.setInt(k, readInt());
				break;
			case Dict::DICT_REAL:
				d.setReal(k, readReal());
				break;
			case Dict::DICT_ASCIISTRING:
				d.setAsciiString(k, readAsciiString());
				break;
			case Dict::DICT_UNICODESTRING:
				d.setUnicodeString(k, readUnicodeString());
				break;
			default:
				throw ERROR_CORRUPT_FILE_FORMAT;
				break;
		}
	}

	return d;
}

// readAsciiString uses the verified BFME provider in DataChunkInput.cpp.

UnicodeString DataChunkInput::readUnicodeString(void) 
{ 
	bfmeDataChunkYieldToOS();

	UnsignedShort len;	
	DEBUG_ASSERTCRASH(m_chunkStack->dataLeft>=sizeof(UnsignedShort), ("Read past end of chunk."));
	m_file->read( &len, sizeof(UnsignedShort) );
	decrementDataLeft( sizeof(UnsignedShort) );
	DEBUG_ASSERTCRASH(m_chunkStack->dataLeft>=len, ("Read past end of chunk."));
	UnicodeString theString;
	if (len>0) {
		WideChar *str = theString.getBufferForRead(len);
		m_file->read( (char*)str, len*sizeof(WideChar) );
		decrementDataLeft( len*sizeof(WideChar) );
		// add null delimiter to string.  Note that getBufferForRead allocates space for terminating null.
		str[len] = '\000';
	}

	return theString; 
}
