/*++

Module Name:

    XHCI.H

Abstract:

    Declarations for the newer USB hub IOCTLs (USB 3 / xHCI era), which the
    Windows headers only provide when building for a new enough Windows.

    USBViewEx is built for Windows XP (_WIN32_WINNT 0x0501, see version.h), but
    still wants to ask these questions when it happens to be running on a
    system whose USB stack can answer them. <usbioctl.h> hides:

      - the Windows Vista declarations when _WIN32_WINNT  < 0x0600, and
      - the Windows 8 declarations     when NTDDI_VERSION < 0x06020000

    so this header supplies exactly those pieces, under the same conditions,
    and nothing when the system headers already have them. The layouts are
    the documented ones from <usbioctl.h> and must not be changed.

    On a system that does not know one of these IOCTLs, DeviceIoControl simply
    fails and the callers in enum.c carry on without that information.

    Include this after <usbioctl.h>, <usbiodef.h> and <usbspec.h>/<usb200.h>.

--*/

#ifndef USBVIEW_XHCI_H_
#define USBVIEW_XHCI_H_

/*****************************************************************************
 I O C T L   F U N C T I O N   C O D E S   ( u s b i o d e f . h )
*****************************************************************************/

#ifndef USB_GET_HUB_CAPABILITIES_EX
#define USB_GET_HUB_CAPABILITIES_EX                 276
#endif

#ifndef USB_GET_HUB_INFORMATION_EX
#define USB_GET_HUB_INFORMATION_EX                  277
#endif

#ifndef USB_GET_PORT_CONNECTOR_PROPERTIES
#define USB_GET_PORT_CONNECTOR_PROPERTIES           278
#endif

#ifndef USB_GET_NODE_CONNECTION_INFORMATION_EX_V2
#define USB_GET_NODE_CONNECTION_INFORMATION_EX_V2   279
#endif

/*****************************************************************************
 I O C T L S   ( u s b i o c t l . h )
*****************************************************************************/

