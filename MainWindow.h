#pragma once

// MainWindow dialog
#include "gta2.segments.fixed.exe.h"

enum TIMER {
	TIMER_CAPTURE_MOUSE
};

class MainWindow : public CDialogEx
{
	DECLARE_DYNAMIC(MainWindow)

public:
	MainWindow(CWnd* pParent = nullptr);   // standard constructor
	virtual ~MainWindow();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	bool firstPaint;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDebugMakeInt3Crash();
	CEdit m_log;
	HWND m_gtaWindow;
	void log(const WCHAR* fmt, ...);
	afx_msg void OnCommandsHello();
	afx_msg void OnCommandsCaptureMouse();
	bool captureMouse;
	void CaptureMouse();
	afx_msg void OnSpawncarTank();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnSpawncarGt();
	uint frames;
};
