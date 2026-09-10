// ?ScoreScreenSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
// partial score=0.45 date=2026-09-10
// ScoreScreenSystem candidate excerpt from the owning ScoreScreen.cpp TU.
// The surrounding ScoreScreen globals and engine declarations remain in that TU.

class ScoreScreenGameSpyInfoView
{
public:
	virtual ~ScoreScreenGameSpyInfoView() {}
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot0A() = 0;
	virtual void slot0B() = 0;
	virtual void slot0C() = 0;
	virtual void slot0D() = 0;
	virtual void slot0E() = 0;
	virtual void slot0F() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual BuddyInfoMap *getBuddyMap() = 0;
};

WindowMsgHandledType ScoreScreenSystem( GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2 )
{
	UnicodeString txtInput;
	GameWindow *control = (GameWindow *)mData1;

	switch( msg )
	{
		case GWM_DESTROY:
		{
			break;
		}

		case GWM_INPUT_FOCUS:
		{
			if( mData1 == TRUE )
				*(Bool *)mData2 = TRUE;
			break;
		}

		case GBM_SELECTED:
		{
			TheTransitionHandler->remove("ScoreScreenShow", TRUE);
			ReplayWasPressed = FALSE;

			Int controlID = control->winGetWindowId();
			if( controlID == buttonOkID )
			{
				TheShell->pop();
				TheCampaignManager->setCampaign(AsciiString::TheEmptyString);
			}
			else if ( controlID == buttonContinueID )
			{
				if(!buttonIsFinishCampaign)
					ReplayWasPressed = TRUE;
				if( screenType == SCORESCREEN_SINGLEPLAYER)
				{
					AsciiString mapName = TheCampaignManager->getCurrentMap();
					if( mapName.isEmpty() )
					{
						ReplayWasPressed = FALSE;
						TheShell->pop();
					}
					else
					{
						CheckForCDAtGameStart( startNextCampaignGame );
					}
				}
			}
			else if ( controlID == buttonBuddiesID )
			{
				GameSpyToggleOverlay( GSOVERLAY_BUDDY );
			}
			else if ( controlID == buttonSaveReplayID )
			{
				ScoreScreenEnableControls(FALSE);
				WindowLayout *saveReplayLayout = TheShell->getPopupReplayLayout();
				DEBUG_ASSERTCRASH( saveReplayLayout, ("Unable to get save replay menu layout.\n") );
				saveReplayLayout->runInit();
				saveReplayLayout->hide( FALSE );
				saveReplayLayout->bringForward();
			}
			else if ( controlID == buttonEmoteID )
			{
				txtInput.set(GadgetTextEntryGetText( textEntryChat ));
				GadgetTextEntrySetText(textEntryChat, UnicodeString::TheEmptyString);
				txtInput.trim();
				if (!txtInput.isEmpty())
					if(TheLAN)
						TheLAN->RequestChat(txtInput, LANAPIInterface::LANCHAT_EMOTE);
			}
			for(Int i = 0; i < MAX_SLOTS; ++i)
			{
				AsciiString name;
				name.format("ScoreScreen.wnd:ButtonAdd%d", i);
				if( controlID == TheNameKeyGenerator->nameToKey(name))
				{
					Bool notBuddy = TRUE;
					Int playerID = (Int)GadgetButtonGetData(TheWindowManager->winGetWindowFromId(NULL,controlID));
					BuddyInfoMap *buddies = ((ScoreScreenGameSpyInfoView *)TheGameSpyInfo)->getBuddyMap();
					BuddyInfoMap::iterator bIt;
					if( playerID > 0)
					{
						bIt = buddies->find(playerID);
						if (bIt != buddies->end())
						{
							notBuddy = FALSE;
						}
					}
					if(notBuddy)
					{
						BuddyRequest req;
						req.buddyRequestType = BuddyRequest::BUDDYREQUEST_ADDBUDDY;
						req.arg.addbuddy.id = playerID;
						UnicodeString buddyAddstr;
						buddyAddstr = TheGameText->fetch("GUI:BuddyAddReq");
						wcsncpy(req.arg.addbuddy.text, buddyAddstr.str(), MAX_BUDDY_CHAT_LEN);
						req.arg.addbuddy.text[MAX_BUDDY_CHAT_LEN-1] = 0;
						TheGameSpyBuddyMessageQueue->addRequest(req);
					}
					break;
				}
			}
		}

		case GEM_EDIT_DONE:
		{
			Int controlID = control->winGetWindowId();
			if ( controlID == textEntryChatID )
			{
				txtInput.set(GadgetTextEntryGetText( textEntryChat ));
				GadgetTextEntrySetText(textEntryChat, UnicodeString::TheEmptyString);
				txtInput.trim();
				if (!txtInput.isEmpty())
					if(TheLAN)
						TheLAN->RequestChat(txtInput, LANAPIInterface::LANCHAT_NORMAL);
			}
		}
	}
	return MSG_HANDLED;
}
