#include <stdio.h>
#include <stdbool.h>
#include "dome.h"

static DOME_API_v0* api;
static WREN_API_v0* wren;

static size_t i;
static bool flag = false;
static const char* source = "class Test {\n"
                  "static begin() { System.print(\"Begun!\") }\n"
                  "foreign static end(value)\n"
                  "foreign static empty\n"
                  "foreign static boolean\n"
                  "foreign static number\n"
                  "foreign static string\n"
                  "foreign static bytes\n"
                  "}";

DOME_PLUGIN_method(end, ctx) {
  flag = GET_BOOL(1);
  RETURN_BOOL(flag);
};

DOME_PLUGIN_method(value, ctx) {
  RETURN_NUMBER(i);
}
DOME_PLUGIN_method(text, ctx) {
  RETURN_STRING("WORDS");
}
DOME_PLUGIN_method(empty, ctx) {
  RETURN_NULL();
}
DOME_PLUGIN_method(boolean, ctx) {
  RETURN_BOOL(flag);
}
DOME_PLUGIN_method(bytes, ctx) {
  char bytes[6] = { 65, 66, 67, 68, 69, 70 };
  RETURN_BYTES(bytes, (i / 60) < 5 ? (i / 60) : 5);
}

WrenForeignClassMethods DOME_PLUGIN_bind(const char* className) {
  WrenForeignClassMethods methods;
  if (strcmp(className, "Test") == 0) {
    methods.allocate = NULL;
    methods.finalize = NULL;
  }
  return NULL;
}

DOME_PLUGIN_init(DOME_getApi, ctx) {

  api = DOME_getApi(API_DOME, DOME_API_VERSION);
  wren = DOME_getApi(API_WREN, WREN_API_VERSION);

  printf("init hook triggered\n");
  i = 0;
  DOME_registerModule(ctx, "external", source);
  DOME_registerBindFn(ctx, "external", DOME_PLUGIN_bind);
  DOME_registerFn(ctx, "external", "static Test.end(_)", end);
  DOME_registerFn(ctx, "external", "static Test.number", value);
  DOME_registerFn(ctx, "external", "static Test.string", text);
  DOME_registerFn(ctx, "external", "static Test.boolean", boolean);
  DOME_registerFn(ctx, "external", "static Test.empty", empty);
  DOME_registerFn(ctx, "external", "static Test.bytes", bytes);
  return DOME_RESULT_SUCCESS;
}
DOME_PLUGIN_shutdown(ctx) {
  printf("shutdown hook triggered\n");
  return DOME_RESULT_SUCCESS;
}

DOME_PLUGIN_preupdate(ctx) {
  i++;
  return DOME_RESULT_SUCCESS;
}


/*
DOME_PLUGIN_postupdate(ctx) {
  printf("postpdate hook triggered\n");
}
DOME_PLUGIN_predraw(ctx) {
  printf("predraw hook triggered\n");
}
DOME_PLUGIN_postdraw(ctx) {
  printf("postdraw hook triggered\n");
}
*/