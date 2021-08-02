/**
 * @file play_scene.h
 * @author Ryan Fong (rybeats@live.com)
 * @brief Header file for what will run the
 *    main portion of the game
 * @version 0.1
 * @date 2021-08-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "scene.h"

/**
 * Name     |P_FLAGS|CLIENT DATA                   |SERVER DATA       |
 * ---------|-------|------------------------------|------------------|
 * Connect  |0      |0 <ID> <USR PKT>              |0 <BOOL STAT>     |
 * Inventory|1      |1 <ID> <OX> <OY> <DX> <DY>    |1 <BOOL STAT>     |
 * Key Event|2      |2 <ID> <KEY EVENT> <KEY EVENT>|2 <E_TYPE> <VALUE>|
 */