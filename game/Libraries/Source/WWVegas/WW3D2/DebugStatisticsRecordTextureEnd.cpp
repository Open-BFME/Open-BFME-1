// ?Record_Texture_End@@YAXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// BFME Debug_Statistics::Record_Texture_End at RVA 0x00937900.
// The Debug_Statistics::End_Statistics caller and the targets/game/reverse/symbols.csv pin
// establish this body's identity. The handle, StringClass, and virtual texture
// calls follow the retail operands and the adjacent WW3D2 texture sources.

#include "wwstring.h"

class TextureClass
{
public:
	void Add_Ref()
	{
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>( this ) + 4);
	}
	void Release_Ref();
};

class TextureStateView
{
public:
	virtual void Slot_00() = 0;
	virtual void Slot_04() = 0;
	virtual void Slot_08() = 0;
	virtual void Slot_0C() = 0;
	virtual void Slot_10() = 0;
	virtual void Slot_14() = 0;
	virtual void Slot_18() = 0;
	virtual void Slot_1C() = 0;
	virtual void Slot_20() = 0;
	virtual void Slot_24() = 0;
	virtual bool Is_Initialized() = 0;
};

class BfmeHandleCX
{
public:
	TextureClass *m_referent;
	StringClass Get_Texture_Name() const;
};

template <typename T> class RefCountPtr
{
public:
	RefCountPtr() : m_referent( 0 ) {}
	RefCountPtr( const RefCountPtr<T> &other ) : m_referent( other.m_referent )
	{
		if ( m_referent != 0 )
			m_referent->Add_Ref();
	}
	~RefCountPtr()
	{
		if ( m_referent != 0 )
			m_referent->Release_Ref();
	}
	T *Peek() const { return m_referent; }
	bool operator==( const RefCountPtr<T> &other ) const { return m_referent == other.m_referent; }
	bool operator!=( const RefCountPtr<T> &other ) const { return m_referent != other.m_referent; }
	unsigned Get_Texture_Memory_Usage() const;

protected:
	T *m_referent;
};

class BfmeTextureHandle : public RefCountPtr<TextureClass>
{
};

template <typename T> class VectorClass
{
public:
	virtual ~VectorClass();
	int Length() const { return m_vectorMax; }
	T &operator[]( int index ) { return m_vector[ index ]; }

protected:
	T *m_vector;
	int m_vectorMax;
	bool m_isValid;
	bool m_isAllocated;
	bool m_padding[ 2 ];
};

template <typename T> class DynamicVectorClass : public VectorClass<T>
{
};

struct TextureStatisticsStruct
{
	BfmeTextureHandle texture;
	int usageCount;
	int changeCount;
};

class Debug_Statistics
{
public:
	enum RecordTextureMode
	{
		RECORD_TEXTURE_NONE,
		RECORD_TEXTURE_SIMPLE,
		RECORD_TEXTURE_DETAILS
	};
};

__declspec(dllimport) int __cdecl bfmeFmt1064(
	char *buffer, unsigned size, char *format, int first, int second );
extern char g_bfmeName1053[];

static int textureMemory;
static int textureCount;
static int lightmapTextureMemory;
static int lightmapTextureCount;
static int proceduralTextureMemory;
static int proceduralTextureCount;
static int recordCount;
static int textureChangeCount;
static int lastFrameTextureMemory;
static int lastFrameTextureCount;
static int lastFrameLightmapTextureMemory;
static int lastFrameLightmapTextureCount;
static int lastFrameProceduralTextureMemory;
static int lastFrameProceduralTextureCount;
static int lastFrameRecordCount;
static int lastFrameTextureChangeCount;
static RefCountPtr<TextureClass> latestTexture;
static Debug_Statistics::RecordTextureMode recordTextureMode;
static StringClass textureStatisticsString;
static DynamicVectorClass<TextureStatisticsStruct> textureStatistics;

void Record_Texture_End()
{
	lastFrameTextureMemory = textureMemory;
	lastFrameTextureCount = textureCount;
	lastFrameLightmapTextureMemory = lightmapTextureMemory;
	lastFrameLightmapTextureCount = lightmapTextureCount;
	lastFrameProceduralTextureMemory = proceduralTextureMemory;
	lastFrameProceduralTextureCount = proceduralTextureCount;
	lastFrameRecordCount = recordCount;
	lastFrameTextureChangeCount = textureChangeCount;

	textureStatisticsString = "";
	if ( recordTextureMode == Debug_Statistics::RECORD_TEXTURE_DETAILS )
	{
		char temporary[ 1024 ];
		bfmeFmt1064( temporary, 0x400, (char *)0x0113cac0,
			lastFrameRecordCount, lastFrameTextureChangeCount );
		textureStatisticsString += temporary;
		for ( int index = 0; index < textureCount; ++index )
		{
			StringClass workingString;
			BfmeTextureHandle texture = textureStatistics[ index ].texture;
			int id = 0;
			StringClass flash = "  ";
			workingString.Format(
				"%4.4d  %3.3d   %3.3d     %s ", id,
				textureStatistics[ index ].usageCount,
				textureStatistics[ index ].changeCount, flash.Peek_Buffer() );
			textureStatisticsString += workingString;

			StringClass error = "";
			if ( texture.Peek() != 0 )
			{
				unsigned bytes = texture.Get_Texture_Memory_Usage();
				if ( texture.Peek() == 0 )
					goto texture_status_missing;
				bool initialized;
				initialized = reinterpret_cast<TextureStateView *>( texture.Peek() )->Is_Initialized();
				if ( initialized == false )
					goto texture_status_missing;
				textureStatisticsString += "  ";
				goto texture_status_done;
				texture_status_missing:
					textureStatisticsString += g_bfmeName1053;
				texture_status_done: ;
				workingString.Format( "%4.4dkb         ", bytes / 1024 );
				textureStatisticsString += workingString;
			}
			else
			{
				textureStatisticsString += "N/A  ";
			}
			textureStatisticsString += reinterpret_cast<const BfmeHandleCX &>( texture ).Get_Texture_Name();
			textureStatisticsString += error;
			textureStatisticsString += "\n";
		}
		textureStatisticsString += "\nid              = id of texture. Use with command 'flash_texture [id]'\n";
		textureStatisticsString += "refs          = # of times texture is used when rendering\n";
		textureStatisticsString += "changes    = # of times texture change needed - BAD IF HIGH!\n";
		textureStatisticsString += "red         = texture reduction factor\n";
		textureStatisticsString += "size          = amount of memory needed for texture\n";
		textureStatisticsString += "(w/o red)     = size of reduction not used\n";
		textureStatisticsString += "percent    = savings of reduction system, in percents\n";
		textureStatisticsString += "\n* = thumbnail used\n";
		textureStatisticsString += "\n";
	}
}
