// ?addGroupRooms@Rva000E5930Owner@@QAEXPAURva000E5930Vec@@@Z
// cl: /DNDEBUG /MD /EHsc
class GameSpyGroupRoom {
public:
	GameSpyGroupRoom(const GameSpyGroupRoom& other);
	~GameSpyGroupRoom();
	void* m_data;
};
struct Rva000E5930Room : GameSpyGroupRoom { Rva000E5930Room(const GameSpyGroupRoom& other) : GameSpyGroupRoom(other) {} };
struct Rva000E5930Vec { GameSpyGroupRoom* m_begin; GameSpyGroupRoom* m_end; unsigned int size() const { return m_end - m_begin; } };
struct Rva000E5930Owner {
	void addRoom(Rva000E5930Room room, bool notFirst);
	void addGroupRooms(Rva000E5930Vec* rooms);
};
void Rva000E5930Owner::addGroupRooms(Rva000E5930Vec* rooms)
{
	bool notFirst = false;
	for (unsigned int i = 0; i < rooms->size(); ++i) {
		addRoom(rooms->m_begin[i], notFirst);
		notFirst = true;
	}
}
