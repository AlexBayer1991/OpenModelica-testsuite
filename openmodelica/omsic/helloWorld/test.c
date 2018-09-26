


#include <helloWorld_omsic.h>
#include <omsi.h>
#include <omsi_global.h>
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


omsi_status simulate (const omsi_callback_functions callbacks, omsi_char* fmuResourceLocation, omsi_string instanceName, omsi_string guid, omsi_bool visible, omsi_bool loggingOn) {

    /* Variables */
    osu_t* OSU;
    omsi_status status;
    omsi_unsigned_int vr[3], nvr;
    omsi_real* value;

    /* Instantiation */
    OSU = omsi_instantiate(instanceName, omsi_model_exchange, guid, fmuResourceLocation, &callbacks, visible, loggingOn);
    if (!OSU) {
        return omsi_error;
    }

    status = omsi_setup_experiment(OSU, omsi_false, 0, 0, omsi_false, 0);
    if(status == omsi_error) {
            return omsi_error;
    }

     /* omsu_print_osu (OSU); */

    /* Initialization */
    status = omsi_enter_initialization_mode(OSU);
    if(status == omsi_error) {
        return omsi_error;
    }

    value = (omsi_real*) global_callback->allocateMemory(1, sizeof(omsi_real));
    *value = 7;

    printf("OSU->osu_data->sim_data->model_vars_and_params->n_reals = %u\n", OSU->osu_data->sim_data->model_vars_and_params->n_reals);

    vr[0] = 0;
    nvr = 1;
    status = omsi_get_real (OSU, vr, nvr, value);
    if(status == omsi_error) {
        return omsi_error;
    }

    printf("value of x: %f\n", *value);

    /* Integration */


    return omsi_ok;
}


int main ( int argc, char **argv ) {

    /* Variables */
    omsi_char fmuResourceLocation[FILENAME_MAX];

    omsi_char* initXMLFilename;
    omsi_string instanceName, guid;
    omsi_bool visible, loggingOn;

    const omsi_callback_functions callbacks = {my_fmuLogger, calloc, free, NULL, NULL};


    /* set input variables for omsi functions*/
    if(!GetCurrentDir(fmuResourceLocation, sizeof(fmuResourceLocation))) {
        return -1;
    }
    fmuResourceLocation[sizeof(fmuResourceLocation) - 1] = '\0';

    instanceName = "helloWorld";
    guid = "{ff70344b-5d3a-430d-b8ed-d372b9224f2e}";

    visible = omsi_true;
    loggingOn = omsi_true;

    if (simulate(callbacks, fmuResourceLocation, instanceName, guid, visible, loggingOn) != omsi_ok) {
        printf("\nFinished test with Errors!\n");
    }
    else {
        printf("\nFinished test successfully!\n");
    }

    return 0;
}
