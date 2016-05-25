/*
 * Copyright (C) 2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/**
 * @file   joffee.cpp
 * @brief  Implements Joffee's HW abstraction layer
 */
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <cutils/log.h>

#include <joffee.h>
#define TAG "JOFFEE!"
/**
 * The function(s) exported by this HAL
 */
int joffee_function_impl(){
  ALOGE(TAG, "Hello Android!!\n");
  /* Here you should interface with your HW devices... */

  return 0;
}

/** This is mandatory, and part of hw_device_t */
int close_joffee(hw_device_t* hw_dev) {
  //TODO
  return 0;
}

/**
 * A pointer to this method is stored in
 * hw_module_method_t.open;
 *
 * Once JNI loads the hw_module_method_t symbol, it
 * can call this function and "open" the HAL layer
 * receiving pointers to this module's additional methods
 */
static int open_joffee(const struct hw_module_t *module,
                       char const *name, struct hw_device_t **device) {
  struct joffee_device_t *dev = (struct joffee_device_t *)
    malloc(sizeof(*dev));

  if (NULL == dev) {
    ALOGE(TAG, "Unable to reserve memory for joffee: %s\n",
        strerror(errno));
        return -ENOMEM;
  }

  /* Store pointer to HAL function(s) */
  dev->joffee_function = joffee_function_impl;

  /* Initialize common fields */
  dev->common.tag = HARDWARE_DEVICE_TAG;
  dev->common.version = 0;
  dev->common.module = (struct hw_module_t *)module;
  dev->common.close = close_joffee;

  /* Store this module's structure in the output parameter 'device' */
  /* Remember the first field of your HAL device must be an hw_device_t */
  *device = (struct hw_device_t *)dev;
  return 0;
}
/*
 * The Joffee HAL description
 * Will be loaded using libhardware
 */
static struct hw_module_methods_t joffee_methods =
{
  .open =  open_joffee,
};

struct hw_module_t HAL_MODULE_INFO_SYM =
{
  .tag = HARDWARE_MODULE_TAG,
  .version_major = 0,
  .version_minor = 1,
  .id = JOFFEE_HARDWARE_MODULE_ID,
  .name = "Joffee HAL",
  .author = "Linaro",
  .methods = &joffee_methods,
};
