// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

//#include "targetver.h"

//#include <stdio.h>
//#include <tchar.h>



// TODO: reference additional headers your program requires here

#define USE_PRECOMPILED_HEADERS

#ifndef __STDAFX_H_INCLUDED__
#define __STDAFX_H_INCLUDED__

#ifdef USE_PRECOMPILED_HEADERS


//#include "targetver.h"
#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif
// end of targetver.h
#define NOMINMAX
#include <sstream>
#include <iostream>
#include <fstream>

#include <stdexcept>  // logic_error
#include <cassert>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cctype>


#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#undef main
#include <boost\shared_ptr.hpp>
#include <boost\enable_shared_from_this.hpp>

#include <string>
#include <vector> 
#include <list>
#include <map>
#include <algorithm>
#include <utility>

#include "Types.h"
//#include <cstdio>
//#include <tchar.h>

#endif  // USE_PRECOMPILED_HEADERS
#endif  // __STDAFX_H_INCLUDED__
