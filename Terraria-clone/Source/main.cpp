#include "App.h"

int main() 
{
    Log::init();
    LOG_INFO("LOG initialized");
    LOG_INFO("APP try to create");
    auto app = new App;
    LOG_INFO("APP created");
    app->Run();
    delete app;
    LOG_INFO("APP destroyed");
}