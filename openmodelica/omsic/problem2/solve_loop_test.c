


#include <problem2_omsic.h>
#include <omsu_common.h>
#include <omsu_initialization.h>
#include <omsu_helper.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
#endif


#define MAX_MSG_SIZE 1000
void my_fmuLogger(const void *componentEnvironment, omsi_string instanceName, omsi_status status,
               omsi_string category, omsi_string message, ...) {
    omsi_char msg[MAX_MSG_SIZE];
    va_list argp;

    /* replace C format strings */
    va_start(argp, message);
    vsprintf(msg, message, argp);
    va_end(argp);


    if (!instanceName) instanceName = "?";
    if (!category) category = "?";
    printf("%s %s (%s): %s\n", "status", instanceName, category, msg); fflush(stdout);
}

/*
 * Test LAPACK solver
 */
omsi_status test_lapack_solver (void) {


    return omsi_ok;
}

int main ( int argc, char **argv ) {

    /* Variables */
    omsi_char fmuResourceLocation[FILENAME_MAX];
    osu_t* OSU;
    omsi_char* initXMLFilename;
    omsi_string instanceName, guid;
    omsi_bool visible, loggingOn;

    const omsi_callback_functions callbacks = {my_fmuLogger, calloc, free, NULL, NULL};


    /* set input variables for omsi functions*/
    if(!GetCurrentDir(fmuResourceLocation, sizeof(fmuResourceLocation))) {
        return -1;
    }
    fmuResourceLocation[sizeof(fmuResourceLocation) - 1] = '\0';

    instanceName = "problem2";
    guid = "{01513bef-2ec9-4f76-a8a1-e3d8cff35dc0}";

    visible = omsi_true;
    loggingOn = omsi_true;

    initXMLFilename = callbacks.allocateMemory(20 + strlen(instanceName) + strlen(fmuResourceLocation), sizeof(omsi_char));
    sprintf(initXMLFilename, "%s/%s_init.xml", fmuResourceLocation, instanceName);

    printf("Begin instantiation:\n"); fflush(stdout);
    OSU = omsi_instantiate(instanceName, omsi_model_exchange, guid, fmuResourceLocation, &callbacks, visible, loggingOn);

    /* print results */
    /*omsu_print_omsi_t (OSU->osu_data, "");*/

    printf("Finished solver test successfully!\n"); fflush(stdout);

    return 0;
}
