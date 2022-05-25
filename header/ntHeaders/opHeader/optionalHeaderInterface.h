#ifndef PEANALCLI_OPTIONALHEADERINTERFACE_H
#define PEANALCLI_OPTIONALHEADERINTERFACE_H

#include <exception>
#include <cwchar>

class OptionalHeaderInterface {
    const size_t    kNumSubSys = 17;
    const char * const * const kMagicArr  = new const char * [2] { "PE32", "PE32+" };
    const char * const * const kSubSysArr = new const char * [kNumSubSys] {
        "IMAGE_SUBSYSTEM_UNKNOWN",                  "IMAGE_SUBSYSTEM_NATIVE",
        "IMAGE_SUBSYSTEM_WINDOWS_GUI",              "IMAGE_SUBSYSTEM_WINDOWS_CUI",
        "",                                         "IMAGE_SUBSYSTEM_OS2_CUI",
        "",                                         "IMAGE_SUBSYSTEM_POSIX_CUI",
        "IMAGE_SUBSYSTEM_NATIVE_WINDOWS",           "IMAGE_SUBSYSTEM_WINDOWS_CE_GUI",
        "IMAGE_SUBSYSTEM_EFI_APPLICATION",          "IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER",
        "IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER",       "IMAGE_SUBSYSTEM_EFI_ROM",
        "IMAGE_SUBSYSTEM_XBOX",                     "",
        "IMAGE_SUBSYSTEM_WINDOWS_BOOT_APPLICATION"
    };

protected:
    virtual ~OptionalHeaderInterface();

    [[nodiscard]] char * getValOfMagic(size_t) const;
    [[nodiscard]] char * getValOfSubSys(size_t) const;
};


#endif //PEANALCLI_OPTIONALHEADERINTERFACE_H
