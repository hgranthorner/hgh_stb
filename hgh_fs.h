/* hgh_fs - no warranty implied; use at your own risk

   Do this:
      #define HGH_FS_IMPLEMENTATION
   before you include this file in *one* C or C++ file to create the implementation.

   // i.e. it should look like this:
   #include ...
   #include ...
   #include ...
   #define HGH_FS_IMPLEMENTATION
   #include "hgh_fs.h"
*/

#ifndef INCLUDE_HGH_FS
#define INCLUDE_HGH_FS

// Read the file into memory, allocating as needed.
// If there are any errors, it returns null
char *hghfs_read_file(const char *path);

// Write the contents into the file, truncating any existing content.
// The file will be created if it doesn't exist.
// Returns 0 on success, nonzero on failure.
int hghfs_write_file(const char *path, const char *content);

#endif // INCLUDE_HGH_FS

#ifdef HGH_FS_IMPLEMENTATION
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *hghfs_read_file(const char *path)
{
  // Open the file in binary mode
  FILE* file = fopen(path, "rb");
  if (!file) {
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  // Allocate memory for the file content plus a null terminator
  char* buffer = (char*)malloc(file_size + 1);
  if (!buffer) {
    fclose(file);
    return NULL;
  }

  // Read the file into the buffer
  size_t bytes_read = fread(buffer, 1, file_size, file);
  if (bytes_read != file_size) {
    free(buffer);
    fclose(file);
    return NULL;
  }

  buffer[file_size] = '\0';
  fclose(file);

  return buffer;
}

int hghfs_write_file(const char *path, const char *content)
{
  // Open the file in write mode ("w")
  FILE* file = fopen(path, "w");
  if (!file) {
    perror("Could not open file");
    return -1;
  }

  size_t content_length = fwrite(content, sizeof(char), strlen(content), file);
  if (content_length != strlen(content)) {
    fclose(file);
    return -1;
  }

  // Close the file
  fclose(file);
  return 0;
}

#endif // HGH_FS_IMPLEMENTATION

/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2024 Grant Horner
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
