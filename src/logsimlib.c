/**
 * @file logsimlib.c
 * @author Suraj Kareppagol (surajkareppagol.dev@gmail.com)
 * @brief LogSim provides a set of functions and macros to simulate logic gates.
 *
 * @copyright Copyright (c) 2025
 *
 */

/*************** C Standard Headers ***************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

/*************** C Custom Headers ***************/

#include "../include/logsimlib.h"
#include "../include/utils.h"

/*************** Variables ***************/

GVC_t *g_graphviz_context = NULL;
Agraph_t *g_graphviz_graph = NULL;

FILE *g_log_file = NULL;
FILE *g_debug_log_file = NULL;

/*************** Function Definitions ***************/

void logic_graph_init(char *name) {
  g_graphviz_context = gvContext();
  g_graphviz_graph = agopen(name, Agundirected, NULL);

  agattr(g_graphviz_graph, AGNODE, "shape", "ellipse");

  agattr(g_graphviz_graph, AGRAPH, "rankdir", "LR");
  agattr(g_graphviz_graph, AGRAPH, "splines", "ortho");
}

void logic_graph_export(char *name) {
  gvLayout(g_graphviz_context, g_graphviz_graph, "dot");

  char svg_path[1024];
  snprintf(svg_path, sizeof(svg_path), "%s/%s", DIR_SVG, name);

  mkdir(DIR_SVG, 0755);

  gvRenderFilename(g_graphviz_context, g_graphviz_graph, "svg", svg_path);

  gvFreeLayout(g_graphviz_context, g_graphviz_graph);
  agclose(g_graphviz_graph);
  gvFreeContext(g_graphviz_context);
}

void logic_utility_init(char *name) {

  char log_path[1024];
  snprintf(log_path, sizeof(log_path), "%s/%s", DIR_LOG, name);

  mkdir(DIR_LOG, 0755);

  g_log_file = fopen(log_path, "w");

  LOG_SIM_FILE_PRINT(g_log_file, "+-----------------+--------+-------+");
  LOG_SIM_FILE_PRINT(g_log_file, "|   BLOCK         | TYPE   | DATA  |");
  LOG_SIM_FILE_PRINT(g_log_file, "+-----------------+--------+-------+");

  /**************************************/

  memset(log_path, 0, sizeof(log_path));
  snprintf(log_path, sizeof(log_path), "%s/%s", DIR_LOG, "debug.log");

  g_debug_log_file = fopen(log_path, "w");
}

void logic_utility_terminate() {
  fclose(g_log_file);
  fclose(g_debug_log_file);
}

logic_output_block_t *logic_output_block(int logic_blocks) {
  logic_output_block_t *logic_output_block = NULL;

  logic_output_block = calloc(1, sizeof(logic_output_block_t));

  logic_output_block->total_blocks = logic_blocks;

  logic_output_block->logic_blocks =
      calloc(logic_blocks, sizeof(logic_block_t *));

  return logic_output_block;
}

logic_block_t *logic_block(logic_block_type_t logic_block_type, int inputs,
                           int outputs, char *name, char *prefix) {
  logic_block_t *logic_block = NULL;

  logic_block = calloc(1, sizeof(logic_block_t));

  logic_block->name = name;
  logic_block->prefix = prefix;
  logic_block->logic_block_type = logic_block_type;
  logic_block->inputs = inputs;
  logic_block->outputs = outputs;

  logic_block->input_streams = calloc(inputs, sizeof(logic_top_block_t *));

  logic_block->output_streams = calloc(outputs, sizeof(logic_top_block_t *));

  /* Create all the top level blocks */
  for (int i = 0; i < inputs; i++) {
    logic_block->input_streams[i] = logic_top_block(NONE);
  }

  for (int i = 0; i < outputs; i++) {
    logic_block->output_streams[i] = logic_top_block(NONE);
  }

  logic_block->current_input = 0;
  logic_block->current_output = 0;

  return logic_block;
}

