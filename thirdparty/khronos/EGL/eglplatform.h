#ifndef __eglplatform_h_
#define __eglplatform_h_

/*
** Copyright 2007-2020 The Khronos Group Inc.
** SPDX-License-Identifier: Apache-2.0
*/

/* Platform-specific types and definitions for egl.h
 *
 * Adopters may modify khrplatform.h and this file to suit their platform.
 * You are encouraged to submit all modifications to the Khronos group so that
 * they can be included in future versions of this file.  Please submit changes
 * by filing an issue or pull request on the public Khronos EGL Registry, at
 * https://www.github.com/KhronosGroup/EGL-Registry/
 */

#include <KHR/khrplatform.h>

/* Macros used in EGL function prototype declarations.
 *
 * EGL functions should be prototyped as:
 *
 * EGLAPI return-type EGLAPIENTRY eglFunction(arguments);
 * typedef return-type (EXPAPIENTRYP PFNEGLFUNCTIONPROC) (arguments);
 *
 * KHRONOS_APICALL and KHRONOS_APIENTRY are defined in KHR/khrplatform.h
 */

#ifndef EGLAPI
#define EGLAPI KHRONOS_APICALL
#endif

#ifndef EGLAPIENTRY
#define EGLAPIENTRY  KHRONOS_APIENTRY
#endif
#define EGLAPIENTRYP EGLAPIENTRY*

/* The types NativeDisplayType, NativeWindowType, and NativePixmapType
 * are aliases of window-system-dependent types, such as X Display * or
 * Windows Device Context. They must be defined in platform-specific
 * code below. The EGL-prefixed versions of Native*Type are the same
 * types, renamed in EGL 1.3 so all types in the API start with "EGL".
 *
 * Khronos STRONGLY RECOMMENDS that you use the default definitions
 * provided below, since these changes affect both binary and source
 * portability of applications using EGL running on different EGL
 * implementations.
 */

#if defined(EGL_NO_PLATFORM_SPECIFIC_TYPES)

typedef void *EGLNativeDisplayType;
typedef void *EGLNativePixmapType;
typedef void *EGLNativeWindowType;

#elif defined(_WIN32) || defined(__VC32__) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__) /* Win32 and WinCE */
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>

typedef HDC     EGLNativeDisplayType;
typedef HBITMAP EGLNativePixmapType;
typedef HWND    EGLNativeWindowType;

#elif defined(__QNX__)

typedef khronos_uintptr_t      EGLNativeDisplayType;
typedef struct _screen_pixmap* EGLNativePixmapType;  /* screen_pixmap_t */
typedef struct _screen_window* EGLNativeWindowType;  /* screen_window_t */

#elif defined(__EMSCRIPTEN__)

typedef int EGLNativeDisplayType;
typedef int EGLNativePixmapType;
typedef int EGLNativeWindowType;

#elif defined(__WINSCW__) || defined(__SYMBIAN32__)  /* Symbian */

typedef int   EGLNativeDisplayType;
typedef void *EGLNativePixmapType;
typedef void *EGLNativeWindowType;

#elif defined(WL_EGL_PLATFORM)

typedef struct wl_display     *EGLNativeDisplayType;
typedef struct wl_egl_pixmap  *EGLNativePixmapType;
typedef struct wl_egl_window  *EGLNativeWindowType;

#elif defined(__GBM__)

typedef struct gbm_device  *EGLNativeDisplayType;
typedef struct gbm_bo      *EGLNativePixmapType;
typedef void               *EGLNativeWindowType;

#elif defined(__ANDROID__) || defined(ANDROID)

struct ANativeWindow;
struct egl_native_pixmap_t;

typedef void*                           EGLNativeDisplayType;
typedef struct egl_native_pixmap_t*     EGLNativePixmapType;
typedef struct ANativeWindow*           EGLNativeWindowType;

#elif defined(USE_OZONE)

typedef intptr_t EGLNativeDisplayType;
typedef intptr_t EGLNativePixmapType;
typedef intptr_t EGLNativeWindowType;
#elif (defined(__psp2__) || defined(__vita__))

