///\file ULConsole.cpp
///\brief cpp ���� �������
#include "ULConsole.h"
#include <stdio.h>
#include "ULPtr.inl"

//����������� (� ��������� � �������)
CULConsole::CULConsole()
{
	//��������� ���������� �� ����������� ���� � �����
	m_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	m_hStdin = GetStdHandle(STD_INPUT_HANDLE);
}

CULConsole::CULConsole(CULConsole& Console):
	m_hStdout(Console.m_hStdout),
	m_hStdin(Console.m_hStdin)
{

}

CULConsole::~CULConsole()
{
};

void CULConsole::operator=(CULConsole& Console)
{
	m_hStdout=Console.m_hStdout;
	m_hStdin=Console.m_hStdin;
}
//������� ������
void CULConsole::Clear()
{
	system("cls");
}

//��������
void CULConsole::Pause()
{
	system("pause");
}

//��������� ��������� ����
LPTSTR CULConsole::GetTitle(LPTSTR pszTitle,WORD wSizeOfBuf)
{
	//��������� ��������� ����
	GetConsoleTitle(pszTitle, wSizeOfBuf);
	//�������������� ���������
//	OemToCharA(szBuf, szBuf);
	//������� ������
	return pszTitle;
}

//��������� ��������� ����
void CULConsole::SetTitle(LPTSTR pszTitle)
{
	//��������� ��������� ����
	SetConsoleTitle(pszTitle);
}

//��������� ����� ������
enConsoleColor CULConsole::GetColor()
{
	//���������� � �������
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	//��������� ���������� � �������
	GetConsoleScreenBufferInfo(m_hStdout, &csbiInfo);
	//������� �����
	return (enConsoleColor)(csbiInfo.wAttributes % 16);
}

//��������� ����� ������
void CULConsole::SetColor(enConsoleColor Color)
{
	SetConsoleTextAttribute(m_hStdout, (WORD)Color + (WORD)GetBgColor() * 16);
}

//��������� ����� ����
enConsoleColor CULConsole::GetBgColor()
{
	//���������� � �������
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	//��������� ���������� � �������
	GetConsoleScreenBufferInfo(m_hStdout, &csbiInfo);
	//������� �����
	return (enConsoleColor)(csbiInfo.wAttributes / 16);
}

//��������� ����� ����
void CULConsole::SetBgColor(enConsoleColor Color)
{
	SetConsoleTextAttribute(m_hStdout, (WORD)Color * 16 + (WORD)GetColor());
}

//����� �������
void CULConsole::Write(TCHAR c)
{
	_puttc(c,stdout);
}

//����� ������ (� ��������������� ���������)
void CULConsole::Write(LPTSTR pszStr)
{
	//�����
	ULOther::CULStrT<char> szBuf;
	//�������������� ���������
	CharToOem(pszStr, szBuf);
	puts(szBuf);
}

//������� �� ����� ������
void CULConsole::WriteLine()
{
	_puttc(_T('\n'),stdout);
}

//����� ������ (� ��������������� ��������� � ��������� �� ����� ������)
void CULConsole::WriteLine(LPTSTR pszStr)
{
	//�����	
	ULOther::CULStrT<char> szBuf;
	//�������������� ���������
	CharToOem(pszStr, szBuf);
	puts(szBuf);
	putc('\n',stdout);
}
//��������� ������� �������
COORD CULConsole::GetCursorPos()
{
	//���������� � �������
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	//��������� ���������� � �������
	GetConsoleScreenBufferInfo(m_hStdout, &csbiInfo);
	return csbiInfo.dwCursorPosition;
}

//��������� ������� �������
void CULConsole::SetCursorPos(short X, short Y)
{
	//���������� �������
	COORD p;
	p.X = X;
	p.Y = Y;
	SetConsoleCursorPosition(m_hStdout, p);
}

