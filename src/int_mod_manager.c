#include "includes.h"
#include "log.h"

int32_t int_mod_ctrl_callback(module_pub_data_t *module_pub_data)
{
	LOG_PACKAGE_STR(intmodule_ctrl_callback);
	return 0;
}

int32_t int_mode_ctr_setup()
{
	LOG_PACKAGE_STR(int_mode_ctr_setup);
	intmodule_ctrl_startup();
	LOG_PACKAGE_STR(1234568);
#if 1
	module_pub_data_t module_pub_data;
	module_pub_data.m_module_id = 0;
	plat_sprintf(module_pub_data.m_name, sizeof(module_pub_data.m_name), "dummy");
	intmodule_ctrl_process_cmd(&module_pub_data);
#endif
	return 0;
}

int32_t int_mode_ctr_desetup()
{
	LOG_PACKAGE_STR(int_mode_ctr_desetup);
	intmodule_ctrl_shutdown();
	return 0;
}