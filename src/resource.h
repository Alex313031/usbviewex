/*++
Copyright (c) 1998-2008 Microsoft Corporation, All Rights Reserved.
--*/

#define IDI_MAINFRAME                   101 // Main application icon, lowest number first
#define IDD_MAINDIALOG                  102 // Main application resource
#define IDR_MENU                        103 // Menu resource
#define IDD_ABOUT                       104 // About dialog
#define IDC_SPLIT                       105 // Pane Splitter
#define IDACCEL                         106 // Accelerators

#define IDI_BADICON                     107 // Warning icon
#define IDI_COMPUTER                    108 // Root of tree list icon
#define IDI_HUB                         109 // USB Hub icon
#define IDI_USB                         110 // USB icon, used to be the main .exe icon
#define IDI_NODEVICE                    111 // No device in port icon
#define IDI_SSUSB                       112 // USB 3.0 icon
#define IDI_NOSSDEVICE                  113 // No USB 3.0 device in port icon
#define IDI_HOST_CTRLR                  114 // USB host controller icon
#define IDI_SMALL                       115 // Small icon used in about dialog

#define IDC_TREE                        1000 // Tree view control
#define IDC_EDIT                        1001 // Output pane
#define IDC_STATUS                      1002 // Status bar

#define IDS_STRINGBASE                  2000
#define IDS_STANDARD_FONT               2001
#define IDS_STANDARD_FONT_HEIGHT        2002
#define IDS_STANDARD_FONT_WIDTH         2003
#define IDS_USBVIEW_USAGE               2004
#define IDS_USBVIEW_PRESSKEY            2005
#define IDS_USBVIEW_INVALIDARG          2006
#define IDS_USBVIEW_FILE_EXISTS_TXT     2007
#define IDS_USBVIEW_INTERNAL_ERROR      2009
#define IDS_USBVIEW_SAVED_TO            2010
#define IDS_USBVIEW_INVALID_FILENAME    2011

#define IDC_VERSION                     3000 // About dialog version area
#define IDC_UVCVERSION                  3001 // About dialog UVC version area

#define ID_EXIT                         40001
#define ID_REFRESH                      40002
#define ID_AUTO_REFRESH                 40003
#define ID_CONFIG_DESCRIPTORS           40004
#define ID_ABOUT                        40005
#define IDM_HELP                        40006
#define ID_ANNOTATION                   40007
#define ID_UNUSED                       40008
#define ID_LOG_DEBUG                    40009
#define ID_SAVE                         40010
#define ID_SAVEALL                      40011

// For controls that are never referenced from code.
#ifndef IDC_STATIC
 #define IDC_STATIC                     -1
#endif // IDC_STATIC

