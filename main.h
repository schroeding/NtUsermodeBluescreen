#include <windows.h>

// the following definitions are taken from the Windows 7 DDK, with
// unnecessary parameters removed / replaced by void

#define SE_SHUTDOWN_PRIVILEGE 19L // see DDK / wdm.h
                                  // please don't ask me why microsoft did not use an enum

typedef NTSTATUS (*DefRtlAdjustPrivilege) (
    unsigned long Privilege, // privilege to adjust, must already be granted
    unsigned char Enable, // NTAPI BOOLEAN, true or false to activate / deactivate
    unsigned char CurrentThread, // enabe the privilege for the current thread only
    void* Enabled // status after change
);

typedef enum HARDERROR_RESPONSE_OPTION {
    OptionAbortRetryIgnore,
    OptionOk,
    OptionOkCancel,
    OptionRetryCancel,
    OptionYesNo,
    OptionYesNoCancel,
    OptionShutdownSystem // other options are also used in stuff like messageboxa/w, but this option can induce a bluescreen
} HARDERROR_RESPONSE_OPTION;

typedef NTSTATUS (*DefNtRaiseHardError) (
    NTSTATUS ErrorStatus, // The NTSTATUS error code that should be raised
    unsigned long NumberOfParameters, // size of Parameters array
    void* UnicodeStringParameterMask, // error string, marked as optional in the DDK
    void** Parameters, // array of pointers to additional parameters
    HARDERROR_RESPONSE_OPTION ResponseOption, // buttons to show (or ShutdownSystem to induce a bluescreen,
                                              //                  as long as the HardErrorPort is csrss, which is the default)
    unsigned long* Response // button the user pressed
);