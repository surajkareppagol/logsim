/**
 * @file logsimlib.h
 * @author Suraj Kareppagol (surajkareppagol.dev@gmail.com)
 * @brief LogSim provides a set of functions and macros to simulate logic gates.
 * @version 0.1
 * @date 2025-09-09
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef LOG_SIM_LIB_H
#define LOG_SIM_LIB_H

/*************** C Standard Headers ***************/

#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>

/*************** Enums ***************/

typedef enum logic_block_type { AND, OR } logic_block_type_t;

typedef enum logic_data_type { INPUT, OUTPUT } logic_data_type_t;

typedef enum logic_top_block_type {
  LOGIC_BLOCK,
  DATA_BLOCK,
  NONE
} logic_top_block_type_t;

typedef enum logic_data_block_status {
  EVALUATED,
  NOT_EVALUATED
} logic_data_block_status_t;

/*************** Structures ***************/

typedef struct logic_top_block logic_top_block_t;

typedef struct logic_data {
  int data;
  int logic_data_type; /* INPUT | OUTPUT */

  int status;
} logic_data_t;

typedef struct logic_block {
  logic_block_type_t logic_block_type;

  char *name;
  Agnode_t *graph_node;

  /* Use these to loop over input and output streams */
  int inputs;
  int outputs;

  int current_input;
  int current_output;

  logic_top_block_t **input_streams;
  logic_top_block_t **output_streams;

} logic_block_t;

typedef struct logic_top_block {
  logic_top_block_type_t logic_top_block_type;

  logic_block_t *logic_block;
  logic_data_t *logic_data;

} logic_top_block_t;

/* For multi output circuits */
typedef struct logic_output_block {
  logic_block_t **logic_blocks;
  int total_blocks;

} logic_output_block_t;

/*************** Function Prototypes ***************/

/**
 * @brief Initialize graphviz.
 *
 * @param name
 */
void logic_graph_init(char *name);

/**
 * @brief Export graph as SVG.
 *
 * @param name
 */
void logic_graph_export(char *name);

/**
 * @brief Create logic output block.
 *
 * @param logic_blocks
 * @return logic_output_block_t*
 */
logic_output_block_t *logic_output_block(int logic_blocks);

/**
 * @brief Create a logic block.
 *
 * @param logic_block_type
 * @param inputs
 * @param outputs
 * @param name
 * @return logic_block_t*
 */
logic_block_t *logic_block(logic_block_type_t logic_block_type, int inputs,
                           int outputs, char *name);

/**
 * @brief Create a logic data block.
 *
 * @param logic_data_type
 * @param data
 * @return logic_data_t*
 */
logic_data_t *logic_data(logic_data_type_t logic_data_type, int data);

/**
 * @brief Create a top level logic block.
 *
 * @param logic_top_block_type
 * @return logic_top_block_t*
 */
logic_top_block_t *logic_top_block(logic_top_block_type_t logic_top_block_type);

/**
 * @brief Connect a logical block with data block.
 *
 * @param logic_block
 * @param logic_data
 * @return int
 */
int logic_block_data_connect(logic_block_t *logic_block,
                             logic_data_t *logic_data);

/**
 * @brief Connect a logical block with logical block.
 *
 * @param logic_block
 * @param logic_block_in
 * @return int
 */
int logic_block_block_connect(logic_block_t *logic_block,
                              logic_block_t *logic_block_in);

/**
 * @brief Evaluate the single logic gate and write to the output block.
 *
 * @param logic_block
 * @return int
 */
int logic_eval_single_block(logic_block_t *logic_block);

/**
 * @brief Evaluate all the connected blocks.
 *
 * @param logic_block
 * @param previous_node
 * @return int
 */
int logic_eval_all(logic_block_t *logic_block, Agnode_t *previous_node);

/**
 * @brief Evaluate all the connected blocks from the output block.
 *
 * @param logic_output_block
 * @return int
 */
int logic_eval_all_output_blocks(logic_output_block_t *logic_output_block);

/**
 * @brief Print the data field to console.
 *
 * @param logic_data
 * @return int
 */
int logic_console(logic_block_t *logic_data);

#endif