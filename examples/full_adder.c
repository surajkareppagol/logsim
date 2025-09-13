/**
 * @file full_adder.c
 * @author Suraj Kareppagol (surajkareppagol.dev@gmail.com)
 * @brief Example for full adder.
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

  logic_graph_init("full_adder");
  logic_utility_init("full_adder.log");

  /*
   *                 XOR
   * A -------------|===|
   *            |   | 5 |-----------|
   * B ----|----|---|===|   |       |            XOR
   *       |    |           |       |-----------|===|
   *       |    |           |                   | 2 |----- SUM
   * C ---------------------|-------------------|===|
   *       |    |           |       |
   *       |    |           |       |            AND
   *       |    |           |       |-----------|===|
   *       |    |           |                   | 3 |-----      OR
   *       |    |           |-------------------|===|    |     |===|
   *       |    |                                        |-----| 1 |--- CARRY
   *       |    |                                AND     |     |===|
   *       |    |                               |===|    |
   *       |    |-------------------------------| 4 |----- CARRY
   *       |------------------------------------|===|
   */

  /************************ Create 3 blocks ************************/
  printf("LOG: Creating logic blocks.\n");

  logic_block_t *lb_1 = logic_create_logic_block(OR, 2, 1, "lb_1", "CARRY");
  logic_block_t *lb_2 = logic_create_logic_block(XOR, 2, 1, "lb_2", "SUM");
  logic_block_t *lb_3 = logic_create_logic_block(AND, 2, 1, "lb_3", NULL);
  logic_block_t *lb_4 = logic_create_logic_block(AND, 2, 1, "lb_4", NULL);
  logic_block_t *lb_5 = logic_create_logic_block(XOR, 2, 1, "lb_5", NULL);

  /************************ Create 6 input blocks ************************/

  printf("LOG: Creating data blocks.\n");

  logic_data_t *lb_i_5_1 = logic_create_data_block(INPUT, 1);
  logic_data_t *lb_i_5_2 = logic_create_data_block(INPUT, 0);

  logic_data_t *lb_i_4_1 = logic_create_data_block(INPUT, 1);
  logic_data_t *lb_i_4_2 = logic_create_data_block(INPUT, 0);

  logic_data_t *lb_i_2_2 = logic_create_data_block(INPUT, 0);

  logic_data_t *lb_i_3_1 = logic_create_data_block(INPUT, 0);

  /************************ Create 3 output blocks ************************/

  logic_data_t *lb_o_1_1 = logic_create_data_block(OUTPUT, 0);
  logic_data_t *lb_o_2_1 = logic_create_data_block(OUTPUT, 0);
  logic_data_t *lb_o_3_1 = logic_create_data_block(OUTPUT, 0);
  logic_data_t *lb_o_4_1 = logic_create_data_block(OUTPUT, 0);
  logic_data_t *lb_o_5_1 = logic_create_data_block(OUTPUT, 0);

  /************************ Connections ************************/

  printf("LOG: Connecting logic-data blocks.\n");

  /* Connections for block 1 */
  logic_block_block_connect(lb_1, lb_3);
  logic_block_block_connect(lb_1, lb_4);

  logic_block_data_connect(lb_1, lb_o_1_1);

  /* Connections for block 2 */
  logic_block_block_connect(lb_2, lb_5);
  logic_block_data_connect(lb_2, lb_i_2_2);

  logic_block_data_connect(lb_2, lb_o_2_1);

  /* Connections for block 3 */
  logic_block_data_connect(lb_3, lb_i_3_1);
  logic_block_block_connect(lb_3, lb_5);

  logic_block_data_connect(lb_3, lb_o_3_1);

  /* Connections for block 4 */
  logic_block_data_connect(lb_4, lb_i_4_1);
  logic_block_data_connect(lb_4, lb_i_4_2);

  logic_block_data_connect(lb_4, lb_o_4_1);

  /* Connections for block 5 */
  logic_block_data_connect(lb_5, lb_i_5_1);
  logic_block_data_connect(lb_5, lb_i_5_2);

  logic_block_data_connect(lb_5, lb_o_5_1);

  /************************ Evaluate ************************/

  printf("LOG: Evaluating all blocks .\n");

  /************************ Evaluate ************************/

  logic_evaluate(2, lb_1, lb_2);

  logic_graph_export("full_adder.svg");
  logic_utility_terminate();

  return 0;
}

/************************************************/
/*                EOF                           */
/************************************************/
