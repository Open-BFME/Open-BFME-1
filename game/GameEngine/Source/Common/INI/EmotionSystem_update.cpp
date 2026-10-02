// EmotionSystem::update, retail 0x0037CAC0: a bare ret.
//
// Slot 5 (+0x14, SubsystemInterface::update) of the table 0x010EA8D4, which the
// EmotionSystem constructor 0x0037CC20 installs; GameEngine::init passes that
// object to initSubsystem<EmotionSystem> with "TheEmotionSystem".
// Evidence: targets/game/reverse/identity_evidence/000febe0-buildassistant-update.md.

class EmotionSystem
{
public:
	virtual void update();
};

// ?update@EmotionSystem@@UAEXXZ
void EmotionSystem::update()
{
}
