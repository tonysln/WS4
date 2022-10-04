# WS4

About...

Make sure to read the Documentation & Reference in `/doc` for a full overview and explanation of the system.

## Project Structure

```shell
/
├── *bin                          # Compiled binary files
├── config                        # System configuration files
├── data                          # Data files for graphics and weather info
├── doc                           # Documentation & reference
├── extlibs                       # External libraries
├── fonts                         # Font files
├── graphics                      # Graphical elements
│     ├── icons
│     └── maps
├── *music                        # Background music
├── *obj                          # Compiled object files
├── src                           # Source and header files
├── .gitignore
├── Makefile
└── README.md
```

*Folders marked with an asterisk (\*) are ignored by git*.

## Requirements

Supported platforms: Linux, macOS, ... Windows(?)

| Library Name  | Version    |
| ------------- |------------|
| G++           | \>= 11     |
| SFML          | \>= 2.6.0  |
| libcurl       | \>= 7.58.0 |



### Build & Run

```bash
$ make clean
$ make
$ ./bin/WS4
```

...

## Configuration

To be updated...

## Resources Used

* Star4000 Fonts by [TWC Classics](https://twcclassics.com/) contributor Nick Smith.
* Icons by [TWC Classics](https://twcclassics.com/) contributors Charles A. and Nick S.
* LaTeX documentation template by [LianTze Lim](https://www.overleaf.com/articles/autorating-calculator-user-guide/fdfgkxkpqczv).

## License

This software is distributed under the [zlib/libpng license](https://opensource.org/licenses/Zlib).