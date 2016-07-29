#include <stdio.h>

#ifdef _WIN32
#define AV_EXPORT extern "C" __declspec(dllexport)
#else
#define AV_EXPORT extern "C"
#endif

static
void override_av_hello( const char *text ) {
    puts("hello dynamic world");
}

AV_EXPORT
void *av_crt[] = {
    "apiVersion", "100",
    "fileName", "main.cc",
    "className", "helloclass",
    "classBase", "hellobase",
    "pluginURL", "https://github.com/r-lyeh/AVA",
    "pluginVersion", "1.0.0",
    "pluginAuthor", "r-lyeh",
    "pluginLicense", "public domain",
    "pluginDependencies", "{}",
    "av_hello", override_av_hello,
    (void*)0
};
