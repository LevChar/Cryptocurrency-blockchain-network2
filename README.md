# Cryptocurrency blockchain network
A multithreaded (POSIX threads) application that illustrates a cryptocurrency blockchain network.
Based on client/server architecture, in which the mining threads(clients) are mining blocks(calculate hashes)
and send those blocks to a server that verifies and adds them to its blockchain.
The clients use synchronization among themselves and between them and the server to get the correct results.

## **Purpose:**
This software was written as part of assignment in the LINUX course. It demonstrates,
in a basic way, the blockchain mining process. It consists of 4 mining threads, one server thread,
and one "dummy" miner thread. Each one of the mining threads is responsible for mining new blocks
to the Blockchain, the server is responsible for validation	of miner's work, and the "dummy" thread
is responsible	for creating wrong blocks, so we can validate that the server is doing its job, and
not letting every block in. In the process of creating this piece of software, there is a lot of practice
in writing multithreaded code, thread synchronization, etc.

## **Compilation & Execution:**
Download \ clone the whole repo & run make command from the 
folder where you downloaded. After the compilaton is done, you can run the 
program by name - "bitcoin".

## **Compatibility:**
Program was compiled and tested in Linux (Mint) environment.
