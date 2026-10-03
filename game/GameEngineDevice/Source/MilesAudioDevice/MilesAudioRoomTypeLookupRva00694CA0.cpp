// cl: /O2 /GR- /EHsc-
// Retail 0x00694CA0: map a Miles 3D room-type value to its display name.
struct Rva006A16B0Entry
{
	const char *m_name;
	int m_roomType;
};

// Retail VA 0x0111BAC8: 26 eight-byte records, ending at 0x0111BB98.
// RVA 0x00694CA0 reads a dword at +4 and a string pointer at +0, with
// stride 8 and count 26. Initializers reproduce retail, including "Hanger".
// No EA table name is proven; keep this datum's address in its name.
Rva006A16B0Entry g_rva0111BAC8[26] = {
	{ "None", 0 },
	{ "Padded Cell", 1 },
	{ "Room", 2 },
	{ "Bathroom", 3 },
	{ "Living Room", 4 },
	{ "Stone Room", 5 },
	{ "Auditorium", 6 },
	{ "Concert Hall", 7 },
	{ "Cave", 8 },
	{ "Arena", 9 },
	{ "Hanger", 10 },
	{ "Carpeted Hallway", 11 },
	{ "Hallway", 12 },
	{ "Stone Corridor", 13 },
	{ "Alley", 14 },
	{ "Forest", 15 },
	{ "City", 16 },
	{ "Mountains", 17 },
	{ "Quarry", 18 },
	{ "Plain", 19 },
	{ "Parking Lot", 20 },
	{ "Sewer Pipe", 21 },
	{ "Underwater", 22 },
	{ "Drugged", 23 },
	{ "Dizzy", 24 },
	{ "Psychotic", 25 }
};

const char *__fastcall rva00694CA0RoomTypeName(int roomType)
{
	for (unsigned int i = 0; i < 26; ++i)
		if (roomType == g_rva0111BAC8[i].m_roomType)
			return g_rva0111BAC8[i].m_name;
	return "<Unknown>";
}
