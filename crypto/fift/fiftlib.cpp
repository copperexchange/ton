/*
    This file is part of TON Blockchain Library.
    TON Blockchain Library is free software: you can redistribute it and/or
   modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.
    TON Blockchain Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.
    You should have received a copy of the GNU Lesser General Public License
    along with TON Blockchain Library.  If not, see
   <http://www.gnu.org/licenses/>.
    Copyright 2017-2019 Telegram Systems LLP
*/

// COPPER CODE: This is implementation of fift that builds and run as dynamic library
#include "fift/fiftlib.h"
#include <string>
#include <vector>

#include "fift/words.h"
#include "fift/Fift.h"
#include "fift/utils.h"

#include "td/utils/filesystem.h"
#include "td/utils/PathView.h"
#include "td/utils/port/path.h"

std::string string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

void loadFiles(fift::FiftOutput & fift_output,
               std::vector<const char*> res, char* const returnFiles[],
               int returnFilesC, int currentFile,
               void (*callback)(const char**, const char*)) {
  if (currentFile == returnFilesC) {
    callback(res.data(), {0});
  } else {
    auto loadFile = fift_output.source_lookup.read_file(
        std::string(returnFiles[currentFile]));

    if (loadFile.is_error()) {
      callback({0}, ("Error on loading file: " + std::string(returnFiles[currentFile]) + " - " + loadFile.error().to_string()).c_str());

    } else {
      auto loadedFile = loadFile.move_as_ok();

      auto byteString = loadedFile.data;

      std::string mystr = string_to_hex(byteString);

      res.push_back(mystr.c_str());

      loadFiles(fift_output, res, returnFiles, returnFilesC, currentFile + 1, callback);
    }
  }
}

void run(const char* sourcePath, const char* fift_path, char* const argv[],
         int argc, char* const add_files[], int add_files_c, char* const returnFiles[], int returnFilesC,
         void (*callback)(const char**, const char*)) {
  SET_VERBOSITY_LEVEL(verbosity_INFO);

  auto loadSource = td::read_file_str(std::string(sourcePath));
  std::vector<std::string> args(argv, argv + argc);
  std::vector<std::string> files(add_files, add_files + add_files_c);

  std::vector<const char*> res;

  if (loadSource.is_error()) {
    callback({0}, loadSource.error().to_string().c_str());
  } else {
    auto source = fift::create_mem_source_lookup(loadSource.move_as_ok(), files, std::string(fift_path));

    if (source.is_error()) {
      callback({0}, source.error().to_string().c_str());
    } else {
    auto call = fift::mem_run_fift(source.move_as_ok(), args);

    if (call.is_error()) {
      callback({0}, ("Error on execution contract - " + call.error().to_string()).c_str());
    } else {
      auto fift_output = call.move_as_ok();

      res.push_back(fift_output.output.c_str());

      loadFiles(fift_output, res, returnFiles, returnFilesC, 0, callback);
    }
    }
  }
}
