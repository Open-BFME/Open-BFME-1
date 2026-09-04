// cl: /DNDEBUG /MD /EHsc

class Player
{
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Gen_0021AAD0
{
public:
	Player *bfmeGet();
};

// ?bfmeGet@Gen_0021AAD0@@QAEPAVPlayer@@XZ
Player *Gen_0021AAD0::bfmeGet()
{
	volatile unsigned int *head = (volatile unsigned int *)((char *)this + 0x99c);
	unsigned int p = *head;
	if (*(volatile unsigned int *)p == p)
		return 0;

	unsigned int first = *(volatile unsigned int *)*head;
	Object *obj = *(Object **)((char *)first + 8);
	return obj->getControllingPlayer();
}
