/**
 * @file utils.h
 * @author Suraj Kareppagol (surajkareppagol.dev@gmail.com)
 * @brief Utility macros and functions.
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef LOG_SIM_UTILS_H
#define LOG_SIM_UTILS_H

/*************** C Custom Headers ***************/

#include "logsimtypes.h"

/*************** Macros ***************/

#define LOG_SIM_DEBUG 1
#define LOG_SIM_PRINT 1
#define LOG_SIM_FILE 1

/**************************************/

#if LOG_SIM_DEBUG

/* Either print to stderr or debug file */
#define LOG_SIM_DEBUG_PRINT(stream, fmt, ...)                                  \
  fprintf(stream, "LOG: " fmt "\n", ##__VA_ARGS__)

#else

#define LOG_SIM_DEBUG_PRINT(fmt, ...)

#endif

/**************************************/

#if LOG_SIM_PRINT

#define LOG_SIM_LOG_PRINT(fmt, ...) fprintf(stdout, fmt "\n", ##__VA_ARGS__)

#else

#define LOG_SIM_LOG_PRINT(fmt, ...)

#endif

/**************************************/

#if LOG_SIM_FILE

#define LOG_SIM_FILE_PRINT(log, fmt, ...) fprintf(log, fmt "\n", ##__VA_ARGS__)

#else

#define LOG_SIM_FILE_PRINT(fmt, ...)

#endif

/*************** Function Prototypes ***************/

/**
 * @brief Create graph node.
 *
 * @param label
 * @param type
 * @return Agnode_t*
 */
Agnode_t *util_create_edge(char *label, logic_block_type_t type);

/**
 * @brief Attach invisible node.
 *
 * @param label
 * @param block_index
 * @param node
 * @return int
 */
int util_attach_invisible_edge(char *label, int block_index, Agnode_t *node);

#endif

/************************************************/
/*                EOF                           */
/************************************************/
