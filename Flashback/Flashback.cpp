// Flashback.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ScreenshotManager.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {

	// Easy Logging initial configuration -----
	START_EASYLOGGINGPP(argc, argv);
	el::Configurations defaultConf;
	defaultConf.setToDefault();
	// Values are always std::string
	defaultConf.set(el::Level::Info, el::ConfigurationType::Format, "%datetime{%H:%m} %msg");
	// default logger uses default configurations
	el::Loggers::reconfigureLogger("default", defaultConf);

	// Set global hotkey ------
	// https://msdn.microsoft.com/pl-pl/library/windows/desktop/ms646309(v=vs.85).aspx

	if (RegisterHotKey(NULL, 1, MOD_NOREPEAT, VK_SNAPSHOT)) { 
		LOG(INFO) << "Hotkey 'PrintScreen' registered, using MOD_NOREPEAT flag";
	}

	if (RegisterHotKey(NULL, 2, MOD_CONTROL | MOD_NOREPEAT, VK_SNAPSHOT)) {
		LOG(INFO) << "Hotkey 'CTRL+PrintScreen' registered, using MOD_NOREPEAT flag";
	}

	// Create Screenshot Manager -----
	ScreenshotManager ScrMan;

	// Wait for hotkeys and take an action -----
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0) != 0) {
		if (msg.message == WM_HOTKEY) { // Defined hotkey received
			if (msg.wParam == 1) {
				ScrMan.Shot(); // ---> Make a screenshot
			}
			else if (msg.wParam == 2) {
				ScrMan.Main(); // ---> Open screenshot manager
			}
		}
	}

	return 0;
}



