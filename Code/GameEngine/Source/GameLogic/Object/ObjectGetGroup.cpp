// ?getGroup@Object@@QAEPAVAIGroup@@XZ
// BFME Object::getGroup, RVA 0x001BFBE0, 7 bytes: returns m_group at +0x188.
// Evidence: reverse/identity_evidence/001bfbe0.md.

class AIGroup;

class Object
{
public:
	AIGroup *getGroup();
	char m_lead[0x188];
	AIGroup *m_group;
};

AIGroup *Object::getGroup()
{
	return m_group;
}
