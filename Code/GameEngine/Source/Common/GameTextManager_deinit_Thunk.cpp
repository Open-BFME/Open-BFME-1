// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?deinit@GameTextManager@@UAEXXZ: Code/GameEngine/Source/GameClient/GameText.cpp
// Lift the GameTextManager::deinit naked dump to clean C++.
//
// Zero Hour's GameText.cpp body; the DEBUG_LOGs around the missing-string walk
// compile out and leave the loop.
//
// The two array deletes are not the same shape and that is the layout evidence.
// m_stringInfo goes through the vector destructor iterator -- retail reads the
// element count from the word ahead of the array, pushes a per-element
// destructor and an element size of 8, then frees the block -- so its element
// type has a destructor and is eight bytes, where ZH's BfmeTextEntry is twelve.
// m_stringLUT is freed with a bare operator delete[], so its elements are
// trivially destructible.
//
// Retail pins the layout: the text count is at this+0x08, the two arrays at
// +0x780C and +0x7810, the initialised flag at +0x7814 and the missing-string
// list head at +0x7818, with each node's next pointer at its own +0x00.

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
	void *m_data;
};

// Eight bytes with a destructor, which is what the vector destructor iterator
// call proves; the member names follow ZH for the two that fit.
// NOTE: this stand-in is deliberately NOT called BfmeTextEntry. GameText.cpp has a
// BfmeTextEntry of its own with three members, and retail proves the two are
// different classes: this one's destructor is at 0x0041510E (the address the
// deinit body's vector-destructor-iterator argument encodes) while
// GameText.cpp's ??_EBfmeTextEntry calls 0x004259EB. Sharing the name made one
// symbol resolve to two addresses and failed the gate's DIR32 consistency
// check for every full gate in the tree.
class BfmeTextEntry
{
public:
	~BfmeTextEntry();

	AsciiString label;
	UnicodeString text;
};

class NoString
{
public:
	~NoString();

	NoString *next;										///< retail this+0x00
	UnicodeString text;
};

class GameTextManager
{
public:
	virtual void deinit(void);

private:
	unsigned char m_unreconstructed_04[8 - 4];
	Int m_textCount;									///< retail this+0x08
	unsigned char m_unreconstructed_0C[0x780C - 0x0C];
	BfmeTextEntry *m_stringInfo;							///< retail this+0x780C
	BfmeTextEntry **m_stringLUT;							///< retail this+0x7810
	Bool m_initialized;									///< retail this+0x7814
	unsigned char m_unreconstructed_7815[3];
	NoString *m_noStringList;							///< retail this+0x7818
};

// ?deinit@GameTextManager@@UAEXXZ
void GameTextManager::deinit( void )
{

	if( m_stringInfo != 0 )
	{
		delete [] m_stringInfo;
		m_stringInfo = 0;
	}

	if( m_stringLUT != 0 )
	{
		delete [] m_stringLUT;
		m_stringLUT = 0;
	}

	m_textCount = 0;

	NoString *noString = m_noStringList;

	while ( noString )
	{
		NoString *next = noString->next;
		delete noString;
		noString = next;
	}

	m_noStringList = 0;

	m_initialized = false;
}
