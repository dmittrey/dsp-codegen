#include "stdbool.h"
#include "sys/ioctl.h"
#include "test/ioctl.h"
#include "math.h"
#include "stdint.h"
#ifndef SCALE_FACTOR
#define SCALE_FACTOR( frac_bits) (1 << frac_bits)
#endif
int32_t ISP_FLASH_CMD_preflash_on_to_fixed(double float_val){
	int32_t sign = float_val < 0 ? 1 : 0;
	uint32_t magnitude = (uint32_t) (fabs(float_val) * SCALE_FACTOR (1));
	return (sign << 24) | magnitude;
};

double ISP_FLASH_CMD_preflash_on_to_float(int32_t fixed_val){
	int32_t sign = fixed_val & (1 << 24);
	uint32_t magnitude = fixed_val & ( ~ (1 << 24));
	double val = (double)magnitude / SCALE_FACTOR (1);
	return sign ? -val : val;
};

uint8_t ISP_FLASH_CONFIG_fl_cap_delay_to_fixed(double float_val){
	return (uint8_t)((float_val) * SCALE_FACTOR (4));
};

double ISP_FLASH_CONFIG_fl_cap_delay_to_float(uint8_t fixed_val){
	return (double)((fixed_val) / SCALE_FACTOR (4));
};


/* Flash command */
struct ISP_FLASH_CMD{
	/* Preflash on 0: no effect 1: flash delay counter is started at next trigger event, No capture */;
	int32_t preflash_on:25;
	/* Flash on 0: no effect 1: flash delay counter is started at next trigger event A capture event is signaled to the sensor interface block */;
	bool flash_on:1;
	uint32_t align:6;
};

int ISP_FLASH_CMD_s_preflash_on(int fd, double preflash_on){
	int32_t val = ISP_FLASH_CMD_preflash_on_to_fixed(preflash_on);
	return ioctl(fd, IOCTL_ISP_FLASH_CMD_S_preflash_on, &val);
};

int ISP_FLASH_CMD_s_flash_on(int fd, bool flash_on){
	return ioctl(fd, IOCTL_ISP_FLASH_CMD_S_flash_on, &flash_on);
};

/* Flash config */
struct ISP_FLASH_CONFIG{
	/* Preflash on 0: no effect 1: flash delay counter is started at next trigger event, No capture */;
	uint8_t fl_cap_delay:4;
	/* Flash on 0: no effect 1: flash delay counter is started at next trigger event A capture event is signaled to the sensor interface block */;
	bool fl_trig_src:1;
	/* Flash on 0: no effect 1: flash delay counter is started at next trigger event A capture event is signaled to the sensor interface block */;
	bool fl_pol:1;
	/* Flash on 0: no effect 1: flash delay counter is started at next trigger event A capture event is signaled to the sensor interface block */;
	bool fl_trig_pol:1;
	/* Flash on 0: no effect 1: flash delay counter is started at next trigger event A capture event is signaled to the sensor interface block */;
	bool prelight_mode:1;
	uint32_t align:24;
};

int ISP_FLASH_CONFIG_s_fl_cap_delay(int fd, double fl_cap_delay){
	uint8_t val = ISP_FLASH_CONFIG_fl_cap_delay_to_fixed(fl_cap_delay);
	return ioctl(fd, IOCTL_ISP_FLASH_CONFIG_S_fl_cap_delay, &val);
};

int ISP_FLASH_CONFIG_g_fl_cap_delay(int fd, double* fl_cap_delay_p){
	uint8_t val;
	int ret = ioctl(fd, IOCTL_ISP_FLASH_CONFIG_G_fl_cap_delay, &val);
	*fl_cap_delay_p = ISP_FLASH_CONFIG_fl_cap_delay_to_float(val);
	return ret;
};

int ISP_FLASH_CONFIG_s_fl_trig_src(int fd, bool fl_trig_src){
	return ioctl(fd, IOCTL_ISP_FLASH_CONFIG_S_fl_trig_src, &fl_trig_src);
};

int ISP_FLASH_CONFIG_g_fl_trig_src(int fd, bool* fl_trig_src_p){
	return ioctl(fd, IOCTL_ISP_FLASH_CONFIG_G_fl_trig_src, fl_trig_src_p);
};

int ISP_FLASH_CONFIG_s_fl_pol(int fd, bool fl_pol){
	return ioctl(fd, IOCTL_ISP_FLASH_CONFIG_S_fl_pol, &fl_pol);
};

int ISP_FLASH_CONFIG_g_fl_pol(int fd, bool* fl_pol_p){
	return ioctl(fd, IOCTL_ISP_FLASH_CONFIG_G_fl_pol, fl_pol_p);
};

int ISP_FLASH_CONFIG_s_fl_trig_pol(int fd, bool fl_trig_pol){
	return ioctl(fd, IOCTL_ISP_FLASH_CONFIG_S_fl_trig_pol, &fl_trig_pol);
};

int ISP_FLASH_CONFIG_g_fl_trig_pol(int fd, bool* fl_trig_pol_p){
	return ioctl(fd, IOCTL_ISP_FLASH_CONFIG_G_fl_trig_pol, fl_trig_pol_p);
};

int ISP_FLASH_CONFIG_s_prelight_mode(int fd, bool prelight_mode){
	return ioctl(fd, IOCTL_ISP_FLASH_CONFIG_S_prelight_mode, &prelight_mode);
};

int ISP_FLASH_CONFIG_g_prelight_mode(int fd, bool* prelight_mode_p){
	return ioctl(fd, IOCTL_ISP_FLASH_CONFIG_G_prelight_mode, prelight_mode_p);
};


