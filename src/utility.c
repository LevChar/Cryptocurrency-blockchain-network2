/* ======================================================== */
/*   utility.c				       						    */
/* ======================================================== */

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "../include/utility.h"

//---------------------------------------------------------------------------
//---------------------- Private Methods Prototypes -------------------------
//---------------------------------------------------------------------------
void 
append_to_string(char* i_OrigString, char* i_PartToAppend);

void 
append_int_to_string(char* i_OrigString, Uint i_Num);

char* 
concat_block(bitcoin_block_data* i_Block);

//---------------------------------------------------------------------------
//-----------------------Private Methods Implementations---------------------
//---------------------------------------------------------------------------
PRIVATE
void 
append_to_string(char* i_OrigString, char* i_PartToAppend)
{
    int partLen = strlen(i_PartToAppend);
    int origStringLen = strlen(i_OrigString);
    for (int i = 0; i < partLen; ++i)
	{
        i_OrigString[origStringLen + i] = i_PartToAppend[i];
    }

    i_OrigString[origStringLen + partLen] = '\0';
}

PRIVATE
void 
append_int_to_string(char* i_OrigString, Uint i_Num)
{
    char* intString = malloc(MAX_PART_SIZE * sizeof(char));
    sprintf((char*)intString, "%x", i_Num);
    append_to_string(i_OrigString, intString);
    free(intString);
}

PRIVATE
char*
concat_block(bitcoin_block_data* i_Block)
{
    char* concatedData = malloc(MAX_STR_SIZE * sizeof(char));

    append_int_to_string(concatedData, i_Block->height);
    append_int_to_string(concatedData, i_Block->time_stamp);
    append_int_to_string(concatedData, i_Block->prev_hash);
    append_int_to_string(concatedData, i_Block->nonce);
    append_int_to_string(concatedData, i_Block->relayed_by);

    return concatedData;
}

//---------------------------------------------------------------------------
//----------------------- Public Methods Implementations --------------------
//---------------------------------------------------------------------------
PUBLIC
Uint
get_current_time_stamp()
{
	return (Uint)time(NULL);
}

PUBLIC
Uint
get_random()
{
    return(rand() % (RAND_HI - RAND_LO + 1)) + RAND_LO;
}

PUBLIC
Uint 
create_hash(char* data)
{
    return(crc32(0L, (unsigned char*)data, strlen((const char*)data)));
}

PUBLIC
EBoolType
check_difficulty(Uint i_hash, Uint i_difficulty)
{
    Uint difficulty_max_hash_val = 1;
    
	difficulty_max_hash_val = difficulty_max_hash_val << (sizeof(Uint) * 8 - i_difficulty);
	difficulty_max_hash_val--;

	return i_hash <= difficulty_max_hash_val ? TRUE : FALSE;
}

PUBLIC
Uint
create_hash_from_block(bitcoin_block_data* i_Block)
{
    char* concatedBlock = concat_block(i_Block);
    Uint hashValue  = create_hash(concatedBlock);

    free(concatedBlock);

    return hashValue;
}
