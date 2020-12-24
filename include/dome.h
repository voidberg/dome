/* DOME Plugin Header v0.0.1 */

#ifndef DOME_PLUGIN_H
#define DOME_PLUGIN_H


// Define DOME_EXPORTED for any platform
#if defined _WIN32 || defined __CYGWIN__
  #ifdef WIN_EXPORT
    // Exporting...
    #ifdef __GNUC__
      #define DOME_EXPORTED __attribute__ ((dllexport))
    #else
      #define DOME_EXPORTED __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define DOME_EXPORTED __attribute__ ((dllimport))
    #else
      #define DOME_EXPORTED __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DOME_NOT_EXPORTED
#else
  #if __GNUC__ >= 4
    #define DOME_EXPORTED __attribute__ ((visibility ("default")))
    #define DOME_NOT_EXPORTED  __attribute__ ((visibility ("hidden")))
  #else
    #define DOME_EXPORTED
    #define DOME_NOT_EXPORTED
  #endif
#endif

typedef struct DOME_Context DOME_Context;
typedef enum {
  DOME_RESULT_SUCCESS,
  DOME_RESULT_FAILURE,
  DOME_RESULT_UNKNOWN
} DOME_Result;

typedef DOME_Result (*DOME_VM_Handler) (DOME_Context* context);

#define internal static
#define DOME_PLUGIN_init(ctx) \
  DOME_EXPORTED internal DOME_Result DOME_hookOnInit(DOME_Context* ctx)


DOME_EXPORTED void DOME_test();

#endif