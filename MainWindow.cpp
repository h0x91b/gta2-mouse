// MainWindow.cpp : implementation file
//

#include "pch.h"
#include "gta2dll.h"
#include "MainWindow.h"
#include "afxdialogex.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <iterator>
#include <map>

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
	ON_COMMAND(ID_SPAWNCAR_TANK, &MainWindow::OnSpawncarTank)
	ON_WM_HOTKEY()
	ON_COMMAND(ID_SPAWNCAR_GT, &MainWindow::OnSpawncarGt)
	ON_COMMAND_RANGE(35000, 35000 + 83, &OnSpawnCarClick)
	ON_COMMAND(ID_SPAWNCAR_GUNJEEP, &MainWindow::OnSpawncarGunjeep)
END_MESSAGE_MAP()


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
	frames = 0;

	SetTimer(TIMER_CAPTURE_MOUSE, 1000 / 60, NULL);

	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x54); //ALT+T

	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x47); //ALT+G

	RegisterHotKey(
		GetSafeHwnd(),
		1,
		MOD_ALT | MOD_NOREPEAT,
		0x4a); //ALT+J

	//AppendMenu();
	CMenu *menu = GetMenu();
	
	CMenu* nMenu = new CMenu();
	nMenu->CreatePopupMenu();

	std::map<std::wstring, DWORD> cars;

	cars.insert(std::pair<std::wstring, DWORD>(L"ALFA", 0));
	cars.insert(std::pair<std::wstring, DWORD>(L"ALLARD", 1));
	cars.insert(std::pair<std::wstring, DWORD>(L"AMDB4", 2));
	cars.insert(std::pair<std::wstring, DWORD>(L"APC", 3));
	cars.insert(std::pair<std::wstring, DWORD>(L"BANKVAN", 4));
	cars.insert(std::pair<std::wstring, DWORD>(L"BMW", 5));
	cars.insert(std::pair<std::wstring, DWORD>(L"BOXCAR", 6));
	cars.insert(std::pair<std::wstring, DWORD>(L"BOXTRUCK", 7));
	cars.insert(std::pair<std::wstring, DWORD>(L"BUG", 8));
	cars.insert(std::pair<std::wstring, DWORD>(L"BUICK", 10));
	cars.insert(std::pair<std::wstring, DWORD>(L"BUS", 11));
	cars.insert(std::pair<std::wstring, DWORD>(L"CAR15", 15));
	cars.insert(std::pair<std::wstring, DWORD>(L"CAR20", 20));
	cars.insert(std::pair<std::wstring, DWORD>(L"CAR43", 43));
	cars.insert(std::pair<std::wstring, DWORD>(L"CAR9", 9));
	cars.insert(std::pair<std::wstring, DWORD>(L"COPCAR", 12));
	cars.insert(std::pair<std::wstring, DWORD>(L"DART", 13));
	cars.insert(std::pair<std::wstring, DWORD>(L"EDSEL", 14));
	cars.insert(std::pair<std::wstring, DWORD>(L"EDSELFBI", 84));
	cars.insert(std::pair<std::wstring, DWORD>(L"FIAT", 16));
	cars.insert(std::pair<std::wstring, DWORD>(L"FIRETRUK", 17));
	cars.insert(std::pair<std::wstring, DWORD>(L"GRAHAM", 18));
	cars.insert(std::pair<std::wstring, DWORD>(L"GT24640", 19));
	cars.insert(std::pair<std::wstring, DWORD>(L"GTRUCK", 21));
	cars.insert(std::pair<std::wstring, DWORD>(L"GUNJEEP", 22));
	cars.insert(std::pair<std::wstring, DWORD>(L"HOTDOG", 23));
	cars.insert(std::pair<std::wstring, DWORD>(L"HOTDOG_D1", 24));
	cars.insert(std::pair<std::wstring, DWORD>(L"HOTDOG_D2", 25));
	cars.insert(std::pair<std::wstring, DWORD>(L"HOTDOG_D3", 26));
	cars.insert(std::pair<std::wstring, DWORD>(L"HOTDOG_D4", 85));
	cars.insert(std::pair<std::wstring, DWORD>(L"ICECREAM", 27));
	cars.insert(std::pair<std::wstring, DWORD>(L"ISETLIMO", 28));
	cars.insert(std::pair<std::wstring, DWORD>(L"ISETTA", 29));
	cars.insert(std::pair<std::wstring, DWORD>(L"JEEP", 30));
	cars.insert(std::pair<std::wstring, DWORD>(L"JEFFREY", 31));
	cars.insert(std::pair<std::wstring, DWORD>(L"KRSNABUS", 86));
	cars.insert(std::pair<std::wstring, DWORD>(L"LIMO", 32));
	cars.insert(std::pair<std::wstring, DWORD>(L"LIMO2", 33));
	cars.insert(std::pair<std::wstring, DWORD>(L"MEDICAR", 34));
	cars.insert(std::pair<std::wstring, DWORD>(L"MERC", 35));
	cars.insert(std::pair<std::wstring, DWORD>(L"MESSER", 36));
	cars.insert(std::pair<std::wstring, DWORD>(L"MIURA", 37));
	cars.insert(std::pair<std::wstring, DWORD>(L"MONSTER", 38));
	cars.insert(std::pair<std::wstring, DWORD>(L"MORGAN", 39));
	cars.insert(std::pair<std::wstring, DWORD>(L"MORRIS", 40));
	cars.insert(std::pair<std::wstring, DWORD>(L"PICKUP", 41));
	cars.insert(std::pair<std::wstring, DWORD>(L"RTYPE", 42));
	cars.insert(std::pair<std::wstring, DWORD>(L"SPIDER", 44));
	cars.insert(std::pair<std::wstring, DWORD>(L"SPRITE", 45));
	cars.insert(std::pair<std::wstring, DWORD>(L"STINGRAY", 46));
	cars.insert(std::pair<std::wstring, DWORD>(L"STRATOS", 47));
	cars.insert(std::pair<std::wstring, DWORD>(L"STRATOSB", 48));
	cars.insert(std::pair<std::wstring, DWORD>(L"STRIPETB", 49));
	cars.insert(std::pair<std::wstring, DWORD>(L"STYPE", 50));
	cars.insert(std::pair<std::wstring, DWORD>(L"STYPECAB", 51));
	cars.insert(std::pair<std::wstring, DWORD>(L"SWATVAN", 52));
	cars.insert(std::pair<std::wstring, DWORD>(L"T2000GT", 53));
	cars.insert(std::pair<std::wstring, DWORD>(L"TANK", 54));
	cars.insert(std::pair<std::wstring, DWORD>(L"TANKER", 55));
	cars.insert(std::pair<std::wstring, DWORD>(L"TAXI", 56));
	cars.insert(std::pair<std::wstring, DWORD>(L"TBIRD", 57));
	cars.insert(std::pair<std::wstring, DWORD>(L"TOWTRUCK", 58));
	//cars.insert(std::pair<std::wstring, DWORD>(L"TRAIN", 59));
	//cars.insert(std::pair<std::wstring, DWORD>(L"TRAINCAB", 60));
	//cars.insert(std::pair<std::wstring, DWORD>(L"TRAINFB", 61));
	cars.insert(std::pair<std::wstring, DWORD>(L"TRANCEAM", 62));
	cars.insert(std::pair<std::wstring, DWORD>(L"TRUKCAB1", 63));
	cars.insert(std::pair<std::wstring, DWORD>(L"TRUKCAB2", 64));
	cars.insert(std::pair<std::wstring, DWORD>(L"TRUKCONT", 65));
	cars.insert(std::pair<std::wstring, DWORD>(L"TRUKTRNS", 66));
	cars.insert(std::pair<std::wstring, DWORD>(L"TVVAN", 67));
	cars.insert(std::pair<std::wstring, DWORD>(L"VAN", 68));
	cars.insert(std::pair<std::wstring, DWORD>(L"VESPA", 69));
	cars.insert(std::pair<std::wstring, DWORD>(L"VTYPE", 70));
	cars.insert(std::pair<std::wstring, DWORD>(L"WBTWIN", 71));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK0", 72));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK1", 73));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK2", 74));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK3", 75));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK4", 76));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK5", 77));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK6", 78));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK7", 79));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK8", 80));
	cars.insert(std::pair<std::wstring, DWORD>(L"WRECK9", 81));
	cars.insert(std::pair<std::wstring, DWORD>(L"XK120", 82));
	cars.insert(std::pair<std::wstring, DWORD>(L"ZCX5", 83));

	std::map<std::wstring, DWORD>::iterator itr;
	for (itr = cars.begin(); itr != cars.end(); ++itr) {
		nMenu->AppendMenuW(MF_STRING, (UINT_PTR)(itr->second + 35000), itr->first.c_str());
	}

	menu->AppendMenuW(MF_POPUP, (UINT_PTR)nMenu->m_hMenu, L"Spawn car");

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

