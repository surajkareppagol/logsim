/**
 * @file logsim.h
 * @author Suraj Kareppagol (surajkareppagol.dev@gmail.com)
 * @brief LogSim provides a set of functions and macros to simulate logic gates.
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef LOG_SIM_H
#define LOG_SIM_H

/*************** Macros ***************/

/* 1. Define a stanard gate block */
/* 2. Provides a unique memory address for that block */
#define LOGIC_BLOCK()

/* 3. Create input blocks */
/* 4. Create output blocks */

/* Here both of these blocks will contain "data" field. */
#define LOGIC_INPUT()
#define LOGIC_OUTPUT()

/* 5. Connect input block to standard gate block. */

/* Gate can keep array of inputs and outputs */
#define LOGIC_INPUT_CONNECT()
#define LOGIC_OUTPUT_CONNECT()

/* 6. Read "data" and neatly print it to the console. */
#define LOGIC_CONSOLE()

#endif

/************************************************/
/*                EOF                           */
/************************************************/
