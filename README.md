# Minimalist Web server in C

This is a minimalist web server written in C. It supports HTTP/1.1 GET requests and serves files from the current directory.

## Usage

Compile the server with the following command

```bash

gcc -o server server.c

```

Run the server with the following command

```bash

./server

```

The server will listen on port 8080.

## Testing

You can test the server in terminal with the following command

```bash

wget localhost:8080/README.md

cat README.md

```

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
