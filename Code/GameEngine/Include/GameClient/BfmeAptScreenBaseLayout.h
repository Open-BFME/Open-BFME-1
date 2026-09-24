#pragma once

// Storage after the APT screen primary vptr. Field order and offsets come
// from BfmeAptScreenBaseConstructor.cpp. The parameter lets that constructor
// keep its WinInstanceData member while layout-only views use opaque storage.
struct BfmeAptScreenBaseOpaqueInstanceData
{
	char m_storage[ 0x1A8 ];
};

template <typename InstanceData = BfmeAptScreenBaseOpaqueInstanceData>
struct BfmeAptScreenBaseLayout
{
	typedef char InstanceDataMustBe0x1A8[
		sizeof( InstanceData ) == 0x1A8 ? 1 : -1 ];

	void *m_bfmeAnchor;
	int m_status;
	int m_sizeX;
	int m_sizeY;
	int m_regionLoX;
	int m_regionLoY;
	int m_regionHiX;
	int m_regionHiY;
	int m_cursorX;
	int m_cursorY;
	void *m_userData;
	InstanceData m_instData;
	void *m_inputData;
	void *m_bfmeInputExtra;
	void *m_input;
	void *m_system;
	void *m_draw;
	void *m_tooltip;
	void *m_bfmeCallbackExtra;
	int m_bfmeCallbackExtra2;
	void *m_next;
	void *m_prev;
	void *m_parent;
	void *m_child;
	void *m_nextLayout;
	void *m_prevLayout;
	void *m_layout;
	void *m_editData;
};
