#include "trpch.h"
#include "App.h"

int main() 
{
    std::srand(time(NULL));
    Log::init();
    LOG_INFO("LOG initialized");
    auto app = new App;
    LOG_INFO("APP created");
    app->Run();
    delete app;
    LOG_INFO("APP destroyed");
}