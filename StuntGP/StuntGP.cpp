// StuntGP.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "StuntGP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// STRING: STUNTGP 0x004130b0
#define EXE_STUNTGP_D3D "StuntGP_D3D.exe"

// STRING: STUNTGP 0x0004130c0
#define EXE_STUNTGP_GLIDE "StuntGP_Glide.exe"

// STRING: STUNTGP 0x0004130d4
#define CONFIG_GLIDE "GLIDE"

// STRING: STUNTGP 0x004130dc
#define CONFIG_END "-END"

// STRING: STUNTGP 0x004130e4
#define FILE_GAME_CFG "GAME.CFG"

// STRING: STUNTGP 0x0004130f0
#define FILE_READ_TEXT "rt"

// STRING: STUNTGP 0x004130f4
#define EXE_CONFIG "Config.exe"

// STRING: STUNTGP 0x00413100
#define FILE_CONFIG_CFG "config.cfg"

// STRING: STUNTGP 0x0041310c
#define FILE_READ_BINARY "rb"




/////////////////////////////////////////////////////////////////////////////
// CStuntGPApp

BEGIN_MESSAGE_MAP(CStuntGPApp, CWinApp)
	//{{AFX_MSG_MAP(CStuntGPApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStuntGPApp construction

// FUNCTION: STUNTGP 0x004090bf
CStuntGPApp::CStuntGPApp(LPCTSTR lpszAppName) :CWinApp(lpszAppName)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	//   FUN_0040893e((int)this);
  // *(undefined ***)this = &PTR_LAB_0040fc80;
  // _memset(this + 0x1c,0,0x20);
  // *(undefined4 *)(this + 0x1c) = param_1;
  // return this;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CStuntGPApp object

CStuntGPApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CStuntGPApp initialization

// FUNCTION: STUNTGP 0x004010a0
BOOL CStuntGPApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	char *exePath;
	// char *exeName;
	char buffer[200];
	BOOL glideMode = false;

	FILE *configFile = fopen(FILE_CONFIG_CFG, FILE_READ_BINARY);
	if(!configFile) {
		exePath = EXE_CONFIG;
		// exeName = EXE_CONFIG;
	} else {
		fclose(configFile);

		FILE *gameConfigFile = fopen("GAME.CFG", FILE_READ_TEXT);
		if(!gameConfigFile) {
			return FALSE;
		}

		// line by line search for -END,
		int found=0;
		do {
			do {
				char *line = fgets(buffer, BUFFER_SIZE, gameConfigFile);
				if(!line) {
					break;
				}
				found = strncmp(buffer, CONFIG_END, 4);
			} while(!found);
			char *line = fgets(buffer, BUFFER_SIZE, gameConfigFile);
			if (!line) {
				break;
			}
			found = strncmp(buffer, CONFIG_GLIDE, 5);
			if (found) {
				glideMode = 1;
			}
		} while(!found);

		fclose(gameConfigFile);
		if(glideMode) {
			exePath = EXE_STUNTGP_GLIDE;
			// exeName = EXE_STUNTGP_GLIDE;
		} else {
			exePath = EXE_STUNTGP_D3D;
		  // exeName = EXE_STUNTGP_D3D;
		}
	}

	run(_P_NOWAIT, exePath, &exePath);
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


// FUNCTION: STUNTGP 0x00401a1a
void __cdecl run(int mode, const char *cmdname, const  char *const *argv) {
    // one of the spawn commands
    _spawnve(mode, cmdname, argv, NULL);
		return;
}