logic_data_t *logic_data(logic_data_type_t logic_data_type, int data) {
  logic_data_t *logic_data = NULL;

  logic_data = calloc(1, sizeof(logic_data_t));

  logic_data->logic_data_type = logic_data_type;
  logic_data->data = data;

  logic_data->status = NOT_EVALUATED;

  return logic_data;
}

logic_top_block_t *
logic_top_block(logic_top_block_type_t logic_top_block_type) {
  logic_top_block_t *logic_top_block = NULL;

  logic_top_block = calloc(1, sizeof(logic_top_block_t));

  logic_top_block->logic_top_block_type = logic_top_block_type;

  logic_top_block->logic_block = NULL;
  logic_top_block->logic_data = NULL;

  return logic_top_block;
}

int logic_block_data_connect(logic_block_t *logic_block,
                             logic_data_t *logic_data) {
  if (logic_block == NULL || logic_data == NULL) {
    return -1;
  }

  logic_data_type_t logic_data_type = logic_data->logic_data_type;

  switch (logic_data_type) {
  case INPUT: {
    int current_input_block = logic_block->current_input;

    /* Assign data block */
    logic_block->input_streams[current_input_block]->logic_top_block_type =
        DATA_BLOCK;
    logic_block->input_streams[current_input_block]->logic_data = logic_data;

    logic_block->current_input += 1;

    break;
  }
  case OUTPUT: {
    int current_output_block = logic_block->current_output;

    /* Assign data block */
    logic_block->output_streams[current_output_block]->logic_top_block_type =
        DATA_BLOCK;
    logic_block->output_streams[current_output_block]->logic_data = logic_data;

    logic_block->current_output += 1;

    break;
  }
  }

  return 0;
}

int logic_block_block_connect(logic_block_t *logic_block,
                              logic_block_t *logic_block_in) {
  if (logic_block_in == NULL || logic_block == NULL) {
    return -1;
  }

  int current_input_block = logic_block->current_input;

  /* Assign data block */
  logic_block->input_streams[current_input_block]->logic_top_block_type =
      LOGIC_BLOCK;
  logic_block->input_streams[current_input_block]->logic_block = logic_block_in;

  logic_block->current_input += 1;

  return 0;
}

int logic_process_data(logic_block_type_t logic_block_type, int input_a,
                       int input_b) {
  switch (logic_block_type) {
  case AND: {
    return input_a & input_b;
  }

  case OR: {
    return input_a | input_b;
  }

  case XOR: {
    return input_a ^ input_b;
  }

  case NOT: {
    return !input_b;
  }
  }

  return 0;
}

int logic_get_initalization_value(logic_block_type_t type) {
  switch (type) {
  case AND:
    return 1;
  case OR:
    return 0;
  case XOR:
    return 0;
  case NOT:
    return 1;
  }

  return 0;
}