//��������� �������� ���� (� ��������)
SIZE CULConsole::GetWindowSize()
{
	//���������� � �������
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	//��������� ���������� � �������
	GetConsoleScreenBufferInfo(m_hStdout, &csbiInfo);
	SIZE szRet={csbiInfo.dwMaximumWindowSize.X,csbiInfo.dwMaximumWindowSize.Y};
	return szRet;
}

//������ ���� ������� ������� (� ���������)
TCHAR CULConsole::ReadKey()
{
	//���������� �������
	DWORD n;
	//������ � �����
	INPUT_RECORD record;
	//������
	TCHAR c;
	//���� �������� ������� ������
	for ( ; ; )
	{
		//���� ���������� �������� �������
		if (!ReadConsoleInput(m_hStdin, &record, 1L, &n ) || (n == 0L))
		{
			//��������� �������� ����� ����� � �����
			c = (TCHAR)EOF;
			break;
		}
		//���� ������ �������
		if ((record.EventType == KEY_EVENT) && record.Event.KeyEvent.bKeyDown)
			//���� ������ ���������� �������, �����
			if ((c = static_cast<TCHAR>(record.Event.KeyEvent.uChar.AsciiChar))!=NULL)
				break;
	}
	//������� �������
	return c;
}

//������ ������ (�� ������)
LPTSTR CULConsole::ReadLine(LPTSTR pszBuf,WORD wSizeOfBuf)
{ 
	//�����
	do
		//������ ������
		_getts_s(pszBuf,wSizeOfBuf);
	//���� ������ ������
	while (_tcslen(pszBuf) < 1);
	//������� ������
	return pszBuf;
}

//������ ������ ����� (�� ������)
long CULConsole::ReadLong()
{
	//��������
	long nVal;
	//����� ������
	LPTSTR pszErr;
	//�����
	ULOther::CULStr szBuf;
	//���� � ��������������
	nVal = _tcstol(ReadLine(szBuf,(WORD)szBuf.GetSize()), &pszErr, 10);
	//���� ������� ����� ������
	while (_tcslen(pszErr) > 0)
	{
		//������ �����
		Write(_T("��������� ����� �����: "));
		nVal = _tcstol(ReadLine(szBuf,(WORD)szBuf.GetSize()), &pszErr, 10);
	}
	//������� ��������
	return nVal;
}

//������ ������ ����� (��� �����)
unsigned long CULConsole::ReadULong()
{
	//��������
	long nVal;
	//����� ������
	TCHAR* pszErr;
	//�����
	ULOther::CULStr szBuf;
	//���� � ��������������
	nVal = _tcstol(ReadLine(szBuf,(WORD)szBuf.GetSize()), &pszErr, 10);
	//���� ������� ����� ������ ��� �������� < 0
	while (_tcslen(pszErr) > 0 || nVal < 0)
	{
		//������ �����
		Write(_T("��������� ����� ��������������� �����: "));
		nVal = _tcstol(ReadLine(szBuf,(WORD)szBuf.GetSize()), &pszErr, 10);
	}
	//������� ��������
	return static_cast<unsigned long>(nVal);
}

//������ ��������������� �����
double CULConsole::ReadDouble()
{
	//��������
	double dblVal;
	//����� ������
	LPTSTR pszErr;
	//�����
	ULOther::CULStr szBuf;
	//���� � ��������������
	dblVal = _tcstod(ReadLine(szBuf,(WORD)szBuf.GetSize()), &pszErr);
	//���� ������� ����� ������
	while (_tcslen(pszErr) > 0)
	{
		//������ �����
		Write(_T("��������� ������������ �����: "));
		dblVal = _tcstod(ReadLine(szBuf,(WORD)szBuf.GetSize()), &pszErr);
	}
	//������� ��������
	return dblVal;
}

int CULConsole::Format(LPTSTR szFormat,...)
{
	va_list va;
	va_start( va, szFormat );	
	int nRet=_vftprintf(stdout,szFormat,va);
	va_end( va );
	return nRet;
}