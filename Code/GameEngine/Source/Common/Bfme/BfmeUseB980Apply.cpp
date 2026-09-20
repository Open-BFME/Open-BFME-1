// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

class Player;

class ThingTemplate
{
public:
	int calcTimeToBuild(const Player *player, int buildTime) const;
};

class BfmeUseB980
{
public:
	void *bfmeApply980B(int first, int second);
};

void *BfmeUseB980::bfmeApply980B(int first, int second)
{
	return (void *)((ThingTemplate *)this)->calcTimeToBuild(
		(const Player *)first, second);
}
