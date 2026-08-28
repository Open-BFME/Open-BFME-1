// cl: /DNDEBUG /MD /EHsc
// readable body of ?addDrawableToLookupTable@GameClient@@: Code/GameEngine/Source/GameClient/GameClient.cpp
// readable body of ?removeDrawableFromLookupTable@GameClient@@: Code/GameEngine/Source/GameClient/GameClient.cpp

// Open-BFME5: the two drawable lookup-table wrappers, retail 0x00431C20 (43
// bytes) and 0x00430B50 (37 bytes). Both carried only machine byte-dump rows;
// reverse/reloc_names.csv holds their names with identity=real.
//
// Each takes the drawable's id and uses it as the key into the table at
// this+0x14. Add asks for the slot and stores the drawable into it; remove
// erases by key. Both take the key's address, so the map's interface is by
// const reference, and both leave the null drawable alone.

class Drawable;

typedef unsigned int DrawableID;

class BfmeDrawableLookupTable
{
public:
	Drawable **bfmeSlot(const DrawableID &id);		// ILT 0x00034A95
	void bfmeErase(const DrawableID &id);			// ILT 0x00043F31
};

class BfmeDrawableWithID
{
public:
	DrawableID bfmeGetID(void);				// ILT 0x00009B01
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
{
public:
	void addDrawableToLookupTable(Drawable *drawable);
	void removeDrawableFromLookupTable(Drawable *drawable);

private:
	char m_bfmeHead[0x14];
	BfmeDrawableLookupTable m_bfmeLookup;			// +0x14
};

// ?addDrawableToLookupTable@GameClient@@QAEXPAVDrawable@@@Z
void GameClient::addDrawableToLookupTable(Drawable *drawable)
{
	if (drawable != 0)
	{
		DrawableID id = ((BfmeDrawableWithID *)drawable)->bfmeGetID();
		*m_bfmeLookup.bfmeSlot(id) = drawable;
	}
}

// ?removeDrawableFromLookupTable@GameClient@@QAEXPAVDrawable@@@Z
void GameClient::removeDrawableFromLookupTable(Drawable *drawable)
{
	if (drawable != 0)
	{
		DrawableID id = ((BfmeDrawableWithID *)drawable)->bfmeGetID();
		m_bfmeLookup.bfmeErase(id);
	}
}
