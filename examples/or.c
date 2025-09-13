/**
 * @file or.c
 * @author Suraj Kareppagol (surajkareppagol.dev@gmail.com)
 * @brief Example for OR gate.
 *
 * @copyright Copyright (c) 2025
 *
 */

/*************** C Standard Headers ***************/

#include <stdio.h>

/*************** C Custom Headers ***************/

#include "logsimlib.h"

/*************** Function Definitions ***************/

int main() {
  printf("LOG: Creating the logic block.\n");

  logic_graph_init("or");
  logic_utility_init("or.log");

  /* Create logic block */
  logic_block_t *lb = logic_block(OR, 2, 1, "lb", NULL);

  printf("LOG: Creating input blocks.\n");

  /* Create data block */
  logic_data_t *input_a = logic_data(INPUT, 1);
  logic_data_t *input_b = logic_data(INPUT, 1);

  printf("LOG: Creating output blocks.\n");

  logic_data_t *output = logic_data(OUTPUT, 0);

  printf("LOG: Connecting input blocks.\n");

  /* Connect data block to logic block */
  logic_block_data_connect(lb, input_a);
  logic_block_data_connect(lb, input_b);

  printf("LOG: Connecting output blocks.\n");

  logic_block_data_connect(lb, output);

  /* Evaluate */
  printf("LOG: Evaluating all blocks .\n");

  logic_evaluate(1, lb);

  logic_graph_export("or.svg");
  logic_utility_terminate();

  return 0;
}

/************************************************/
/*                EOF                           */
/************************************************/
