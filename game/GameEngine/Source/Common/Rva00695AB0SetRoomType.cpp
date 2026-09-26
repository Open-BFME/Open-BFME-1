// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Set Miles 3D/digital room type; LOD may force room off; update +0x633/+0x634.

extern "C" __declspec(dllimport) void __stdcall _AIL_set_3D_room_type(int handle, int room);
extern "C" __declspec(dllimport) void __stdcall _AIL_set_digital_master_room_type(
	void *dig, int room);

class GameLODManager
{
public:
	char m_pad0[0x175];
	// bytes at 0x175, 0x17d, 0x185 via eax*8
	char m_bytes[0x16cc - 0x175];
	int m_level; // +0x16cc
};

extern GameLODManager *TheGameLODManager;

class Rva00695AB0Owner
{
public:
	void setRoomType(int room);

	char m_bytes[0x964];
};

void Rva00695AB0Owner::setRoomType(int room)
{
	int value = room;
	if (value)
	{
		if (*(int *)(m_bytes + 0x604))
			value = 0;
		else
		{
			GameLODManager *lod = TheGameLODManager;
			if (lod)
			{
				int level = lod->m_level;
				if (level >= 0 && level <= 2)
				{
					if (!*((unsigned char *)lod + level * 8 + 0x175))
						value = 0;
				}
			}
		}
	}

	int index = *(int *)(m_bytes + 0x958);
	if (index != -1)
	{
		int scaled = index + index * 2;
		_AIL_set_3D_room_type(*(int *)(m_bytes + 0x658 + scaled * 4), value);
		_AIL_set_digital_master_room_type(*(void **)(m_bytes + 0x960), value);
	}

	unsigned char flag = m_bytes[0x633];
	if (!value)
	{
		if (flag)
		{
			m_bytes[0x633] = 0;
			m_bytes[0x634] = 1;
		}
	}
	else if (!flag)
	{
		m_bytes[0x633] = 1;
		m_bytes[0x634] = 1;
	}
}
