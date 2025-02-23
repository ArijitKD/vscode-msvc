#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 512
#define BITNESS 64  // Determines which toolchains will be initialized (32 for x86, 64 for x64)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    printf ("Attempting to launch Visual Studio Code with %d-bit MSVC Toolchain...\n", BITNESS);
    char* vsbuildtoolsdir = getenv("VSBUILDTOOLSDIR");
    if (vsbuildtoolsdir == NULL)
    {
        printf ("ERROR: The environment variable VSBUILDTOOLSDIR might not have been set or is not accessible.\n");
        MessageBox(NULL, "The environment variable VSBUILDTOOLSDIR might not have been set or is not accessible.", "Error", MB_ICONERROR | MB_OK);
        return 1;
    }
    char cmdArgs[MAX_LEN] = {0};
    #if BITNESS == 64
        snprintf (cmdArgs, sizeof(cmdArgs), "/c call \"%s\\VC\\Auxiliary\\Build\\vcvars64.bat\" && code && exit", vsbuildtoolsdir);
    #else
        snprintf (cmdArgs, sizeof(cmdArgs), "/c call \"%s\\VC\\Auxiliary\\Build\\vcvars32.bat\" && code && exit", vsbuildtoolsdir);
    #endif
    
    DWORD retCode = (DWORD)ShellExecute(NULL, "open", "cmd.exe", cmdArgs, NULL, SW_HIDE);
    if (retCode <= 32)
    {
        char errormsg[MAX_LEN] = {0};

        switch(retCode)
        {
            case SE_ERR_OOM:
                snprintf(errormsg, sizeof(errormsg), "Failed to start Visual Studio Code with %d-bit MSVC Toolchain. Error code: %X\n\nOut of Memory.", BITNESS, retCode);
                break;
            case ERROR_FILE_NOT_FOUND:
                snprintf(errormsg, sizeof(errormsg), "Failed to start Visual Studio Code with %d-bit MSVC Toolchain. Error code: %X\n\nFile %s not found. %%VSBUILDTOOLSDIR%% is probably incorrect.",BITNESS, retCode, cmdArgs);
                break;
            case ERROR_PATH_NOT_FOUND:
                snprintf(errormsg, sizeof(errormsg), "Failed to start Visual Studio Code with %d-bit MSVC Toolchain. Error code: %X\n\nPath %s as in %%PS32DIR%% is incorrect or missing.",BITNESS, retCode, vsbuildtoolsdir);
                break;
            case ERROR_ACCESS_DENIED:
                snprintf(errormsg, sizeof(errormsg), "Failed to start Visual Studio Code with %d-bit MSVC Toolchain. Error code: %X\n\nAccess to shell is denied.",BITNESS, retCode);
                break;
            default:
                snprintf(errormsg, sizeof(errormsg), "Failed to start Visual Studio Code with %d-bit MSVC Toolchain. Error code: %X.",BITNESS, retCode);
        }
        printf ("ERROR: %s\n", errormsg);
        MessageBox(NULL, errormsg, "Error", MB_ICONERROR | MB_OK);
    }
    return 0;
}