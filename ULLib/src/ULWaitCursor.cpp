///\file ULWaitCursor.cpp
///\brief ���� ���������� ������ ������� ��������
#include "ULWaitCursor.h"

namespace ULOther
{
	CULWaitCursor::CULWaitCursor()
	{
		m_hWaitCursor=::LoadCursor(NULL,IDC_WAIT);
		m_hCursor=::SetCursor(m_hWaitCursor);
	}
	CULWaitCursor::~CULWaitCursor()
	{
		::SetCursor(m_hCursor);
	}
	void CULWaitCursor::Restore()
	{
		::SetCursor(m_hCursor);
	}
}