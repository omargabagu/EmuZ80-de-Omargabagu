## 📖 Introduction
EmuZ80 de omargabagu is a simple **Zilog Z80 emulator** written in C. It simulates the execution of Z80 machine code, allowing you to load and run programs in **.hex format**. The emulator provides a basic interface to inspect **registers, memory, and execution flow**.

## ⚡ Features
- **Load programs in .hex format** and execute them in a simulated memory environment.
- **Emulate Z80 instructions** step by step, with full control over execution.
- **Display registers and memory states** in real-time.
- **Edit memory manually** for debugging and testing purposes.
- **Support for HALT instruction** to stop execution.
- **Basic user interface** for navigation and program control.

## 🛠️ Installation
To compile the emulator, use `gcc` or any compatible C compiler:

```sh
gcc z80_emulator.c -o z80_emulator
```

Run the emulator:

```sh
./z80_emulator
```

## 📌 Usage
The emulator allows you to load programs, execute instructions step by step, and inspect the memory and registers during execution. You can also manually edit memory and navigate through loaded data.

### 🏁 Main Menu
When you run the program, you will see the following options:

1️⃣ **Load Program**
   - Enter the name of the `.hex` file to load.
   - Specify the memory address where the program will be loaded.

2️⃣ **Run Program**
   - Starts executing the loaded program in memory.
   - Displays the status of registers and memory.
   - Allows step-by-step execution or manual stopping.
   - Execution stops when a `HALT` instruction is encountered or an error occurs.

3️⃣ **Edit Memory**
   - View and modify memory values manually.
   - Controls:
     - `a`: Move cursor left  
     - `d`: Move cursor right  
     - `w`: Move cursor to a specific address  
     - `s`: Edit the value at the current address  
     - `x`: Exit memory editing

4️⃣ **Show Credits**
   - Displays information about the contributors and developers of the emulator.

5️⃣ **Exit**
   - Closes the emulator.

### 🖥️ Execution Interface
During program execution, the interface displays:

- **Processor Registers** (A, B, C, D, E, H, L, I, R, SP, PC, IX, IY, F).
- **Z80 Flags** (Z, S, H, N, P/V, NC).
- **Last executed instruction**.
- **Memory in hexadecimal format**, highlighting the value at `PC`.

📌 **Execution Controls:**
- `Enter`: Execute the next cycle.
- `x`: Exit execution and return to the menu.

## 🏗️ Future Improvements
- Implement more Z80 instructions.
- Add support for interrupts.

## 📜
User manual: https://docs.google.com/document/d/14_mNV07MLMQKWAN7Nvndz8rO4_aEsMrJc-zqRen7XVg/edit
Maual de zilog: https://www.zilog.com/docs/z80/um0080.pdf
