/* ======================================================== */
/*   utility.h				       						    */
/* ======================================================== */
#ifndef UTILITY_H
#define UTILITY_H

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "bitcoin.h"

//---------------------------------------------------------------------------
//--------------------------- Bitcoin Defines -------------------------------
//---------------------------------------------------------------------------
#define PLACE_HOLDER_TILL_MINER_WILL_MINE   0
#define NUM_OF_MINERS                       4
#define GENESIS_VAL                         0
#define DIFFICULTY                          16
#define RAND_HI                             2000000
#define RAND_LO                             1
#define MAX_PART_SIZE                       30
#define MAX_STR_SIZE                        60

//---------------------------------------------------------------------------
//-------------------------- Global Variables -------------------------------
//---------------------------------------------------------------------------
bitcoin_block_data* g_proposed_srv_head;
bitcoin_block_data* g_curr_srv_head;

//---------------------------------------------------------------------------
//---------------------- Synchronization Variables --------------------------
//---------------------------------------------------------------------------
pthread_mutex_t get_block_lock;
pthread_mutex_t set_block_lock;
pthread_mutex_t set_id;
pthread_cond_t new_block_arrive;

//---------------------------------------------------------------------------
//---------------------- Public Methods Prototypes---------------------------
//---------------------------------------------------------------------------
EBoolType 
check_difficulty(Uint i_hash, Uint i_difficulty);

Uint 
create_hash_from_block(bitcoin_block_data* i_Block);

Uint 
get_current_time_stamp();

Uint 
create_hash(char* data);

Uint 
get_random();

#endif // !UTILITY_H
