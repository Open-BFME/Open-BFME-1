// cl: /DNDEBUG /MD /EHsc

class QueuedDownload
{
public:
	~QueuedDownload();
};

void d_004f39b0(QueuedDownload *response)
{
	response->~QueuedDownload();
}
