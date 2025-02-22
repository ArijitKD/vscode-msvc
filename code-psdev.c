#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 512

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    printf ("Attempting to launch Visual Studio Code with Developer PowerShell enabled...\n");
    char* vstoolsdir = getenv("VSTOOLSDIR");
    char* ps32dir = getenv("PS32DIR");
    if (vstoolsdir == NULL || ps32dir == NULL)
    {
        printf ("ERROR: The environment variables VSTOOLSDIR and PS32DIR might not have been set or are not accessible.\n");
        MessageBox(NULL, "The environment variables VSTOOLSDIR and PS32DIR might not have been set or are not accessible.", "Error - Visual Studio Code", MB_ICONERROR | MB_OK);
        return 1;
    }
    char psargs[MAX_LEN] = {0};
    char pspath[MAX_LEN] = {0};
    snprintf (psargs, sizeof(psargs),
            "-noe -c \"&{Import-Module \"\"\"%s\\Microsoft.VisualStudio.DevShell.dll\"\"\"; Enter-VsDevShell 7c0518b3;Start-Process code -WindowStyle Hidden;exit}\"",
            vstoolsdir);
    snprintf (pspath, sizeof(pspath), "%s\\powershell.exe", ps32dir);
    HINSTANCE result = ShellExecute(NULL, "open", pspath, psargs, NULL, SW_HIDE);
    if ((int)result <= 32)
    {
        DWORD errCode = GetLastError();
        char errormsg[MAX_LEN] = {0};

        switch((int)result)
        {
            case 0:
                snprintf(errormsg, sizeof(errormsg), "Failed to start VS Code via Developer PowerShell. Error code: %d\n\nOut of Memory.", (int)result);
                break;
            case 2:
                snprintf(errormsg, sizeof(errormsg), "Failed to start VS Code via Developer PowerShell. Error code: %d\n\nFile %s not found. %%PS32DIR%% is probably incorrect.", (int)result, pspath);
                break;
            case 3:
                snprintf(errormsg, sizeof(errormsg), "Failed to start VS Code via Developer PowerShell. Error code: %d\n\nPath %s as in %%PS32DIR%% is incorrect or missing.", (int)result, ps32dir);
                break;
            case 5:
                snprintf(errormsg, sizeof(errormsg), "Failed to start VS Code via Developer PowerShell. Error code: %d\n\nAccess to %s is denied.", (int)result, pspath);
                break;
            case 8:
                snprintf(errormsg, sizeof(errormsg), "Failed to start VS Code via Developer PowerShell. Error code: %d\n\nOut of Memory.", (int)result);
                break;
            default:
                snprintf(errormsg, sizeof(errormsg), "Failed to start VS Code via Developer PowerShell. Error code: %d.", (int)result);
        }
        printf ("ERROR: %s\n", errormsg);
        MessageBox(NULL, errormsg, "Error - Visual Studio Code", MB_ICONERROR | MB_OK);
    }
    return 0;
}