typedef enum Psp2DrawableType
{
	PSP2_DRAWABLE_TYPE_UNKNOWN,
	PSP2_DRAWABLE_TYPE_WINDOW,
	PSP2_DRAWABLE_TYPE_PIXMAP
} Psp2DrawableType;

typedef enum Psp2WindowSize
{
	PSP2_WINDOW_960X544,
	PSP2_WINDOW_480X272,
	PSP2_WINDOW_640X368,
	PSP2_WINDOW_720X408,
	PSP2_WINDOW_1280X725,
	PSP2_WINDOW_1920X1088
} Psp2WindowSize;
typedef enum VitaEGLNativeWindow {
    VITA_INVALID_WINDOW = 0,
    VITA_WINDOW_960X544,
    VITA_WINDOW_720X408,
    VITA_WINDOW_640X368,
    VITA_WINDOW_480X272,
    VITA_WINDOW_1280X720,
    VITA_WINDOW_1920X1080
} woew;
typedef struct Psp2NativeWindow
{
	unsigned int type;
	unsigned int windowSize;
	unsigned int numFlipBuffers;
	unsigned int flipChainThrdAffinity;

	unsigned int swapChainId;
	void *swapChain;
	void *psConnection;
	unsigned int ahSwapChainBuffers[4]; //PSP2_SWAPCHAIN_MAX_BUFFER_NUM
	void *apsSwapBufferMemInfo[4]; //PSP2_SWAPCHAIN_MAX_BUFFER_NUM
	void *psDevData;
	unsigned int hDevMemContext;
	unsigned int currBufIdx;
	unsigned int swapInterval;
} Psp2NativeWindow;

typedef struct Psp2NativePixmap
{
	Psp2DrawableType type;
	unsigned int sizeX;
	unsigned int sizeY;
	unsigned int memType;

	int memUID;
	void *memBase;
	void *psDevData;
	unsigned int hDevMemContext;
} Psp2NativePixmap;

typedef int	EGLNativeDisplayType;
typedef Psp2NativeWindow *EGLNativeWindowType;
typedef Psp2NativePixmap *EGLNativePixmapType;

#elif defined(USE_X11)

/* X11 (tentative)  */
#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef Display *EGLNativeDisplayType;
typedef Pixmap   EGLNativePixmapType;
typedef Window   EGLNativeWindowType;

#elif defined(__unix__)

typedef void             *EGLNativeDisplayType;
typedef khronos_uintptr_t EGLNativePixmapType;
typedef khronos_uintptr_t EGLNativeWindowType;

#elif defined(__APPLE__) || defined(__QNXNTO__)

typedef int   EGLNativeDisplayType;
typedef void *EGLNativePixmapType;
typedef void *EGLNativeWindowType;

#elif defined(__HAIKU__)

#include <kernel/image.h>

typedef void              *EGLNativeDisplayType;
typedef khronos_uintptr_t  EGLNativePixmapType;
typedef khronos_uintptr_t  EGLNativeWindowType;

#elif defined(__Fuchsia__)

typedef void              *EGLNativeDisplayType;
typedef khronos_uintptr_t  EGLNativePixmapType;
typedef khronos_uintptr_t  EGLNativeWindowType;

#else
#error "Platform not recognized"
#endif

/* EGL 1.2 types, renamed for consistency in EGL 1.3 */
typedef EGLNativeDisplayType NativeDisplayType;
typedef EGLNativePixmapType  NativePixmapType;
typedef EGLNativeWindowType  NativeWindowType;


/* Define EGLint. This must be a signed integral type large enough to contain
 * all legal attribute names and values passed into and out of EGL, whether
 * their type is boolean, bitmask, enumerant (symbolic constant), integer,
 * handle, or other.  While in general a 32-bit integer will suffice, if
 * handles are 64 bit types, then EGLint should be defined as a signed 64-bit
 * integer type.
 */
typedef khronos_int32_t EGLint;


/* C++ / C typecast macros for special EGL handle values */
#if defined(__cplusplus)
#define EGL_CAST(type, value) (static_cast<type>(value))
#else
#define EGL_CAST(type, value) ((type) (value))
#endif

#endif /* __eglplatform_h */
