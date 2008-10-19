///\file ULSplitter.h 
///\brief фаил объ€влени€ класса оконного разделител€
#ifndef _ULSPLITTER_H__
#define _ULSPLITTER_H__
#include "ULWnd.h"

namespace ULWnds
{
	namespace ULControls
	{
		///\class CULSplitter
		///\brief класс контрола оконного разделител€ 
		class CULSplitter:
			public ULWnds::CULWnd
		{
		private:
			int m_nSplitterPos;
			int m_nSplitterBorder;
			ULWnds::CULWnd* m_arPane[2];
			int  m_oldPos;
			BOOL m_fMoved;
			BOOL m_fDragMode;

		public:
			enum enSplitterCommand
			{
				scPaneSized
			};
			enum enSplitterOrientation
			{
				soHorz,
				soVert
			};
			enSplitterOrientation m_SplitterOrientation;
		public:
			///\brief  онструктор
			CULSplitter();
			BOOL Create(HWND hParentWnd,WORD wID,int x,int y,int cx,int cy,enSplitterOrientation SplitterOrientation,int nSplitterPos);
			BOOL SetPane(int nPos,ULWnds::CULWnd* pwndPane);
		protected:
			void SizeWindowContents(int nWidth, int nHeight);
			void DrawXorBar(HDC hDC, int x1, int y1, int width, int height);
		protected:
			virtual LRESULT OnMessage(UINT uMsg,WPARAM wParam,LPARAM lParam);
			virtual LRESULT OnLButtonDown(WPARAM wParam,LPARAM lParam);
			virtual LRESULT OnLButtonUp(WPARAM wParam,LPARAM lParam);
			virtual LRESULT OnMouseMove(WPARAM wParam,LPARAM lParam);
			virtual LRESULT OnSize(WPARAM wParam,LPARAM lParam);
			virtual LRESULT OnWindowPosChanged(WPARAM wParam,LPARAM lParam);
		};
	}
}

#endif _ULSPLITTER_H__
