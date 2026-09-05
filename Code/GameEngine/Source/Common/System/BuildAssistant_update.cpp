// BFME's BuildAssistant update hook is intentionally empty. GameLogic calls
// this virtual during phase 5 through vtable 0x010EA8D4 slot +0x14.

class BuildAssistant
{
public:
	virtual void update();
};

void BuildAssistant::update()
{
}
