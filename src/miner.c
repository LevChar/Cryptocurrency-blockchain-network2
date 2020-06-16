/* ======================================================== */
/*   miner.c		        								*/
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "../include/miner.h"

//---------------------------------------------------------------------------
//-------------------------- Global Variables -------------------------------
//---------------------------------------------------------------------------
int thread_id = 0;

//---------------------------------------------------------------------------
//---------------------- Private Methods Prototypes -------------------------
//---------------------------------------------------------------------------
bitcoin_block_data* 
get_current_block_from_server();

bitcoin_block_data* 
initialize_new_block(bitcoin_block_data* i_head_block);

EBoolType 
verify_block_is_relevant(bitcoin_block_data* i_block);

void 
mine_block(bitcoin_block_data* i_block, int i_miner_id);

void 
send_block_to_server(bitcoin_block_data* i_block);

void 
falsely_mine_block(bitcoin_block_data* i_block);

void 
print_mine_msg(bitcoin_block_data* i_block);

//---------------------------------------------------------------------------
//-----------------------Private Methods Implementations---------------------
//---------------------------------------------------------------------------
PRIVATE
bitcoin_block_data*
initialize_new_block(bitcoin_block_data* i_head_block)
{
	bitcoin_block_data* new_block = malloc(sizeof(bitcoin_block_data));
	new_block->height = i_head_block->height + 1;
	new_block->time_stamp = get_current_time_stamp();
	new_block->prev_hash = i_head_block->hash;
	new_block->difficulty = DIFFICULTY;
	new_block->nonce = PLACE_HOLDER_TILL_MINER_WILL_MINE;		// MINER responsibility
	new_block->relayed_by = PLACE_HOLDER_TILL_MINER_WILL_MINE;  // MINER responsibility
    new_block->hash = PLACE_HOLDER_TILL_MINER_WILL_MINE;		// MINER responsibility
    return new_block;
}

PRIVATE
bitcoin_block_data* 
get_current_block_from_server()
{
    pthread_mutex_lock(&get_block_lock);
    bitcoin_block_data* currBlock = g_curr_srv_head;
    pthread_mutex_unlock(&get_block_lock);

    return currBlock;
}

PRIVATE
void 
send_block_to_server(bitcoin_block_data* i_Block)
{
    pthread_mutex_lock(&set_block_lock);
    g_proposed_srv_head = i_Block;
    pthread_mutex_unlock(&set_block_lock);

    pthread_cond_broadcast(&new_block_arrive);
}

PRIVATE
EBoolType 
verify_block_is_relevant(bitcoin_block_data* i_Block)
{
    return (i_Block == get_current_block_from_server());
}

PRIVATE
void 
mine_block(bitcoin_block_data* i_block, int i_miner_id)
{
    i_block->relayed_by = i_miner_id;

    do
    {
        i_block->nonce = get_random();
        i_block->time_stamp = get_current_time_stamp();
        i_block->hash = create_hash_from_block(i_block);
    }
    while (!check_difficulty(i_block->hash, DIFFICULTY));

    print_mine_msg(i_block);
}

PRIVATE
void 
falsely_mine_block(bitcoin_block_data* i_block)
{
    i_block->hash = create_hash_from_block(i_block) + FALSE_FACTOR;
    print_mine_msg(i_block);

}

PRIVATE
void
print_mine_msg(bitcoin_block_data* i_block)
{
    printf("Miner #%d%s: Mined a new block #%d, with the hash 0x%x\n", 
           i_block->relayed_by,
           i_block->relayed_by == (NUM_OF_MINERS + 1) ? "(Dummy)" : "",
           i_block->height, 
           i_block->hash);
}

//---------------------------------------------------------------------------
//----------------------- Public Methods Implementations --------------------
//---------------------------------------------------------------------------
PUBLIC
void* 
programLoop()
{
    bitcoin_block_data* currBlock;
    bitcoin_block_data* newBlock;

    pthread_mutex_lock(&set_id);
    int miner_id = ++thread_id;
    pthread_mutex_unlock(&set_id);

    while(1)
    {
        currBlock = get_current_block_from_server();

        while(verify_block_is_relevant(currBlock))
        {
            newBlock = initialize_new_block(currBlock);
            mine_block(newBlock, miner_id);
            send_block_to_server(newBlock);
            sleep(2);
        }
    }
        return NULL;   
}

PUBLIC
void* 
programFalseLoop()
{
    bitcoin_block_data* currBlock;
    bitcoin_block_data* newBlock;

    int miner_id = NUM_OF_MINERS + 1;    

    while(1)
    {
        currBlock = get_current_block_from_server();

        while(verify_block_is_relevant(currBlock))
        {
            newBlock = initialize_new_block(currBlock);
            newBlock->relayed_by = miner_id;
            falsely_mine_block(newBlock);
            send_block_to_server(newBlock);
            sleep(2);
        }
    }

    return NULL;
}

PUBLIC
void
generate_miners()
{
    //at this point, the server, which is currently the only thread running,
    // will receive high priority, all the miners which will be created 
    //after this point will get ordinary priority.
    setpriority(PRIO_PROCESS, 0, -20);

    pthread_t* thread_ids = (pthread_t*)malloc(sizeof(pthread_t) * (NUM_OF_MINERS + 1));

    for(int i = 0; i < NUM_OF_MINERS; ++i)
    {
            pthread_create(&thread_ids[i], NULL, programLoop, NULL);
    }

    pthread_create(&thread_ids[NUM_OF_MINERS], NULL, programFalseLoop, NULL);

    free(thread_ids);
}