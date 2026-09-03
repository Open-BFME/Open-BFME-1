// Open-BFME5 conversion for the validated handle setter at 0x0073B5F0.

enum FilterTypes {};
enum FilterModes {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShaderManager.h
class W3DShaderManager
{
public:
	static bool filterSetup(FilterTypes type, FilterModes mode);
};

class BfmeValidatedHandle
{
public:
	bool setValue(void *value);

private:
	char m_pad0[0x10c];
	void *volatile m_value;
	void *m_reference;
};

bool BfmeValidatedHandle::setValue(void *value)
{
	void *oldValue = m_value;
	m_value = value;

	if (value != 0 && m_reference != 0 &&
		!W3DShaderManager::filterSetup(
			static_cast<FilterTypes>(reinterpret_cast<unsigned int>(m_reference)),
			static_cast<FilterModes>(reinterpret_cast<unsigned int>(value))))
	{
		m_value = oldValue;
		return false;
	}

	return true;
}
