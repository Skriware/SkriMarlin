#include "Skriware_Variables.h"

void set_to_print_Z();
bool checkTestPin(int pin);
void invert_E0();
void Extruder_Up();
void Extruder_Down();
void Z_distance_Test(float Z_start,int N_Cycles);
void Set_Extruder_Type(byte TYPE);
void Set_up_Time(int time);
void extruder_swap(uint8_t tmp_extruder,uint8_t active);