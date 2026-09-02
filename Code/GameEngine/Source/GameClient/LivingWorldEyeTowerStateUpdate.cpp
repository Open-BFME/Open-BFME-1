// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class Gen0060CBB0
{
public:
	void updateState();

private:
	void beginState();
	void processFrame();

	char m_head[0x48];
	unsigned int m_state;
	char m_gap[0x20];
	float m_rate;
	float m_progress;
};

void Gen0060CBB0::updateState()
{
	switch (m_state) {
		case 0:
			beginState();
			break;

		case 1:
			m_progress += m_rate;
			if (m_progress >= 1.0f)
				m_state = 0;
			break;
	}

	processFrame();
}
