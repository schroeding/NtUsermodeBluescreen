#include "main.h"

int main(unsigned int argc, char* argv[]) {

    // this programm can induce a bluescreen on Windows Vista and Windows 7.

    // it uses NtRaiseHardError, a function normally used to display a message box without
    // invoking any Win32 libraries, to send a Hard Error to csrss (standard Hard Error Port) with
    // the OptionShutdownSystem option

    // requires only the SE_SHUTDOWN_PRIVILEGE that any user has on default windows installations, even guest accounts

    // will probably be fixed in future versions, still kinda funny :-D

    void* ntdll = LoadLibraryA("ntdll.dll");
    if (!ntdll) { return 0; }

    DefRtlAdjustPrivilege RtlAdjustPrivilege = (DefRtlAdjustPrivilege)GetProcAddress(ntdll, "RtlAdjustPrivilege");
    DefNtRaiseHardError NtRaiseHardError = (DefNtRaiseHardError)GetProcAddress(ntdll, "NtRaiseHardError");
    if (!RtlAdjustPrivilege || !NtRaiseHardError) { return 0; }

    int returnValue = 0;
    returnValue = MessageBoxA(NULL, "Attention! The following programm will crash your system!\n\nPress 'OK' to induce a Bluescreen!", "Attention!", MB_OKCANCEL | MB_ICONWARNING | MB_SYSTEMMODAL);
    if (returnValue != IDOK) { return 0; }

    unsigned char privilegeStatus = 0;
    if (RtlAdjustPrivilege(SE_SHUTDOWN_PRIVILEGE, 1, 0, &privilegeStatus) == 0) { // STATUS_SUCCESS == 0
        
        unsigned long responseStatus = 0;
        NTSTATUS errorStatus = 0xC000035A; // STATUS_INVALID_IMAGE_WIN_64, see http://deusexmachina.uk/ntstatus.html
        NtRaiseHardError(errorStatus, 0, 0, 0, OptionShutdownSystem, &responseStatus);    

    }

    return 0;
    
}