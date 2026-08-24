// ?readChatMessage@NetPacket@@KAPAVNetCommandMsg@@PAEAAH@Z
// partial score=0.19 date=2026-08-24
NetCommandMsg *NetPacket::readChatMessage(UnsignedByte *data, Int &i)
{
	NetChatCommandMsg *msg = new NetChatCommandMsg;

	UnsignedShort text[256];
	UnsignedByte length;
	Int playerMask;
	memcpy(&length, data + i, sizeof(UnsignedByte));
	++i;
	memcpy(text, data + i, length * sizeof(UnsignedShort));
	i += length * sizeof(UnsignedShort);
	text[length] = 0;
	memcpy(&playerMask, data + i, sizeof(Int));
	i += sizeof(Int);

	UnicodeString unitext;
	unitext.set(text);

	msg->setText(unitext);
	msg->setPlayerMask(playerMask);
	return msg;
}
