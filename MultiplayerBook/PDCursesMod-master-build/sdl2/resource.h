//{{NO_DEPENDENCIES}}
// Used by version.rc
//
#define PRODUCT_VERSION_MAJOR                  4
#define PRODUCT_VERSION_MINOR                  4
#define PRODUCT_VERSION_PATCH                  0
#define PRODUCT_VERSION_BUILD                  0

#define FILE_VERSION_MAJOR                     4
#define FILE_VERSION_MINOR                     4
#define FILE_VERSION_PATCH                     0
#define FILE_VERSION_BUILD                     0

#ifndef __TO_STRING
#define __TO_STRING_IMPL(x) #x
#define __TO_STRING(x) __TO_STRING_IMPL(x)
#endif

#define PRODUCT_VERSION_MAJOR_MINOR_STR        __TO_STRING(PRODUCT_VERSION_MAJOR) "." __TO_STRING(PRODUCT_VERSION_MINOR)
#define PRODUCT_VERSION_MAJOR_MINOR_PATCH_STR  PRODUCT_VERSION_MAJOR_MINOR_STR "." __TO_STRING(PRODUCT_VERSION_PATCH)
#define PRODUCT_VERSION_FULL_STR               PRODUCT_VERSION_MAJOR_MINOR_PATCH_STR "." __TO_STRING(PRODUCT_VERSION_BUILD)
#define PRODUCT_VERSION_RESOURCE               PRODUCT_VERSION_MAJOR,PRODUCT_VERSION_MINOR,PRODUCT_VERSION_PATCH,PRODUCT_VERSION_BUILD
#define PRODUCT_VERSION_RESOURCE_STR           PRODUCT_VERSION_FULL_STR "\0"

#define FILE_VERSION_MAJOR_MINOR_STR           __TO_STRING(FILE_VERSION_MAJOR) "." __TO_STRING(FILE_VERSION_MINOR)
#define FILE_VERSION_MAJOR_MINOR_PATCH_STR     FILE_VERSION_MAJOR_MINOR_STR "." __TO_STRING(FILE_VERSION_PATCH)
#define FILE_VERSION_FULL_STR                  FILE_VERSION_MAJOR_MINOR_PATCH_STR "." __TO_STRING(FILE_VERSION_BUILD)
#define FILE_VERSION_RESOURCE                  FILE_VERSION_MAJOR,FILE_VERSION_MINOR,FILE_VERSION_PATCH,FILE_VERSION_BUILD
#define FILE_VERSION_RESOURCE_STR              FILE_VERSION_FULL_STR "\0"


#define PRODUCT_FILE_DESCRIPTION              "Public Domain Curses  MS x86_64\0"
#define PRODUCT_INTERNAL_NAME                 "PDCurses - sdl2\0"
#define PRODUCT_COMPANY_COPYRIGHT             "Public Domain\0"
#define PRODUCT_ORIGINAL_FILENAME             "PDCURSES.DLL\0"
#define PRODUCT_NAME                          "Public Domain Curses Library\0"
#define PRODUCT_ICON                          ""

#define VS_VERSION_INFO                        1
#define IDC_STATIC                             -1


// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE              101
#define _APS_NEXT_COMMAND_VALUE               40001
#define _APS_NEXT_CONTROL_VALUE               1000
#define _APS_NEXT_SYMED_VALUE                 101
#endif
#endif
