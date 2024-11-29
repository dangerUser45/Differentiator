#pragma once

#include "Diff_Common.h"

FILE* Create_file (const char* name_of_file);
diff* Diff_init (int argc ,char* argv[]);
void Close_File (FILE* file);