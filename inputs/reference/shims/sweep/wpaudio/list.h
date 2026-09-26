/*
**  Miles/WPAudio SDK shim — minimal declarations for sweep compilation
*/

#pragma once

#include <wpaudio/altypes.h>

struct ListNode {
	ListNode* prev;
	ListNode* next;
	void* pri;
};

void ListNodeInit(ListNode* node);
ListNode* ListNodeNext(ListNode* node);
void ListNodeInsert(ListNode* node, ListNode* after);
void ListNodeRemove(ListNode* node);
