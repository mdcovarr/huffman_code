# Huffman Coding Project
The Huffman Coding Project will help you with data compression and decompression. Even though disk space is alot cheaper now than ever before in history, there are still importance in efficiently and effectively compress information. It is possible to make a file significantly smaller without any loss of information whatsoever, leading to lossless compression. The Huffman coding was a technique introduced by David Huffman 1952. Huffman coding compression is still used today as part of JPEG image compression, mp3 audio compression, Unix file compression command pack, and other applications. 

## Getting Started
These instructions will guide you on how to grab the repo, and use the huffman coding project to start compression and decompression files. 

### Grab the Repo

First we need to clone this repo
1. Open Terminal 
2. cd into the directory where you want to copy the repo 
3. clone the repository
```
git clone https://github.com/mdcovarr/huffman_code.git
```

### Makefile

Included with the repo, is a Makefile
1. we need to make the porject with the following command
```
make
```

This will produce the executable files 'compress' and 'uncompress' which will be used in order to compress data or decompress compressed data.

### Compressing

the 'compress' executable can be run with two arguments. The first argument is the name of the input file you would like to compress. The second argument is the name of the output file where you want the compress data to be placed. The following line below is an example:

```
./compress input-file.txt output-file.txt
```

### Decompressing

The 'uncompress' executable can be run with two arguments. The first argument is the name of the input file. The input file would be a previously compressed file. The second argument is the name of the output file where you want to output the decompressed data. The following line below is an example: 

```
./uncompress input-file.txt output-file.txt
```
