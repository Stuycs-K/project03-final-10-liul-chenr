#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

struct song_node {
    char name[100];
    struct song_node *next;};