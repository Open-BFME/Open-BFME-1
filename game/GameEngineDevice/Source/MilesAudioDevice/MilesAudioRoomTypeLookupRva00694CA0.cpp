// cl: /O2 /GR- /EHsc-
// Retail 0x00694CA0: map a Miles 3D room-type value to its display name.
struct Rva006A16B0Entry
{
	const char *m_name;
	int m_roomType;
};
extern Rva006A16B0Entry Rva006A16B0Table[];

const char *__fastcall rva00694CA0RoomTypeName(int roomType)
{
	for (unsigned int i = 0; i < 26; ++i)
		if (roomType == Rva006A16B0Table[i].m_roomType)
			return Rva006A16B0Table[i].m_name;
	return "<Unknown>";
}
