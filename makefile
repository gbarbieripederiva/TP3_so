all:client

client:client.c
	gcc client.c -o client

.PHONY: all