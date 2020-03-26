/*
    This file is part of TON Blockchain Library.

    TON Blockchain Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    TON Blockchain Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with TON Blockchain Library.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2017-2019 Telegram Systems LLP
*/

// COPPER CODE: This is implementation of fift that builds and run as dynamic library
#pragma once

#include "fiftlib_export.h"
#include <string>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

FIFTLIB_EXPORT void run(const char* source, const char* fift_path, char* const argv[], int argc, char* const add_files[], int add_files_c, char *const returnFiles[], int returnFilesC, void (*callback)(const char **, const char*));

#ifdef __cplusplus
}  // extern "C"
#endif
