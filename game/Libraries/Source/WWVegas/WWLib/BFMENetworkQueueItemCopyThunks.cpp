class BFMENetworkQueueItem1
{
public:
	BFMENetworkQueueItem1 &operator=(const BFMENetworkQueueItem1 &other);
	void copyFromQueueNode(void *);
};

class BFMENetworkQueueItem
{
public:
	BFMENetworkQueueItem &operator=(const BFMENetworkQueueItem &other);
	void copyFromQueueNode(void *);
};

void BFMENetworkQueueItem1::copyFromQueueNode(void *node)
{
	*this = *static_cast<const BFMENetworkQueueItem1 *>(node);
}

void BFMENetworkQueueItem::copyFromQueueNode(void *node)
{
	*this = *static_cast<const BFMENetworkQueueItem *>(node);
}
