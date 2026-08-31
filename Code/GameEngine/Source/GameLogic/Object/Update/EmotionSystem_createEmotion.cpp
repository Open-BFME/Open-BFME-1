// cl: /DNDEBUG /MD /EHsc

class Object;
class EmotionTrackerUpdateEntry;

class Emotion
{
public:
	Emotion(Object *object, EmotionTrackerUpdateEntry *entry);

private:
	unsigned char m_unknown00[0x34];
};

class EmotionSystem
{
public:
	Emotion *createEmotion(EmotionTrackerUpdateEntry *entry, Object *object);
};

// ?createEmotion@EmotionSystem@@QAEPAVEmotion@@PAVEmotionTrackerUpdateEntry@@PAVObject@@@Z
Emotion *EmotionSystem::createEmotion(EmotionTrackerUpdateEntry *entry, Object *object)
{
	if (entry == 0 || object == 0)
		return 0;

	return new Emotion(object, entry);
}
