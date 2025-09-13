/**
 * @file logsimlib.h
 * @author Suraj Kareppagol (surajkareppagol.dev@gmail.com)
 * @brief LogSim provides a set of functions and macros to simulate logic gates.
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef LOG_SIM_LIB_H
#define LOG_SIM_LIB_H

/*************** C Standard Headers ***************/

#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>

/*************** C Custom Headers ***************/

#include "logsimtypes.h"

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
 * @brief Utility function.
 *
 * @param name
 */
void logic_utility_init(char *name);

/**
 * @brief Close all the resources.
 */
void logic_utility_terminate();

/**
 * @brief Create a top level logic block.
 *
 * @param logic_top_block_type
 * @return logic_top_block_t*
 */
logic_top_block_t *
logic_create_top_block(logic_top_block_type_t logic_top_block_type);

/**
 * @brief Create a logic block.
 *
 * @param logic_block_type
 * @param inputs
 * @param outputs
 * @param name
 * @param prefix
 * @return logic_block_t*
 */
logic_block_t *logic_create_logic_block(logic_block_type_t logic_block_type,
                                        int inputs, int outputs, char *name,
                                        char *prefix);

/**
 * @brief Create a logic data block.
 *
 * @param logic_data_type
 * @param data
 * @return logic_data_t*
 */
logic_data_t *logic_create_data_block(logic_data_type_t logic_data_type,
                                      int data);

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
 * @brief Process logic data.
 *
 * @param logic_block_type
 * @param input_a
 * @param input_b
 * @return int
 */
int logic_process_data(logic_block_type_t logic_block_type, int input_a,
                       int input_b);

/**
 * @brief Get initialization value.
 *
 * @param type
 * @return int
 */
int logic_get_initalization_value(logic_block_type_t type);

/**
 * @brief Evaluate all the connected blocks.
 *
 * @param logic_block
 * @param previous_node
 * @return int
 */
int logic_evaluate_single_block(logic_block_t *logic_block,
                                Agnode_t *previous_node);

/**
 * @brief Evaluate all the output blocks.
 *
 * @param total_logic_blocks
 * @param ...
 * @return int
 */
int logic_evaluate(int total_logic_blocks, ...);

/**
 * @brief Print the data field to console.
 *
 * @param logic_data
 * @return int
 */
int logic_console(logic_block_t *logic_data);

#endif

/************************************************/
/*                EOF                           */
/************************************************/
