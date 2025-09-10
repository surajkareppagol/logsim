/**
 * @file logsimlib.c
 * @author Suraj Kareppagol (surajkareppagol.dev@gmail.com)
 * @brief LogSim provides a set of functions and macros to simulate logic gates.
 * @version 0.1
 * @date 2025-09-09
 *
 * @copyright Copyright (c) 2025
 *
 */

/*************** C Standard Headers ***************/

#include <stdio.h>
#include <stdlib.h>

/*************** C Custom Headers ***************/

#include "../include/logsimlib.h"

/*************** Macros ***************/

#define TRUE 1
#define FALSE 0

/*************** Variables ***************/

GVC_t *g_graphviz_context = NULL;
Agraph_t *g_graphviz_graph = NULL;

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
  gvRenderFilename(g_graphviz_context, g_graphviz_graph, "svg", name);

  gvFreeLayout(g_graphviz_context, g_graphviz_graph);
  agclose(g_graphviz_graph);
  gvFreeContext(g_graphviz_context);
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
                           int outputs, char *name) {
  logic_block_t *logic_block = NULL;

  logic_block = calloc(1, sizeof(logic_block_t));

  logic_block->name = name;
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

int logic_eval_single_block(logic_block_t *logic_block) {
  if (logic_block == NULL) {
    return -1;
  }

  logic_block_type_t logic_block_type = logic_block->logic_block_type;

  int logic_inputs = logic_block->inputs;
  int logic_output = logic_block->outputs;

  for (int i = 0; i < logic_output; i++) {

    /* Save the initial value */
    int logic_eval_result = 1;

    for (int j = 0; j < logic_inputs; j++) {
      switch (logic_block_type) {
      case AND: {
        logic_eval_result = logic_eval_result &&
                            logic_block->input_streams[j]->logic_data->data;
        break;
      }

      case OR: {
        logic_eval_result = logic_eval_result ||
                            logic_block->input_streams[j]->logic_data->data;
        break;
      }
      }
    }

    /* Write to output data block */
    logic_block->output_streams[i]->logic_data->data = logic_eval_result;
    logic_block->output_streams[i]->logic_data->status = EVALUATED;
  }

  return 0;
}

int logic_eval_all(logic_block_t *logic_block, Agnode_t *previous_node) {
  if (logic_block == NULL) {
    printf("LOG: No data found.\n");
    return -1;
  }

  /* Create graph node */

  Agnode_t *node = agnode(g_graphviz_graph, logic_block->name, TRUE);

  switch (logic_block->logic_block_type) {
  case AND: {
    agset(node, "label", "AND");
    break;
  }
  case OR: {
    node = agnode(g_graphviz_graph, logic_block->name, TRUE);
    agset(node, "label", "OR");
    break;
  }
  }

  printf("LOG: Evaluating logic block (%s).\n", logic_block->name);

  agset(node, "shape", "rectangle");

  if (previous_node != NULL) {
    printf("LOG: (PREVIOUS NODE: %s) Connecting (%s) -> (%s).\n",
           agnameof(previous_node), agnameof(node), agnameof(previous_node));
    agedge(g_graphviz_graph, node, previous_node, NULL, TRUE);
  }

  logic_block->graph_node = node;

  /* Loop over the input streams and check the connected block */
  int logic_inputs = logic_block->inputs;
  int logic_output = logic_block->outputs;

  /* Save the initial value */

  for (int i = 0; i < logic_output; i++) {
    int logic_eval_result = 1;

    for (int j = 0; j < logic_inputs; j++) {
      logic_top_block_t *logic_top_block = logic_block->input_streams[j];

      /* If it is logic block then recursively evaluate it */
      switch (logic_top_block->logic_top_block_type) {
      case LOGIC_BLOCK: {
        if (logic_top_block->logic_block->output_streams[0]
                ->logic_data->status == NOT_EVALUATED) {
          logic_eval_all(logic_top_block->logic_block, node);
        } else {
#if 0
          printf("LOG: (PREVIOUS NODE: %s) Connecting (%s) -> (%s).\n",
                 agnameof(previous_node), agnameof(node),
                 agnameof(previous_node));
#endif
          agedge(g_graphviz_graph, logic_top_block->logic_block->graph_node,
                 node, NULL, TRUE);
        }

        /* Use the data from the result */
        logic_block_type_t logic_block_type = logic_block->logic_block_type;

        switch (logic_block_type) {
        case AND: {
          logic_eval_result =
              logic_eval_result &&
              logic_top_block->logic_block->output_streams[0]->logic_data->data;
          break;
        }

        case OR: {
          logic_eval_result =
              logic_eval_result ||
              logic_top_block->logic_block->output_streams[0]->logic_data->data;
          break;
        }
        }

        break;
      }
      case DATA_BLOCK: {

        /* Create unique name for data node */
        char data_node_name[1024];

        snprintf(data_node_name, sizeof(data_node_name), "%s_%d",
                 logic_block->name, j);

        Agnode_t *invisible_input_node =
            agnode(g_graphviz_graph, data_node_name, 1);

        agsafeset(invisible_input_node, "style", "invis", "");
        agedge(g_graphviz_graph, invisible_input_node, logic_block->graph_node,
               NULL, 1);

        /* Get the top logic block */
        logic_block_type_t logic_block_type = logic_block->logic_block_type;

        switch (logic_block_type) {
        case AND: {
          logic_eval_result =
              logic_eval_result && logic_top_block->logic_data->data;
          break;
        }

        case OR: {
          logic_eval_result =
              logic_eval_result || logic_top_block->logic_data->data;
          break;
        }
        }
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
    printf("LOG: Current block (%d).\n", i);
    logic_eval_all(logic_output_block->logic_blocks[i], NULL);
  }

  for (int i = 0; i < logic_output_block->total_blocks; i++) {

    /* Create unique name for data node */
    char data_node_name[1024];

    snprintf(data_node_name, sizeof(data_node_name), "output_%s_%d",
             logic_output_block->logic_blocks[i]->name, i);

    Agnode_t *invisible_output_node =
        agnode(g_graphviz_graph, data_node_name, 1);

    agsafeset(invisible_output_node, "style", "invis", "");
    agedge(g_graphviz_graph, logic_output_block->logic_blocks[i]->graph_node,
           invisible_output_node, NULL, 1);
  }

  return 0;
}

int logic_console(logic_block_t *logic_block) {
  if (logic_block == NULL) {
    printf("LOG: No data found.\n");
    return -1;
  }

  int logic_inputs = logic_block->inputs;

  printf("----------\n"
         "| LOGSIM |\n"
         "----------\n\n");

  printf("LOG: LOGICAL BLOCK (%s).\n", logic_block->name);

#if 1
  for (int i = 0; i < logic_inputs; i++) {
    if (logic_block->input_streams[i]->logic_top_block_type == LOGIC_BLOCK) {
      printf("LOG: Input data found (%d).\n",
             logic_block->input_streams[i]
                 ->logic_block->output_streams[0]
                 ->logic_data->data);
    } else {
      printf("LOG: Input data found (%d).\n",
             logic_block->input_streams[i]->logic_data->data);
    }
  }
#endif

  printf("LOG: Output data found (%d).\n",
         logic_block->output_streams[0]->logic_data->data);

  return 0;
}

/************************************************/
/*                EOF                           */
/************************************************/
