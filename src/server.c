/* ======================================================== */
/*   server.c		        								*/
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "../include/server.h"

//---------------------------------------------------------------------------
//-------------------------- Global Variables -------------------------------
//---------------------------------------------------------------------------
bitcoin_block_data* curr_candidate;

//---------------------------------------------------------------------------
//---------------------- Private Methods Prototypes -------------------------
//---------------------------------------------------------------------------
void 
initialize_list_with_genesis(Singly_Linked_List* blockchain);

void 
print_block_acceptance();

void 
print_block_rejection(Uint err_type, Uint error_detail);

EBoolType 
verify_block(bitcoin_block_data* i_Block);

bitcoin_block_data* 
createGenesis();

//---------------------------------------------------------------------------
//-----------------------Private Methods Implementations---------------------
//---------------------------------------------------------------------------
PRIVATE
bitcoin_block_data* 
createGenesis()
{
		bitcoin_block_data* new_block = malloc(sizeof(bitcoin_block_data));
		new_block->height = GENESIS_VAL;
		new_block->time_stamp = get_current_time_stamp();
		new_block->prev_hash = GENESIS_VAL;
		new_block->difficulty = DIFFICULTY;
		new_block->nonce = GENESIS_VAL;
		new_block->relayed_by = GENESIS_VAL;
		new_block->hash = create_hash_from_block(new_block);
		return new_block;
}

PRIVATE
void
initialize_list_with_genesis(Singly_Linked_List* blockchain)
{
	bitcoin_block_data* genesis_block = createGenesis();	
	append_To_List(blockchain, genesis_block);
	g_curr_srv_head = genesis_block;
}

PRIVATE
void
print_block_acceptance()
{
	printf("Server: New block added by %d, attributes: ", curr_candidate->relayed_by);
	print_bitcoin_block_data(curr_candidate);
	printf("\n");
}

PRIVATE
void
print_block_rejection(Uint err_type, Uint error_detail)
{
    char *err_str = (err_type == WRONG_HASH) 
    ? "Wrong hash for block #%d by miner %d received %x but calculated %x\n" 
    : "Wrong height for block #%d by miner %d received %d but height is already %d\n"
    ;

    printf(
        err_str, 
        curr_candidate->height, 
        curr_candidate->relayed_by,
        err_type == WRONG_HASH ? curr_candidate->hash : curr_candidate->height,
        error_detail
    );
}

PRIVATE
EBoolType
verify_block(bitcoin_block_data* i_Block)
{
    Uint headBlockHeight, calculatedHash;

    pthread_mutex_lock(&get_block_lock);
    headBlockHeight = g_curr_srv_head->height;
    pthread_mutex_unlock(&get_block_lock);

    calculatedHash = create_hash_from_block(i_Block);

    if((i_Block->height != headBlockHeight + 1) || i_Block->hash != calculatedHash){
        if(i_Block->height != headBlockHeight + 1)
            print_block_rejection(WRONG_HEIGHT,headBlockHeight);
        else
            print_block_rejection(WRONG_HASH,calculatedHash);
        return FALSE;
    }
    
	return TRUE;
}
//---------------------------------------------------------------------------
//----------------------- Public Methods Implementations---------------------
//---------------------------------------------------------------------------
PUBLIC
Singly_Linked_List*
init_server()
{
	Singly_Linked_List* blockchain = initialize_Empty_List(
	        sizeof(bitcoin_block_data),
            release_bitcoin_block_data);

    initialize_list_with_genesis(blockchain);
    return blockchain;
}

PUBLIC
void
simulate_server(Singly_Linked_List* blockchain)
{
    while(blockchain->length < 100)
    {
        pthread_mutex_lock(&set_block_lock);
        pthread_cond_wait(&new_block_arrive, &set_block_lock);
        curr_candidate = g_proposed_srv_head;
        pthread_mutex_unlock(&set_block_lock);

        if (verify_block(curr_candidate))
        {
            append_To_List(blockchain, curr_candidate);
            print_block_acceptance();

            pthread_mutex_lock(&get_block_lock);
            g_curr_srv_head = curr_candidate;
            pthread_mutex_unlock(&get_block_lock);
        }
        else
        {
            free(curr_candidate);
        }
    }

    destroy_List(blockchain);
}