/********************************
 * Basic HIDAPI impl using UsbDkHelper lib for UsbDk Windows redirection driver
 * 
 * LICENSE (and much of everything else) TODO
 * 
 * Based on the other hidapi backends.
 * 
 * 2018-09-?? .. ???
************************************/

#include <windows.h>
// for MinGW < 5.3 look at windows/hid.c stuff here

#ifdef __MINGW32__
#include <ntdef.h>
#include <winbase.h>
#include <devpropdef.h>
#endif

#ifdef __CYGWIN__
#include <ntdef.h>
#define _wcsdup wcsdup
#endif

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <assert.h>

#include "UsbDkCompat.h"
#include "UsbDkHelper.h"

#ifdef __cplusplus
extern "C" {
#endif

struct hid_device_ {
    HANDLE device_handle;
}

static hid_device *new_hid_device()
{

}

static void free_hid_device(hid_device *dev)
{

}

int HID_API_EXPORT hid_init(void)
{

}

int HID_API_EXPORT hid_exit(void)
{

}

struct hid_device_info HID_API_EXPORT * HID_API_CALL hid_enumerate(unsigned short vendor_id, unsigned short product_id)
{
    ssize_t num_devs;
    int i = 0;

    struct hid_device_info *root = NULL;
    struct hid_device_info *cur_dev = NULL;

    if (hid_init() < 0) {
        return NULL;
    }

    //cur_dev->next
    //cur_dev->path
    //cur_dev->serial_number
    //cur_dev->manufacturer_string
    //cur_dev->product_string
    //..let's ignore other stuff (report), needs attach..
    //cur_dev->vendor_id
    //cur_dev->product_id
    //cur_dev->release_number
    //cur_dev->interface_number

    PUSB_DK_DEVICE_INFO dkdevs;
    ULONG count;

    BOOL res0 = UsbDk_GetDevicesList(&dkdevs, &count);

    if (res0 != TRUE) {
        printf("UsbDk_GetDevicesList call FAILED - Is UsbDk installed?");
        return NULL;
    }

    for (i = 0; i < count; i++) {
        USB_DK_DEVICE_ID did = dkdevs[i].ID;
        
    }



}

void HID_API_EXPORT HID_API_CALL hid_free_enumeration(struct hid_device_info *devs)
{

}

HID_API_EXPORT hid_device * HID_API_CALL hid_open(unsigned short vendor_id, unsigned short product_id, const wchar_t *serial_number)
{

}

HID_API_EXPORT hid_device * HID_API_CALL hid_open_path(const char *path)
{

}

int HID_API_EXPORT HID_API_CALL hid_get_report_descriptor(hid_device *dev, unsigned char *data, size_t length)
{

}

int HID_API_EXPORT HID_API_CALL hid_write(hid_device *dev, const unsigned char *data, size_t length)
{

}

int HID_API_EXPORT HID_API_CALL hid_read_timeout(hid_device *dev, unsigned char *data, size_t length, int milliseconds)
{

}


int HID_API_EXPORT HID_API_CALL hid_read(hid_device *dev, unsigned char *data, size_t length)
{
	return hid_read_timeout(dev, data, length, (dev->blocking)? -1: 0);
}

int HID_API_EXPORT HID_API_CALL hid_set_nonblocking(hid_device *dev, int nonblock)
{
	dev->blocking = !nonblock;
	return 0; /* Success */
}

// return an event handle that can be used for poll/epoll/select etc
hid_handle_t HID_API_EXPORT HID_API_CALL hid_get_event_handle(hid_device *dev)
{
    return (hid_handle_t) dev->ol.hEvent;
}

int HID_API_EXPORT HID_API_CALL hid_send_feature_report(hid_device *dev, const unsigned char *data, size_t length)
{
	BOOL res = HidD_SetFeature(dev->device_handle, (PVOID)data, length);
	if (!res) {
		register_error(dev, "HidD_SetFeature");
		return -1;
	}

	return length;
}

int HID_API_EXPORT HID_API_CALL hid_get_feature_report(hid_device *dev, unsigned char *data, size_t length)
{

}


void HID_API_EXPORT HID_API_CALL hid_close(hid_device *dev)
{
	if (!dev)
		return;
	CancelIo(dev->device_handle);
	free_hid_device(dev);
}

int HID_API_EXPORT_CALL HID_API_CALL hid_get_manufacturer_string(hid_device *dev, wchar_t *string, size_t maxlen)
{
	BOOL res;

	res = HidD_GetManufacturerString(dev->device_handle, string, sizeof(wchar_t) * maxlen);
	if (!res) {
		register_error(dev, "HidD_GetManufacturerString");
		return -1;
	}

	return 0;
}

int HID_API_EXPORT_CALL HID_API_CALL hid_get_product_string(hid_device *dev, wchar_t *string, size_t maxlen)
{
	BOOL res;

	res = HidD_GetProductString(dev->device_handle, string, sizeof(wchar_t) * maxlen);
	if (!res) {
		register_error(dev, "HidD_GetProductString");
		return -1;
	}

	return 0;
}

int HID_API_EXPORT_CALL HID_API_CALL hid_get_serial_number_string(hid_device *dev, wchar_t *string, size_t maxlen)
{
	BOOL res;

	res = HidD_GetSerialNumberString(dev->device_handle, string, sizeof(wchar_t) * maxlen);
	if (!res) {
		register_error(dev, "HidD_GetSerialNumberString");
		return -1;
	}

	return 0;
}

int HID_API_EXPORT_CALL HID_API_CALL hid_get_indexed_string(hid_device *dev, int string_index, wchar_t *string, size_t maxlen)
{
	BOOL res;

	res = HidD_GetIndexedString(dev->device_handle, string_index, string, sizeof(wchar_t) * maxlen);
	if (!res) {
		register_error(dev, "HidD_GetIndexedString");
		return -1;
	}

	return 0;
}


HID_API_EXPORT const wchar_t * HID_API_CALL  hid_error(hid_device *dev)
{
	return (wchar_t*)dev->last_error_str;
}

HANDLE HID_API_EXPORT get_device_handle(hid_device *dev){
    return dev->device_handle;
}



#ifdef __cplusplus
} /* extern "C" */
#endif
