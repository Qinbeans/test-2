# Architecture
## Flags
|Name     |P_FLAGS|CLIENT DATA                   |SERVER DATA              |
|---------|-------|------------------------------|-------------------------|
|Connect  |0      |0 (ID) (USR PKT)              |0 (BOOL STAT)            |
|Inventory|1      |1 (ID) (OX) (OY) (DX) (DY)    |1 (BOOL STAT)            |
|Key Event|2      |2 (ID) (EVENT) (EVENT)        |2 (E_TYPE) (VALUE)       |
|Recipient|3      |								       |3 (E_TYPE) (dX) (dY) (dZ)|

## Types
|Name|E_TYPE     |
|----|-----------|
|0   |Attack     |
|1   |X Direction|
|2   |Y Direction|
|3   |Z Direction|

## Event
|Event            |Direction  |
|-----------------|-----------|
|KEY_W            |Y Direction|
|KEY_A            |X Direction|
|KEY_S            |Y Direction|
|KEY_D            |X Direction|
|MOUSE_BUTTON_LEFT|Attack     |

Packets will be structured like this