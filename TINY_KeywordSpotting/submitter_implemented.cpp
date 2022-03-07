/*
Copyright 2020 EEMBC and The MLPerf Authors. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

This file reflects a modified version of th_lib from EEMBC. The reporting logic
in th_results is copied from the original in EEMBC.
==============================================================================*/
/// \file
/// \brief C++ implementations of submitter_implemented.h


#include "submitter_implemented.h"
#include "internally_implemented.h"


#include <zephyr.h>
#include <sys/printk.h>
#include <drivers/uart.h>

#include <console/console.h>
#include <shell/shell.h>

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <zephyr.h>
#include <sys/printk.h>
#include <drivers/uart.h>

// Util
#include "quantization_helpers.h"
#include "tf_micro_model_runner.h"

// Tensorflow
#include "tensorflow/lite/micro/kernels/micro_ops.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"

//  KWS
#include "kws_input_data.h"
#include "kws_model_data.h"
#include "kws_model_settings.h"


//  Minimum kTensorArenaSize = 23
//  Minimum tensor_arena to run = 23
constexpr int kTensorArenaSize = 23 * 1024;
alignas(16) uint8_t tensor_arena[kTensorArenaSize];

tflite::MicroModelRunner<int8_t, int8_t, 6> *runner;

// Implement this method to prepare for inference and preprocess inputs.
void th_load_tensor() {
  // ADD QUANTIZATION #############
  // uint8_t input_quantized[kKwsInputSize];
  // int8_t input_asint[kKwsInputSize];
  int8_t input[kKwsInputSize];

  size_t bytes = ee_get_buffer(reinterpret_cast<uint8_t *>(input),
                               kKwsInputSize * sizeof(int8_t));
  if (bytes / sizeof(int8_t) != kKwsInputSize) {
    th_printf("Input db has %d elemented, expected %d\n", bytes / sizeof(int8_t),
              kKwsInputSize);
    return;
  }
  // uint16_t i = 0;
  // for(i=0; i<kKwsInputSize;i++)
  // {
	//   if(input_quantized[i]<=127)
	//     input_asint[i] = ((int8_t)input_quantized[i]) - 128;
	//   else
	//     input_asint[i] = (int8_t)(input_quantized[i] - 128);
  // }
 
  // runner->SetInput(input_asint);
  runner->SetInput(input);
}


// Add to this method to return real inference results.
void th_results() {
  /**
   * The results need to be printed back in exactly this format; if easier
   * to just modify this loop than copy to results[] above, do that.
   */
  th_printf("m-results-[");
  int kCategoryCount = 12;

  for (size_t i = 0; i < kCategoryCount; i++) {
    float converted =
        DequantizeInt8ToFloat(runner->GetOutput()[i], runner->output_scale(),
                              runner->output_zero_point());

	// Some platforms don't implement floating point formatting.
    th_printf("0.%d", static_cast<int>(converted * 10));
    th_printf("%d", static_cast<int>(converted * 100) % 10);
    th_printf("%d", static_cast<int>(converted * 1000) % 10);

    if (i < (kCategoryCount - 1)) {
      th_printf(",");
    }
  }
  th_printf("]\r\n");
}

// Implement this method with the logic to perform one inference cycle.
void th_infer() { runner->Invoke(); }

/// \brief optional API.
void th_final_initialize(void) {
  static tflite::MicroMutableOpResolver<6> resolver;
  resolver.AddFullyConnected();
  resolver.AddConv2D();
  resolver.AddDepthwiseConv2D();
  resolver.AddReshape();
  resolver.AddSoftmax();
  resolver.AddAveragePool2D();

  static tflite::MicroModelRunner<int8_t, int8_t, 6> model_runner(
         g_kws_model_data, resolver, tensor_arena, kTensorArenaSize);
  runner = &model_runner;
}

void th_pre() {}
void th_post() {}

void th_command_ready(char volatile *p_command) {
  p_command = p_command;
  ee_serial_command_parser_callback((char *)p_command);
}

// th_libc implementations.
int th_strncmp(const char *str1, const char *str2, size_t n) {
  return strncmp(str1, str2, n);
}

char *th_strncpy(char *dest, const char *src, size_t n) {
  return strncpy(dest, src, n);
}

size_t th_strnlen(const char *str, size_t maxlen) {
  return strnlen(str, maxlen);
}

