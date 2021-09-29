#include <node_api.h>
#include "main.c"

napi_value startGame(napi_env env, napi_callback_info info) 
{
  game();
  return NULL;
}

napi_value Init(napi_env env, napi_value exports) 
{
  napi_status status;
  napi_value fn;

  status = napi_create_function(env, "Start Snake Game", 15, startGame, NULL, &fn);
  
  status = napi_set_named_property(env, exports, "startGame", fn);

  return exports;
}


NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)




