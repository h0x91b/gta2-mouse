// MainWindow.cpp : implementation file
//

#include "pch.h"
#include "gta2dll.h"
#include "MainWindow.h"
#include "afxdialogex.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "gta2.segments.fixed.exe.h"
#include <string>

// MainWindow dialog

IMPLEMENT_DYNAMIC(MainWindow, CDialogEx)

MainWindow::MainWindow(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

MainWindow::~MainWindow()
{
}

void MainWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_log);
}


BEGIN_MESSAGE_MAP(MainWindow, CDialogEx)
	ON_BN_CLICKED(IDOK, &MainWindow::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &MainWindow::OnBnClickedCancel)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_COMMAND(ID_DEBUG_MAKEINT3CRASHTOATTACHDEBUGGER, &MainWindow::OnDebugMakeInt3Crash)
	ON_COMMAND(ID_COMMANDS_HELLO, &MainWindow::OnCommandsHello)
	ON_COMMAND(ID_COMMANDS_CAPTUREMOUSE, &MainWindow::OnCommandsCaptureMouse)
END_MESSAGE_MAP()


// MainWindow message handlers


void MainWindow::OnBnClickedOk()
{
	//CDialogEx::OnOK();
}


void MainWindow::OnBnClickedCancel()
{
	if (m_gtaWindow) {
		::DestroyWindow(m_gtaWindow);
		::exit(0);
	}
}


int MainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_gtaWindow = NULL;
	firstPaint = true;

	SetTimer(1, 50, NULL);
	SetTimer(TIMER_CAPTURE_MOUSE, 1000 / 60, NULL);
	return 0;
}


void MainWindow::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	if (firstPaint && m_gtaWindow) {
		firstPaint = false;
		CRect rect, rect2;
		
		GetWindowRect(&rect);
		::GetWindowRect(m_gtaWindow, &rect2);

		int x = GetSystemMetrics(SM_CXSCREEN) - rect2.Width();
		
		::MoveWindow(m_gtaWindow, x, 0, rect2.Width(), rect2.Height(), true);
		MoveWindow(0, 0, rect.Width(), rect.Height(), true);

		m_log.ShowScrollBar(SB_VERT);
		InvalidateRect(rect);
	}
	else if (!m_gtaWindow) {
		m_gtaWindow = FindWindowA("WinMain", "GTA2");
	}
}


void MainWindow::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_CAPTURE_MOUSE && captureMouse) {
		CaptureMouse();
	}

	CDialogEx::OnTimer(nIDEvent);
}


void MainWindow::OnDebugMakeInt3Crash()
{
	log(L"__asm int 3");
	__asm int 3;
}


void MainWindow::log(const WCHAR* fmt, ...)
{
	CString tmp;
	m_log.GetWindowTextW(tmp);
	std::wstring logStore(tmp.GetBuffer());
	logStore.append(L"\r\n");
	WCHAR buf[1024];
	va_list args;
	va_start(args, fmt);
	vswprintf(buf, 512, fmt, args);

	logStore.append(buf);
	std::wstring str;
	if (logStore.length() > 16384) {
		str = logStore.substr(logStore.length() - 4096, 4096).c_str();
	}
	else {
		str = logStore;
	}

	m_log.SetWindowTextW(str.c_str());
	DWORD len = str.length();
	m_log.SetSel(len-1, len, false);
}


void MainWindow::OnCommandsHello()
{
	MessageBox(L"Hello", L"GTA 2 DLL");
}


void MainWindow::OnCommandsCaptureMouse()
{
	CMenu *menu = GetMenu();
	MENUITEMINFO menuItem = { 0 };
	menuItem.cbSize = sizeof(MENUITEMINFO);
	menuItem.fMask = MIIM_STATE;

	menu->GetMenuItemInfoW(ID_COMMANDS_CAPTUREMOUSE, &menuItem);

	if (menuItem.fState == MFS_CHECKED) {
		// Checked, uncheck it
		menuItem.fState = MFS_UNCHECKED;
		log(L"Do not capture mouse");
		captureMouse = false;
	}
	else {
		// Unchecked, check it
		menuItem.fState = MFS_CHECKED;
		log(L"Capture mouse");
		captureMouse = true;
	}
	menu->SetMenuItemInfoW(ID_COMMANDS_CAPTUREMOUSE, &menuItem);
}

DWORD ptrToPedManager = 0x005e5bbc;
DWORD ptrToGame = 0x005eb4fc;

typedef Ped* GetPedById(int);
GetPedById* (__stdcall fnGetPedByID) = (GetPedById*)0x0043ae10;

//Save* __thiscall Game::GetSaveSlotByIndex(Game* this, byte index);
typedef Save* (__fastcall GetSaveSlotByIndex)(Game* game, DWORD edx, byte index);
GetSaveSlotByIndex* fnGetSaveSlotByIndex = (GetSaveSlotByIndex*)0x004219e0;

void MainWindow::CaptureMouse()
{
	if (*(DWORD*)ptrToPedManager == 0) {
		// not in game
		return;
	}
	Ped* playerPed = fnGetPedByID(1);

	if (!playerPed || playerPed->currentCar) {
		return;
	}

	POINT p;
	RECT rect;
	GetCursorPos(&p);
	::GetWindowRect(m_gtaWindow, &rect);
	if (p.x < rect.left || p.x > rect.right || p.y < rect.top || p.y > rect.bottom) {
		return;
	}

	int nCaptionHeight = ::GetSystemMetrics(SM_CYCAPTION);

	int centerX = rect.left + (rect.right - rect.left) / 2;
	int centerY = rect.top + nCaptionHeight + (rect.bottom - rect.top - nCaptionHeight) / 2;

	int relX = p.x - centerX;
	int relY = p.y - centerY;
	double angle = atan2(relX, relY) * (180.0 / M_PI);
	double nAngle = 0;

	short gtaAngle = 0;
	if (angle >= 0) {
		gtaAngle = (short)(angle * 4.0);
		nAngle = angle + 90;
	}
	else {
		//on top -180, 0 on bottom
		gtaAngle = (short)((angle + 360) * 4.0);
	}

	nAngle = 270 + angle;

	log(L"cursor at %dx%d angle is %f", relX, relY, angle);

	if (playerPed->pedSprite) {
		playerPed->pedSprite->spriteRotation = gtaAngle;
	}
}