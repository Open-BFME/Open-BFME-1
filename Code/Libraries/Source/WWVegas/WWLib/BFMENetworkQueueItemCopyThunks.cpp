class BFMENetworkQueueItem1
{
public:
	void copyFromQueueNode(void *);
};

class BFMENetworkQueueItem
{
public:
	void copyFromQueueNode(void *);
};

class BFMENetworkQueueItem1copyFromQueueNodeShim
{
public:
	void copyFromQueueNode(void *node);
};

void BFMENetworkQueueItem1::copyFromQueueNode(void *node)
{
	((BFMENetworkQueueItem1copyFromQueueNodeShim *)this)->copyFromQueueNode(node);
}

class BFMENetworkQueueItemcopyFromQueueNodeShim
{
public:
	void copyFromQueueNode(void *node);
};

void BFMENetworkQueueItem::copyFromQueueNode(void *node)
{
	((BFMENetworkQueueItemcopyFromQueueNodeShim *)this)->copyFromQueueNode(node);
}

