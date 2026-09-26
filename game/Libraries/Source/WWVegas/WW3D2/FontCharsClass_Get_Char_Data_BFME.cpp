struct FontCharsClassCharDataStruct;

struct FontCharDataMapNode
{
	char fields[0x14];
	const FontCharsClassCharDataStruct *value;
};

class FontCharDataMap
{
public:
	FontCharDataMapNode *find(unsigned short *character);
	FontCharDataMapNode *m_end;
};

class FontCharsClass
{
public:
	const FontCharsClassCharDataStruct *Get_Char_Data(unsigned short character);
	const FontCharsClassCharDataStruct *loadCharacterData(unsigned short character);

private:
	char m_fields00[8];
	FontCharsClass *m_alternateUnicodeFont;
	char m_fields0C[0x444];
	FontCharDataMap m_characterData;
};

const FontCharsClassCharDataStruct *FontCharsClass::Get_Char_Data(
	unsigned short character)
{
	unsigned short originalCharacter = character;
	FontCharsClass *font = this;
	for (;;)
	{
		FontCharDataMap *map = &font->m_characterData;
		const FontCharsClassCharDataStruct *data;
		FontCharDataMapNode *node = map->find(&character);
		if (node == map->m_end || (data = node->value) == 0)
			data = font->loadCharacterData(originalCharacter);
		if (data != reinterpret_cast<const FontCharsClassCharDataStruct *>(-1))
			return data;
		FontCharsClass *alternate = font->m_alternateUnicodeFont;
		if (alternate == 0 || font == alternate)
			return 0;
		font = alternate;
	}
}
