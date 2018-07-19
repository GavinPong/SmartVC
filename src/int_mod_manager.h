#ifndef __INT_MOD_MANAGER_H__
#define __INT_MOD_MANAGER_H__

#ifdef __cplusplus
extern "C"{
#endif

int intmodule_ctrl_callback(module_pub_data_t *module_pub_data);
int int_mode_ctr_setup();
int int_mode_ctr_desetup();

#ifdef __cplusplus
};
#endif

#endif