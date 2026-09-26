// ?getGroup@AIUpdateInterface@@QAEPAVAIGroup@@XZ
// BFME AIUpdateInterface::getGroup, RVA 0x0026FB30, 8 bytes: getObject()->getGroup() as a tail call.
// Evidence: targets/game/reverse/identity_evidence/001bfbe0.md.

class AIGroup;

class Object
{
public:
	AIGroup *getGroup();
};

class AIUpdateInterface
{
public:
	AIGroup *getGroup();
	Object *getObject() const { return m_object; }
	char m_prefix[8];
	Object *m_object;
};

AIGroup *AIUpdateInterface::getGroup()
{
	return getObject()->getGroup();
}
