#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\Processor\Onegin_for_proc\Onegin_processing.h"
#include "..\Processor\Onegin_for_proc\Onegin_General.h"
#include "..\Processor\Onegin_for_proc\Print.h"
#include "Diff.h"

FILE* Log_File;
FILE* Graph_File;
FILE* Graph_File_Utf8;

FILE* Create_file (const char* name_of_file);

diff*  Diff_init (int argc ,char* argv[])
{

    Log_File = Create_file ("LOG_DIFF.html");        //!!!    
    fprintf (Log_File, "<pre>");

    diff* diff_data = (diff*) calloc (1, sizeof (diff));
    if (!diff_data) { fprintf (Log_File, "ERROR IN AKIN INIT: akin_data = null\n"); return 0; }

    ONEGIN* onegin_data = (ONEGIN*)   calloc (1, sizeof (ONEGIN));
    if (!onegin_data) { fprintf (Log_File, "ERROR IN AKIN INIT: onegin_data = null\n"); return 0; }

    diff_data -> onegin = onegin_data;

    Check_argc (argc);
    onegin_data -> name = argv[1];
    onegin_data -> fsize = file_size (argv[1]);
    Check_fsize (onegin_data -> fsize);
    Read_File (onegin_data); 
    DBG_Print (onegin_data);

    return diff_data;
}
//==================================================================================================
FILE* Create_file (const char* name_of_file)
{
    FILE* file = fopen (name_of_file, "w+"); 

    if (file == NULL)
    {
        fprintf (stdout, "ERROR in open file\n %s", name_of_file);
        return 0;
    }
    
    setvbuf (file, 0, 0, _IONBF);

    return file;
}
//==================================================================================================
