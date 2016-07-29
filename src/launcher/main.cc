#ifndef AVA$
#   include <stdio.h>
#   define AVA$ //puts(__PRETTY_FUNCTION__);
#endif
#ifndef __PRETTY_FUNCTION__
#   define __PRETTY_FUNCTION__ __FUNCTION__
#endif


#ifdef _WIN32
#   include <winsock2.h>
#   define DLL                  HMODULE
#   define dlopen(name,mode)    LoadLibraryA( name )
#   define dlsym(handle,symbol) GetProcAddress( handle, symbol )
#   define dlclose(handle)      0
#else
#   include <dlfcn.h>
#   define DLL void*
#endif
DLL plugins[32] = {0};
static bool av_symload(int plug_id, const char *filename) { AVA$
    return plugins[plug_id] = dlopen(filename, RTLD_NOW | RTLD_LOCAL);
}
static void *av_symlookup(int plug_id, const char *name) { AVA$
    return dlsym(plugins[plug_id], name);
}
static void av_symclose(int plug_id) { AVA$
    dlclose(plugins[plug_id]);
}


extern "C"
void av_hello_(const char *str) { AVA$
    puts( "hello static world" );
};


extern "C"
void (*av_hello)(const char *str) = av_hello_;
//---
void *av_vtbl[] = {
    "av_hello", &av_hello, av_hello, // name: addr -> alias
    0
};
#include <string.h>
static void av_hotpatch( const char *name, void *ptr ) { AVA$ // 0=all, 0=restore
    for( int i = 0; av_vtbl[i]; i+=3 ) {
        if( !name || !strcmpi((const char *)av_vtbl[i], name) ) {
            printf("hot patch '%s'...\n", av_vtbl[i]);
            *(void **)av_vtbl[1] = ptr ? ptr : av_vtbl[2];
        }
    }
}
#include <stdio.h>
static int av_hotpatch( const void **vtable ) { AVA$
    for( int i = 0; ; i += 2 ) {
        if( !vtable[i] ) break;
        const char *key = (const char *)vtable[i+0];
        const char *value = (const char *)vtable[i+1];
        if( key[0] == 'a' && key[1] == 'v' && key[2] == '_' ) {
            av_hotpatch( key, (void *)vtable[i+1] );
        } else {
            printf("\t%s: %s\n", key, value);
        }
    }
    return 1;
}

static int av_plug(const char *filename) { AVA$
    if( av_symload(0, filename) ) {
        if( const void **vtable = (const void **)av_symlookup(0, "av_crt") ) {
            puts("AVA plugin found");
            return av_hotpatch( vtable );
        }
        av_symclose(0);
    }
    return 0;
}

int main() { AVA$
    int plug0 = av_plug("avDllPlayer.dll");
    printf("plugged (avDllPlayer.dll)? %d\n", plug0 );
    av_hello("");

    int plug1 = av_plug("avDllEditor.dll");
    printf("plugged (avDllEditor.dll)? %d\n", plug1 );
    av_hello("");

    int plug2 = av_plug("avDllGame.dll");
    printf("plugged (avDllGame.dll)? %d\n", plug2 );
    av_hello("");

    av_hotpatch("av_hello", 0);
    av_hello("");

    int replug = av_plug("avDllGame.dll");
    printf("plugged (avDllGame.dll)? %d\n", replug );
    av_hello("");

    av_hotpatch(0, 0);
    av_hello("");
}
