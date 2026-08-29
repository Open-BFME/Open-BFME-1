class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Player *getControllingPlayer() const;
};

struct Rva2225E0Node
{
	Rva2225E0Node *next;
	void *previous;
	Object *value;
};

struct Rva2225E0Filter
{
	bool accepts(Object *value, Player *player);
};

struct Rva2225E0FilteredCountThunk
{
	int count(Rva2225E0Filter *filter);

	unsigned char unused00[0x18];
	Rva2225E0Node *sentinel;
	int cachedCount;
};

// ?count@Rva2225E0FilteredCountThunk@@ absent-from-retail
int Rva2225E0FilteredCountThunk::count(Rva2225E0Filter *filter)
{
	if (filter == 0) {
		return cachedCount;
	}

	int result = 0;
	for (Rva2225E0Node *node = sentinel->next; node != sentinel; node = node->next) {
		Object *contextObject = *(Object **)((unsigned char *)this - 0x18);
		if (filter->accepts(node->value, contextObject->getControllingPlayer())) {
			++result;
		}
	}
	return result;
}
