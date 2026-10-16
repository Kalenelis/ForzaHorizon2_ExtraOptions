#include "runtime.h"
#include "support.h"

#define DXGI_E_FAIL ((HRESULT)0x80004005L)

typedef HRESULT (WINAPI *PFN_CreateDXGIFactory)(const void *riid, void **ppFactory);
typedef HRESULT (WINAPI *PFN_CreateDXGIFactory1)(const void *riid, void **ppFactory);
typedef HRESULT (WINAPI *PFN_CreateDXGIFactory2)(UINT Flags, const void *riid, void **ppFactory);
typedef HRESULT (WINAPI *PFN_DXGIDeclareAdapterRemovalSupport)(void);
typedef HRESULT (WINAPI *PFN_DXGIDumpLiveObjects)(void *pDXGIHandle, int Flags);
typedef HRESULT (WINAPI *PFN_DXGIGetDebugInterface1)(UINT Flags, const void *riid, void **pDebug);
typedef HRESULT (WINAPI *PFN_DXGIReportAdapterConfiguration)(void *pContext);

static HMODULE g_real_dxgi = NULL;
static PFN_CreateDXGIFactory pfn_CreateDXGIFactory = NULL;
static PFN_CreateDXGIFactory1 pfn_CreateDXGIFactory1 = NULL;
static PFN_CreateDXGIFactory2 pfn_CreateDXGIFactory2 = NULL;
static PFN_DXGIDeclareAdapterRemovalSupport pfn_DXGIDeclareAdapterRemovalSupport = NULL;
static PFN_DXGIDumpLiveObjects pfn_DXGIDumpLiveObjects = NULL;
static PFN_DXGIGetDebugInterface1 pfn_DXGIGetDebugInterface1 = NULL;
static PFN_DXGIReportAdapterConfiguration pfn_DXGIReportAdapterConfiguration = NULL;

static void load_real_dxgi(void) {
    if (g_real_dxgi) {
        return;
    }
    static wchar_t sys_dir[PATH_CAPACITY];
    UINT len = GetSystemDirectoryW(sys_dir, MAX_PATH);
    if (!len || len >= MAX_PATH - 15) {
        return;
    }
    static wchar_t dxgi_path[PATH_CAPACITY];
    if (!path_join(dxgi_path, sys_dir, L"dxgi.dll")) {
        return;
    }

    g_real_dxgi = LoadLibraryW(dxgi_path);
    if (!g_real_dxgi) {
        return;
    }

    pfn_CreateDXGIFactory = (PFN_CreateDXGIFactory)(void *)GetProcAddress(g_real_dxgi, "CreateDXGIFactory");
    pfn_CreateDXGIFactory1 = (PFN_CreateDXGIFactory1)(void *)GetProcAddress(g_real_dxgi, "CreateDXGIFactory1");
    pfn_CreateDXGIFactory2 = (PFN_CreateDXGIFactory2)(void *)GetProcAddress(g_real_dxgi, "CreateDXGIFactory2");
    pfn_DXGIDeclareAdapterRemovalSupport = (PFN_DXGIDeclareAdapterRemovalSupport)(void *)GetProcAddress(g_real_dxgi, "DXGIDeclareAdapterRemovalSupport");
    pfn_DXGIDumpLiveObjects = (PFN_DXGIDumpLiveObjects)(void *)GetProcAddress(g_real_dxgi, "DXGIDumpLiveObjects");
    pfn_DXGIGetDebugInterface1 = (PFN_DXGIGetDebugInterface1)(void *)GetProcAddress(g_real_dxgi, "DXGIGetDebugInterface1");
    pfn_DXGIReportAdapterConfiguration = (PFN_DXGIReportAdapterConfiguration)(void *)GetProcAddress(g_real_dxgi, "DXGIReportAdapterConfiguration");
}

__declspec(dllexport) HRESULT WINAPI CreateDXGIFactory(const void *riid, void **ppFactory) {
    load_real_dxgi();
    if (!pfn_CreateDXGIFactory) return DXGI_E_FAIL;
    return pfn_CreateDXGIFactory(riid, ppFactory);
}

__declspec(dllexport) HRESULT WINAPI CreateDXGIFactory1(const void *riid, void **ppFactory) {
    load_real_dxgi();
    if (!pfn_CreateDXGIFactory1) return DXGI_E_FAIL;
    return pfn_CreateDXGIFactory1(riid, ppFactory);
}

__declspec(dllexport) HRESULT WINAPI CreateDXGIFactory2(UINT Flags, const void *riid, void **ppFactory) {
    load_real_dxgi();
    if (!pfn_CreateDXGIFactory2) return DXGI_E_FAIL;
    return pfn_CreateDXGIFactory2(Flags, riid, ppFactory);
}

__declspec(dllexport) HRESULT WINAPI DXGIDeclareAdapterRemovalSupport(void) {
    load_real_dxgi();
    if (!pfn_DXGIDeclareAdapterRemovalSupport) return DXGI_E_FAIL;
    return pfn_DXGIDeclareAdapterRemovalSupport();
}

__declspec(dllexport) HRESULT WINAPI DXGIDumpLiveObjects(void *pDXGIHandle, int Flags) {
    load_real_dxgi();
    if (!pfn_DXGIDumpLiveObjects) return DXGI_E_FAIL;
    return pfn_DXGIDumpLiveObjects(pDXGIHandle, Flags);
}

__declspec(dllexport) HRESULT WINAPI DXGIGetDebugInterface1(UINT Flags, const void *riid, void **pDebug) {
    load_real_dxgi();
    if (!pfn_DXGIGetDebugInterface1) return DXGI_E_FAIL;
    return pfn_DXGIGetDebugInterface1(Flags, riid, pDebug);
}

__declspec(dllexport) HRESULT WINAPI DXGIReportAdapterConfiguration(void *pContext) {
    load_real_dxgi();
    if (!pfn_DXGIReportAdapterConfiguration) return DXGI_E_FAIL;
    return pfn_DXGIReportAdapterConfiguration(pContext);
}

__declspec(dllexport) const char *Fh2TweaksStatus(void) {
    return status_get();
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved) {
    (void)reserved;
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(instance);
        load_real_dxgi();
        adapter_process_attach(instance);
    } else if (reason == DLL_PROCESS_DETACH) {
        if (g_real_dxgi) {
            FreeLibrary(g_real_dxgi);
            g_real_dxgi = NULL;
        }
    }
    return TRUE;
}
