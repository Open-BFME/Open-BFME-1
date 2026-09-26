struct BfmeWindowNode
{
	char m_bfmeFields[0x70];
	int m_bfmeFocus;
};

struct BfmeWindowResult
{
	char m_bfmeFields[0x20];
	int m_bfmeValue;
};

class BfmeWindowManager
{
public:
	void bfmeClear(int *focus);
	void bfmeSet(int *focus);
};

extern BfmeWindowManager *g_bfmeWindowManager;

class Gen_0028B810
{
public:
	int bfmeUpdate(void);

private:
	char m_bfmeFields[0x14];
	unsigned char m_bfmeActive;
	unsigned char m_bfmePending;
};

// ?bfmeUpdate@Gen_0028B810@@QAEHXZ
int Gen_0028B810::bfmeUpdate(void)
{
	if (m_bfmeActive) {
		if (g_bfmeWindowManager != 0) {
			BfmeWindowNode *node = *reinterpret_cast<BfmeWindowNode **>(
				reinterpret_cast<char *>(this) - 8);
			int *focus = node != 0 ? &node->m_bfmeFocus : 0;
			g_bfmeWindowManager->bfmeClear(focus);
		}

		m_bfmeActive = 0;
		m_bfmePending = 0;
		BfmeWindowResult *result = *reinterpret_cast<BfmeWindowResult **>(
			reinterpret_cast<char *>(this) - 12);
		return result->m_bfmeValue;
	}

	if (!m_bfmePending && g_bfmeWindowManager != 0) {
		BfmeWindowNode *node = *reinterpret_cast<BfmeWindowNode **>(
			reinterpret_cast<char *>(this) - 8);
		int *focus = node != 0 ? &node->m_bfmeFocus : 0;
		g_bfmeWindowManager->bfmeSet(focus);
	}

	return 1;
}
