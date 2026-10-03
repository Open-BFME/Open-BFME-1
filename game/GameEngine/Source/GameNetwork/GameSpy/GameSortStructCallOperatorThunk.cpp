class GameSpyStagingRoom;

void d_0053edd0();

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
	union {
		void (*asFunction)(void);
		bool (GameSortStructCallOperatorShim::*asMember)(GameSpyStagingRoom *, GameSpyStagingRoom *);
	} target;
	target.asFunction = d_0053edd0;
	return (((GameSortStructCallOperatorShim *)this)->*target.asMember)(left, right);
}
