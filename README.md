# ΛVΛ <a href="https://travis-ci.org/r-lyeh/AVA"><img src="https://api.travis-ci.org/r-lyeh/AVA.svg?branch=master" align="right" /></a> <a href="https://www.quantifiedcode.com/app/project/7fc9dc58fa9441238223c803f63cfe7e"><img src="https://www.quantifiedcode.com/api/v1/project/7fc9dc58fa9441238223c803f63cfe7e/badge.svg" alt="Code issues" align="right" /></a> <a href="http://unlicense.org/"><img src="http://img.shields.io/badge/license-Unlicense-blue.svg?style=flat" alt="Unlicensed" align="right" /></a>

A tiny 3D game engine in C++, with C and Lua interfaces. Written in 32 random ~~days~~ ~~months~~ years.

My very last attempt at creating a full game engine in a (jam) rush.

## Features and dogmas
- [x] 100% free and unencumbered [public domain](http://unlicense.org/) software, usable in any context and for any purpose.
- [x] No build prerequisites beyond a decent compiler.
- [x] Open specification: featuring a free, open-source game-engine API in the header.
- [x] Open implementation: reference implementation is tidy, tiny, free and open-source.
- [x] Useable: C-Linkage ABI. Use it everywhere.
- [x] Lightweight: no deps, no boost, minimal STL subset.
- [x] Orthodox C++: no rtti (typeid), no exceptions thrown.
- [x] Embedded C++: no mutables, no style_casts<>, no virtuals, no multiple inheritance.
- [x] Simple: using the simplest implementation for each task.
- [x] Manageable: almost flat disk layout, spacewise, and logical data pipeline.
- [x] Modular: plugins, scripts, every native function API is overridable.
- [x] Data-driven: JSON flow, still mergeable, still human-readable.
- [x] Consistency everywhere: return codes, output format, naming, convenions, etc...
- [x] Extendable: native C, native C++, scripted Lua or your favourite scripting engine.
- [x] Heap allocations under control.

## Disk structure (click the arrows below)
<details><summary>:open_file_folder:`art/`, uncooked assets.</summary>
</details>
<details><summary>:open_file_folder:`bin/`, binary tools.</summary>
</details>
<details><summary>:open_file_folder:`doc/`, documentation.</summary>
</details>
<details><summary>:open_file_folder:`ide/`, ide project files.</summary>
</details>
<details><summary>:open_file_folder:`lib/`, library addons.</summary>
</details>
<details><summary>:open_file_folder:`pkg/`, packaged binaries.</summary>
</details>
<details><summary>:open_file_folder:`pub/`, public served content.</summary>
<details><summary>:open_file_folder:` \- 8080/`, web service at localhost:8080</summary>
</details>
</details>
<details><summary>:open_file_folder:`res/`, resources to embed.</summary>
</details>
<details><summary>:open_file_folder:`src/`, source code.</summary>
<details><summary>:open_file_folder:` +- 3rd/`, third-party free-standing common libraries.</summary>
</details>
<details><summary>:open_file_folder:` +- editor/`, editor source code.</summary>
</details>
<details><summary>:open_file_folder:` +- engine/`, engine source code.</summary>
</details>
<details><summary>:open_file_folder:` +- launcher/`, launcher source code.</summary>
</details>
<details><summary>:open_file_folder:` +- game/`, blank game template.</summary>
</details>
<details><summary>:open_file_folder:` \- tutorial/`, tutorial source code.</summary>
</details>
</details>
<details><summary>:open_file_folder:`tmp/`, temporary directory.</summary>
</details>
<details><summary>:open_file_folder:`usr/`, overridable user content.</summary>
<details><summary>:open_file_folder:` +- gid/`, group ID based content overrides.</summary>
</details>
<details><summary>:open_file_folder:` \- uid/`, user ID based content overrides.</summary>
</details>
</details>
<details><summary>:open_file_folder:`wrk/`, working directory.</summary>
</details>

## Code structure
<details><summary>Coding convention</summary>
## Macros
```c++
         +-----------------> bind, namespace: `AVA` always
         |  +--------------> nouns, uppercased, underscore separated
         |  |
#define AVA_VERSION        "0.0.0"
```

## Enums
```c++
      +-----------------------> bind, namespace: `AV` always
      |  +--------------------> enum, namespace: uppercase always, no underscore separator
      |  |          +---------> zero, reserved for invalid enumerations
enum AVMESSAGE {    |     +---> size, a list size entry is added as well
      AVMESSAGE_INVALID, |
      AVMESSAGE_1,       |
      AVMESSAGE_2,       |
      AVMESSAGE_TOTAL ---+
};
```

## API style
Every API function:
```c++
+-------------------------------------------> code: error (if <0), ok (if ==0), ok and id (if >0)
|     +-------------------------------------> bind, namespace: `av` always
|     | +-----------------------------------> noun, subsystem: network, disk, memory...
|     | |      +----------------------------> verb, action, imperative: get, set, update...
|     | |      |       +--------------------> args, mutable output args first (if any)
|     | |      |       |                 +--> args, const input args later (if any)
|     | |      |       |                 |
int64 avNetworkEncode( std::string *out, const std::string &input );
```

## Return codes
Every return code:
```c++
Negative return codes are ERRORCODEs.
Positive return codes are IDENTIFIERs.

int64_t code = avAPISomeFunction();
if( code  < 0 ) { /* error            */ } 
if( code == 0 ) { /* ok, no handle id */ } 
if( code  > 0 ) { /* ok and handle id */ } 
```

## Data style
Every data struct:
```c++
          +------------------> type, plain public structs
          |     +------------> bind, namespace: `av` always
          |     |  +---------> noun, single noun, shorter forms preferred (uppercase acronyms too)
          |     |  |    +----> name, members have no prefixes (no m_, g_, etc...)
          |     |  |    |
typedef struct avRGB {  |
   uint8_t r,g,b,a; ----+
} avRGB;
```

## Comments style
- `C` style comments /**/.
- `!` prefix for important notes.
- `>` prefix for code quotes.
```c++
/* Chop any token word starting at 'src', delimited by characters in the string
 * 'delim', and store up to 'avail' pairs of pointers to char* 'tokens' and
 * strlens 'sizes' respectively.
!* Returns zero if done, or -1 if more pairs are needed.
!* Does not validate arguments.
 * 
>* const char *str = "There is a lady who's sure, all that glitter is gold...";
>* const char *tokens[128]; int sizes[128];
>* printf("errorcode: %d\n", strchop( tokens, sizes, 128, str, " ,." ));
>* for( int i = 0; tokens[i]; ++i ) {
>* printf("'%.*s'\n", sizes[i], tokens[i]);
>* }
 */
int avStrChop( const char **tokens, int *sizes, int avail, const char *src, const char *delim );
```

## Extending API
Every API call is overridable:
```c++
// This is a direct API call
avStrPuts("hello");

// This is an overloaded API call
avStrPuts = []() -> int {
puts(";; Hello overloaded!");
return 0;
};
avStrPuts("hello");

// This is an overloaded API call, with super call invoked
static auto super = avStrPuts;
avStrPuts = []() -> int {
puts(";; Hello overloaded #2 {");
super();
puts(";; } ---");
return 0;
};
avStrPuts("hello");

// And if you need to retrieve the real API call address...
printf("addr:%p\n", &avStrPuts); // real API call ID
```

## Logging
Every log line:
```c++
;; Double semi-colons: comment from engine.
; Single semi-colons: comment from application.
No semi-colons: standard output from application.
```

## Timestamps
Every timestamp is a 64-bit, base10 number:
```
18446744073709551615
0YYYMMDDhhmmssuuuuuu uuu,uuu = microseconds
18446744073709551615
1TTTTYYMMDDhhmmssxxx TT:TT = timezone, xxx = milliseconds
```

## Packages
- launcher.osx
- launcher.linux
- launcher.exe
- launcher.pak
- game.dll
- game.pak

## Addons
```c++
lib/avxSplash.zip {
- splash/index.json
- splash/3rd/glfw/glfw.sources.cc
- splash/api/splash.h
- splash/art/tex/banner.png
- splash/art/snd/bing.wav
- splash/lib/init.lua
- splash/doc/index.html
- splash/src/banner.cc
- splash/pkg/index.json
- splash/tut/demo.c
    ^      ^   ^
    |      |   +--- name
    |      +------- type
    +-------------- namespace
}
```
</details>
<details><summary>APIs</summary>
</details>
<details><summary>Documentation</summary>
</details>

## Build
<details><summary>AVA as engine</summary>
- Compile the amalgamated `ava.cc` source file to get a functional game engine.
- Compile your game as a dynamic library and place it near the `AVA` executable.
</details>
<details><summary>AVA as framework</summary>
- Link the amalgamated `ava.cc` source file to your game to get a functional game.
</details>
<details><summary>Additional build instructions for Windows</summary>
```c++
cl ava.cc         && echo AVA as engine
cl game.cc ava.cc && echo AVA as framework
```
</details>
<details><summary>Additional build instructions for Linux</summary>
```c++
g++ -std=c++11 ava.cc         && echo AVA as engine
g++ -std=c++11 game.cc ava.cc && echo AVA as framework
```
</details>
<details><summary>Additional build instructions for OSX</summary>
```c++
clang++ -std=c++11 ava.cc         && echo AVA as engine
clang++ -std=c++11 game.cc ava.cc && echo AVA as framework
```
</details>

## Todo ᕕ(ᐛ)ᕗ 
-
-
-

## License
100% free and unencumbered [public domain](http://unlicense.org/) software, usable in any context and for any purpose.
