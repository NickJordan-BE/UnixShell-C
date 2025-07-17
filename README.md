# Shelldon

**Shelldon** is a Unix-style shell built entirely in C. It replicates essential functionality of traditional shells like `bash`, including command execution, piping, redirection, job control, and signal handling. The project was developed to gain a deep understanding of how operating systems and terminal interfaces work under the hood.

---

## 🚀 How to Run

### Prerequisites

- C compiler (e.g., `gcc` or `clang`)
- Unix-based OS (Linux/macOS)

### Build and Run

Using the provided Makefile:

```bash
make
./shelldon
Or compile manually:

bash
Copy
Edit
gcc -o shelldon main.c handler.c parser.c piping.c redirection.c external.c commands.c shell.c
./shelldon
```
✅ Implemented Features
Command Parsing – Tokenization, argument handling, command separation

External Command Execution – Executes system binaries like ls, cat, grep

Built-in Commands – Includes cd, exit, fg, bg, jobs

Multi-Stage Piping – Supports complex pipelines like ls | grep c | sort

Redirection – Input/output redirection using <, >, and >>

Job Control – Handles background execution (&), jobs, fg, bg

Signal Handling – Supports Ctrl+C (SIGINT), Ctrl+Z (SIGTSTP), SIGCHLD for job tracking

💡 What I Learned
This project gave me a practical, in-depth understanding of:

Process creation and management using fork, execvp, and waitpid

Inter-process communication with pipe and dup2

Managing Unix signals and implementing foreground/background job control

Writing modular, maintainable C code across multiple source files

How a real shell parses and executes commands while maintaining interactivity

📂 Project Structure
main.c – Shell initialization and REPL loop

handler.c – Dispatches built-in and external commands

parser.c – Parses user input into executable tokens

piping.c – Sets up and handles multi-stage pipes

redirection.c – Implements input/output redirection logic

external.c – Forks and runs external programs

commands.c – Built-in command implementations

shell.c – Core shell control logic and signal setup

Shelldon was built from the ground up as a systems programming exercise. It's a lightweight, interactive, and modular shell implementation that mirrors many of the control mechanisms found in production Unix shells.

🧑‍💻 Author
Nicholas Jordan
Computer Science @ University of Washington Tacoma
GitHub: NickJordan-BE

