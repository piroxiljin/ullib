///\file ULProfileReg.h
///\brief Заголовочный файл класса профиля приложения в реестре(17.08.2007)
#pragma once
#ifndef __UL_ULPROFILE_REG_H__
#define __UL_ULPROFILE_REG_H__
#include <windows.h>
namespace ULOther
{
	///\class CULProfileReg
	///\brief Класс профиля приложения в реестре(17.08.2007)
	class CULProfileReg
	{
	protected:
		///\brief Хендл ключа реестра приложения
		HKEY m_hAppKey;
		///\brief Флаг секции, если TRUE то заносятся все значения в HKEY_LOCAL_MACHINE
		BOOL m_fAllUsers;
		///\brief Функция для получения ключа реестра секции
		///\param pcszSection - Имя секции
		///\param возвращает: хендл секции
		HKEY GetSectionKey(LPCTSTR pcszSection);
	public:
		///\brief Конструктор 
		CULProfileReg();
		///\brief Деструктор
		~CULProfileReg();
		///\brief Функция для создания секции компании и подсекции приложения
		///\param pcszCompanyName - Имя компании
		///\param pcszAppName - Имя приложения
		///\param fAllUsers - Использовать конфигурацию для всех пользователей
		///\return возвращает: TRUE в случае успеха, иначе FALSE
		BOOL SetRegistryKey(LPCTSTR pcszCompanyName,LPCTSTR pcszAppName,BOOL fAllUsers=FALSE);
		///\brief Функция для записи строкового параметра в указанную секцию
		///\param pcszSection - Имя секции
		///\param pcszEntry - Имя параметра(строки)
		///\param pcszValue - Значение(строки)
		///\return возвращает: TRUE в случае успеха, иначе FALSE
		BOOL WriteProfileString(LPCTSTR pcszSection,LPCTSTR pcszEntry,
			LPCTSTR pcszValue);
		///\brief Функция для записи числового параметра в указанную секцию
		///\param pcszSection - Имя секции
		///\param pcszEntry - Имя параметра(числа)
		///\param nValue - Значение(числа)
		///\return возвращает: TRUE в случае успеха, иначе FALSE
		BOOL WriteProfileInt(LPCTSTR pcszSection, LPCTSTR pcszEntry,int nValue);
		///\brief Функция для записи строкового параметра в указанную секцию
		///\param pcszSection - Имя секции
		///\param pcszEntry - Имя параметра(строки)
		///\param pszValue - Указатель на возвращаемое значение(строки)
		///\param lpdwValLen - размер pcszValue
		///\return возвращает: TRUE в случае успеха, иначе FALSE
		BOOL GetProfileString(LPCTSTR pcszSection, LPCTSTR pcszEntry,
			LPTSTR pszValue,LPDWORD lpdwValLen);
		///\brief Функция для чтения числового параметра в указанную секцию
		///\param pcszSection - Имя секции
		///\param pcszEntry - Имя параметра(числа)
		///\param pdwValue - Указатель на возвращаемое значение(числа)
		///\return возвращает: TRUE в случае успеха, иначе FALSE
		BOOL GetProfileInt(LPCTSTR pcszSection, LPCTSTR pcszEntry,DWORD* pdwValue);
		///\brief Функция для добавления указанного пути в авторан
		///\param pcszName - имя параметра
		///\param pcszFilePath - путь к файлу(если NULL,то пое pcszName удалится)
		///\return  возвращает: TRUE в случае успеха, иначе FALSE
		BOOL AddToAutoRun(LPCTSTR pcszName,LPCTSTR pcszFilePath);
		///\brief Закрывает сессию профиля
		void Close();
		///\brief отсоединяет класс от хендла 
		///\return хэндл
		inline HKEY Detach()
			{HKEY hRetKey=m_hAppKey;m_hAppKey=NULL;return hRetKey;}
	};
}
#endif//__UL_ULPROFILE_REG_H__
