/**
 * @file logsimtypes.h
 * @author Suraj Kareppagol (surajkareppagol.dev@gmail.com)
 * @brief LogSim types.
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef LOG_SIM_TYPES_H
#define LOG_SIM_TYPES_H

/*************** C Standard Headers ***************/

#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>

/*************** Macros ***************/

#define TRUE 1
#define FALSE 0

#define DIR_SVG "svg"
#define DIR_LOG "logs"
#define BUFFER 1024

/*************** Variables ***************/

extern GVC_t *g_graphviz_context;
extern Agraph_t *g_graphviz_graph;

/*************** Enums ***************/

typedef enum logic_block_type { AND, OR, NOT, XOR } logic_block_type_t;

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
  char *prefix;
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

#endif

/************************************************/
/*                EOF                           */
/************************************************/
