/* ======================================================== */
/*   server.h		        								*/
/* ======================================================== */
#ifndef SERVER_H
#define SERVER_H

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "../include/utility.h"

//---------------------------------------------------------------------------
//-------------------------- General Defines --------------------------------
//---------------------------------------------------------------------------
#define WRONG_HEIGHT 1
#define WRONG_HASH   2

//---------------------------------------------------------------------------
//---------------------- Public Methods Prototypes---------------------------
//---------------------------------------------------------------------------
Singly_Linked_List* 
init_server();

void 
simulate_server(Singly_Linked_List* blockchain);

#endif // !SERVER_H
