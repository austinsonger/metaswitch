// device_enumeration.c
#include "device_enumeration.h"
#include <windows.h>
#include <dshow.h>
#include <stdio.h>

#pragma comment(lib, "Strmiids.lib")
#pragma comment(lib, "Ole32.lib")

void EnumerateDevices(void) {
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        printf("Failed to initialize COM library. Error code = 0x%x\n", hr);
        return;
    }

    ICreateDevEnum *pDevEnum = NULL;
    IEnumMoniker *pEnum = NULL;

    hr = CoCreateInstance(&CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, &IID_ICreateDevEnum, (void **)&pDevEnum);
    if (FAILED(hr)) {
        printf("Failed to create device enumerator. Error code = 0x%x\n", hr);
        CoUninitialize();
        return;
    }

    hr = pDevEnum->lpVtbl->CreateClassEnumerator(pDevEnum, &CLSID_VideoInputDeviceCategory, &pEnum, 0);
    if (hr == S_FALSE) {
        printf("No devices found.\n");
        pDevEnum->lpVtbl->Release(pDevEnum);
        CoUninitialize();
        return




