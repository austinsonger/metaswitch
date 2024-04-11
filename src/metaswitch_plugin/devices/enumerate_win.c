// devices/enumerate_win.c
#include <stdio.h>
#include <dshow.h>
#pragma comment(lib, "strmiids.lib")  // Link against the DirectShow library

void enumerate_devices() {
    HRESULT hr;
    ICreateDevEnum *pSysDevEnum = NULL;
    IEnumMoniker *pEnumCat = NULL;
    IMoniker *pMoniker = NULL;

    printf("Enumerating video capture devices on Windows...\n");

    // Initialize COM library
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (SUCCEEDED(hr)) {
        // Create a System Device Enumerator
        hr = CoCreateInstance(&CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
                              &IID_ICreateDevEnum, (void **)&pSysDevEnum);
        if (SUCCEEDED(hr)) {
            // Obtain a class enumerator for the video input device category
            hr = pSysDevEnum->lpVtbl->CreateClassEnumerator(pSysDevEnum, &CLSID_VideoInputDeviceCategory,
                                                            &pEnumCat, 0);
            if (SUCCEEDED(hr) && pEnumCat != NULL) {
                // Enumerate devices
                while (pEnumCat->lpVtbl->Next(pEnumCat, 1, &pMoniker, NULL) == S_OK) {
                    IPropertyBag *pPropBag;
                    hr = pMoniker->lpVtbl->BindToStorage(pMoniker, NULL, NULL,
                                                         &IID_IPropertyBag, (void **)&pPropBag);
                    if (SUCCEEDED(hr)) {
                        VARIANT varName;
                        VariantInit(&varName);
                        hr = pPropBag->lpVtbl->Read(pPropBag, L"FriendlyName", &varName, 0);
                        if (SUCCEEDED(hr)) {
                            printf("Found device: %ls\n", varName.bstrVal);
                        }
                        VariantClear(&varName);
                        pPropBag->lpVtbl->Release(pPropBag);
                    }
                    pMoniker->lpVtbl->Release(pMoniker);
                }
            } else {
                printf("No devices found.\n");
            }
            if (pEnumCat != NULL) {
                pEnumCat->lpVtbl->Release(pEnumCat);
            }
        }
        pSysDevEnum->lpVtbl->Release(pSysDevEnum);
    }
    CoUninitialize();
}
