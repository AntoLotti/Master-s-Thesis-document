<img src="https://r2cdn.perplexity.ai/pplx-full-logo-primary-dark%402x.png" style="height:64px;margin-right:32px"/>

## STM32F4 I2C Controller Finite State Machine (FSM) Transitions

The STM32F4 I2C controller implements a **table-driven FSM** (`stm32f4xx_i2c_fsm_transition_table`) that manages protocol state based on register access patterns and flag settings. The FSM transitions are triggered by writes to CR1 (START/STOP generation) and DR (slave address/data transmission), with conditions evaluating the current state, register being accessed, and control flags. Below is a complete transition table:


| **Current State** | **Transition Condition** | **Next State** | **Output Action** |
| :-- | :-- | :-- | :-- |
| `DISABLED` | `CR1[PE] = 1` (Peripheral Enable) | `IDLE` | Initialize FSM |
| `IDLE` | `CR1[START] = 1` | `START` | Set MSL/BUSY, set SB flag |
| `START` | `DR write` (R/W=0) | `S_WRITE` | `i2c_start_transfer()`, set ADDR/TXE/BTF |
| `S_WRITE` | `DR write` | `TRANSMITTING` | `i2c_send()`, set TXE/BTF |
| `TRANSMITTING` | `DR write` | `TRANSMITTING` | `i2c_send()`, set TXE/BTF |
| `TRANSMITTING` | `CR1[START] = 1` | `START` | Repeated START condition |
| `TRANSMITTING` | `CR1[STOP] = 1` | `IDLE` | `i2c_end_transfer()`, clear flags |
| `START` | `DR write` (R/W=1) | `S_READ` | `i2c_start_transfer()`, set ADDR/RXNE/BTF |
| `S_READ` | `DR read` + `CR1[STOP]=1` + `ACK=0` + `POS=0` | `RECV_1BYTE` | `i2c_recv()`, set RXNE/BTF |
| `S_READ` | `DR read` + `CR1[STOP]=1` + `ACK=0` + `POS=1` | `RECV_2BYTES_FIRST` | `i2c_recv()`, set RXNE/BTF |
| `S_READ` | `DR read` + `ACK=0` + `POS=0` | `RECV_3BYTES` | `i2c_recv()`, set RXNE/BTF |
| `S_READ` | `DR read` + `ACK=1` | `RECV_NBYTES` | `i2c_recv()`, set RXNE/BTF |
| `RECV_2BYTES_FIRST` | `DR read` + `STOP=1` | `RECV_2BYTES_SECOND` | `i2c_recv()` (last byte), generate NACK |
| `RECV_3BYTES` | `DR read` + `STOP=1` | `RECV_2BYTES_FIRST` | Transition to 2-byte receive mode |
| `RECV_NBYTES` | `DR read` + `ACK=1` | `RECV_NBYTES` | `i2c_recv()`, continue NACK sequence |
| `RECV_NBYTES` | `DR read` + `ACK=0` | `RECV_3BYTES` | Prepare for 3-byte special case |
| `RECV_NBYTES` | `DR read` + `STOP=1` + `ACK=0` | `RECV_2BYTES_FIRST` | Final byte handling |
| `RECV_1BYTE` | `STOP=1` | `IDLE` | `i2c_end_transfer()` |
| `RECV_2BYTES_SECOND` | `STOP=1` | `IDLE` | `i2c_end_transfer()` |

### Key FSM Design Features

**1. Table-Driven Architecture**
The FSM uses a static transition table (`stm32f4xx_i2c_fsm_transition_table`) with entries `{origin_state, condition_function, destination_state, output_function}`. The `fsm_fire()` function iterates through the table, evaluating conditions until a match is found.

**2. Condition Evaluation**
Conditions test:

- **Register accessed** (`config.addr == CR1_DR`)
- **Control flags** (`flg_start`, `flg_stop`, `ACK`, `POS`)
- **Data content** (`DR[^0] = R/W bit`)
- **Current status flags** (`SR1[ADDR]`)

**3. Self-Clearing Bits**
START/STOP bits in CR1 are **self-clearing**: firmware writes them, FSM consumes them, and clears them in the output action.

**4. Special Receive Cases**

- **1-byte read:** NACK immediately after address
- **2-byte read:** NACK on second byte (POS=1 selects second-byte handling)
- **3-byte read:** Special logic for exact 3 bytes (POS=0, ACK=0)
- **N-byte read:** Continuous ACK→NACK sequence

This FSM implementation faithfully reproduces the STM32F4 Reference Manual's state diagram (RM0090 Section 27.5.5), ensuring HAL drivers (`HAL_I2C_Mem_Read/Write`) execute correctly in the emulated environment.
<span style="display:none">[^1][^10][^11][^12][^13][^14][^15][^16][^17][^18][^19][^2][^20][^3][^4][^5][^6][^7][^8][^9]</span>

<div align="center">⁂</div>

[^1]: qom_final_text.md

[^2]: qom_final_text.md

[^3]: qdev_final_text.md

[^4]: 1_code_trans_final_test.md

[^5]: 1_qemu_back_final_text.md

[^6]: 1_qemu_back_final_text.md

[^7]: 1_code_trans_final_test.md

[^8]: qom_final_text.md

[^9]: qdev_final_text.md

[^10]: qemu_sub_final_text.md

[^11]: lis3dh.c

[^12]: lis3dh.h

[^13]: lis3dh_types.h

[^14]: lis3dh_types.h

[^15]: stm32f4xx_it.h

[^16]: main.h

[^17]: lis3dh_driver.h

[^18]: stm32f4xx_hal_conf.h

[^19]: stm32f4xx_it.c

[^20]: main.c

