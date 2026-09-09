// ?BuddyControlSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// partial score=0.62 date=2026-09-09
WindowMsgHandledType BuddyControlSystem( GameWindow *window, UnsignedInt msg,
                                         WindowMsgData mData1, WindowMsgData mData2)
{
	if(!TheGameSpyInfo || TheGameSpyInfo->getLocalProfileID() == 0 || !buddyControls.isInit)
	{
		return MSG_IGNORED;
	}

	switch( msg )
	{
		case GLM_RIGHT_CLICKED:
		{
			GameWindow *control = (GameWindow *)mData1;
			Int controlID = control->winGetWindowId();

			if( controlID == buddyControls.listboxBuddiesID )
			{
				RightClickStruct *rc = (RightClickStruct *)mData2;
				WindowLayout *rcLayout;
				if(rc->pos < 0)
					break;

				GPProfile profileID = (GPProfile)GadgetListBoxGetItemData(control, rc->pos, 0);
				RCItemType itemType = (RCItemType)(Int)GadgetListBoxGetItemData(control, rc->pos, 1);
				UnicodeString nick = GadgetListBoxGetText(control, rc->pos);

				GadgetListBoxSetSelected(control, rc->pos);
				if (itemType == ITEM_BUDDY)
					rcLayout = TheWindowManager->winCreateLayout(AsciiString("Menus/RCBuddiesMenu.wnd"));
				else if (itemType == ITEM_REQUEST)
					rcLayout = TheWindowManager->winCreateLayout(AsciiString("Menus/RCBuddyRequestMenu.wnd"));
				else
					rcLayout = TheWindowManager->winCreateLayout(AsciiString("Menus/RCNonBuddiesMenu.wnd"));
				rcMenu = rcLayout->getFirstWindow();
				rcMenu->winGetLayout()->runInit();
				rcMenu->winBringToTop();
				rcMenu->winHide(FALSE);

				ICoord2D rcSize, rcPos;
				rcMenu->winGetSize(&rcSize.x, &rcSize.y);
				rcPos.x = rc->mouseX;
				rcPos.y = rc->mouseY;
				if(rc->mouseX + rcSize.x > TheDisplay->getWidth())
					rcPos.x = TheDisplay->getWidth() - rcSize.x;
				if(rc->mouseY + rcSize.y > TheDisplay->getHeight())
					rcPos.y = TheDisplay->getHeight() - rcSize.y;
				rcMenu->winSetPosition(rcPos.x, rcPos.y);

				GameSpyRCMenuData *rcData = NEW GameSpyRCMenuData;
				rcData->m_id = profileID;
				rcData->m_nick.translate(nick);
				rcData->m_itemType = itemType;
				setUnignoreText(rcLayout, rcData->m_nick, rcData->m_id);
				rcMenu->winSetUserData((void *)rcData);
				TheWindowManager->winSetLoneWindow(rcMenu);
			}
			else
				return MSG_IGNORED;
			break;
		}
		case GEM_EDIT_DONE:
		{
			GameWindow *control = (GameWindow *)mData1;
			Int controlID = control->winGetWindowId();
			if(controlID != buddyControls.textEntryEditID)
				return MSG_IGNORED;

			Int selected = -1;
			GadgetListBoxGetSelected(buddyControls.listboxBuddies, &selected);
			if (selected >= 0)
			{
				GPProfile selectedProfile = (GPProfile)GadgetListBoxGetItemData(buddyControls.listboxBuddies, selected);
				BuddyInfoMap *m = TheGameSpyInfo->getBuddyMap();
				BuddyInfoMap::iterator recipIt = m->find(selectedProfile);
				if (recipIt == m->end())
					break;

				if (TheGameSpyGame && TheGameSpyGame->isInGame() && TheGameSpyGame->isGameInProgress() &&
					!ThePlayerList->getLocalPlayer()->isPlayerActive())
				{
					for (Int i=0; i<MAX_SLOTS; ++i)
					{
						if (TheGameSpyGame->getGameSpySlot(i)->getProfileID() == selectedProfile)
						{
							if (buddyControls.listboxChat)
							{
								GadgetListBoxAddEntryText( buddyControls.listboxChat, TheGameText->fetch("Buddy:CantTalkToIngameBuddy"),
									GameSpyColor[GSCOLOR_DEFAULT], -1, -1 );
							}
							return MSG_HANDLED;
						}
					}
				}

				UnicodeString txtInput;
				txtInput.set(GadgetTextEntryGetText( buddyControls.textEntryEdit ));
				GadgetTextEntrySetText(buddyControls.textEntryEdit, UnicodeString::TheEmptyString);
				txtInput.trim();
				if (!txtInput.isEmpty())
				{
					BuddyRequest req;
					req.buddyRequestType = BuddyRequest::BUDDYREQUEST_MESSAGE;
					wcsncpy(req.arg.message.text, txtInput.str(), MAX_BUDDY_CHAT_LEN);
					req.arg.message.text[MAX_BUDDY_CHAT_LEN-1] = 0;
					req.arg.message.recipient = selectedProfile;
					TheGameSpyBuddyMessageQueue->addRequest(req);

					BuddyMessageList *messages = TheGameSpyInfo->getBuddyMessages();
					BuddyMessage message;
					message.m_timestamp = time(NULL);
					message.m_senderID = TheGameSpyInfo->getLocalProfileID();
					message.m_senderNick = TheGameSpyInfo->getLocalBaseName();
					message.m_recipientID = selectedProfile;
					message.m_recipientNick = recipIt->second.m_name;
					message.m_message = UnicodeString(req.arg.message.text);
					messages->push_back(message);
					insertChat(message);
				}
			}
			else if (buddyControls.listboxChat)
			{
				GadgetListBoxAddEntryText( buddyControls.listboxChat, TheGameText->fetch("Buddy:SelectBuddyToChat"),
					GameSpyColor[GSCOLOR_DEFAULT], -1, -1 );
			}
			break;
		}
		default:
			return MSG_IGNORED;
	}
	return MSG_HANDLED;
}
