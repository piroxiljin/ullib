///\file ULQueueThread.cpp
///\brief ���� ���������� ������ ������ � ��������(27.08.2007)
#include "ULQueueThread.h"
namespace ULThreads
{
	CULQueueThread::CULQueueThread(void):CULThread()
	{
		
	};

	CULQueueThread::~CULQueueThread(void)
	{
	}

	DWORD CULQueueThread::ThreadProc(LPVOID param)
	{
		CULQueueThread* pThread=(CULQueueThread*)param;
		MSG msg;
		
		while(::GetMessage(&msg,NULL,0,0))
		{
			if(msg.message==0)
				::SetEvent(pThread->m_hStartedEvent);
			if(pThread->MessageMap.ProcessMessage(pThread,msg.message,msg.wParam,msg.lParam)==TRUE)
				break;
			if(msg.message==WM_QUIT)
				break;
		}
		return 0;
	}

	BOOL CULQueueThread::Create(LPSECURITY_ATTRIBUTES lpThreadAttributes,
			SIZE_T dwStackSize,
			DWORD dwCreationFlags)
	{
		if(!CULThread::Create(lpThreadAttributes,dwStackSize,dwCreationFlags))
			return FALSE;
		m_hStartedEvent=::CreateEvent(NULL,TRUE,FALSE,NULL);
		//��� ����� � ���� ���������
		while(::WaitForSingleObject(m_hStartedEvent,1)!=WAIT_OBJECT_0)
			PostThreadMessage(0,0,0);
		::CloseHandle(m_hStartedEvent);
		return (m_hThread!=NULL);
	};
}