int logic_eval_all(logic_block_t *logic_block, Agnode_t *previous_node) {
  if (logic_block == NULL) {
    LOG_SIM_DEBUG_PRINT(g_debug_log_file, "No data found.");
    return -1;
  }

  LOG_SIM_DEBUG_PRINT(g_debug_log_file, "Evaluating logic block (%s).",
                      logic_block->name);

  /* Create graph node */
  Agnode_t *node =
      util_create_edge(logic_block->name, logic_block->logic_block_type);

  /* Add an edge from node to previous_node */
  if (previous_node != NULL) {
    LOG_SIM_DEBUG_PRINT(
        g_debug_log_file, "(Previous Node: %s) Connecting (%s) -> (%s).",
        agnameof(previous_node), agnameof(node), agnameof(previous_node));

    agedge(g_graphviz_graph, node, previous_node, NULL, TRUE);
  }

  logic_block->graph_node = node;

  /* Loop over the input streams and check the connected block */
  int logic_inputs = logic_block->inputs;
  int logic_output = logic_block->outputs;

  for (int i = 0; i < logic_output; i++) {
    /* Evaluation result */
    int logic_eval_result =
        logic_get_initalization_value(logic_block->logic_block_type);

    for (int j = 0; j < logic_inputs; j++) {
      logic_top_block_t *logic_top_block = logic_block->input_streams[j];

      /* If it is logic block then recursively evaluate it */
      switch (logic_top_block->logic_top_block_type) {
      case LOGIC_BLOCK: {
        if (logic_top_block->logic_block->output_streams[0]
                ->logic_data->status == NOT_EVALUATED) {
          logic_eval_all(logic_top_block->logic_block, node);
        } else {

          agedge(g_graphviz_graph, logic_top_block->logic_block->graph_node,
                 node, NULL, TRUE);
        }

        /* Use the data from the result */
        logic_block_type_t logic_block_type = logic_block->logic_block_type;

        int input_a = logic_eval_result;
        int input_b =
            logic_top_block->logic_block->output_streams[0]->logic_data->data;

        logic_eval_result =
            logic_process_data(logic_block_type, input_a, input_b);

        break;
      }
      case DATA_BLOCK: {
        /* Create unique name for data node */
        util_attach_invisible_edge(logic_block->name, j,
                                   logic_block->graph_node);

        /* Get the top logic block */
        logic_block_type_t logic_block_type = logic_block->logic_block_type;

        int input_a = logic_eval_result;
        int input_b = logic_top_block->logic_data->data;

        logic_eval_result =
            logic_process_data(logic_block_type, input_a, input_b);

        break;
      }
      case NONE: {
        break;
      }
      }
    }

    /* Write to output data block */
    logic_block->output_streams[i]->logic_data->data = logic_eval_result;
    logic_block->output_streams[i]->logic_data->status = EVALUATED;
  }

  logic_console(logic_block);

  return 0;
}

int logic_eval_all_output_blocks(logic_output_block_t *logic_output_block) {
  if (logic_output_block == NULL) {
    return -1;
  }

  for (int i = 0; i < logic_output_block->total_blocks; i++) {
    logic_eval_all(logic_output_block->logic_blocks[i], NULL);
  }

  /* Add output invible nodes */
  for (int i = 0; i < logic_output_block->total_blocks; i++) {
    util_attach_invisible_edge(logic_output_block->logic_blocks[i]->name, i,
                               logic_output_block->logic_blocks[i]->graph_node);
  }

  return 0;
}

int logic_console(logic_block_t *logic_block) {
  if (logic_block == NULL) {
    LOG_SIM_DEBUG_PRINT(g_debug_log_file, "No data found.");

    return -1;
  }

  int logic_inputs = logic_block->inputs;

  LOG_SIM_LOG_PRINT("----------\n"
                    "| LOGSIM |\n"
                    "----------\n");

  LOG_SIM_LOG_PRINT("Result for logic block (%s)\n"
                    "---------------------------",
                    logic_block->name);

#if 1
  for (int i = 0; i < logic_inputs; i++) {
    if (logic_block->input_streams[i]->logic_top_block_type == LOGIC_BLOCK) {
      int input = logic_block->input_streams[i]
                      ->logic_block->output_streams[0]
                      ->logic_data->data;

      LOG_SIM_LOG_PRINT("INPUT Found (%d).", input);

      LOG_SIM_FILE_PRINT(g_log_file, "| %-5s (%-5s)   | INPUT  | %d     |",
                         logic_block->name,
                         logic_block->prefix ? logic_block->prefix : "", input);

    } else {
      int input = logic_block->input_streams[i]->logic_data->data;
      LOG_SIM_LOG_PRINT("INPUT Found (%d).", input);

      LOG_SIM_FILE_PRINT(g_log_file, "| %-5s (%-5s)   | INPUT  | %d     |",
                         logic_block->name,
                         logic_block->prefix ? logic_block->prefix : "", input);
    }
  }
#endif

  int output = logic_block->output_streams[0]->logic_data->data;

  LOG_SIM_LOG_PRINT("OUTPUT data found (%d).", output);

  LOG_SIM_FILE_PRINT(g_log_file, "| %-5s (%-5s)   | OUTPUT | %d     |",
                     logic_block->name,
                     logic_block->prefix ? logic_block->prefix : "", output);

  LOG_SIM_FILE_PRINT(g_log_file, "+-----------------+--------+-------+");

  return 0;
}

/************************************************/
/*                EOF                           */
/************************************************/
