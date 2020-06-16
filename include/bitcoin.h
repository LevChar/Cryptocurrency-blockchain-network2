/* ======================================================== */
/*   bitcoin.h				       						    */
/* ======================================================== */
#ifndef BITCOIN_H
#define BITCOIN_H

//---------------------------------------------------------------------------
//----------------------------- Includes ------------------------------------
//---------------------------------------------------------------------------
#include "linked_list.h"

//---------------------------------------------------------------------------
//--------------------------- Bitcoin Defines -------------------------------
//---------------------------------------------------------------------------
#define DIFFICULTY 16

//---------------------------------------------------------------------------
//---------------------- Bitcoin Block Data Structure -----------------------
//---------------------------------------------------------------------------
typedef struct _bitcoin_block_data
{
	Uint height;
	Uint time_stamp;
	Uint hash;
	Uint prev_hash;
	Uint difficulty;
	Uint nonce;
	Uint relayed_by;
	
} bitcoin_block_data;

//---------------------------------------------------------------------------
//---------------------- Public Method Prototypes ---------------------------
//---------------------------------------------------------------------------
void 
print_bitcoin_block_data(bitcoin_block_data* block_to_print);

void 
release_bitcoin_block_data(pVoid block_to_release);

#endif // !BITCOIN_H