// cl: /DNDEBUG /MD /EHs-c- /O1
// Size-optimised destructor for the related inline-buffer conversion holder.

#include <stdlib.h>

class Rva0005D7B0Holder
{
public:
	~Rva0005D7B0Holder(void);

private:
	char *m_text;
	char m_buffer[1];
};

// ??1Rva0005D7B0Holder@@QAE@XZ
Rva0005D7B0Holder::~Rva0005D7B0Holder(void)
{
	if (m_text != m_buffer) {
		free(m_text);
	}
}
