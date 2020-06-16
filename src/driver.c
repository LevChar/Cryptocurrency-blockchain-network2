/* ======================================================== */
/*   bitcoin.c		        								*/
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "../include/server.h"
#include "../include/miner.h"

//---------------------------------------------------------------------------
//---------------------- Private Methods Prototypes -------------------------
//---------------------------------------------------------------------------
void program_destroy();
void program_init();

//---------------------------------------------------------------------------
//-----------------------Private Methods Implementations---------------------
//---------------------------------------------------------------------------
PRIVATE
void 
program_init()
{
	pthread_mutex_init(&get_block_lock, NULL);
	pthread_mutex_init(&set_block_lock, NULL);
    pthread_mutex_init(&set_id, NULL);
	pthread_cond_init(&new_block_arrive, NULL);
}

PRIVATE
void 
program_destroy()
{
	pthread_mutex_destroy(&get_block_lock);
	pthread_mutex_destroy(&set_block_lock);
	pthread_mutex_destroy(&set_id);
    pthread_cond_destroy(&new_block_arrive);
}

//---------------------------------------------------------------------------
//---------------------- Public Methods Implementations----------------------
//---------------------------------------------------------------------------


int 
main()
{
    program_init();
    Singly_Linked_List* blockchain = init_server();
    generate_miners();
    simulate_server(blockchain);
    program_destroy();
}