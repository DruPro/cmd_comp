## Technical Documentation: Lexer Data Flow & State Transition Architecture

This document details the internal mechanics of the `CMDLEX` system, focusing on how data is passed between the context container and the logic engine.

### 1. Diagram



### 2. The Data Loop

The lexer operates on a **Request-Evaluate-Update** cycle. Here is how data moves through the classes:

1. **Buffer Initialization:** The `CMDLEX::scan` method receives a raw string. It populates the `LEXCTX` (Lexer Context), setting the pointer (`charIdx`) to zero and capturing the first character (`currChar`).
2. **Reference Passing:** The `FSM::exec` function now accepts `LEXCTX &ctx` by **reference**. This is a critical professional optimization:
* **Efficiency:** It avoids creating a new copy of the string buffer on every single character evaluation.
* **Persistence:** Changes made to the index or current character within the FSM are reflected immediately in the main scan loop.


3. **State Evaluation:** The FSM reads `ctx.currChar`, determines the next `states` value, and updates the `charIdx` via `ctx.stepIdx()`.

---

### 3. Component Specifications

#### **LEXCTX (Data Container)**

Acts as the "Source of Truth" for the current position in the input stream.

* **`buffer`**: The immutable raw input.
* **`currChar`**: The specific byte currently being scrutinized.
* **`charIdx`**: The cursor position.

#### **FSM (Transition Logic)**

A deterministic engine that maps inputs to states.

| Current State | Input Condition | Target State | Action |
| --- | --- | --- | --- |
| `START` | Char is `/` | `CMD_START` | `ctx.stepIdx()` |
| `CMD_START` | Char is `[a-z]` | `CMD_START` | Append to token |
| `CMD_START` | Char is `     ` (space) | `WHITESPACE` | Finalize command token |
| `WHITESPACE` | Char is `     ` (space) | `WHITESPACE` | `ctx.stepIdx()` (skip) |
| `ANY` | `charIdx == bufferSize` | `CMD_END` | Terminate loop |

---

### 4. Implementation Analysis

> [!NOTE]
> **Key Improvement:** By switching to `void FSM::exec(LEXCTX &ctx)`, you have moved from a "Snapshot" model to a "Shared Memory" model. This allows the FSM to directly manipulate the cursor, which is standard practice in high-performance parsing.

#### **Termination Logic**

The `while` loop in `CMDLEX::scan` acts as the safety gate:

```cpp
while (currentState != CMD_END && currentState != CMD_ERR) {
    this->fsm.exec(lexCtx); 
    currentState = this->fsm.getState(); 
}

```
