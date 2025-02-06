#ifndef PROCESS_H
#define PROCESS_H

/* Includes ***************************************************************/

#include "common.h"

/* Functions **************************************************************/

int KillProcess(LPCTSTR name);
BOOL RunAsUser(LPWSTR command);

/**************************************************************************/

#endif
