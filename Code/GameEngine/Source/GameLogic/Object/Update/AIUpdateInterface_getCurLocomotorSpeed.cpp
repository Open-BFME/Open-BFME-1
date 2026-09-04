// cl: /DNDEBUG /MD /EHsc

class Object;

extern "C" const float g_zeroLocomotorSpeed;

class AIUpdateInterface
{
public:
	float getFormationMovementSpeed(Object *object);
	float getCurLocomotorSpeed();

private:
	char m_fields[8];
	Object *m_object;
	char m_fieldsAfterObject[0x1cc - 0x0c];
	AIUpdateInterface *m_locomotorController;
};

float AIUpdateInterface::getCurLocomotorSpeed()
{
	if (m_locomotorController != 0)
		return m_locomotorController->getFormationMovementSpeed(m_object);

	return g_zeroLocomotorSpeed;
}
