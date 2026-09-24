// ?setDesiredSpeed@AIUpdateInterface@@QAEXM@Z
// BFME AIUpdateInterface::setDesiredSpeed, RVA 0x0026EDC0, 10 bytes: stores m_desiredSpeed at +0x44.
// Evidence: reverse/identity_evidence/0016aeb0.md.

class AIUpdateInterface
{
public:
	void setDesiredSpeed(float speed);
	char m_lead[0x44];
	float m_desiredSpeed;
};

void AIUpdateInterface::setDesiredSpeed(float speed)
{
	m_desiredSpeed = speed;
}
