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

# Net Tutorial

My network wrapper for ENet.

## Starting Net
```cpp
network net();
net.init();
```
## Connecting
```cpp
string init_pkt = "Hello World"//connect requires a packet to be sent
net.connect("localhost",1234,init_pkt);
```

## Disconnecting
```cpp
//it's proper to always disconnect from the network
net.disconnect();
//HINT: If you plan on using a pointer and re-pointing to different networks,
//do not forget to free/delete the pointers otherwise they become headless 
//pointers in memory
```

## Sending Packets
```cpp
//ID is a 6 character sized string
string ID = "1p231H";
string event1 = "KEY_W";
string event2 = "KEY_SHIFT";
string packet = "2 "+ID+" "+event1+" "+event2;
net.send(str);
```

# Hint
If you're looking to use this in a project with multiple classes that work together and you plan on passing around networking, keep the network object as a pointer.
