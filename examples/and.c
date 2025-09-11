/**
 * @file and.c
 * @author Suraj Kareppagol (surajkareppagol.dev@gmail.com)
 * @brief Example for AND gate.
 * @version 0.1
 * @date 2025-09-09
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
  logic_block_t *lb = logic_block(AND, 2, 1, "lb", NULL);

  printf("LOG: Creating input blocks.\n");

  /* Create data block */
  logic_data_t *input_a = logic_data(INPUT, 1);
  logic_data_t *input_b = logic_data(INPUT, 0);

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

  logic_output_block_t *lob = logic_output_block(1);

  lob->logic_blocks[0] = lb;

  logic_eval_all_output_blocks(lob);

  logic_graph_export("and.svg");
  logic_utility_terminate();

  return 0;
}

/************************************************/
/*                EOF                           */
/************************************************/