char *th_strcat(char *dest, const char *src) { return strcat(dest, src); }

char *th_strtok(char *str1, const char *sep) { return strtok(str1, sep); }

int th_atoi(const char *str) { return atoi(str); }

void *th_memset(void *b, int c, size_t len) { return memset(b, c, len); }

void *th_memcpy(void *dst, const void *src, size_t n) {
  return memcpy(dst, src, n);
}

/* N.B.: Many embedded *printf SDKs do not support all format specifiers. */
int th_vprintf(const char *format, va_list ap) { return vprintf(format, ap); }
void th_printf(const char *p_fmt, ...) {
  va_list args;
  va_start(args, p_fmt);
  (void)th_vprintf(p_fmt, args); /* ignore return */
  va_end(args);
}

char th_getchar() { return getchar(); }

void th_serialport_initialize(void) {
// # if EE_CFG_ENERGY_MODE==1
//   pc.baud(9600);
// # else
//   pc.baud(115200);
// # endif
}

void th_timestamp(void) {
#if EE_CFG_ENERGY_MODE == 1
/* USER CODE 1 BEGIN */
/* Step 1. Pull pin low */
       g_timestampPin = 0;
       for (int i=0; i<100000; ++i) {
               asm("nop");
       }
/* Step 2. Hold low for at least 1us */
/* Step 3. Release driver */
       g_timestampPin = 1;

/* USER CODE 1 END */
#else
       int64_t uptime_usec = (k_uptime_ticks() * 1000000) / CONFIG_SYS_CLOCK_TICKS_PER_SEC;
       //int64_t uptime_usec = (k_uptime_get() * 1000);
       unsigned long microSeconds = (unsigned long) uptime_usec;
       /* USER CODE 2 BEGIN */
    //   microSeconds = us_ticker_read();
       /* USER CODE 2 END */
       /* This message must NOT be changed. */
       th_printf(EE_MSG_TIMESTAMP, microSeconds);
#endif
}

void th_timestamp_initialize(void) {
  /* USER CODE 1 BEGIN */
  // Setting up BOTH perf and energy here
  /* USER CODE 1 END */
  /* This message must NOT be changed. */
  th_printf(EE_MSG_TIMESTAMP_MODE);
  /* Always call the timestamp on initialize so that the open-drain output
     is set to "1" (so that we catch a falling edge) */
  th_timestamp();
}

#if CONFIG_SHELL
static char cmd_buf[128];
K_SEM_DEFINE(start_sem, 0, 1);

static int cmd_start(const struct shell *shell, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);

  size_t len = 0;

  for (size_t i = 1; i < argc; ++i) {
    int err;
    err = snprintf(&cmd_buf[len], sizeof(cmd_buf) - len, "%s ", argv[i]);
    if ((len + err) > sizeof(cmd_buf) || err < 0) {
      shell_print(shell, "Format error");
      return 0;
    }
    len += err;
  }
  if (len > 0) {
    cmd_buf[len - 1] = '\0';
  }

  // shell_print(shell, "cmd_buf %s", cmd_buf);

  k_sem_give(&start_sem);

  // if (argc < 2) {
  //   shell_print(shell, "Zephyr version", 1);
  // }
	// // shell_print(shell, "Zephyr version", 1);
  // size_t cpy_len = strlen;

	return 0;
}

SHELL_CMD_ARG_REGISTER(start, 0, "test", cmd_start, 1, 10);

#endif /* CONFIG_SHELL */


int main(int argc, char *argv[]) {
console_init();
printk("#### \n");

ee_benchmark_initialize();
#if CONFIG_SHELL
while (1) {
  k_sem_take(&start_sem, K_FOREVER);
  int c;
  for (size_t i = 0; i < strlen(cmd_buf); ++i) {
    c = (int) cmd_buf[i];
    ee_serial_callback(c);
  }
  }
#else
  console_init();
  
  
  
  
    while (1) {
    int c;

    c = console_getchar();
    if (c < 0) {
      continue;
    }
    // printk("c: %d", c);
    ee_serial_callback(c);
  }
#endif /* CONFIG_SHELL */
  //   while (1) {
      
  //     int c;
  //     c = th_getchar();
      //  ee_serial_callback(c);
  //   }
  return 0;
} 