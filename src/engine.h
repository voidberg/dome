// Forward-declaring some methods for interacting with the AudioEngine
// for managing memory and initialization
struct AUDIO_ENGINE_t;
internal struct AUDIO_ENGINE_t* AUDIO_ENGINE_init(void);
internal void AUDIO_ENGINE_free(struct AUDIO_ENGINE_t*);

typedef struct {
  int64_t x;
  int64_t y;
  int64_t w;
  int64_t h;
} DOME_RECT;

typedef struct {
  bool relative;
  int x;
  int y;
  int scrollX;
  int scrollY;
} ENGINE_MOUSE_STATE;

typedef struct {
  double avgFps;
  double alpha;
  int32_t elapsed;
  FILE* logFile;
  size_t errorBufLen;
  size_t errorBufMax;
  char* errorBuf;
} ENGINE_DEBUG;

typedef struct {
  bool makeGif;
  uint32_t* gifPixels;
  volatile bool frameReady;
  char* gifName;
} ENGINE_RECORDER;

typedef struct {
  size_t height;
  size_t width;
  uint32_t* pixels;
} PIXEL_BUFFER;

typedef struct {
  void* pixels;
  uint32_t width;
  uint32_t height;
  int32_t offsetX;
  int32_t offsetY;
  DOME_RECT clip;
} CANVAS;

typedef struct ENGINE_t {
  ENGINE_RECORDER record;
  SDL_Window* window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  SDL_Rect viewport;
  CANVAS canvas;
  PIXEL_BUFFER blitBuffer;
  ABC_FIFO fifo;
  MAP moduleMap;
  // PLUGIN_MAP pluginMap;
  PLUGIN_COLLECTION plugins;
  mtar_t* tar;
  bool running;
  char** argv;
  size_t argc;
  bool lockstep;
  ENGINE_MOUSE_STATE mouse;
  int exit_status;
  struct AUDIO_ENGINE_t* audioEngine;
  bool initialized;
  bool debugEnabled;
  bool vsyncEnabled;
  ENGINE_DEBUG debug;
} ENGINE;


typedef enum {
  EVENT_NOP,
  EVENT_LOAD_FILE,
  EVENT_WRITE_FILE,
  EVENT_WRITE_FILE_APPEND
} EVENT_TYPE;

typedef enum {
  TASK_NOP,
  TASK_PRINT,
  TASK_LOAD_FILE,
  TASK_WRITE_FILE,
  TASK_WRITE_FILE_APPEND
} TASK_TYPE;

typedef enum {
  ENGINE_WRITE_SUCCESS,
  ENGINE_WRITE_PATH_INVALID
} ENGINE_WRITE_RESULT;

global_variable uint32_t ENGINE_EVENT_TYPE;