// Windows Vista
#ifndef IOCTL_USB_GET_HUB_CAPABILITIES_EX
#define IOCTL_USB_GET_HUB_CAPABILITIES_EX  \
    CTL_CODE(FILE_DEVICE_USB, USB_GET_HUB_CAPABILITIES_EX, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif

// Windows 8
#ifndef IOCTL_USB_GET_HUB_INFORMATION_EX
#define IOCTL_USB_GET_HUB_INFORMATION_EX  \
    CTL_CODE(FILE_DEVICE_USB, USB_GET_HUB_INFORMATION_EX, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif

#ifndef IOCTL_USB_GET_PORT_CONNECTOR_PROPERTIES
#define IOCTL_USB_GET_PORT_CONNECTOR_PROPERTIES  \
    CTL_CODE(FILE_DEVICE_USB, USB_GET_PORT_CONNECTOR_PROPERTIES, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif

#ifndef IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX_V2
#define IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX_V2  \
    CTL_CODE(FILE_DEVICE_USB, USB_GET_NODE_CONNECTION_INFORMATION_EX_V2, METHOD_BUFFERED, FILE_ANY_ACCESS)
#endif

/*****************************************************************************
 T Y P E D E F S   ( u s b i o c t l . h )
*****************************************************************************/

// <usbioctl.h> packs all of its structures on 1 byte boundaries
#pragma pack(push, 1)

#ifndef __MINGW32__
#pragma warning(push)
#pragma warning(disable:4201) // nameless struct/union
#pragma warning(disable:4214) // bit field types other than int
#endif // __MINGW32__

//
// Windows Vista: IOCTL_USB_GET_HUB_CAPABILITIES_EX
//
#if (_WIN32_WINNT < 0x0600)

typedef union _USB_HUB_CAP_FLAGS {
    ULONG ul;
    struct {
        ULONG HubIsHighSpeedCapable:1;
        ULONG HubIsHighSpeed:1;
        ULONG HubIsMultiTtCapable:1;
        ULONG HubIsMultiTt:1;
        ULONG HubIsRoot:1;
        ULONG HubIsArmedWakeOnConnect:1;
        ULONG HubIsBusPowered:1;
        ULONG ReservedMBZ:25;
    };
} USB_HUB_CAP_FLAGS, *PUSB_HUB_CAP_FLAGS;

typedef struct _USB_HUB_CAPABILITIES_EX {
    USB_HUB_CAP_FLAGS CapabilityFlags;
} USB_HUB_CAPABILITIES_EX, *PUSB_HUB_CAPABILITIES_EX;

#endif // (_WIN32_WINNT < 0x0600)

//
// Windows 8: IOCTL_USB_GET_HUB_INFORMATION_EX,
//            IOCTL_USB_GET_PORT_CONNECTOR_PROPERTIES,
//            IOCTL_USB_GET_NODE_CONNECTION_INFORMATION_EX_V2
//
#if !defined(NTDDI_VERSION) || (NTDDI_VERSION < 0x06020000)

typedef enum _USB_HUB_TYPE {
    UsbRootHub = 1,
    Usb20Hub = 2,
    Usb30Hub = 3
} USB_HUB_TYPE;

typedef struct _USB_HUB_INFORMATION_EX {
    USB_HUB_TYPE HubType;

    // The highest valid port number on the hub
    USHORT HighestPortNumber;

    union {
        USB_HUB_DESCRIPTOR UsbHubDescriptor;
        USB_30_HUB_DESCRIPTOR Usb30HubDescriptor;
    } u;
} USB_HUB_INFORMATION_EX, *PUSB_HUB_INFORMATION_EX;

typedef union _USB_PORT_PROPERTIES {
    ULONG ul;
    struct {
        ULONG PortIsUserConnectable:1;
        ULONG PortIsDebugCapable:1;
        ULONG ReservedMBZ:30;
    };
} USB_PORT_PROPERTIES, *PUSB_PORT_PROPERTIES;

typedef struct _USB_PORT_CONNECTOR_PROPERTIES {
    // One based port number
    ULONG ConnectionIndex;

    // The number of bytes required to hold the entire structure
    ULONG ActualLength;

    USB_PORT_PROPERTIES UsbPortProperties;

    // Zero based index number of the companion port being queried
    USHORT CompanionIndex;

    // Port number of the companion port
    USHORT CompanionPortNumber;

    // Symbolic link name for the companion hub
    WCHAR CompanionHubSymbolicLinkName[1];
} USB_PORT_CONNECTOR_PROPERTIES, *PUSB_PORT_CONNECTOR_PROPERTIES;

typedef union _USB_PROTOCOLS {
    ULONG ul;
    struct {
        ULONG Usb110:1;
        ULONG Usb200:1;
        ULONG Usb300:1;
        ULONG ReservedMBZ:29;
    };
} USB_PROTOCOLS, *PUSB_PROTOCOLS;

typedef union _USB_NODE_CONNECTION_INFORMATION_EX_V2_FLAGS {
    ULONG ul;
    struct {
        ULONG DeviceIsOperatingAtSuperSpeedOrHigher:1;
        ULONG DeviceIsSuperSpeedCapableOrHigher:1;
        ULONG DeviceIsOperatingAtSuperSpeedPlusOrHigher:1;
        ULONG DeviceIsSuperSpeedPlusCapableOrHigher:1;
        ULONG ReservedMBZ:28;
    };
} USB_NODE_CONNECTION_INFORMATION_EX_V2_FLAGS, *PUSB_NODE_CONNECTION_INFORMATION_EX_V2_FLAGS;

typedef struct _USB_NODE_CONNECTION_INFORMATION_EX_V2 {
    // One based port number
    ULONG ConnectionIndex;

    // Length of the structure
    ULONG Length;

    // On input, the protocols the caller knows about;
    // on output, the protocols supported by the port
    USB_PROTOCOLS SupportedUsbProtocols;

    USB_NODE_CONNECTION_INFORMATION_EX_V2_FLAGS Flags;
} USB_NODE_CONNECTION_INFORMATION_EX_V2, *PUSB_NODE_CONNECTION_INFORMATION_EX_V2;

#endif // !defined(NTDDI_VERSION) || (NTDDI_VERSION < 0x06020000)

#ifndef __MINGW32__
#pragma warning(pop)
#endif // __MINGW32__

#pragma pack(pop)

#endif // USBVIEW_XHCI_H_
