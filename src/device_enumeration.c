#include "device_enumeration.h"
#include <windows.h>
#include <dshow.h>
#include <obs-module.h>

// Helper function to log device names (or handle them as needed)
static void LogDeviceName(IMoniker *pMoniker) {
    IPropertyBag *pPropBag;
    HRESULT hr = pMoniker->BindToStorage(0, 0, IID_PPV_ARGS(&pPropBag));
    if (FAILED(hr)) {
        return;
    }

    VARIANT var;
    VariantInit(&var);

    // Get the description or friendly name.
    hr = pPropBag->Read(L"Description", &var, 0);
    if (FAILED(hr)) {
        hr = pPropBag->Read(L"FriendlyName", &var, 0);
    }
    if (SUCCEEDED(hr)) {
        // Log the device name
        wchar_t *name = var.bstrVal;
        blog(LOG_INFO, "Found device: %ls", name);
        VariantClear(&var);
    }

    pPropBag->Release();
}

void EnumerateVideoCaptureDevices(void) {
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (SUCCEEDED(hr)) {
        ICreateDevEnum *pDevEnum;
        hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void **)&pDevEnum);
        if (SUCCEEDED(hr)) {
            IEnumMoniker *pEnum;
            hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, 0);
            if (hr == S_OK) {
                IMoniker *pMoniker = NULL;
                while (pEnum->Next(1, &pMoniker, NULL) == S_OK) {
                    LogDeviceName(pMoniker);
                    pMoniker->Release();
                }
                pEnum->Release();
            }
            pDevEnum->Release();
        }
        CoUninitialize();
    }
}
