// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <glm/glm.hpp>
//Convenience
namespace glm {
using lvec2 = tvec2<long, highp>;
using lvec3 = tvec3<long, highp>;
using lvec4 = tvec4<long, highp>;
}
