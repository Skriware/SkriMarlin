#include "Marlin.h"
#include "planner.h"
#include "stepper.h"
#include "Skriware_Variables.h"
#include "configuration_store.h"


#define EEPROM_WRITE(VAR) write_data(*eeprom_index, (uint8_t*)&VAR, sizeof(VAR), working_crc)
#define EEPROM_READ(VAR) read_data(*eeprom_index, (uint8_t*)&VAR, sizeof(VAR), working_crc)

void MarlinSettings::save_eeprom_sk2(uint16_t *working_crc,int *eeprom_index){

    //V56
    EEPROM_WRITE(home_offset_E1);
    EEPROM_WRITE(home_offset_E0);
    EEPROM_WRITE(extruder_change_time_offset);
    EEPROM_WRITE(servo_up_pos);
    EEPROM_WRITE(servo_down_pos);
    EEPROM_WRITE(up_delay);
    EEPROM_WRITE(extruder_type);
    EEPROM_WRITE(X_up_pos);
    EEPROM_WRITE(X_down_pos);
    EEPROM_WRITE(Y_change);
    EEPROM_WRITE(dY_change);
    EEPROM_WRITE(dX_change);
    EEPROM_WRITE(Stepper::Software_Invert);
    EEPROM_WRITE(Stepper::E0_inverted);
    //V57
    EEPROM_WRITE(sensor_noise_offset);
  
    
}

void MarlinSettings::load_eeprom_sk2(uint16_t *working_crc,int *eeprom_index, char version[4]){
 int sk_eeprom_verison = (version[2]-'0')+10*(version[1]-'0');  

if(sk_eeprom_verison > 55){
    EEPROM_READ(home_offset_E1);
    EEPROM_READ(home_offset_E0);
    EEPROM_READ(extruder_change_time_offset);
    EEPROM_READ(servo_up_pos);
    EEPROM_READ(servo_down_pos);
    EEPROM_READ(up_delay);
    EEPROM_READ(extruder_type);
    EEPROM_READ(X_up_pos);
    EEPROM_READ(X_down_pos);
    EEPROM_READ(Y_change);
    EEPROM_READ(dY_change);
    EEPROM_READ(dX_change);
    EEPROM_READ(Stepper::Software_Invert);
    EEPROM_READ(Stepper::E0_inverted);

}

if(sk_eeprom_verison > 56){
    EEPROM_READ(sensor_noise_offset);
}
}

void MarlinSettings::reset_eeprom_sk2(){
	
    home_offset_E1 = 0.0;
    home_offset_E0 = 0.0;
    servo_up_pos = SERVO_POS_UP;
    servo_down_pos = SERVO_POS_DOWN;
    extruder_change_time_offset = EXT_CHANGE_TIME_OFFSET;
    up_delay = MOTOR_UP_TIME;
    extruder_type = DEF_EXTRDER_TYPE;
    X_up_pos = 0.0;
    X_down_pos = 0.0;
    Y_change = 0.0;
    dY_change = 0.0;
    dX_change = 0.0;
    sensor_noise_offset = OPTICAL_SENSOR_NOISE_OFFSET;
}

 bool MarlinSettings::nan_Matrix_Test(float z_values[GRID_MAX_POINTS_X][GRID_MAX_POINTS_Y]){
    bool nanTest = true;                                      
          for(byte yy = 0 ; yy < GRID_MAX_POINTS_Y; yy++){
            for(byte xx = 0; xx < GRID_MAX_POINTS_X; xx++){
              if(isnan(z_values[xx][yy])){
                nanTest = false;
                break;
              }
            }
          }
          if(!nanTest){
            SERIAL_ECHOLN("ERROR: Calibration data corrupted!");
          }else{
            SERIAL_ECHOLN("Bed matrix loaded, with no errors.");
          }
          return(nanTest);
}