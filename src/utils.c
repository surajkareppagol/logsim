/**
 * @file logsimlib.c
 * @author Suraj Kareppagol (surajkareppagol.dev@gmail.com)
 * @brief LogSim provides a set of functions and macros to simulate logic gates.
 *
 * @copyright Copyright (c) 2025
 *
 */

/*************** C Custom Headers ***************/

#include "../include/utils.h"
#include "../include/logsimtypes.h"

/*************** Function Definitions ***************/

Agnode_t *util_create_edge(char *label, logic_block_type_t type) {
  Agnode_t *node = agnode(g_graphviz_graph, label, TRUE);

  switch (type) {
  case AND: {
    agset(node, "label", "AND");
    break;
  }
  case OR: {
    node = agnode(g_graphviz_graph, label, TRUE);
    agset(node, "label", "OR");
    break;
  }
  case XOR: {
    node = agnode(g_graphviz_graph, label, TRUE);
    agset(node, "label", "XOR");
    break;
  }
  case NOT: {
    node = agnode(g_graphviz_graph, label, TRUE);
    agset(node, "label", "NOT");
    break;
  }
  }

  agset(node, "shape", "rectangle");

  return node;
}

int util_attach_invisible_edge(char *label, int block_index, Agnode_t *node) {
  char data_node_name[1024];

  snprintf(data_node_name, sizeof(data_node_name), "%s_%d", label, block_index);

  Agnode_t *invisible_input_node = agnode(g_graphviz_graph, data_node_name, 1);

  agsafeset(invisible_input_node, "style", "invis", "");
  agedge(g_graphviz_graph, invisible_input_node, node, NULL, 1);

  return 0;
}

/************************************************/
/*                EOF                           */
/************************************************/
