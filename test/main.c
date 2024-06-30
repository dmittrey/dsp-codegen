#include "stdint.h"
#include "assert.h"
#include "stdio.h"

uint32_t ISP_FLASH_CMD_preflash_on_to_fixed(double float_val);
double ISP_FLASH_CMD_preflash_on_to_float(uint32_t fixed_val);

uint8_t ISP_FLASH_CMD_flash_on_to_fixed(double float_val);
double ISP_FLASH_CMD_flash_on_to_float(uint8_t fixed_val);

int8_t ISP_FLASH_CONFIG_fl_cap_delay_to_fixed(double float_val);
double ISP_FLASH_CONFIG_fl_cap_delay_to_float(int8_t fixed_val);

int main() {
    // Example floating-point numbers
    double a = 2.75;
    double b = -5.75;
    
    // Convert to fixed-point Q1.4.3 in sign-magnitude format
    uint8_t a_fixed = ISP_FLASH_CONFIG_fl_cap_delay_to_fixed(a);
    uint8_t b_fixed = ISP_FLASH_CONFIG_fl_cap_delay_to_fixed(b);
    
    // Convert back to floating-point for verification
    double a_converted = ISP_FLASH_CONFIG_fl_cap_delay_to_float(a_fixed);
    double b_converted = ISP_FLASH_CONFIG_fl_cap_delay_to_float(b_fixed);
    
    // Print results
    printf("Float: %.3f -> Fixed Q1.4.3: %02X -> Float: %.3f\n", a, (uint8_t) a_fixed, a_converted);
    printf("Float: %.3f -> Fixed Q1.4.3: %02X -> Float: %.3f\n", b, (uint8_t) b_fixed, b_converted);

    return 0;
}