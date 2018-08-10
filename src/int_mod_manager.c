#include "includes.h"
#include "log.h"

int32_t int_mod_ctrl_callback(module_pub_data_t *module_pub_data)
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	return 0;
}

int32_t int_mode_ctr_setup()
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	intmodule_ctrl_startup();
#if 1
	module_pub_data_t module_pub_data;
	//dummy test
	module_pub_data.m_module_id = 0;
	plat_sprintf(module_pub_data.m_name, sizeof(module_pub_data.m_name), "dummy");
	intmodule_ctrl_process_cmd(&module_pub_data);
	//rec_muxer test
	module_pub_data.m_module_id = 1;
	plat_sprintf(module_pub_data.m_name, sizeof(module_pub_data.m_name), "rec_muxer");
	intmodule_ctrl_process_cmd(&module_pub_data);
#endif
	return 0;
}

int32_t int_mode_ctr_desetup()
{
	log_output(LOG_LEVEL_FILE_SCREEN, "%s->%d:into %s", __FUNCTION__, __LINE__, __FUNCTION__);
	intmodule_ctrl_shutdown();
	return 0;
}