typedef Ped* (__stdcall GetPedById)(int);
GetPedById* fnGetPedByID = (GetPedById*)0x0043ae10;

//Save* __thiscall Game::GetSaveSlotByIndex(Game* this, byte index);
typedef Save* (__fastcall GetSaveSlotByIndex)(Game* game, DWORD edx, byte index);
GetSaveSlotByIndex* fnGetSaveSlotByIndex = (GetSaveSlotByIndex*)0x004219e0;

//void __thiscall ShowBigOnScreenLabel(void* this, WCHAR* txt, int timeToShowInSeconds);
typedef void(__fastcall ShowBigOnScreenLabel)(void* ptr, DWORD edx, WCHAR* txt, int time);
ShowBigOnScreenLabel* fnShowBigOnScreenLabel = (ShowBigOnScreenLabel*)0x004c6060;

//void SpawnCar(int x, int y, int z, short rot, CAR_MODEL model)
typedef Car* (SpawnCar)(int x, int y, int z, short rot, CAR_MODEL model);
SpawnCar* fnSpawnCar = (SpawnCar*)0x00426e10;

void MainWindow::CaptureMouse()
{
	if (*(DWORD*)ptrToPedManager == 0) {
		if (frames++ % 60 == 0) {
			log(L"Not in a game");
		}
		return;
	}
	Ped* playerPed = fnGetPedByID(1);

	if (!playerPed || playerPed->currentCar) {
		if (frames++ % 60 == 0) {
			log(L"No player ped is found");
		}
		return;
	}

	POINT p;
	RECT rect;
	GetCursorPos(&p);
	::GetWindowRect(m_gtaWindow, &rect);
	if (p.x < rect.left || p.x > rect.right || p.y < rect.top || p.y > rect.bottom) {
		if (frames++ % 60 == 0) {
			log(L"Cursor is outside of the game window");
		}
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

	if (frames++ % 60 == 0) {
		log(L"cursor at %dx%d angle is %f", relX, relY, angle);
	}

	if (playerPed->pedSprite) {
		playerPed->pedSprite->spriteRotation = gtaAngle;
	}
}

struct SPAWNCAR {
	CAR_MODEL model;
	MainWindow* win;
};

UINT SpawnCarThread(LPVOID data)
{
	SPAWNCAR* info = (SPAWNCAR*)data;
	if (*(DWORD*)ptrToPedManager == 0) {
		//info->win->log(L"ptrToPedManager isn't set. Not in a game probably.");
		return 0;
	}

	//info->win->log(L"The car will be spawned in 3 secs on front of you");

	S10* s10 = (S10*) * (DWORD*)0x00672f40;
	fnShowBigOnScreenLabel(&s10->ptrToSomeStructRelToBIG_LABEL, 0, (WCHAR*)L"3!", 1);
	Sleep(1000);
	fnShowBigOnScreenLabel(&s10->ptrToSomeStructRelToBIG_LABEL, 0, (WCHAR*)L"2!", 1);
	Sleep(1000);
	fnShowBigOnScreenLabel(&s10->ptrToSomeStructRelToBIG_LABEL, 0, (WCHAR*)L"1!", 1);
	Sleep(1000);

	Ped* playerPed = fnGetPedByID(1);

	if (!playerPed || playerPed->currentCar || !playerPed->pedSprite || !playerPed->pedSprite->actualPosition) {
		//info->win->log(L"Cannot find ped location");
		return 0;
	}

	//info->win->log(L"Player ped -> %08X", playerPed);


	//info->win->log(L"Spawn %d", info->model);
	double nAngle = playerPed->pedSprite->actualPosition->rotation / 4.0 + 270.0;
	const double distance = 1;
	Car* car = fnSpawnCar(
		playerPed->pedSprite->actualPosition->x + (int)(cos(nAngle * (M_PI / 180.0)) * distance * 16384.0),
		playerPed->pedSprite->actualPosition->y - (int)(sin(nAngle * (M_PI / 180.0)) * distance * 16384.0),
		playerPed->pedSprite->actualPosition->z,
		180 * 4,
		info->model
	);
	if (car) {
		//info->win->log(L"The car spawned at 0x%08X", car);
		fnShowBigOnScreenLabel(&s10->ptrToSomeStructRelToBIG_LABEL, 0, (WCHAR*)L"Car is here!", 10);
	}

	delete info;
	return 0;
}


void MainWindow::OnSpawncarTank()
{
	SPAWNCAR *info = new SPAWNCAR;
	info->win = this;
	info->model = TANK;
	::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SpawnCarThread, info, 0, 0);
}


void MainWindow::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	log(L"OnHotKey(%X, %X, %X)", nHotKeyId, nKey1, nKey2);
	switch (nKey2)
	{
	case 0x54:
		OnSpawncarTank();
		break;
	case 0x47:
		OnSpawncarGt();
		break;
	case 0x4a:
		OnSpawncarGunjeep();
		break;
	default:
		break;
	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void MainWindow::OnSpawncarGt()
{
	SPAWNCAR* info = new SPAWNCAR;
	info->win = this;
	info->model = GT24640;
	::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SpawnCarThread, info, 0, 0);
}


void MainWindow::OnSpawnCarClick(UINT nID) {
	log(L"OnSpawnCarClick on %d", nID);

	SPAWNCAR* info = new SPAWNCAR;
	info->win = this;
	info->model = (CAR_MODEL)(nID - 35000);
	::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SpawnCarThread, info, 0, 0);
}

void MainWindow::OnSpawncarGunjeep()
{
	SPAWNCAR* info = new SPAWNCAR;
	info->win = this;
	info->model = GUNJEEP;
	::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SpawnCarThread, info, 0, 0);
}
