# SIMPLE-C-SHELL

A simple shell implementation written in C, built as a learning project.

## Features

- Executes basic commands with arguments
- Supports piping between multiple commands (e.g. `cmd1 | cmd2 | cmd3`)

## Build

```bash
git clone https://github.com/ygt-ernsy/simple-c-shell.git
cd simple-c-shell
make
```

## Usage

```bash
./main
```

Type commands at the prompt just like in a regular shell:

```bash
ls -l | grep main
```

To clean up build artifacts:

```bash
make clean
```

## License

MIT — see [LICENSE](LICENSE).
