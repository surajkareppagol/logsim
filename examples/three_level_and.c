/**
 * @file three_level_and.c
 * @author Suraj Kareppagol (surajkareppagol.dev@gmail.com)
 * @brief Example for three level AND gate.
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

  logic_graph_init("three_level_and");
  logic_utility_init("three_level_and.log");

  /*
   * ---|===|
   *    | 4 |---|===|
   * ---|===|   | 2 |---|
   *          |-|===|   |
   * ---|===| |         |---|===|
   *    | 5 |-|             | 1 |---
   * ---|===| |         |---|===|
   *          |         |
   * ---|===| |-|===|   |
   *    | 6 |---| 3 |---|
   * ---|===|   |===|
   */

  /************************ Create 3 blocks ************************/
  printf("LOG: Creating logic blocks.\n");

  logic_block_t *lb_1 = logic_block(AND, 2, 1, "lb_1", "OUT");
  logic_block_t *lb_2 = logic_block(AND, 2, 1, "lb_2", NULL);
  logic_block_t *lb_3 = logic_block(AND, 2, 1, "lb_3", NULL);
  logic_block_t *lb_4 = logic_block(AND, 2, 1, "lb_4", NULL);
  logic_block_t *lb_5 = logic_block(AND, 2, 1, "lb_5", NULL);
  logic_block_t *lb_6 = logic_block(AND, 2, 1, "lb_6", NULL);

  /************************ Create 6 input blocks ************************/

  printf("LOG: Creating data blocks.\n");

  logic_data_t *lb_i_4_1 = logic_data(INPUT, 1);
  logic_data_t *lb_i_4_2 = logic_data(INPUT, 0);

  logic_data_t *lb_i_5_1 = logic_data(INPUT, 1);
  logic_data_t *lb_i_5_2 = logic_data(INPUT, 1);

  logic_data_t *lb_i_6_1 = logic_data(INPUT, 1);
  logic_data_t *lb_i_6_2 = logic_data(INPUT, 1);

  /************************ Create 3 output blocks ************************/

  logic_data_t *lb_o_1_1 = logic_data(OUTPUT, 0);
  logic_data_t *lb_o_2_1 = logic_data(OUTPUT, 0);
  logic_data_t *lb_o_3_1 = logic_data(OUTPUT, 0);
  logic_data_t *lb_o_4_1 = logic_data(OUTPUT, 0);
  logic_data_t *lb_o_5_1 = logic_data(OUTPUT, 0);
  logic_data_t *lb_o_6_1 = logic_data(OUTPUT, 0);

  /************************ Connect block 1 ************************/

  printf("LOG: Connecting logic-logic blocks.\n");

  /* Connect block 2 to block 1 as input */
  logic_block_block_connect(lb_1, lb_2);
  logic_block_block_connect(lb_1, lb_3);

  logic_block_data_connect(lb_1, lb_o_1_1);

  /************************ Connect block 2 ************************/

  printf("LOG: Connecting logic-data blocks.\n");

  logic_block_block_connect(lb_2, lb_4);
  logic_block_block_connect(lb_2, lb_5);

  logic_block_data_connect(lb_2, lb_o_2_1);

  /************************ Connect block 3 ************************/

  logic_block_block_connect(lb_3, lb_5);
  logic_block_block_connect(lb_3, lb_6);

  logic_block_data_connect(lb_3, lb_o_3_1);

  /************************ Connect block 4 ************************/

  logic_block_data_connect(lb_4, lb_i_4_1);
  logic_block_data_connect(lb_4, lb_i_4_2);

  logic_block_data_connect(lb_4, lb_o_4_1);

  /************************ Connect block 5 ************************/

  logic_block_data_connect(lb_5, lb_i_5_1);
  logic_block_data_connect(lb_5, lb_i_5_2);

  logic_block_data_connect(lb_5, lb_o_5_1);

  /************************ Connect block 6 ************************/

  logic_block_data_connect(lb_6, lb_i_6_1);
  logic_block_data_connect(lb_6, lb_i_6_2);

  logic_block_data_connect(lb_6, lb_o_6_1);

  /************************ Evaluate ************************/

  printf("LOG: Evaluating all blocks .\n");

  logic_output_block_t *lob = logic_output_block(1);

  lob->logic_blocks[0] = lb_1;

  logic_eval_all_output_blocks(lob);

  logic_graph_export("three_level_and.svg");
  logic_utility_terminate();

  return 0;
}

/************************************************/
/*                EOF                           */
/************************************************/
