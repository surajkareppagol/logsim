# LogSim

`LogSim` is a minimal C library to build and simulate small circuits using logic gates as building blocks.

The library provides two types of building blocks `LOGIC` blocks and `DATA`
blocks.

The logic blocks are the one such as `AND` and `OR`, data blocks are `INPUT` and `OUTPUT`.

Apart from these additional APIs are provided to connect these different blocks together to build circuits.

Check the `examples` directory for some circuts built using this library. Below
is the usage guide, to generate graph calls should be made to
`logic_graph_init()` and `logic_graph_export()` APIs.

The whole process can be described in 4 steps.

- Create logic blocks.
- Create data blocks.
- Connect all the blocks, either logic-logic or logic-data.
- Create output block (set of logic blocks with output) and evaluate.

## Build

> Note: Make sure to install the graphviz library.

```sh
sudo apt install libgraphviz-dev
```

`Makefile` is provided, use the below command to build the examples.

```sh
make
```

The examples will be available in the `bin` directory.

```sh
make clean
```

```sh
make run
```

Run all the binaries from the `bin` directory at once.

## API Usage

- Include the header `logsimlib.h`.

  ```c
  #include "logsimlib.h"
  ```

- Create the logic blocks.

  ```c
  logic_block_t *lb_1 = logic_block(AND, 2, 1, "lb_1");
  ```

  ```c
  logic_block_t *lb_2 = logic_block(AND, 2, 1, "lb_2");
  ```

- Create the data blocks.

  ```c
  logic_data_t *lb_i_1_1 = logic_data(INPUT, 1);
  logic_data_t *lb_i_1_2 = logic_data(INPUT, 1);

  logic_data_t *lb_o_1_1 = logic_data(OUTPUT, 1);
  ```

  ```c
  logic_data_t *lb_i_2_1 = logic_data(INPUT, 1);
  logic_data_t *lb_i_2_2 = logic_data(INPUT, 1);

  logic_data_t *lb_o_2_1 = logic_data(OUTPUT, 1);
  ```

- Connect the blocks, either _Data-Block_ or _Block-Block_.

  ```c
  logic_block_data_connect(lb_1, lb_i_1_1);
  logic_block_data_connect(lb_1, lb_i_1_2);

  logic_block_data_connect(lb_1, lb_o_1_1);
  ```

  ```c
  logic_block_data_connect(lb_2, lb_i_2_1);
  logic_block_data_connect(lb_2, lb_i_2_2);

  logic_block_data_connect(lb_2, lb_o_2_1);
  ```

- Once connected add the output blocks to top blocks array.

  ```c
  logic_output_block_t *lob = logic_output_block(1);

  lob->logic_blocks[0] = lb_1;
  ```

- Use the evaluation function to evaluate all the gates.

  ```c
  logic_eval_all_output_blocks(lob);
  ```

> Note: Please make calls to `logic_graph_init("and");`,
> `logic_utility_init("and.log");` and `logic_graph_export("and.svg");` > `logic_utility_terminate();` as for graph and log generation checks are not
> added.
