class GameSpyStagingRoom;

class GameSortStructCallOperatorShim
{
public:
	bool compare( GameSpyStagingRoom *left, GameSpyStagingRoom *right );
};

class GameSortStruct
{
public:
	bool operator()( GameSpyStagingRoom *left, GameSpyStagingRoom *right ) const;
};

bool GameSortStruct::operator()( GameSpyStagingRoom *left, GameSpyStagingRoom *right ) const
{
	return ((GameSortStructCallOperatorShim *)this)->compare( left, right );
}
