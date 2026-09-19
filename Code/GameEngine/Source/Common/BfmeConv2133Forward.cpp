class Shadow
{
public:
	void setSize(float width, float height);
};

class Gen_001D5EE0Target
{
public:
	void bfmeForward(void *width, void *height);
};

void Gen_001D5EE0Target::bfmeForward(void *width, void *height)
{
	((Shadow *)this)->setSize(*(float *)&width, *(float *)&height);
}
