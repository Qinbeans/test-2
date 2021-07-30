#include "scene.h"

/**
 * P_FLAGS|CLIENT DATA       |SERVER DATA       |
 * -------|------------------|------------------|
 * 0      |0 <ID> <USR PKT>  |0 <BOOL STAT>     |
 * 1      |1 <ID> <X> <Y>    |1 <BOOL STAT>     |
 * 2      |2 <ID> <KEY EVENT>|2 <E_TYPE> <VALUE>|
 */

typedef enum{
   CONNECT = 0,
   INV_EVT,
   EVENT
}P_FLAG;

typedef enum{
   ATCK = 0,//attack
   XDIR,//x direction
   YDIR//y direction
}E_TYPE;