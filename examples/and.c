/**
 * @file and.c
 * @author Suraj Kareppagol (surajkareppagol.dev@gmail.com)
 * @brief Example for AND gate.
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

  logic_graph_init("and");
  logic_utility_init("and.log");

  /* Create logic block */
  logic_block_t *lb = logic_create_logic_block(AND, 2, 1, "lb", NULL);

  printf("LOG: Creating input blocks.\n");

  /* Create data block */
  logic_data_t *input_a = logic_create_data_block(INPUT, 1);
  logic_data_t *input_b = logic_create_data_block(INPUT, 0);

  printf("LOG: Creating output blocks.\n");

  logic_data_t *output = logic_create_data_block(OUTPUT, 0);

  printf("LOG: Connecting input blocks.\n");

  /* Connect data block to logic block */
  logic_block_data_connect(lb, input_a);
  logic_block_data_connect(lb, input_b);

  printf("LOG: Connecting output blocks.\n");

  logic_block_data_connect(lb, output);

  /* Evaluate */
  printf("LOG: Evaluating all blocks .\n");

  logic_evaluate(1, lb);

  logic_graph_export("and.svg");
  logic_utility_terminate();

  return 0;
}

/************************************************/
/*                EOF                           */
/************************************************/
