//
// say.exe - copyright (c) 2006 by Antoni Sawicki <as@tenoware.com>;
//

#include <windows.h>
#include <sapi.h>
#include <wchar.h>

#pragma comment(lib,"ole32")

int wmain(int argc, WCHAR **argv) {
    WCHAR buff[8192];
    int n;
    ISpVoice *pVoice = NULL;

    for(n=1; n<argc; n++) {
        if(wcslen(buff) + wcslen(argv[n]) + 2 > ARRAYSIZE(buff))
            break;
        wcscat(buff, argv[n]);
        wcscat(buff, L" ");
    }

	if(!wcslen(buff)) {
		wprintf(L"Copyright (c) 2006 by Antoni Sawicki <as@tenoware.com>\n\nusage: say.exe <text to say>\n\n");
		return 1;
	}

    if(FAILED(::CoInitialize(NULL))) {
        wprintf(L"ERROR: Unable to initialize SAPI\n\n");
        return 2;
    }

    if(SUCCEEDED(CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice))) {
        pVoice->Speak(buff, 0, NULL);
        pVoice->Release();
        pVoice=NULL;
    }

    ::CoUninitialize();

    return 0;
}