/* Copyright 2020 The MLPerf Authors. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
/// \file
/// \brief Main function to run benchmark on device.

//#include <zephyr.h>
//#include <sys/printk.h>
//#include <drivers/uart.h>

//#include <shell/shell.h>
//#include <console/console.h>


// #include "internally_implemented.h"
// #include "submitter_implemented.h"


// #if CONFIG_SHELL
// static char cmd_buf[128];
// K_SEM_DEFINE(start_sem, 0, 1);

// static int cmd_start(const struct shell *shell, size_t argc, char **argv)
// {
// 	ARG_UNUSED(argc);
// 	ARG_UNUSED(argv);

//   size_t len = 0;

//   for (size_t i = 1; i < argc; ++i) {
//     int err;
//     err = snprintf(&cmd_buf[len], sizeof(cmd_buf) - len, "%s ", argv[i]);
//     if ((len + err) > sizeof(cmd_buf) || err < 0) {
//       shell_print(shell, "Format error");
//       return 0;
//     }
//     len += err;
//   }
//   if (len > 0) {
//     cmd_buf[len - 1] = '\0';
//   }

//   // shell_print(shell, "cmd_buf %s", cmd_buf);

//   k_sem_give(&start_sem);

//   // if (argc < 2) {
//   //   shell_print(shell, "Zephyr version", 1);
//   // }
// 	// // shell_print(shell, "Zephyr version", 1);
//   // size_t cpy_len = strlen;

// 	return 0;
// }

// SHELL_CMD_ARG_REGISTER(start, 0, "test", cmd_start, 1, 10);

// #endif /* CONFIG_SHELL */


// int main(int argc, char *argv[]) {
// console_init();

// ee_benchmark_initialize();
// #if CONFIG_SHELL
// while (1) {
//   k_sem_take(&start_sem, K_FOREVER);
//   int c;
//   for (size_t i = 0; i < strlen(cmd_buf); ++i) {
//     c = (int) cmd_buf[i];
//     ee_serial_callback(c);
//   }
//   }
// #else
//   console_init();

//   while (1) {
//     int c;

//     c = console_getchar();
//     if (c < 0) {
//       continue;
//     }
//     // printk("c: %d", c);
//     ee_serial_callback(c);
//   }
// #endif /* CONFIG_SHELL */
//   //   while (1) {
      
//   //     int c;
//   //     c = th_getchar();
//       //  ee_serial_callback(c);
//   //   }
//   return 0;
// } 