/*
	Author: Mohamed Kazma
	Description: Precompiled header for the project
*/

#pragma once

#define GLM_ENABLE_EXPERIMENTAL

// C++ default libraries
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include <cmath>

// MTRX defs
#include <Defs.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

// SpdLog
#include <spdlog.h>
#include <logger.h>
#include <sinks/rotating_file_sink.h>

// Premake