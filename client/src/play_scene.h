#include "scene.h"

/**
 * Name     |P_FLAGS|CLIENT DATA                   |SERVER DATA       |
 * ---------|-------|------------------------------|------------------|
 * Connect  |0      |0 <ID> <USR PKT>              |0 <BOOL STAT>     |
 * Inventory|1      |1 <ID> <OX> <OY> <DX> <DY>    |1 <BOOL STAT>     |
 * Key Event|2      |2 <ID> <KEY EVENT> <KEY EVENT>|2 <E_TYPE> <VALUE>|
 */