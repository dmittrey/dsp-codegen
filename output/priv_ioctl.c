long private_ioctls_function(struct device* dev, unsigned int cmd, void __user* args){
	int ret = 0;
	u32 val = * args;
	switch(cmd)  {
 case IOCTL_ISP_FLASH_CMD_S_flash_on:
	__raw_writel(*val, 1560);
	break;
 case IOCTL_ISP_FLASH_CONFIG_S_fl_cap_delay:
	__raw_writel(*val, 616);
	break;
 case IOCTL_ISP_FLASH_CONFIG_S_fl_cap_delay:
	*val = __raw_readl(616);
	break;
 case IOCTL_ISP_FLASH_CONFIG_S_fl_trig_src:
	__raw_writel(*val, 615);
	break;
 case IOCTL_ISP_FLASH_CONFIG_S_fl_trig_src:
	*val = __raw_readl(615);
	break;
 case IOCTL_ISP_FLASH_CONFIG_S_fl_pol:
	__raw_writel(*val, 614);
	break;
 case IOCTL_ISP_FLASH_CONFIG_S_fl_pol:
	*val = __raw_readl(614);
	break;
 case IOCTL_ISP_FLASH_CONFIG_S_fl_trig_pol:
	__raw_writel(*val, 613);
	break;
 case IOCTL_ISP_FLASH_CONFIG_S_fl_trig_pol:
	*val = __raw_readl(613);
	break;
 case IOCTL_ISP_FLASH_CONFIG_S_prelight_mode:
	__raw_writel(*val, 612);
	break;
 case IOCTL_ISP_FLASH_CONFIG_S_prelight_mode:
	*val = __raw_readl(612);
	break;
 default: 
 	break; 
 };
	return ret;
};


